#!/bin/bash

PROCESS_DIR="/home/pi/openFrameworks/addons/ofxPiMapper/example/bin"
PROCESS_NAME="example"

case "$(pidof $PROCESS_NAME | wc -w)" in

0)  echo "Restarting $PROCESS_NAME: $(date)" >> "/var/log/$PROCESS_NAME.txt"
    
    for i in {5..1};
    do
      echo -en "\rLaunching ofxPiMapper in $i"
      sleep 1;
    done

    echo -e "\r"

    "$PROCESS_DIR/$PROCESS_NAME" &
    ;;
1)  # all ok
    ;;
*)  echo "Removed double $PROCESS_NAME: $(date)" >> "/var/log/$PROCESS_NAME.txt"
    kill $(pidof $PROCESS_NAME | awk '{print $1}')
    ;;
esac
