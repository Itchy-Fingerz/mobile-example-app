#!/bin/sh

targetName=$1

echo
echo "Analyze xcode project step..."
echo

# Path where the project is located.
projectpath=$(pwd)/eegeo-stream-app-ios/build/
rm -rf $projectpath
mkdir -p $projectpath
cd $projectpath 
cmake -DCMAKE_TOOLCHAIN_FILE=../../cmake/toolchain/ios/iOS.cmake -GXcode ..

logfilename="buildout.log"

rm $projectpath/$logfilename

if [ $resultcode != 0 ] ; then
   echo "CLEAN FAILED"
   exit $resultcode
fi 

(cd $projectpath && xcodebuild -target $targetName analyze 2>&1 | tee $logfilename)
resultcode=$?

# Output the result of the operation.
echo
if [ $resultcode = 0 ] ; then
grep -Fxq 'The following commands produced analyzer issues:' $projectpath/$logfilename
  analyzerresult=$?
  if [ $analyzerresult = 1 ] ; then
    echo "ANALYZE XCODE PROJECT SUCCEEDED"
  else
    echo "ANALYZE XCODE PROJECT RESULTED IN STATIC ANALYSIS ERRORS"
    exit 1
  fi
else
  echo "ANALYZE XCODE PROJECT FAILED"
fi
echo

exit $resultcode
