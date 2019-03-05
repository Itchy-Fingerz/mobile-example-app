#!/bin/sh
readonly script_name=${0##*/}

trap_failure() {
   echo "Error: $script_name: $1" >&2
   exit 1
}
trap 'trap_failure $LINENO' ERR

set -e

versionCode=${1:-0}
versionName=${2:-"0.0.test"}
deployToHockeyApp=${3:-1}
buildUrl=${4:-"testBuildUrl"}
githubUrl=${5:-"testGithubUrl"}
pathToProjectDir=${6:-"eegeo-stream-app-droid"}
hockeyAppIdentifier=${7:-71c276a07ae93583cfe600d1ab58de8d}
gradleTask=${8:-":app:assembleRelease"}
cleanBuild=${9:-0}


# Hack because the bash version in MinGW (4.3.42) fails to do the -d check
# unless the path is fully qualified
pwd=$(pwd)
pathToProjectDir=$pwd/$pathToProjectDir


if [ ${cleanBuild} -ne 0 ] ; then
	echo "Performing clean" >&2
	./gradlew clean
fi


pushd $pathToProjectDir
	./gradlew -PversionCode=${versionCode} -PversionName=${versionName} ${gradleTask}
	gradle_resultcode=$?
popd

if [ ${gradle_resultcode} -ne 0 ] ; then
    echo "Error performing gradle build" >&2
    exit 1
fi


if [ ${deployToHockeyApp} -ne 0 ] ; then

	if [ -z $UNITY_BUILD ]; then
		pathToApk=$pathToProjectDir/app/build/outputs/apk/release/app-release.apk
		sh "./build-scripts/android/commit_to_hockeyapp.step.sh" $pathToApk $buildUrl $githubUrl $hockeyAppIdentifier

		if [ $? -ne 0 ] ; then
			exit 1
		fi
	fi
fi
#===

trap : 0

echo
echo "BUILD SUCCEEDED" >&2
echo

