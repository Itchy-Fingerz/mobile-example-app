#!/bin/bash 


readonly script_name=${0##*/}

echo
echo "Running: $0 $@"
echo

appname=$1
pathToProjectDir=$2
archivePath=$3
ipaName=$4
provisioningProfile=$5
generateDistSignedIpa=$6
productVersion=$7
distributedBundleId=$8

echo $@ >&2

# https://developer.apple.com/account/ios/certificate/?teamId=QBCVJ28BRW
readonly appStoreDistributionCert="iPhone Distribution: eeGeo Limited (77LF7Y24G3)"
readonly appStoreDistributionTeamId="77LF7Y24G3"


function trap_failure {
    echo "FAILED: $1 LINE $2"
    exit 1
}

trap 'trap_failure $0 $LINENO' ERR

CWD="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "CWD is ${CWD}"

XcodeAppDir=`xcode-select --print-path`
if [ ! -d "${XcodeAppDir}" ]; then
	echo "No xcode directory found!"
	exit 1
fi

if [ -z "$appname" ]; then
        echo
        echo "Error: appname must be provided"
        echo
        exit 1
fi

if [ -z "$pathToProjectDir" ]; then
        echo
        echo "Error: pathToProjectDir must be provided"
        echo
        exit 1
fi

if [ -z "$archivePath" ]; then
        echo
        echo "Error: archivePath must be provided (eg. ./Appname.xcarchive)"
        echo
        exit 1
fi

if [ -z "$ipaName" ]; then
    echo
    echo "Error: ipaName must be provided (eg. Appname)"
    echo
exit 1
fi

if [ -z "$provisioningProfile" ]; then
    echo
    echo "Error: provisioningProfile must be provided and should match installed enterprise distribution provisioning Profile"
    echo
    exit 1
fi



echo 
echo "Exporting "${pathToProjectDir}/${ipaName}.ipa" from ${pathToProjectDir}/${archivePath}"
echo 

pushd $pathToProjectDir 

    # Delete old ipa if exists
    rm -rf "$ipaName.ipa"
    rm -rf ./EnterpriseDistribution


    # export ipa for Enterprise Deployment (for Enterprise distribution outside the App Store), will have bundleId com.eegeo.ExampleApp
    xcodebuild -exportArchive -archivePath "$archivePath" -exportPath ./EnterpriseDistribution -exportOptionsPlist $CWD/../../mobile-example-app/ios/ExportOptions/ExportOptions.plist -allowProvisioningUpdates

    mv ./EnterpriseDistribution/${ipaName}.ipa ./${ipaName}.ipa
popd


if [ ! -z "$generateDistSignedIpa" ]; then

    #todo - rather than build another archive for com.eegeo.Recce, make use of previous created archive, poke bundle id, and export with appropriate app-store distribution credentials 

    echo 
    echo "Exporting ${ipaName}Signed.ipa for $distributedBundleId ..."
    echo 

    pushd "$pathToProjectDir"

    rm -rf "${ipaName}Signed.ipa"
    rm -rf ./AppStoreDistribution

    appStoreArchive="${ipaName}Signed.xcarchive"
    rm -rf ${appStoreArchive}
    echo " Copying $archivePath to ${appStoreArchive}."
    cp -R -f $archivePath ${appStoreArchive}

    echo " Injecting CFBundleIdentifier '$distributedBundleId', CFBundleVersion / CFBundleShortVersionString '$productVersion'."

    # poke app bundle Info.plist
    app_store_app_bundle_plist=$(pwd)/${appStoreArchive}/Products/Applications/ExampleApp.app/Info.plist
    #plutil -convert xml1 ${app_store_app_bundle_plist}
    plutil -replace CFBundleIdentifier -string "$distributedBundleId" "$app_store_app_bundle_plist"
    plutil -replace CFBundleVersion -string "$productVersion" "$app_store_app_bundle_plist"
    plutil -replace CFBundleShortVersionString -string "$productVersion" "$app_store_app_bundle_plist"

    # poke root xcarchive Info.plist
    app_store_archive_plist=$(pwd)/${appStoreArchive}/Info.plist
    plutil -replace ApplicationProperties.CFBundleIdentifier -string "$distributedBundleId" "$app_store_archive_plist"
    plutil -replace ApplicationProperties.CFBundleVersion -string "$productVersion" "$app_store_archive_plist"
    plutil -replace ApplicationProperties.CFBundleShortVersionString -string "$productVersion" "$app_store_archive_plist"
    plutil -replace ApplicationProperties.Team -string "$appStoreDistributionTeamId" "$app_store_archive_plist"
    plutil -replace ApplicationProperties.SigningIdentity -string "$appStoreDistributionCert" "$app_store_archive_plist"

    codesign \
      --force --verbose=4 --sign "${appStoreDistributionCert}" \
      -i "$distributedBundleId" \
      --entitlements "$CWD/../entitlements/$distributedBundleId-release.plist" \
      "${appStoreArchive}/Products/Applications/ExampleApp.app"


    # export ipa for app store distribution
    xcodebuild -exportArchive -archivePath "$appStoreArchive" -exportPath ./AppStoreDistribution -exportOptionsPlist $CWD/../../mobile-example-app/ios/ExportOptions/RecceAppStoreExportOptions.plist 

    mv ./AppStoreDistribution/${ipaName}.ipa ./${ipaName}Signed.ipa

    #todo - delete this commented block, only retaining temporarily for reference until after next app-store submission
: '

    rm -rf Payload/
    unzip -q "$ipaName.ipa"


    echo " Stripping unwanted simulator architectures... "
    for framework in $(ls Payload/$ipaName.app/Frameworks/ | grep framework); do
        echo " Stripping $framework... "
        frameworkFatBinary=${framework::${#framework}-10}
        frameworkFatBinaryRelPath="Payload/$ipaName.app/Frameworks/$framework/$frameworkFatBinary"

        if lipo $frameworkFatBinaryRelPath -verify_arch i386 ; then
            lipo -remove i386 $frameworkFatBinaryRelPath -o $frameworkFatBinaryRelPath
        fi 

        if lipo $frameworkFatBinaryRelPath -verify_arch x86_64 ; then
            lipo -remove x86_64 $frameworkFatBinaryRelPath -o $frameworkFatBinaryRelPath
        fi
    done

    echo " Injecting new bundle id '$distributedBundleId' with version string '$productVersion'."

    cp -f "$CWD/../mobileprovisions/$distributedBundleId-release.mobileprovision" "Payload/$ipaName.app/embedded.mobileprovision"
	defaults write "$(pwd)/Payload/$ipaName.app/Info.plist" CFBundleIdentifier "$distributedBundleId"
    defaults write "$(pwd)/Payload/$ipaName.app/Info.plist" CFBundleVersion "$productVersion"
    defaults write "$(pwd)/Payload/$ipaName.app/Info.plist" CFBundleShortVersionString "$productVersion"

    # presumably to avoid "Missing SwiftSupport email knock-back when submitting to app store?"
    echo "Adding SwiftSupport..."
    if [ -d "Payload/$ipaName.app/Frameworks" ]; then
        mkdir -p SwiftSupport/iphoneos

        for SWIFT_LIB in $(ls -1 Payload/$ipaName.app/Frameworks/libswift*); do
            echo "Copying ${SWIFT_LIB}"
            cp "${XcodeAppDir}/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/iphoneos/$(basename ${SWIFT_LIB})" ./SwiftSupport/iphoneos
        done
    fi

    # resign frameworks
    codesign --force --verbose=4 --sign "${appStoreDistributionCert}"  Payload/$ipaName.app/Frameworks/*

    # resign app bundle
    codesign \
      --force --verbose=4 --sign "${appStoreDistributionCert}" \
      -i "$distributedBundleId" \
      --entitlements "$CWD/../entitlements/$distributedBundleId-release.plist" \
      "Payload/$ipaName.app"


    zip -q -r "${ipaName}Signed.ipa" Payload SwiftSupport
'
    popd
fi


trap : 0

echo "SUCCEEDED: $0"

exit 0
