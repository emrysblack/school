#!/usr/bin/perl
use strict;
use warnings;

# These are the IP addresses of every computer in the linux lab
my @servers = (
    "157.201.194.201",    "157.201.194.202",    "157.201.194.203",    "157.201.194.204",    "157.201.194.205",
    "157.201.194.206",    "157.201.194.207",    "157.201.194.208",    "157.201.194.209",    "157.201.194.210",
    "157.201.194.211",    "157.201.194.212",    "157.201.194.213",    "157.201.194.214",    "157.201.194.215",
    "157.201.194.216",    "157.201.194.217",    "157.201.194.218",    "157.201.194.219",    "157.201.194.220",
    "157.201.194.221",    "157.201.194.222",    "157.201.194.223",    "157.201.194.224",    "157.201.194.225",
    "157.201.194.226",    "157.201.194.227",    "157.201.194.228",    "157.201.194.229",    "157.201.194.230",
    "157.201.194.231",    "157.201.194.232",    "157.201.194.233",    "157.201.194.234",    "157.201.194.235"
);

print "Do you have passwordless login already enabled (y/n):";
my $answer = <STDIN>;
if ($answer =~ /n/i)
{
    print "Generating ssh keys for autonomous login, please press [enter] at prompts: ssh-keygen".$/;
    system('ssh-keygen');

    print "Adding your keys to authorized keys: cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys".$/;
    system('cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys');

    print "Notifying ssh-agent of keys with: ssh-add".$/;
    system('ssh-add');
}

print "Starting to add linux lab server rsa keys. This is going to get flashy. Press [enter] when ready.".$/;
<STDIN>;
system('./touchServer.sh', $_) for (@servers);
