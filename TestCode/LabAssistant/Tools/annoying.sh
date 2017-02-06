#!/bin/bash
# Script to switch between wallpaper images

#time between switches
time=10

#get correct pathname for account
cd
pwd=$(pwd)
path="/.icon.jpg"

while :
do
#switch wallpaper
    gconftool-2 -t str -s /desktop/gnome/background/picture_filename $pwd$path

#sleep for time
sleep $time;

done


