#!/usr/bin/perl
use strict;
use warnings;
use Term::ProgressBar;

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

# Only the first argument can be 'islocal', which only shows local sessions.
my $LOCAL_ONLY = 0;
if (scalar @ARGV and $ARGV[0] eq 'islocal')
{
    shift @ARGV;
    $LOCAL_ONLY = 1;
}

# 'andmap' or 'map' can be either the first or second argument, and controls
# printing the map. Map is only of the local logins, 'map' implies LOCAL_ONLY.
my $PRINT_MAP = 0;
my $MAP_ONLY  = 0;
if (scalar @ARGV)
{
    if ($ARGV[0] eq 'andmap')
    {
        shift @ARGV;
        $PRINT_MAP = 1;
    }
    elsif ($ARGV[0] eq 'map')
    {
        shift @ARGV;
        $PRINT_MAP  = 1;
        $LOCAL_ONLY = 1;
        $MAP_ONLY   = 1;
    }
}

# 'isdead' can only be a lone command, which only checks if the
# machine is live
my $PULSE_CHECK = 0;
$PULSE_CHECK = 1 if (scalar @ARGV == 1 and $ARGV[0] eq 'isdead');

# This seems short with the progress bar, really, really long without it.
my $progressBar = Term::ProgressBar->new(scalar @servers);
my $progress = 0;

my %usernames;
my %dead_machines;
for my $ip(@servers)
{    
    $progress++;

    # Returns 'dead' if the machine is non-responsive
    my @whoData = split ($/, &remoteExec ($ip, 'who'));    
    
    if (scalar @whoData and $whoData[0] eq "dead")
    {
        $dead_machines{$ip} = 1;
    }
    elsif (scalar @whoData and !$PULSE_CHECK)
    {
        # Extract login data from remote compute and strip out the cruft
        @whoData = map { my @temp = split(/ +/, $_); 
                         $temp[-1] =~ /\((.*)\)/;
                         [$temp[0], $1] } @whoData;

        my @users = map { $_->[0] } @whoData;
        
        for my $loginName(@users)
        {                
            chomp $loginName;
            # pinky -l prints usefull information about the user, but
            # we have to extract the bit we are interested in.
            my $realName = `pinky -l $loginName`;
            chomp $realName;
            if ($realName =~ /In real life:  (.*)?\s*/)
            {
                # Names should be capitalized, so this does. Pretty,
                # but doesn't really add anything. Doesn't cost
                # anything either.
                my $possible_name = $1;
                if ($possible_name =~ /^\s*$/)
                {
                    $realName = '<<<REDACTED>>>';
                }
                else
                {
                    $realName = $1;
                }
                $realName =~ s/(\w+)/\u\L$1/g;
                
                # Check for remote / local logins
                my $remote = 0;
                my $local = 0;
                my $nx = 0;
                for (@whoData)
                {
                    # search for possibly truncated match 
                    if ($loginName =~ /$_->[0]/)
                    {       
                        if ($_->[1])
                        {
                            if ($_->[1] =~ /:\d$/) # Local session
                            {
                                $local = 1;
                            }
                            elsif ($_->[1] =~ /:0.\d+/) { ; }# Local terminal, do nothing 
                            elsif ($_->[1] =~ /:\d+.\d+/){ # NX session (probably)
                                $nx++;
                            }
                            else
                            {
                                $remote++;
                            }
                        }
                    }
                }

                $ip =~ /194.2(\d+)/;
                
                $remote = '' unless $remote;
                $nx = '' unless $nx;

                my $key = sprintf("%2d |%-16s|%-35s|%3s|%2s|", $1, $loginName, $realName, $remote, $nx);
           
                if ($local)
                {
                    $key .= '  X';
                }

                # Store the server/name combo as a key to avoid duplication
                $usernames{$key.$/} = 1;
            }
        }
    }

    $progressBar->update($progress);
}

# Newline after the progress bar
print $/;

