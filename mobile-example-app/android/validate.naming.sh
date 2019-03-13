#!/bin/sh
# to run locally without requiring the eegeo-mobile repo, just change the paths to ./../eegeo-mobile
PYTHONPATH=./eegeo-mobile/libs/naming_validator/ply-3.4/build/lib python ./eegeo-mobile/libs/naming_validator/check_member_names.py ./src ./android/jni
