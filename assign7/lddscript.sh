#!/bin/bash

IFS=$'\n'
filename='commandsFile.txt'
dynamLibs=""
while read line; do
    dynamLibs=$(ldd /usr/bin/$line)
    printf '%s\n'"$dynamLibs"
done < $filename
