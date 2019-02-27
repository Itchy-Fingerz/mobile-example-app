#!/bin/sh

echo
echo "Commit .ipa file to testflight.com step..."
echo

# Path where the app is located.
apppath=$(pwd)

# API_TOKEN, from https://testflightapp.com/account/#api-token
apitoken='90232c2de030ef4aada06d9392f579b9_NjEyNTU1MjAxMi0wOS0wNSAwOToyODoxMi45NTc5Njc'

# TEAM_TOKEN, from https://testflightapp.com/dashboard/team/edit/
teamtoken='45e14faba5c13a733e9c765626eca09a_NDI3MTIyMDExLTExLTIyIDEwOjA3OjMyLjY2Mzg2NQ'

# Full path where the app file is located.
filepath=$apppath/eegeo-stream-app-ios/build/Release-iphoneos/"Streaming_Test.ipa"

# Release notes for the build.
notes='Ad hoc build from route-conforming branch.'

# Path of the commit log.
commitlog=$apppath/"commit_result.log"

# Execute the commit.
resultcode=$(curl --write-out %{http_code} --output "$commitlog" -H 'Expect:' https://testflightapp.com/api/builds.json \
    -F file="@$filepath" \
    -F api_token="$apitoken" \
    -F team_token="$teamtoken" \
    -F notes="$notes" \
    -F notify=True \
    -F distribution_lists="Eegeo_Mobile")
cat $commitlog

# Output the result of the operation.
echo
if [ $resultcode = 200 ] ; then
  echo "COMMIT IPA FILE SUCCEEDED"
  echo
  exit 0
else
  echo "COMMIT IPA FILE FAILED"
  echo
  exit 1
fi
