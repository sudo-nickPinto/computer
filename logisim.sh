#!/bin/bash
# quick Logisim launcher 
LOGISIM_JAR="logisimHDL/Logisim Evolution 5.0.4.jar"

if [ $# -eq 0 ]; then
    # no arguments - open Logisim
    java -jar "$LOGISIM_JAR"
elif [ $# -eq 1 ]; then
    # one argument - open specific file in logisim
    java -jar "$LOGISIM_JAR" "$1"
else
    echo "Usage: ./logisim.sh [circuit_file.circ]"
fi