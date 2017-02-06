#!/usr/bin/expect -f
set timeout 30

#example of getting arguments passed from command line..
#not necessarily the best practice for passwords though...
set server [lindex $argv 0]

# connect to server via ssh, login, and su to root
send_user "connecting to $server\n"
spawn ssh -p 215 $server

#login handles cases:
#   login with keys (no user/pass)
#   user/pass
#   login with keys (first time verification)
expect {
  "> " { }
  "$ " { }
  "assword: " { 
        send "$pass\n" 
        exp_continue
  }
  "(yes/no)? " { 
        send "yes\n"
        exp_continue
  }
  default {
        send_user "Login failed\n"
        exit
  }
}

#login out
send "exit\n"

expect {
    "$ " {}
    default {}
}

send_user "finished\n"
