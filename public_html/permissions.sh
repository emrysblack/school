#!/bin/bash
# HTML Permissions
# sets all permissions for CS213 to correct permissions in /public_html/
# all directories must be set to 755
# all files must be set to 644
# this script must be 755 or 7**(any number)
# home directory must be set to 711

chmod 711 ~
chmod 755 $(find ~/cgi-bin/ -type d)
chmod 755 $(find ~/cgi-bin/ -type f)
chmod 755 $(find ~/public_html/ -type d)
chmod 644 $(find ~/public_html/ -type f)
chmod 755 permissions.sh
