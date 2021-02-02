#!/bin/bash

usage() { echo "Usage: $0 -p android|ios|windows [-c]"; echo "  -p -> platform, ios, android or windows (required), -v -> {teamcitybuildnumber} (optional)"; 1>&2; exit 1; }

baseUrl="http://s3.amazonaws.com/eegeo-static/"
srcPackageName="INVALID"
destPackageName="./sdk.package.tar.gz"
includeDestination="INVALID"
sdkDestination="INVALID"

while getopts "p:v:" o; do
    case "${o}" in
        p)
          p=${OPTARG}
          if [ "$p" != "ios" ]; then
            if [ "$p" != "android" ]; then
              if [ "$p" != "windows" ]; then
                  usage
              fi
            fi
          fi
        ;;
        v)
          v=${OPTARG}
          echo "sdk version set to v${v}"
        ;;
        *)
          usage
        ;;
    esac
done

shift $((OPTIND-1))

if [ -z "${p}" ]; then
    usage
fi

if [ "$p" == "ios" ]; then
   srcPackageName="sdk.package.ios.cpp11.tar.gz"
   includeDestination="./ios/Include/eegeo"
   sdkDestination="sdk.package"
elif [ "$p" == "android" ]; then
   srcPackageName="sdk.package.android.cpp11.c++_static.tar.gz"
   includeDestination="./android/libs/eegeo"
   sdkDestination="sdk.package.android"
elif [ "$p" == "windows" ]; then
   srcPackageName="sdk.package.windows.tar.gz"
   includeDestination="./windows/libs/eegeo"
   sdkDestination="sdk.package.windows"
fi

downloadUrl="${baseUrl}wrldsdk/v${v}/${srcPackageName}"

if [ -z "${v}" ]; then
   echo "using latest version of SDK"
   downloadUrl="${baseUrl}${srcPackageName}"
fi

downloadUrl=$(echo ${downloadUrl} | sed "s:+:%2B:g")

echo "Updating $p platform..."
rm -f ./$destPackageName
rm -rf $includeDestination
echo "$downloadUrl"
curl $downloadUrl > ./$destPackageName

statuscode=$?
if [ $statuscode -ne 0 ] ; then
    echo "Failed to download sdk package ${downloadUrl}" >&2
    exit $statuscode
fi

if [ ! -d `dirname "$includeDestination"` ]; then
    mkdir -p `dirname "$includeDestination"`
fi

tar -zxvf $destPackageName

if [ $? -ne 0 ] ; then
    echo "Failed to unzip sdk package ${destPackageName}"
    exit 1
fi

rm -f ./$destPackageName
platformVersion=`cat ./$sdkDestination/version.txt`
echo "Platform version --> $platformVersion"
echo mv ./$sdkDestination $includeDestination
mv ./$sdkDestination $includeDestination
