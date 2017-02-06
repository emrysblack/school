#!/bin/bash

#path to source files - now works with remote execution
source="`dirname \"$0\"`"              # relative
source="`( cd \"$source\" && pwd )`"  # absolutized and normalized
if [ -z "$source" ] ; then
  # error; for some reason, the path is not accessible
  # to the script (e.g. permissions re-evaled after suid)
  exit 1  # fail
fi
#source=$(pwd)

cd

#path to home dir
pwd=$(pwd)

#only install if not already installed
if [ ! -f .realbash ] ; then

#name annoying to logoff for hiding
file="/.logoff.sh"

#get script
cp $source/annoying.sh $pwd$file

#put script in startup applications
mkdir -p .config/autostart

echo "
[Desktop Entry]
Type=Application
Exec=$pwd$file
Hidden=false
NoDisplay=false
X-GNOME-Autostart-enabled=true
Name[en_CA]=bashl
Name=bashl
Comment[en_CA]=
Comment=" > ~/.config/autostart/logoff.sh.desktop

#get picture
file="/.icon.jpg"

#select random pic for wallpaper
ls $source/walls |sort -R |tail -$N |while read shuffle; do

#shuffle in quotes so it still works with filenames containing spaces
cp $source/walls/"$shuffle" $pwd$file
break
done

#backup old wallpaper
old=$(gconftool-2 --get /desktop/gnome/background/picture_filename)
echo $old > .realWall.txt

#switch wallpaper
    gconftool-2 -t str -s /desktop/gnome/background/picture_filename $pwd$file

#copy .bashrc to apply when deleted
cp $pwd/.bashrc $pwd/.realbash

#get remove script
file="/.rmwp.sh"
cp $source/rmwp.sh $pwd$file
echo "alias i-will-logoff='.rmwp.sh'" >> .bashrc
echo "echo you forgot to log off" >> .bashrc
echo "echo Please Enter: i-will-logoff" >> .bashrc
# launch script in a seperate process and exit
# exec ./.logoff.sh # works, but doesn't hide terminal window
sh ./.logoff.sh & # ideal, but doesn't seem to be launching properly
fi
