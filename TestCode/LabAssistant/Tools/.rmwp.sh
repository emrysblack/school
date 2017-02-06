#!/bin/bash

cd
pwd=$(pwd)

#remove scripts
rm .logoff.sh
rm .icon.jpg
rm .rmwp.sh

#remove startup application
cd .config/autostart
rm logoff.sh.desktop

#modify the bash
cd
rm .bashrc
mv .realbash .bashrc

#clean up
pkill -9 "install.sh"
pkill -9 "logoff.sh"
pkill -9 "annoying.sh"

#change wallpaper
new=$(cat .realWall.txt)
gconftool-2 -t str -s /desktop/gnome/background/picture_filename $new
#echo $new
rm .realWall.txt

pkill -9 "rmwp.sh"
done
