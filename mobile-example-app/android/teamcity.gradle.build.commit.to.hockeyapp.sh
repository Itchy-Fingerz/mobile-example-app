#!/bin/sh

script_name=${0##*/}
script_dir=$(dirname "$0")
current_dir=$(pwd)

trap_failure() {
   echo "Error: $script_name: $1" >&2
   exit 1
}
trap 'trap_failure $LINENO' ERR

set -e

if [[ "$#" -lt 3 || "$#" -gt 5 ]]; then
    echo -e "Invalid argument(s).\nUsage:\n${script_name} versionName buildUrl githubUrl [app_store_application_id] [external_signing]" >&2
    echo "e.g. ${script_name} 0.0.123 http://teamcity/buildurl http://github.com/etc com.eegeo.recce ../eegeo-mobile/build-scripts/mobile-example-app/android/signing" >&2
    exit 1
fi

echo $@

versionName=$1
buildUrl=$2
githubUrl=$3
# if 0 will not create additional apk
appStoreApplicationId=${4:-0}
# default param assumes eegeo-mobile and wrld-example-app repos in sibling checkout dirs
externalSigning=${5:-../../eegeo-mobile/build-scripts/mobile-example-app/android/signing}


echo "versionName is ${versionName}"
echo "buildUrl is ${buildUrl}"
echo "githubUrl is ${githubUrl}"
echo "appStoreApplicationId is ${appStoreApplicationId}"
echo "externalSigning is ${externalSigning}"

# this is maintaining the behaviour from non-gradle teamcity.build.commit.to.hockeyapp.sh
readonly versionCode=$(date +%s)
readonly appDir=./android
readonly hockeyAppIdentifier=efaf66c60bd97e9e33840f7abdf12095
readonly pathToApkBase=$current_dir/$appDir/build/outputs/apk/normal/release
readonly pathToApk=$pathToApkBase/android-normal-release.apk
readonly nonAppStoreApplicationId=com.eegeo.mobileexampleapp
readonly pathToNonAppStoreApk=$pathToApkBase/$nonAppStoreApplicationId.apk

echo "versionCode is $versionCode"
echo "appDir is ${appDir}"
echo "hockeyAppIdentifier is ${hockeyAppIdentifier}"
echo "pathToApk is ${pathToApk}"
echo "nonAppStoreApplicationId is ${nonAppStoreApplicationId}"


echo "Performing gradle build..."

pushd $appDir
    ./build.sh --release --version-code ${versionCode} --version-name ${versionName} --application-id ${nonAppStoreApplicationId} --external-signing ${externalSigning}

    if [ $? -ne 0 ] ; then
        exitCode=$?
        echo "Error performing gradle build" >&2
        exit $exitCode
    fi

    rm -f $pathToNonAppStoreApk
    mv $pathToApk $pathToNonAppStoreApk

    echo "app store apk is: ${pathToNonAppStoreApk}"

popd


if [ ! -z "$appStoreApplicationId" ]; then

    echo "Performing gradle build for app store app $appStoreApplicationId ..."

    pushd $appDir
        ./build.sh --release --version-code ${versionCode} --version-name ${versionName} --application-id ${appStoreApplicationId} --external-signing ${externalSigning}

        if [ $? -ne 0 ] ; then
            exitCode=$?
            echo "Error performing gradle build" >&2
            exit $exitCode
        fi

        readonly pathToAppStoreApk=$current_dir/$appDir/build/outputs/apk/normal/release/${appStoreApplicationId}.apk
        rm -f $pathToAppStoreApk
        mv $pathToApk $pathToAppStoreApk

        echo "app store apk is: ${pathToAppStoreApk}"
    popd

fi

echo "Performing commit_to_hockeyapp..."

pushd .
    sh "$script_dir/../../android/commit_to_hockeyapp.step.sh" $pathToNonAppStoreApk $buildUrl $githubUrl $hockeyAppIdentifier
    if [ $? -ne 0 ] ; then
        exitCode=$?
        echo "Error performing commit_to_hockeyapp" >&2
        exit $exitCode
    fi
popd


#===

trap : 0

echo
echo "BUILD AND DEPLOY SUCCEEDED" >&2
echo

