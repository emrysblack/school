#!/usr/bin/perl
###########################################################################
##  Program: server.pl                                                   ##
##  Author: Brian George                                                 ##
##  Copyright: 2003 BYU-I Department of Computer Science and Engineering ##
##                                                                       ##
##  Function: Server that is used to submit                              ##
##     student homework across a client/server                           ##
##     connection.  Server handles files that are ready to be submitted  ##
##     and copies them to the correct directory to be graded.            ##
##     Server writes to a log file found in here: "logs/server.log".     ##
##                                                                       ##
##  Fixed filenaming for files and paths with unusual names              ##
##  Brady Field: May 11, 2015                                            ##
###########################################################################

use Socket;
use POSIX qw(setsid);

$SIG{CHLD} = 'IGNORE';

######################################################
##Finds directory in which program files are located##
######################################################
open (DIR, "directory.dat");
my @file = <DIR>;
close DIR;

foreach (@file)
{
   if ($_ =~ /local\s(.*)/)
   {
      $local = $1
   }
}

######################
##creates the daemon##
######################
chdir '/'                 or die "Can't chdir to /: $!";
umask 0;
defined(my $pid = fork)   or die "Can't fork: $!";
exit if $pid;
setsid                    or die "Can't start a new session: $!";

##########################
##declares socket to use##
##########################
socket (SH, PF_INET, SOCK_STREAM, getprotobyname('tcp')) or die "$!\n";

my $addr = sockaddr_in (3021, 157.201.194.254);

bind (SH, $addr) or die "2 $!\n";

###############################
##Writes action to server log##
###############################
open (LOG, ">>$local/logs/server.log");
print LOG "Server up and running\t\t\t" . `date`;
close LOG;

chdir $local;

while (1)
{
   listen (SH, 5);
   accept (NEW, SH) or print LOG "Error in server: Report this error to Bro. Twitchell\n\t$!\n";
   recv (NEW, my $num, 3, 0);
   recv (NEW, my $user, $num - 100, 0);
   open (LOG, ">>$local/logs/server.log");

   ###############################
   ##Writes action to server log##
   ###############################
   print LOG "New connection made with $user\t" . `date`;
   close LOG;
   recv (NEW, my $data, 256, 0);

   #####################################################
   ##starts process with infomation passed from client##
   #####################################################
   $forker = fork();
   if (!$forker)
   {
      $status = childProcess($user, $data, $local);
      if($status == 0)
      {
         send (NEW, "Submit successful", 0);   
      }
      else
      {
         send (NEW, "Error in submit.\n\tSee your submittedHomework directory for details.", 0);
      }
      close (NEW);
      exit(0);
   }
}

close (SH);


sub sendConfirm
{
   my $code = shift;
   my $user = shift;
   my $newFile = shift;
   my $class = shift;
   my $currentDir = shift;
   my $hwNum = shift;
   my $ext;


   ## $newFile =~ /.*\.(\w$)/; ## <-- the problem is here 
   $newFile =~ /(\.[^.]+)$/; ## no problem anymore :)


   $ext = $1;

   my $stuDir = "/home/$currentDir/submittedHomework";
   my $stuFile = $class . "_" . $hwNum . $ext;
   
   if (!(-e $stuDir))
   {
      ## system("mkdir -m 700 $stuDir");
      mkdir $stuDir, 0700 or die "can't mkdir $stuDir: $!";
      system("chown $user:student $stuDir");
   }
   if($code == 1)
   {
      ################
      ##System Error##
      ################
      @error = shift;
      open(FILE, ">$stuDir/unsuccessful_submit_$stuFile");
      print FILE "Error in submit:\n\t";
      print FILE @error;
      print FILE "\n\nPlease correct errors and resubmit.\n";
      close FILE;
   }
   else
   {
      #############
      ##No Errors##
      #############
      open(FILE, $newFile);
      @file = <FILE>;
      close FILE;

      open(FILE, ">$stuDir/$stuFile"); ## <-- or possible here

      print FILE @file;
      close FILE;
   }
   system("chmod 600 $stuDir/$stuFile");
   system("chown $user:student $stuDir/$stuFile");
}

sub childProcess
{
   my $user = shift;
   my $data = shift;
   my $local = shift;

   (my $instr, my $file, my $path, my $class, my $currentDir, my $hwNum) = split(/ /,$data);

   ## put the spaces back in the filename
   $file =~ s/\\\\/ /g;
   
   ## $file =~ /\.(\w+)/;
   $file =~ /(\.[^.]+)$/; ## better extension match
   my $ext = $1;
   my $status;

   ###########################################
   ##Gets week and year for submit file name##
   ###########################################
      my $date = `date +%U`;
      my $year = `date +%Y`;
      
      chomp $date;
      chomp $year;


##################################################
##Opens log file ane writes action to submit log##
##################################################
   open (LOG, ">>$local/logs/$date-$year.log");
   print LOG "User: $user\n";

################################
##Check to see if file exists ##
################################
   if(!(-e $file))
   {
      print LOG "\tFile was not copied correctly\n";
      $status = 1;
      sendConfirm($status, $user, null, $class, $currentDir, $hwNum);
   }
   else
   {
   ######################################################
   ##Creates new file using the username of the student##
   ######################################################
      my $newFile = $path . $user . $ext;

   #####################################
   ##Copies file to specified location##
   #####################################
      
      system("cp '" . $file . "' '" . $newFile . "' 2>$local/logs/error.log");
      system("chown " . $instr . ":faculty " . $newFile);
      system("chmod 400 " . $newFile);
      

   ######################
   ##Get errors, if any##
   ######################
      open (FILE, "$local/logs/error.log");
      my @error = <FILE>;
      close FILE;
      
      `rm $local/logs/error.log`;

   ###############################
   ##Writes action to submit log##
   ###############################
      if (@error)
      {
	 print LOG "\tERROR:\n";
	 foreach (@error)
	 {
	    print LOG "\t$_";
	 }
         $status = 1;
	 sendConfirm($status, $user, $newFile, $class, $currentDir, $hwNum, @error);
      }
      else
      {
	 print LOG "\tFile to copy: $file\n";
	 print LOG "\tFile copied to: $path$user.$ext\n";
         $status = 0;
	 sendConfirm($status, $user, $newFile, $class, $currentDir, $hwNum);
      }
  }

###############################
##Writes action to submit log##
###############################
   print LOG "\t" . `date`;
   print LOG "\n";
   close LOG;
   
###############################
##Writes action to server log##
###############################
   open (LOG, ">>$local/logs/server.log");
   print LOG "$user Disconnected\t\t\t" . `date`;
   close LOG;
   
   return $status;
}
