#!/bin/sh
readonly script_name=${0##*/}

trap_failure() {
   echo "Error: $script_name: $1" >&2
   exit 1
}
trap 'trap_failure $LINENO' ERR

set -eu

if [ "$#" -ne 5 ]; then
  echo -e "Invalid argument(s).\nUsage:\n${script_name} aws_access_key_id aws_secret_access_key sdk_version_number sdk_version_commit_hash sdk_package_name_prefix" >&2
  echo "e.g. ${script_name} AKIAXXXXXXXXXXXXXXXX AWS_SECRET 103 a7231ab051069fa6be5a57c848e9d6a50d39bcaa sdk.package.android.cpp11" >&2
  echo "results in deploying the following files in the root of s3://eegeo-static/, and also to versioned store eg 's3://eegeo-static/wrldsdk/v1234/':" >&2
  echo -e "sdk.package.android.cpp11.c++_static.tar.gz\t\t - built with clang libc++ static C++ runtime." >&2
  echo -e "sdk.package.android.cpp11.tar.gz\t\t - default package, built with gnustl static C++ runtime. This is deprecated, due to switch to c++_static late 2018." >&2
  exit 1
fi

readonly aws_access_key_id="$1"
readonly aws_secret_access_key="$2"

readonly platform_sdk_version_number=$3
readonly platform_sdk_version_commit_hash=$4

readonly sdk_package_name_prefix=$5
readonly sdk_package_ext="tar.gz"
readonly sdkPackageDirPrefix="sdk.package.android"
readonly cpp_runtimes="c++_static gnustl_static"
readonly default_cpp_runtime="gnustl_static"

#undo changes if a build was interrupted before by doing a checkout . on poked file
git checkout ./platform/EegeoWorld.h

#poke file
readonly placeholder_version_number=EEGEO_PLATFORM_VERSION_NUMBER_TARGET
readonly placeholder_version_commit_hash=EEGEO_PLATFORM_VERSION_COMMIT_HASH_TARGET
sed -i.bak -e s@$placeholder_version_number@$platform_sdk_version_number@g -e s@$placeholder_version_commit_hash@$platform_sdk_version_commit_hash@g ./platform/EegeoWorld.h

#build platform against poked version symbols
sh build-scripts/android/create.sdk.package.android.sh ${platform_sdk_version_number} ${platform_sdk_version_commit_hash}

#cleanup
mv ./platform/EegeoWorld.h.bak ./platform/EegeoWorld.h

function upload_to_s3 {
    local input_path="$1"
    local destination_path="$2"

    AWS_ACCESS_KEY_ID="$aws_access_key_id" AWS_SECRET_ACCESS_KEY="$aws_secret_access_key" aws s3 cp \
        --region us-east-1 \
        --acl public-read \
        --cache-control 'public,no-cache' \
        "$input_path" \
        "$destination_path"

    # other candidates:
    # --content-type "$content_type"
    # --content-encoding gzip
}

for cpp_runtime in ${cpp_runtimes}
do
    srcSdkPackageDir="${sdkPackageDirPrefix}.${cpp_runtime}"
    
    if [ "$cpp_runtime" = "$default_cpp_runtime" ] ; then
        destSdkPackage="${sdk_package_name_prefix}.${sdk_package_ext}"
    else
        destSdkPackage="${sdk_package_name_prefix}.${cpp_runtime}.${sdk_package_ext}"
    fi

    echo "Creating ${destSdkPackage} from ${srcSdkPackageDir}" >&2

    version_file=./$srcSdkPackageDir/version.txt

    #dump version file into sdk root
    echo "sdk_version_number: ${platform_sdk_version_number}, sdk_version_commit_hash: ${platform_sdk_version_commit_hash}"
    echo "${platform_sdk_version_number} ${platform_sdk_version_commit_hash} ${cpp_runtime}" > ${version_file}

    sh "./build-scripts/validate_version_file.sh" ${version_file}

    #compress and deploy
    rm -f temp.tar.gz
    rm -rf ${sdkPackageDirPrefix}
    cp -r ${srcSdkPackageDir} ${sdkPackageDirPrefix}

    tar -pvczf temp.tar.gz ./$sdkPackageDirPrefix/

    upload_to_s3 "temp.tar.gz" "s3://eegeo-static/$destSdkPackage"
    sh "./build-scripts/copy.sdk.package.to.versioned.folders.s3.sh" "$aws_access_key_id" "$aws_secret_access_key" "$destSdkPackage" "$platform_sdk_version_number"

    rm -f temp.tar.gz
done

trap : 0
echo -e "\n$0 SUCCEEDED\n" >&2

exit 0
