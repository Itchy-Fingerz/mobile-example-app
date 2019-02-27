#!/bin/sh

echo
echo "Running: $0 $@"
echo "Compile xcode project step..."
echo

readonly targetName=$1
readonly productName=$2
readonly productVersion=$3
readonly pathToProjectDir=$4
readonly relativeOutputDir=${5:-Release-iphoneos}


abort()
{
  echo "FAILED: $1 LINE $2" >&2
  exit 1
}

trap 'abort $0 $LINENO' 0

set -e


usage_example="usage format: compile_xcode.step.sh targetName productName productVersion pathToProjectDir"
usage_example+="\nusage example: compile_xcode.step.sh Eegeo_Streaming StreamAlpha 0.0.4.1 eegeo-stream-app-ios" 

if [ -z "$targetName" ]; then
        echo
        echo "Error: targetName must be provided (this is the xcode target)"
        echo $usage_example
        exit 1
fi

if [ -z "$productName" ]; then
        echo
        echo "Error: productName must be provided"
        echo $usage_example
        exit 1
fi

if [ -z "$productVersion" ]; then
        echo
        echo "Error: productVersion must be provided"
        echo $usage_example
        exit 1
fi

if [ -z "$pathToProjectDir" ]; then
        echo
        echo "Error: pathToProjectDir must be provided"
        echo $usage_example
        exit 1
fi


mkdir -p $pathToProjectDir

pushd $pathToProjectDir

    # generate xcode project
    cmake_args="-G Xcode .."

    echo "Calling: cmake $cmake_args"
    cmake $cmake_args

    readonly xcodebuild_args="\
-target $targetName \
-configuration Release \
ONLY_ACTIVE_ARCH='NO' \
PRODUCT_VERSION=$productVersion \
-allowProvisioningUpdates"

    echo "calling xcodebuild $xcodebuild_args"

    xcodebuild $xcodebuild_args | tee xcodebuild.log | xcpretty && xcodebuild_result=${PIPESTATUS[0]}
    if [ $xcodebuild_result -ne 0 ] ; then
        echo "xcodebuild failed with result $xcodebuild_result" >&2
        echo "Displaying last 100 lines of xcodebuild log $(pwd)/xcodebuild.log" >&2
        tail -n 100 xcodebuild.log >&2
        exit 1
    fi

    # validate that Info.plist contains expected properties
    appBundleInfoPlist=$relativeOutputDir/$productName.app/Info.plist
    stat $appBundleInfoPlist >/dev/null
    testCFBundleShortVersionString=$(/usr/libexec/PlistBuddy -c "Print :CFBundleShortVersionString" $appBundleInfoPlist)
    if [ $testCFBundleShortVersionString != $productVersion ] ; then
        echo "Incorrect CFBundleShortVersionString, expected '$productVersion', found '$testCFBundleShortVersionString'" >&2
        exit 1
    fi

    testCFBundleName=$(/usr/libexec/PlistBuddy -c "Print :CFBundleName" $appBundleInfoPlist)
    if [ $testCFBundleName != $productName ] ; then
        echo "Incorrect CFBundleName, expected '$productName', found '$testCFBundleName'" >&2
        exit 1
    fi

popd

trap : 0

echo "\n$0 SUCCEEDED\n" >&2


exit 0
