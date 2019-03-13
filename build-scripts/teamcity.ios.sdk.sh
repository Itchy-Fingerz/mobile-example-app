#!/bin/sh

readonly script_name=${0##*/}

trap_failure() {
   echo "Error: $script_name: $1" >&2
   exit 1
}
trap 'trap_failure $LINENO' ERR

set -eu

if [ "$#" -ne 7 ]; then
  echo -e "Invalid argument(s).\nUsage:\n${script_name} aws_access_key_id aws_secret_access_key sdk_version_number sdk_version_commit_hash xcode_target_name library_name sdk_archive_name" >&2
  echo "e.g. ${script_name} AKIAXXXXXXXXXXXXXXXX AWS_SECRET 103 a7231ab051069fa6be5a57c848e9d6a50d39bcaa Eegeo_Streaming libapps-on-maps sdk.package.ios.tar.gz" >&2
  exit 1
fi

readonly aws_access_key_id="$1"
readonly aws_secret_access_key="$2"
readonly platform_sdk_version_number=$3
readonly platform_sdk_version_commit_hash=$4
readonly targetName=$5
readonly libraryName=$6
readonly sdkArchiveName=$7

#undo changes if a build was interrupted before by doing a checkout . on poked file
git checkout ./platform/EegeoWorld.h

#poke file
readonly placeholder_version_number=EEGEO_PLATFORM_VERSION_NUMBER_TARGET
readonly placeholder_version_commit_hash=EEGEO_PLATFORM_VERSION_COMMIT_HASH_TARGET
sed -i.bak -e s@$placeholder_version_number@$platform_sdk_version_number@g -e s@$placeholder_version_commit_hash@$platform_sdk_version_commit_hash@g ./platform/EegeoWorld.h

#build platform against poked version symbols
sh "build-scripts/ios/create.sdk.package.ios.sh" $targetName $libraryName

#cleanup
mv ./platform/EegeoWorld.h.bak ./platform/EegeoWorld.h
rm -f ./sdk.package/platform/EegeoWorld.h.bak 

readonly version_file=./sdk.package/version.txt

#dump version file into sdk root
echo "sdk_version_number: $platform_sdk_version_number, sdk_version_commit_hash: $platform_sdk_version_commit_hash"
echo "$platform_sdk_version_number $platform_sdk_version_commit_hash" > ${version_file}

sh "./build-scripts/validate_version_file.sh" "$version_file"

#compress and deploy
tar -pvczf "sdk.package.tar.gz" "./sdk.package/"

AWS_ACCESS_KEY_ID="$aws_access_key_id" AWS_SECRET_ACCESS_KEY="$aws_secret_access_key" aws s3 cp \
    --region us-east-1 \
    --acl public-read \
    --cache-control 'public,no-cache' \
    "sdk.package.tar.gz" \
    "s3://eegeo-static/$sdkArchiveName"

sh "./build-scripts/copy.sdk.package.to.versioned.folders.s3.sh" "$aws_access_key_id" "$aws_secret_access_key" "$sdkArchiveName" "$platform_sdk_version_number"
