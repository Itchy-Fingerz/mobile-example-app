#!/bin/sh
readonly script_name=${0##*/}

trap_failure() {
   echo "Error: $script_name: $1" >&2
   exit 1
}
trap 'trap_failure $LINENO' ERR

set -e

if [ "$#" -ne 2 ]; then
  echo -e "Invalid argument(s).\nUsage:\n${script_name} sdk_version_number sdk_version_commit_hash" >&2
  echo "e.g. ${script_name} 103 a7231ab051069fa6be5a57c848e9d6a50d39bcaa" >&2
  exit 1
fi

readonly platform_sdk_version_number=$1
readonly platform_sdk_version_commit_hash=$2

readonly sdkPackageDirPrefix="sdk.package.android"
rm -rf "./$sdkPackageDirPrefix"

readonly script_dir=`dirname $0`
. ./$script_dir/is_windows.sh
is_windows=$(is_windows)

readonly target_archs="armeabi-v7a arm64-v8a x86 x86_64"
readonly cpp_runtimes="c++_static gnustl_static"
readonly platformLibDir=./eegeo-stream-app-droid/sdk/build/lib


if [ "$is_windows" == true ]; then
  local_host_arch=windows-x86_64
  local_host_ext=.exe
else
  local_host_arch=darwin-x86_64
  local_host_ext=
fi

# todo - perform all this via a cmake install, avoid this fragility
readonly tool_path_prefix_aarch64=${ANDROID_NDK_HOME}/toolchains/aarch64-linux-android-4.9/prebuilt/${local_host_arch}/bin/aarch64-linux-android-
readonly tool_path_prefix_armeabi=${ANDROID_NDK_HOME}/toolchains/arm-linux-androideabi-4.9/prebuilt/${local_host_arch}/bin/arm-linux-androideabi-
readonly tool_path_prefix_x86=${ANDROID_NDK_HOME}/toolchains/x86-4.9/prebuilt/${local_host_arch}/bin/i686-linux-android-
readonly tool_path_prefix_x86_64=${ANDROID_NDK_HOME}/toolchains/x86_64-4.9/prebuilt/${local_host_arch}/bin/x86_64-linux-android-

readonly striptool_aarch64=${tool_path_prefix_aarch64}strip${local_host_ext}
readonly striptool_armeabi=${tool_path_prefix_armeabi}strip${local_host_ext}
readonly striptool_x86=${tool_path_prefix_x86}strip${local_host_ext}
readonly striptool_x86_64=${tool_path_prefix_x86_64}strip${local_host_ext}

echo "Build Android C++ SDK static libraries..."
echo "platform_sdk_version_number is ${platform_sdk_version_number}"
echo "platform_sdk_version_commit_hash is ${platform_sdk_version_commit_hash}"

pushd eegeo-stream-app-droid
    ./gradlew -PversionCode=${platform_sdk_version_number} -PversionName=${platform_sdk_version_commit_hash} :sdk:assembleRelease

    if [ $? -ne 0 ] ; then
        exitCode=$?
        echo "Error performing gradle build" >&2
        exit $exitCode
    else
        echo "Build Android C++ SDK static libraries: SUCCEEDED"
    fi

popd


for cpp_runtime in ${cpp_runtimes}
do
    sdkPackageDir="${sdkPackageDirPrefix}.${cpp_runtime}"
    rm -rf "./$sdkPackageDir"

    #####


    mkdir -p ./${sdkPackageDir}/prebuilt


    # copy sdk headers
    for project in platform eegeo-api eegeo-api-host
    do
      echo "copying headers for $project"
      find ${project} -type d -exec mkdir -p -- ./${sdkPackageDir}/{} \;
      find ${project} -type f \( -iname \*.h -o -iname \*.inl \) -exec cp {} ./${sdkPackageDir}/{} \;
    done

    # clean up (empty) build folders (todo fix with out-of-source build ?)
    rm -rf ./${sdkPackageDir}/eegeo-api/build
    rm -rf ./${sdkPackageDir}/eegeo-api/.idea
    rm -rf ./${sdkPackageDir}/eegeo-api-host/build
    rm -rf ./${sdkPackageDir}/eegeo-api-host/.idea


    # copy 3rd-party header-only libs
    echo "copying prebuilt lib headers"
    cp -R "./libs/httpxx" ./${sdkPackageDir}/httpxx
    cp -R "./libs/rapidjson" ./${sdkPackageDir}/rapidjson

    # remove Windows-specific rapidjson headers
    rm -R "./${sdkPackageDir}/rapidjson/msinttypes"

    pushd ${sdkPackageDir}
      echo "regenerating sourceless cmakelists"
      `python ../build-scripts/gen_cmakes.py -p . -e -r libs/eegeo/ -i */rapidjson/*`
    popd

    # copy headers for 3rd-party static libs (intentionally not including in CMakeList, would require arch-
    # specific include guards, headers are not consumed by our internal apps)
    # They also contain license file for each library
    prebuilt_lib_headers="curl uv http-parser jpeg-turbo png ssl"
    for target in ${target_archs}
    do
        echo "copying prebuilt libs headers for $target"
        prefix=android-${target}
        for lib in ${prebuilt_lib_headers}
        do
            mkdir -p ./${sdkPackageDir}/${lib}
            cp -R ./libs/${lib}/${prefix} ./${sdkPackageDir}/${lib}/
        done
    done

    # copy prebuilt libs 
    for target in ${target_archs}
    do
      echo "copying prebuilt libs for $target"
      prefix=android-${target}
      dest_prebuilt_dir=./${sdkPackageDir}/prebuilt/${prefix}
      mkdir -p ${dest_prebuilt_dir}

      cp -R ./libs/prebuilt/${prefix}/libcrypto.a $dest_prebuilt_dir
      cp -R ./libs/prebuilt/${prefix}/libcurl.a $dest_prebuilt_dir
      cp -R ./libs/prebuilt/${prefix}/libuv.a $dest_prebuilt_dir
      cp -R ./libs/prebuilt/${prefix}/libhttp-parser.a $dest_prebuilt_dir
      cp -R ./libs/prebuilt/${prefix}/libjpeg.a $dest_prebuilt_dir
      cp -R ./libs/prebuilt/${prefix}/libpng.a $dest_prebuilt_dir
      cp -R ./libs/prebuilt/${prefix}/libssl.a $dest_prebuilt_dir
      cp -R ./libs/prebuilt/${prefix}/libturbojpeg.a $dest_prebuilt_dir

    done


    #copy license
    cp "./LICENSE.md" "./${sdkPackageDir}/LICENSE.md"


    # copy sdk static libraries


    for target in ${target_archs}
    do
        echo "copying platform libs for $target"
        prefix=android-${target}

        src_lib_dir=${platformLibDir}/${cpp_runtime}/${prefix}
        dest_prebuilt_dir=./${sdkPackageDir}/prebuilt/${prefix}

        # copy sdk static lib 
        #cp ./eegeo-stream-app-droid/obj/local/${target}/libeegeo-sdk.a $dest_prebuilt_dir
        cp ${src_lib_dir}/libeegeo-sdk.a $dest_prebuilt_dir
        cp ${src_lib_dir}/libeegeo-api.a $dest_prebuilt_dir
        cp ${src_lib_dir}/libeegeo-api-host.a $dest_prebuilt_dir

        if [ ${target} = "arm64-v8a" ] ; then
            striptool=$striptool_aarch64
        elif [ ${target} = "armeabi-v7a" ] ; then
            striptool=$striptool_armeabi
        elif [ ${target} = "x86" ] ; then
            striptool=$striptool_x86
        elif [ ${target} = "x86_64" ] ; then
            striptool=$striptool_x86_64
        else
            echo "unknown target architecture ${target}"
            exit 1
        fi

        echo "striptool is ${striptool}"

        for static_lib in ${sdkPackageDir}/prebuilt/${prefix}/*.a
        do
            echo "stripping ${static_lib}"

            $striptool -S $static_lib

            resultcode=$?
            if [ $resultcode -ne 0 ] ; then
              echo "Failed to strip static lib binary ${static_lib}" >&2
              exit $resultcode
            fi
        done
    done
done

#===

trap : 0


echo
echo "BUILD SUCCEEDED" >&2
echo
