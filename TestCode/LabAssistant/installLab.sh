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

cd ~

#path to home dir
pwd=$(pwd)

echo "Installing Lab Apps to bin directory..."
#put apps into bin directory
mkdir -p bin
cp $source/LabAssistantPackage/bin/* $pwd/bin/
echo "done\n"
echo "Moving dependencies into place..."
#setup commands
mv $pwd/bin/commands $pwd/.commands 
cp $pwd/.bashrc $pwd/.bashrc_old
mv $pwd/bin/bashrc $pwd/.bashrc
#put script in startup applications
mkdir -p $pwd/.config/autostart
mv $pwd/bin/LabAssistant.jar.desktop ~/.config/autostart/
echo "done\n"
#setup whoall
echo "Preparing to setup WhoAll"
read -p "Press <ENTER> when ready" -i "<ENTER>"
cd $pwd/bin/
./setUpWhoAll.pl
#exit
echo "Welcome to the Lab Team"
read -p "Press <ENTER> to finish installation" -i "<ENTER>"