# Diagnostic info about non-responsive machines
if (scalar keys %dead_machines)
{
    print
        "##################################################\n".
        "##################################################\n".
        " The following machines did not respond:\n";
    print "\t$_$/" for (sort keys %dead_machines);
    print
        "##################################################\n".
        "##################################################\n";    
}

# Convert the hash keys into a sorted list
my @sorted = sort keys %usernames;
my @locals;

# Print header for remote logins
unless ($MAP_ONLY)
{
    print $/;
    print
        '===+----------------+================================================'.$/;

    if ($LOCAL_ONLY)
    {
        print  
            '===|  Local Logins  |================================================'.$/;
    }
    else
    {
        print  
            '===|   All Logins   |================================================'.$/;
    }
    
    print  
        '===+----------------+================================================'.$/;
    print $/;
    
    printf "CPU|%-16s|%-35s|SSH|NX|Local$/", 'Login ID', 'Real Name';
    print  '---+----------------+-----------------------------------+---+--+-----'.$/;
}



unless (scalar @ARGV)
{
    my @localList = grep {/X$/} @sorted;
        
    @locals = map { my @temp = split(/ *[|]+ */, $_);
                    @temp = map { s/ +/ /g; $_ } @temp;
                    [ $temp[2], $temp[0] ]; } @localList;

    # Print them all out if no-one in particular was requested
    if ($LOCAL_ONLY)
    {
        unless ($MAP_ONLY) { print $_ for (@localList) };
    }
    else
    {
        print $_ for (@sorted);
    }
}
else
{
    # Otherwise search for each string in the commmand line args
    for my $name(@ARGV)
    {
        for my $record(@sorted)
        {
            if ($record =~ /$name/i)
            {                
                my @info = map {s/ +/ /g; $_} split (/ *[|]+ */, $record);
                
                my $isLocal = $record =~ /X$/;
                push (@locals, [$info[2], $info[0]]) if ($isLocal);
                
                if (!$MAP_ONLY and (!$LOCAL_ONLY or ($LOCAL_ONLY and $isLocal)))
                {
                    print $record;
                }                    
            }            
        }
    }
}

if (scalar @locals and $PRINT_MAP)
{
    print $/;
    print  '===+----------------+================================================'.$/;
    print  '===|   Local Map    |================================================'.$/;
    print  '===+----------------+================================================'.$/;
    print $/;
    
    # Print out the legend
    my $i = 0; for my $student (@locals)
    {
        printf
            '%s) [CPU %2s] %s'.$/,
            chr(ord('a') + $i),
            $student->[1],
            $student->[0];
        ++$i;
    }

    print $/;

    # Print out the key
    &map (map {$_->[1]} @locals);
}

sub remoteExec{
    my $ip = shift @_;
    my $cmd = shift @_;
    
    my $response;
    # Sequester this in an eval loop so die() doesn't kill the program
    eval{
        # Remap SIGDIE so it's quieter
        local $SIG{__DIE__} = sub {};
        # Remap SIGALRM so it dies with our error message
        local $SIG{ALRM} = sub {die 'alarm'};
        
        # Set a 5 second alarm and run our remote command
        alarm 5;
        $response = `ssh -p215 $ip "$cmd" 2>&1`;
        alarm 0;

    };
    if ($@){ # If we timed out, return 'dead' or propagate the error
        die unless $@ =~ /alarm/;
        return "dead";
    }
    if ($response =~ /refused|No route to host/i)
    {
        return "dead";
    }

    return $response;
}

sub map{
    my $char = 0;
    my $loc = shift @_;

    print "\t";
    for (my $i = 1; $i < 36; ++$i)
    {
        if ($loc && $i == $loc)
        {
            print chr(ord('a') + $char);
            ++$char;
            $loc = shift @_;
        }
        else
        {
            print '-';
        }
        
        if ($i == 30)
        {
            print "$/\t      ";
        }
        elsif ($i % 5 == 0 && $i % 10)
        {
            print ' ';
        }
        elsif ($i % 10 == 0)
        {
            print "$/\t";
        }
    }
    print $/;
}
