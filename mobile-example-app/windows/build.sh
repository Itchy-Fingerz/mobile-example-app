#!/bin/sh

usage()
{ 
	echo "Usage: $0 -p windows [-k <APIKEY> -n <PRODUCT_NAME> -v <FILE_VERSION> -i <INFORMATIONAL_VERSION>]"; 
	echo "  -p -> platform, windows (required)"; 
	echo "  -k -> the Eegeo API key to use for the app"; 
	echo "  -n -> the product name of the app"; 
	echo "  -v -> file version of executable"; 
	echo "  -i -> informational version of executable"; 
	1>&2; 
	exit 1; 
}

projectPath=$(pwd)/windows/WinBuild
rm -rf $projectPath
mkdir $projectPath

while getopts "p:k:n:v:i:" o; do
    case "${o}" in
        p)
            p=${OPTARG}
            if [ "$p" != "windows" ]; then
               usage
            fi
            ;;
    	k)
            k=${OPTARG}
            ;;
    	n)
            productName=${OPTARG}
            ;;
    	v)
            fileVersion=${OPTARG}
            ;;
    	i)
            informationalVersion=${OPTARG}
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

# poking ApiKey.h now optional, EEA now has ./scripts/poke_config.sh to poke values into config file instead
eegeo_api_key="${k}"

if [ ! -z "$eegeo_api_key" ]; then
    
	git checkout ./src/ApiKey.h

	if [ $? -ne 0 ] ; then
		echo "Failed to checkout ApiKey" >&2
		exit $?
	fi

	apiKeyFile=./src/ApiKey.h
	apiKeyFileTemp="${apiKeyFile}.tmp"

	# poke the api key
	sed -e "s/OBTAIN API_KEY FROM https:\/\/www.eegeo.com\/developers\/ AND INSERT IT HERE/${eegeo_api_key}/" $apiKeyFile > $apiKeyFileTemp

	if [ $? -ne 0 ] ; then    
		exitCode=$?
		echo "Failed to poke eegeo api key" >&2
		exit $exitCode
	fi

	mv $apiKeyFileTemp $apiKeyFile

	# poke the yelp consumer key
	sed -e 's/OBTAIN YELP CONSUMER KEY AND INSERT IT HERE/s-21y64qFi2xapp16bm31A/' $apiKeyFile > $apiKeyFileTemp

	if [ $? -ne 0 ] ; then    
		exitCode=$?
		echo "Failed to poke yelp consumer key" >&2
		exit $exitCode
	fi

	mv $apiKeyFileTemp $apiKeyFile

	# poke the yelp consumer secret
	sed -e 's/OBTAIN YELP CONSUMER SECRET AND INSERT IT HERE/cg0IO1a_ic-E_HzxP1tYW8sOWkk/' $apiKeyFile > $apiKeyFileTemp

	if [ $? -ne 0 ] ; then    
		exitCode=$?
		echo "Failed to poke yelp consumer secret" >&2
		exit $exitCode
	fi

	mv $apiKeyFileTemp $apiKeyFile

	# poke the yelp oauth token
	sed -e 's/OBTAIN YELP OAUTH TOKEN AND INSERT IT HERE/jlp9H0ICyX4cl6sRrKYS7ALPzeUl2ZzX/' $apiKeyFile > $apiKeyFileTemp

	if [ $? -ne 0 ] ; then    
		exitCode=$?
		echo "Failed to poke yelp oauth token" >&2
		exit $exitCode
	fi

	mv $apiKeyFileTemp $apiKeyFile

	# poke the yelp oauth token secret
	sed -e 's/OBTAIN YELP OAUTH TOKEN SECRET AND INSERT IT HERE/M5oIT3N2LiyFy9Sh0o_sIoj0mZs/' $apiKeyFile > $apiKeyFileTemp

	if [ $? -ne 0 ] ; then    
		exitCode=$?
		echo "Failed to poke yelp oauth token secret" >&2
		exit $exitCode
	fi

	mv $apiKeyFileTemp $apiKeyFile

	# poke the geonames user name
	sed -e 's/OBTAIN GEONAMES USERNAME AND INSERT IT HERE/eegeo/' $apiKeyFile > $apiKeyFileTemp

	if [ $? -ne 0 ] ; then    
		exitCode=$?
		echo "Failed to poke geonames username" >&2
		exit $exitCode
	fi

	mv $apiKeyFileTemp $apiKeyFile
fi
	
if [ ! -z "${productName}" ]; then
    sed -i "s/string\s*ProductName\s*=\s*@\"[^\"]*\"/string ProductName = @\"$productName\"/g" windows/ExampleApp/ExampleAppWPF/Properties/VersionInfo.cs
	sed -i "s/\s*Title\s*=\s*\"[^\"]*\"/        Title=\"$productName\"/g" windows/ExampleApp/ExampleAppWPF/MainWindow.xaml
	
fi

if [ ! -z "${fileVersion}" ]; then
    sed -i "s/string\s*FileVersion\s*=\s*@\"[^\"]*\"/string FileVersion = @\"$fileVersion\"/g" windows/ExampleApp/ExampleAppWPF/Properties/VersionInfo.cs
fi

if [ ! -z "${informationalVersion}" ]; then
    sed -i "s/string\s*InformationalFileVersion\s*=\s*@\"[^\"]*\"/string InformationalFileVersion = @\"$informationalVersion\"/g" windows/ExampleApp/ExampleAppWPF/Properties/VersionInfo.cs
fi

if [ ! -f windows/nuget.exe ]; then
	curl -o windows/nuget.exe https://api.nuget.org/downloads/nuget.exe
fi

pushd $projectPath
cmake -G "Visual Studio 14 Win64" ..
resultcode=$?
popd

if [ $resultcode -ne 0 ] ; then 
  echo "CMAKE WINDOWS PROJECT FAILED"
  exit $resultcode
fi

echo "CMAKE WINDOWS PROJECT SUCCEEDED"
 
cmd //C windows\\build.bat
resultcode=$?

if [ $resultcode = 0 ] ; then
  echo "COMPILE WINDOWS PROJECT SUCCEEDED"
else
  echo "COMPILE WINDOWS PROJECT FAILED"
fi

exit $resultcode
