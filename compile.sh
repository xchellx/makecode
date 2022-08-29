#!/usr/bin/env bash
ASAN=""
OUTEXT=""
if [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ] || [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then
    OUTEXT=".exe"
elif [ $# -gt 0 ]; then
    if [ "$1" == "asan" ]; then
        ASAN="-fsanitize=address -g"
    fi
fi
if [ ! -d "./dst" ]; then mkdir ./dst ; fi
gcc -std=c99 $ASAN -Wvla -o ./dst/makecode$OUTEXT ./src/makecode.c
md5sum -b ./dst/makecode$OUTEXT > ./dst/makecode$OUTEXT.md5
sha1sum -b ./dst/makecode$OUTEXT > ./dst/makecode$OUTEXT.sha1
sha256sum -b ./dst/makecode$OUTEXT > ./dst/makecode$OUTEXT.sha256
