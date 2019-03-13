#!/bin/sh

echo "Copying Senion SDK"
cp -r ./eagle-app/libs/Senion/ios/*.framework ios/Include/SenionLab
if [ $? -ne 0 ] ; then
    exitCode=$?
    echo "Failed to copy Senion SDK" >&2
    exit $exitCode
fi
