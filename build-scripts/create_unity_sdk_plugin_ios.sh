#!/bin/sh

echo "Running: $0 $@"

script_name=${0##*/}

CLEAN_ALL=false
product_version=""

usage()
{
    echo "$0 - Build WRLD Unity SDK plugin for iOS"
    echo
    echo "Usage:"
    echo "  ./$script_name --version [--clean | c]"
    echo "  ./$script_name [--help | -h]"
    echo ""
    echo "Options:"
    echo "  --clean: clean all intermediate directories before build."
    echo "  --help: display this message."
}

while test -n "$1"
do
    case $1 in
        --help|-h)
            usage
            ;;
        --clean|-c)
            CLEAN_ALL=true
            ;;
        --version=*)
            product_version="${1#--version=}"
            ;;
        *)
            echo "ERROR: unknown option $1"
            usage
            exit 1
            ;;
    esac
    shift
done


abort()
{
    echo "FAILED: $1 LINE $2" >&2
    exit 1
}

trap 'abort $0 $LINENO' 0

set -e

echo "setting VERSION to ${VERSION}"

readonly targetName="StreamAlpha"
readonly buildDirectory=eegeo-stream-app-ios/build-unity
readonly relativeOutputDir=../../eegeo-unity/public/project/Assets/Wrld/Plugins/iOS/
readonly cmake_args="-DUNITY=1 -G Xcode .."


readonly streamingAssetsDir=eegeo-unity/public/project/Assets/StreamingAssets


if [ "$CLEAN_ALL" = true ] ; then
    echo "Performing clean - deleting $buildDirectory"
    rm -rf ${buildDirectory}
fi

echo "Cleaning ${streamingAssetsDir} (assets are copied to this directory during xcode build)"
rm -rf $streamingAssetsDir

mkdir -p ${buildDirectory}

pushd $buildDirectory

    # generate xcode project

    echo "Calling: cmake $cmake_args"
    cmake $cmake_args

    readonly xcodebuild_args="\
-target $targetName \
-configuration Release \
ONLY_ACTIVE_ARCH='NO' \
PRODUCT_VERSION=$product_version \
-allowProvisioningUpdates"

    echo "calling xcodebuild $xcodebuild_args"

    xcodebuild $xcodebuild_args | tee xcodebuild.log | xcpretty && xcodebuild_result=${PIPESTATUS[0]}
    if [ $xcodebuild_result -ne 0 ] ; then
        echo "xcodebuild failed with result $xcodebuild_result" >&2
        echo "Displaying last 100 lines of xcodebuild log $(pwd)/xcodebuild.log" >&2
        tail -n 100 xcodebuild.log >&2
        exit 1
    fi
popd


echo "Copying resources to ${streamingAssetsDir}/WrldResources/"
python build-scripts/unity/selective_assets_removal.py --input build-scripts/unity/input.json --ios ${streamingAssetsDir}/WrldResources/

trap : 0


echo "$0 SUCCEED"

exit 0