#!/bin/sh

usage() { 
	echo "Usage: $0 -[o] -[u]"; echo " -o -> open project automatically after generation\n -u -> generate project for unity library"; 1>&2; exit 1; 
}

buildDirectory=eegeo-stream-app-ios/XcodeBuild

generate_cmake_project() {
	pushd .

	rm -rf $buildDirectory
	mkdir -p $buildDirectory
	cd $buildDirectory
    local use_unity=$1
    local unity_flag=""

    if [ $use_unity == "1" ]; then
        unity_flag="-DUNITY=1"
    fi

	cmakeCommand="cmake ${unity_flag} -DCMAKE_TOOLCHAIN_FILE=../../cmake/toolchain/ios/iOS.cmake -GXcode .."
	echo "Invoking cmake with command: $cmakeCommand"
	$cmakeCommand

	popd
}

build_for_unity="0"

while getopts "ou" o; do
    case "${o}" in
        o)
			auto_open_project="1"
			;;
        u)
            build_for_unity="1"
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

generate_cmake_project $build_for_unity

if [ "$auto_open_project" == "1" ]; then
	open $buildDirectory/streamalpha.xcodeproj
fi
