                                README
                                ======

Date: 2013-01-16 15:31:07 MST


This is a collection of useful scripts, tools, notes, and etc that may be useful
for the Lab Assistants.

Table of Contents
=================
1 bash-config-files
    1.1 rename_to_.bash-aliases
    1.2 rename_to_.bashrc
    1.3 rename_to_.bash-scripture-grep
2 bin
    2.1 check.name
    2.2 emacs-nox
    2.3 publish
    2.4 svr
    2.5 unpublish
3 config
4 custom-installs
    4.1 guake
    4.2 guake-prefs
    4.3 xsel
5 dirsizeCmd
6 emacs-config-files
    6.1 rename_to_.emacs
    6.2 rename_to_.emacs.d
7 goodReads.txt
8 greppableScriptures
9 LabAssistant.jar.desktop
    9.1 Installation
10 linuxCommands.png
11 linux_reference.txt
12 now-serving.org
13 now-serving.txt
14 nx.key
15 README.org
16 README.txt
17 rename_to_.XmodMap
18 whoall
    18.1 setUpWhoAll.pl
    18.2 touchServer.sh
    18.3 whoall.pl


1 bash-config-files
~~~~~~~~~~~~~~~~~~~~
  This folder contains sample bash configuration files. They are normally
  invisible as they start with a . and will need to be renamed and put into the
  home folder.

  rename_to_.bash-aliases        -> ~/.bash-aliases
  rename_to_.bashrc              -> ~/.bashrc
  rename_to_.bash-scripture-grep -> ~/.bash-scripture-grep

1.1 rename_to_.bash-aliases
============================
   Contains aliases, functions and other useful definitions. This is sourced by
   the .bashrc as a matter of best practice, and to facilitate the operation of
   certain functions defined within.

1.2 rename_to_.bashrc
======================
   Primary configuration file, this sets up path and default variables that are
   required for some of the other goodies to function - principally the locally
   installed applications.

1.3 rename_to_.bash-scripture-grep
===================================
   This defines some functions for working with a searchable plain text version
   of the Standard Works. This is a bit of a goodie rather than a necessary
   tool, but has some nice functions for working with Bro Twitchell's
   scripture checker.

   On the other hand, the scriptures themselves are 7.4M, so if space is an
   issue, delete this file and (optionally) remove the sourcing command from
   the top of the .bash-aliases file.

2 bin
~~~~~~
  These are convenience functions for working in the lab. The .bashrc adds
  ~/bin to the execution path, so you can copy the whole folder there.

2.1 check.name
===============
   This prints out the value of the other Lab Assistant's .name files -
   provided they have set their permissions to allow it (which this program
   also handles).

2.2 emacs-nox
==============
   A simple wrapper, more of an example than anything else.

2.3 publish
============
   Recursively traverses directories passed as command line arguments and sets
   the permissions consistent with what is needed for public_html in cs213.

2.4 svr
========
   Translates computer numbers into IP addresses. Very useful with command
   substitution.

   $ svr 2
   157.201.194.202

   $ ssh $(svr 2)
   This will log into aus213l2.

2.5 unpublish
==============
   This acts as an 'undo' for the publish command.

3 config
~~~~~~~~~
  This file should be copied to ~/.ssh/config and sets various useful settings
  for ssh connections, such as using port 215 for the lab computers, and using
  keepalives so the connection doesn't shut down if it's idle for 5 min. This
  also sets up SSH multiplexing so as long as the first connection is
  established, additional connections are sent through the same
  connection. This saves time because it can skip the encryption setup,
  handshaking, and all the rest.

4 custom-installs
~~~~~~~~~~~~~~~~~~
  This contains some useful applications that I have installed locally. The
  paths for execution and man pages are set in the .bashrc file, so copying
  this file to ~/custom-installs will give you access to the following
  programs.

4.1 guake
==========
   Provides a drop-down terminal.

4.2 guake-prefs
================
   Configures the drop-down terminal.

4.3 xsel
=========
   Allows manipulation of clipboard data on the command line. Two convenience
   aliases are supplied in the .bash-aliases file: xcopy and xpaste. An example
   of how they would be used would be:

   $ xpaste | grep 'some string' | xcopy

   This would take the contents of the clipboard, search for all lines
   containing 'some string' and load only those results back into the clipboard.

5 dirsizeCmd
~~~~~~~~~~~~~
  This contains two functions to help handle over quota issues. These functions
  are already included in the .bash-aliases file, but are duplicated here to
  allow sourcing from a student's account without copying anything into their
  directories (as over quota problems generally mean this is impossible).

  dirsize    : prints the size of everything in the current directory, sorted in
               ascending order by size. This makes it very easy to find the largest
               file in a directory with many files (like a home directory).

  checkquota : provides a much easier to read report on quota usage.

6 emacs-config-files
~~~~~~~~~~~~~~~~~~~~~
  This folder contains sample Emacs configuration files. They are normally
  invisible as they start with a . and will need to be renamed and put into the
  home folder.

  rename_to_.emacs   -> ~/.emacs
  rename_to_.emacs.d -> ~/.emacs.d

6.1 rename_to_.emacs
=====================
   The main configuration file. The standard BYU-I configuration is at the top,
   the rest of the file is useful additions that may make life easier.

