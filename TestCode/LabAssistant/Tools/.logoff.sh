#!/bin/bash
# Script to switch between wallpaper images

#time between switches
time=10

#get correct pathname for account
cd
pwd=$(pwd)
path="/.icon.jpg"
echo $pwd$path

#backup old wallpaper
old=$(gconftool-2 --get /desktop/gnome/background/picture_filename)
echo $old >> .realWall.txt
while :
do

#switch wallpaper
    gconftool-2 -t str -s /desktop/gnome/background/picture_filename $pwd$path

#sleep for time
sleep $time;

done


