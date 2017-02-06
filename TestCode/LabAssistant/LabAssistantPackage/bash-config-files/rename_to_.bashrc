# Written by Morgen Peschke

##############################
##############################
##
## Set environmental variables
## Needed here so that they are
## availible when executing
## commands over ssh
##
##############################
##############################

# Set browser
if [ -n "$DISPLAY" ]; then
    export BROWSER="firefox"
else
    export BROWSER="lynx"
fi

# PATH FIX
export PATH="$HOME/bin/:$HOME/custom-installs/bin/:$PATH"

# Variables so python can find my custom installs
PYTHONPATH="$HOME/custom-installs/lib/python2.6/site-packages/:$PYTHONPATH"
export PYTHONPATH

# Lets man use my custom installs
export MANPATH="$MANPATH:$HOME/custom-installs/share/man/"

# Check for an interactive session
[ -z "$PS1" ] && return

##############################
##############################
##
## Source other files
##
##############################
##############################

# Source global
if [ -f /etc/bashrc ]; then
    . /etc/bashrc
fi

# Source aliases
# This is badly named, as there are functions in there as well
if [ -f ~/.bash-aliases ]; then
    . ~/.bash-aliases
fi

##############################
##############################
##
## Set environmental variables
##
##############################
##############################

# A simple prompt
PS1='[\u@\h \W]\$ '

# Misc bash settings
export HISTCONTROL=ignoredups:ignorespace
set echo-control-characters off

# Set default editor, set to emacs-nox because it's easier for me to have a
# consistent interface when local and remote
export EDITOR="emacs-nox"
export VISUAL="emacs-nox"

# Completion settings
complete -cf sudo
complete -cf ssudo
complete -cf man
complete -cf until

##############################
##############################
##
## Fix stuff that bugs me
##
##############################
##############################

# No-x numberlock fix
TYPE=`tty | cut -d'/' -f3 | head -c3`
if [[ "$TYPE" == "tty" ]]; then
    setleds +num
fi
