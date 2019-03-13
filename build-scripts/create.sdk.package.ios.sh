#!/bin/sh

script_name=${0##*/}

if [ "$#" -ne 2 ]; then
  echo "Invalid argument(s).\nUsage:\n${script_name} targetName libraryName" >&2
  echo "e.g. ${script_name} StreamAlpha libapps-on-maps-cpp11" >&2
  exit 1
fi

current_directory=$(pwd)
pushd .

targetName=$1
libraryName=$2
sdkprojectpath=$current_directory/eegeo-stream-app-ios/build-cpp11/

mkdir -p $sdkprojectpath
cd $sdkprojectpath
cmake -G Xcode ..
if [ $? -ne 0 ] ; then  
  echo "failed to generate cmake build; exiting." >&2
  exit 1
fi

# build sdk library
(cd $sdkprojectpath && xcodebuild -configuration Release -target $targetName ONLY_ACTIVE_ARCH='NO' -sdk "iphonesimulator")

if [ $? -ne 0 ] ; then  
  echo "failed to build sdk package (iphonesimulator); exiting." >&2
  exit 1
fi

(cd $sdkprojectpath && xcodebuild -configuration Release -target $targetName ONLY_ACTIVE_ARCH='NO' -sdk "iphoneos")

if [ $? -ne 0 ] ; then  
  echo "failed to build sdk package (iphoneos); exiting." >&2
  exit 1
fi


popd

tmpSdkPackageDir="eegeo"
sdkPackageDir="sdk.package"
rm -rf "./$tmpSdkPackageDir"
rm -rf "./$sdkPackageDir"
 
# copy sdk header includes
mkdir "./$tmpSdkPackageDir"
cp -R "./libs/ASIHttpRequest" "./$tmpSdkPackageDir/ASIHttpRequest"
cp -R "./platform" "./$tmpSdkPackageDir/platform"
cp -R "./eegeo-api" "./$tmpSdkPackageDir/eegeo-api"
cp -R "./eegeo-api-host" "./$tmpSdkPackageDir/eegeo-api-host"
cp -R "./libs/ios/curl" "./$tmpSdkPackageDir/curl"
cp -R "./libs/ios/libuv" "./$tmpSdkPackageDir/libuv"
cp -R "./libs/ios-jpeg-turbo/include" "./$tmpSdkPackageDir/ios-libjpeg-turbo"
cp -R "./libs/rapidjson" "./$tmpSdkPackageDir/rapidjson"

# remove Windows-specific rapidjson headers
rm -R "./$tmpSdkPackageDir/rapidjson/msinttypes"


#copy license
cp "./LICENSE.md" "./$tmpSdkPackageDir/LICENSE.md"

# clean up non-header files
pushd "./$tmpSdkPackageDir"
rm -rf `find . -type d -name .svn`
rm -rf `find . -type d -name .git`
find ./ -iname "*.cpp" -exec rm '{}' ';'
find ./ -iname "*.c" -exec rm '{}' ';'
find ./ -iname "*.m" -exec rm '{}' ';'
find ./ -iname "*.mm" -exec rm '{}' ';'
find ./ -iname "*.gradle" -exec rm '{}' ';'
popd

# regenerate sourceless cmakelists
`python ./build-scripts/gen_cmakes.py -p "$tmpSdkPackageDir" -e -r Include/`

# copy sdk library dependencies
cp "./libs/ios-jpeg-turbo/libturbojpeg.a" "./$tmpSdkPackageDir/libturbojpeg.a"
cp "./libs/ios/libcurl.a" "./$tmpSdkPackageDir/libcurl.a"
cp "./libs/ios/libuv.a" "./$tmpSdkPackageDir/libuv.a"
cp "$sdkprojectpath/eegeo-sdk/Release-iphoneos/libeegeo-sdk.a" "./$tmpSdkPackageDir/$libraryName.a"
cp "$sdkprojectpath/eegeo-sdk/Release-iphonesimulator/libeegeo-sdk.a" "./$tmpSdkPackageDir/$libraryName-sim.a"

cp "$sdkprojectpath/eegeo-sdk/eegeo-api/Release-iphoneos/libeegeo-api.a" "./$tmpSdkPackageDir/"
cp "$sdkprojectpath/eegeo-sdk/eegeo-api/Release-iphonesimulator/libeegeo-api.a" "./$tmpSdkPackageDir/libeegeo-api-sim.a"
cp "$sdkprojectpath/eegeo-sdk/eegeo-api-host/Release-iphoneos/libeegeo-api-host.a" "./$tmpSdkPackageDir/"
cp "$sdkprojectpath/eegeo-sdk/eegeo-api-host/Release-iphonesimulator/libeegeo-api-host.a" "./$tmpSdkPackageDir/libeegeo-api-host-sim.a"


# strip symbols
strip -S ./$tmpSdkPackageDir/$libraryName.a
strip -S ./$tmpSdkPackageDir/$libraryName-sim.a

strip -S ./$tmpSdkPackageDir/libeegeo-api.a
strip -S ./$tmpSdkPackageDir/libeegeo-api-sim.a
strip -S ./$tmpSdkPackageDir/libeegeo-api-host.a
strip -S ./$tmpSdkPackageDir/libeegeo-api-host-sim.a

mv $tmpSdkPackageDir $sdkPackageDir

echo
echo "BUILD SUCCEEDED"
echo

exit 0
