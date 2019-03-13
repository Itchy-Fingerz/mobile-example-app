#!/bin/sh

echo "Running: $0 $@"

xcodeTargetName_IGNORED=$1
productName=$2
productVersion=$3
teamcityBuildUrl=$4
githubCommitUrl=$5
pathToProjectDir=${6}
pathToProjectSchemes_IGNORED=$7
hockeyAppIdentifier=${8:-61e8f1e9bab3429ba18d9fe491ef9cf3}
provisioningProfile=$9
buildDSYM=${10:-0}
generateDistSignedIpa=${11}
distributedBundleId=${12}
buildVersion=${13:-${productVersion}"-enterprise"}

# build archive using automatic signing with development cert, using Team Id for apple.enterprise.developer@kimbleoperations.com
# https://developer.apple.com/account/ios/certificate/?teamId=77LF7Y24G3
# A subsequent step may export an ipa from the archive and resign with eg distribution cert.
readonly developmentTeamId="77LF7Y24G3"


function trap_failure {
  echo "FAILED: $1 LINE $2" >&2
  exit 1
}

trap 'trap_failure $0 $LINENO' ERR


# creates archive using enterprise signing cert, exports ipa for IH distribution and deploys

archivePath="$productName.xcarchive"
ipaName="$productName"

mkdir -p "$pathToProjectDir"

sh "$pathToProjectDir/../build.sh" --archive --pretty-print --build-dir XcodeBuild --development-team $developmentTeamId --resolve-codesign-identity --product-name $productName --product-version $productVersion"-enterprise" --build-version $buildVersion

sh "build-scripts/enterprise/create_ipa_file.step.sh" $productName.app $pathToProjectDir $archivePath $ipaName $provisioningProfile

dSymFilename="${productName}.dsym.zip"

sh "build-scripts/enterprise/commit_to_hockeyapp.step.sh" $teamcityBuildUrl $githubCommitUrl $pathToProjectDir $ipaName "63c9a8e2f19441efaf12a6cadce54220" "/$ipaName/$dSymFilename" $buildDSYM

#if [ ! -z "$generateDistSignedIpa" ]; then
#    sh "build-scripts/enterprise/commit_to_hockeyapp.step.sh" $teamcityBuildUrl $githubCommitUrl $pathToProjectDir ${ipaName}Signed $hockeyAppIdentifier "/$ipaName/$dSymFilename" $buildDSYM
#fi

echo
echo "$0 SUCCEEDED"
echo

trap : 0

exit 0