6.2 rename_to_.emacs.d
=======================
   This folder contains locally installed modules. The .elc files are byte
   compiled versions of the .el modules, for faster execution.

   auctex       : Main folder for the AucTeX module, which makes creating LaTeX
                  documents significantly easier.
   auctex.el    : Loading module for the AucTeX module
   tex-site.el  : Loading module for the AucTeX module
   jump-char.el : Provides movement by jumping to the next instance of a character
   xclip.el     : Links the X11 clipboard, even when using emacs -nw

7 goodReads.txt
~~~~~~~~~~~~~~~~
  Recommended reading, currently only two articles. One is a tutorial /
  mini-course on makefiles, the other is on Revision Control in Emacs.

8 greppableScriptures
~~~~~~~~~~~~~~~~~~~~~~
  This is the folder with the ASCII copy of the scriptures, one verse per line
  to facilitate using grep on them. This can be placed anywhere, provided the
  variable at the beginning of the .bash-scripture-grep file is updated to
  point to it.

9 LabAssistant.jar.desktop
~~~~~~~~~~~~~~~~~~~~~~~~~~~
  This file contains the auto-start configuration for the Lab Assistant control
  program. This can avoid the intermittent issues with creating the auto-start
  entry through the GUI which can happen when the local config is missing a
  folder.

9.1 Installation
=================
   If ~/.config/autostart does not exist then create it.
   $ mkdir ~/.config/autostart

   $ cp LabAssistant.jar.desktop ~/.config/autostart/LabAssistant.jar.desktop

10 linuxCommands.png
~~~~~~~~~~~~~~~~~~~~~
  A background image with common terminal / Emacs commands. It is missing a few
  (like pwd), but mostly covers it.

11 linux_reference.txt
~~~~~~~~~~~~~~~~~~~~~~~
  A more extensive reference file. Notably includes an example of tunneling
  using SSH.

12 now-serving.org
~~~~~~~~~~~~~~~~~~~
  This file has information about how to configure the Now Serving System , in a
  format that is easier to traverse when using Emacs. [TAB] folds or unfolds
  headings (marked by at least one leading '*').

13 now-serving.txt
~~~~~~~~~~~~~~~~~~~
  This file has information about how to configure the Now Serving System , in a
  flat text format, with index and other niceties. Generated from README.org via
  the Emacs command: "Alt-x org-export-as-ascii [RET]"

14 nx.key
~~~~~~~~~~
  This is the RSA key for the NX clients. Students using the Mac OSX won't be
  able to use the key in the pdf, as the line-breaks are replaced with spaces.

  Often the easiest way to get the file to them is (provided you have some
  directory shared, with appropriate permissions) to have them catch it via an
  ssh command.

  This will look something like this:
  ssh -p215 student_user_name@157.201.194.2xx 'cat ../your_home_folder/shared_folder/nx.key'

  This will print the key to their terminal, from which it can be safely copied
  and pasted into the NX client configuration.

15 README.org
~~~~~~~~~~~~~~
  The README file, in a format that is easier to traverse when using
  Emacs. [TAB] folds or unfolds headings (marked by at least one leading '*').

16 README.txt
~~~~~~~~~~~~~~
  The README file, in a flat text format, with index and other
  niceties. Generated from README.org via the Emacs command:
  "Alt-x org-export-as-ascii [RET]"

17 rename_to_.XmodMap
~~~~~~~~~~~~~~~~~~~~~~
  By default this is loaded on login and re-configures the X11 keymapping. It
  needs to be moved and renamed to take effect.
  $ mv rename_to_.XmodMap ~/.XmodMap

  At the moment, all this does is remap the numeric pad so that the Number Lock
  is always on, and remaps the Number Lock key itself to a BackSpace to make
  typing equations and numbers in general easier.

  There are also commented commands (comment character is '!') which will swap
  the CapsLock, Tab, and Backspace commands to make typing a bit ergonomic.

18 whoall
~~~~~~~~~~
  These files provide the ability to find who is logged in where. Originally
  setup to allow tutors to find tutees in a crowded lab. It's also great for
  checking who forgot to log out at the end of day - or sneaked in during
  Devotional.

  They need to be placed somewhere in your executable path. ~/bin/ is probably
  ideal. Then run setUpWhoAll.pl before running whoall.pl .

18.1 setUpWhoAll.pl
====================
   This is used to set up the automatic login required by the script. Follow
   the prompts, it's pretty self explanatory. Don't set a local password when
   requested or it won't work.

18.2 touchServer.sh
====================
   This is used to get the RSA key for all of the lab computers.

18.3 whoall.pl
===============
   This is the main program, and it is not documented as well as it probably
   should be.

   Basic syntax:
   whoall.pl <islocal> <map|andmap> <pattern>
   whoall.pl isdead

   Syntax notes:
   - All arguments are optional.

   - 'islocal' must be the first argument if it is present.

   - 'map' implies 'islocal'.
   - 'map' and 'andmap' must be either the first argument, or the second argument
     if 'islocal' is present.

   - 'isdead' can only be a lone argument.

   - 'pattern' can match the user's first name, last name, or username.

   Here are some examples:
   $ whoall.pl         # Print a list of everyone in the lab, both remote and locally

   $ whoall.pl pattern # Filters the list by pattern, which can match username,
                       # or real name.

   $ whoall.pl islocal # Filters the list to only those who are logged in locally.

   $ whoall.pl map     # Prints a map of the Lab, indicating who is logged in,
                       # and where.

   $ whoall.pl andmap  # Prints a list of everyone in the lab, as well as a
                       # map.

   $ whoall.pl isdead  # Checks which computers are up, and which are dead
