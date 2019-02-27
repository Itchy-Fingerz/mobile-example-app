#!/bin/sh

echo "Running: $0 $@"

# incremental Release build of an ios app with Developer signing identity, deploy to Hockeyapp. 
# Currently called directly from TC to build https://github.com/wrld3d/wrld-sdk-samples 
# Caleed from ./build-scripts/ios/teamcity.ios.streamalpha.sh to build ios stream app

xcodeTargetName=$1
productName=$2
productVersion=$3
teamcityBuildUrl=$4
githubCommitUrl=$5
pathToProjectDir=$6
hockeyAppIdentifier=$7


abort()
{
  echo "FAILED: $1 LINE $2" >&2
  exit 1
}

trap 'abort $0 $LINENO' 0

set -e

readonly relativeOutputDir=Release-iphoneos

sh "build-scripts/ios/compile_xcode.step.sh" $xcodeTargetName $productName $productVersion $pathToProjectDir $relativeOutputDir

apppath=$pathToProjectDir/$relativeOutputDir

sh "build-scripts/ios/create_ipa_file.step.sh" $productName.app $apppath

sh "build-scripts/ios/commit_to_hockeyapp.step.sh" $teamcityBuildUrl $githubCommitUrl $apppath $hockeyAppIdentifier


trap : 0

echo "\n$0 SUCCEEDED\n"


exit 0
