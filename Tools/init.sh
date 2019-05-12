#!/bin/bash

# https://stackoverflow.com/questions/42712971/how-to-detect-when-a-file-is-being-sourced-from-bash
if [[ "$0" = "$BASH_SOURCE" ]]; then
	echo "Please source this script. Do not execute."
	exit
fi

export PATH=$PWD:$PATH
echo Added current directory to PATH

