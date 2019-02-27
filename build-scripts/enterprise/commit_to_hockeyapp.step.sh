#!/bin/sh

echo
echo "Commit .ipa file to hockeyapp step..."
echo "Running $0 $@"
echo

buildUrl=$1

if [ -z "$buildUrl" ]; then
        echo
        echo "Error: buildUrl must be provided"
        echo
        exit 1
fi

sourceControlUrl=$2

if [ -z "$sourceControlUrl" ]; then
        echo
        echo "Error: sourceControlUrl must be provided"
        echo
        exit 1
fi

pathToProjectDir=$3

if [ -z "$pathToProjectDir" ]; then
        echo
        echo "Error: pathToProjectDir must be provided"
        echo
        exit 1
fi

ipaName=$4

if [ -z "$ipaName" ]; then
        echo
        echo "Error: ipaName must be provided (eg. Appname)"
        echo
        exit 1
fi

hockeyAppIdentifier=$5

if [ -z "$hockeyAppIdentifier" ]; then
        echo
        echo "Error: hockeyAppIdentifier must be provided"
        echo
        exit 1
fi

dSymFilename=$6

if [ -z "$dSymFilename" ]; then
echo
echo "Error: dSymFilename must be provided"
echo
exit 1
fi

buildDSYM=$7

# API_TOKEN, from https://rink.hockeyapp.net/manage/auth_tokens
apitoken='cb892b89a008470fbf91b469cbc2268a'

# Full path where the app file is located.
filepath=$pathToProjectDir"/$ipaName.ipa"

# Full path where the dsym file is located.
dsympath=$pathToProjectDir"${dSymFilename}"

# Release notes for the build.
notes="Build uploaded automatically from teamcity ($buildUrl) from commit: $sourceControlUrl"

# Path of the commit log.
commitlog=$pathToProjectDir/"commit_result.log"

if [ "$buildDSYM" = 1 ]; then
# Execute the commit with dSYM file.
resultcode=$(curl --write-out %{http_code} --output "$commitlog" \
  -F status="2" \
  -F notify="1" \
  -F tags="engineering,qa,internal,ldc" \
  -F notes="$notes" \
  -F notes_type="0" \
  -F ipa="@$filepath" \
  -F dsym="@$dsympath" \
  -F build_server_url="$buildUrl" \
  -F repository_url="$sourceControlUrl" \
  -H "X-HockeyAppToken: $apitoken" \
  https://rink.hockeyapp.net/api/2/apps/"$hockeyAppIdentifier"/app_versions/upload)
else
  # Execute the commit.
resultcode=$(curl --write-out %{http_code} --output "$commitlog" \
  -F status="2" \
  -F notify="1" \
  -F tags="engineering,qa,internal,ldc" \
  -F notes="$notes" \
  -F notes_type="0" \
  -F ipa="@$filepath" \
  -F build_server_url="$buildUrl" \
  -F repository_url="$sourceControlUrl" \
  -H "X-HockeyAppToken: $apitoken" \
  https://rink.hockeyapp.net/api/2/apps/"$hockeyAppIdentifier"/app_versions/upload)
fi

cat $commitlog

# Output the result of the operation.
#echo
if [ $resultcode = 201 ] ; then
  echo "COMMIT IPA FILE SUCCEEDED"
  echo
  exit 0
else
  echo "COMMIT IPA FILE FAILED"
  echo
  exit 1
fi
