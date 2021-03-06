#!/usr/bin/perl
###########################################################################
##  Program: submit.pl                                                   ##
##  Author: Brian George                                                 ##
##  Copyright: 2003 BYU-I Department of Computer Science and Engineering ##
##                                                                       ##
##  Function: Client that is used to submit                              ##
##     student homework across a client/server                           ##
##     connection.  Client checks for class,                             ##
##     professor and homework number in program                          ##
##     header.                                                           ##
##                                                                       ## 
##   File size check and netID compatability added by                    ##
##   Conrad Kennington: Feb 1, 2005                                      ##
##                                                                       ##
##   Test functionality added and error message disobfuscation by        ##
##   Michael Glenn Brown Jr: Jan 12, 2007                                ##
##                                                                       ##
##   Tar file header submit functionality added by                       ##
##   Brady Field: Jan 14, 2015                                           ##
##                                                                       ##
##   Fixed filenaming for files and paths with unusual names             ##
##   Brady Field: May 11, 2015                                           ##
###########################################################################

use Socket;
use Archive::Extract; ## for submitting tar files
use File::Path; ## clean up temp dirs
###########################################
## Local path to the program files.      ##
## WARNING!! MUST CHANGE THIS PATH WHEN  ##
## PROGRAM FILES ARE MOVED.              ##
###########################################
$local = "/mnt/local/submit";


########################
#  Function: checkCompile
#  Purpose: Checks to ensure that the program to be submitted
#     compiles.  Handles c++ and java code and assumes others
#     don't need compilation.
########################
sub checkCompile
{
   my $file = shift;
   $file =~ /(\.[^.]+)$/;
   ## $file =~ /\.(\w+)/;
   ## check file size 
   my $size;
   $size = (stat($file))[7];
   if($size <= 0)
   {
      print "Error: $file is $size bytes! Check submit file.\n\n";
      exit(1);      
   } 

   my $ext = $1;
   my $compile;
   ## should I add c with gcc in here?
   if ($ext eq ".cpp")
   {
      $compile = "g++ ";
   }
   elsif ($ext eq ".java")
   {
      $compile = "javac ";
   }
   elsif ($ext eq ".c")
   {
      $compile = "gcc ";
   }
   else
   {
      $ext = "other";
      return;
   }

   $compile .= $file . " 2> compile.log";
   `$compile`;

   open (LOG, "compile.log");
   my $error = <LOG>;
   close LOG;

   `rm compile.log`;

   if ($error)
   {
      print "Warning: $file did not compile. Submitting continued.\n\n$error\n";
   }
   else
   {
      `rm a.out` if ($ext eq "cpp" || $ext eq "c");
   }
}

########################
#  Function: getInfo
#  Purpose: Reads the comment header in the submitted file to get the
#     professors name, class, and homework number.  Then verifies that
#     the name and the class are valid.  Returns the path were the program
#     will be copied for submission.
########################
sub getInfo
{
   my $path = shift;
   my @header;
   $hwNum;
   my $instr;
   $class;
   my $type;
   my $tarpath;
   my $tardir = '.temptar/';
   ## $program =~ /\w+\.(\w+)/;
   $path =~ /(\.[^.]+)$/; # better matching for extension
   my $ext = $1;
   if ($ext eq ".tar")
   {
       ## extract contents from tar 
       Archive::Extract->new( archive => "$path" )->extract( to => "$tardir");
       $tarpath = `pwd`;
       chomp $tarpath;
       $tarpath .= "/" . $tardir . "makefile";
       ## set scanner on makefile
       $path = $tarpath;
   }
   unless (-B $path)   ## no need to try to get the header of binary files
   {
      open (FILE, $path);
      for (my $i = 0; $i < 4; ++$i)
      {
         $header[$i] = <FILE>;
      }
      close FILE;
   }

   my %directory;
   my %owners;
   my $line;
   open (DAT, "$local/directory.dat");
   my $i = 0;
   while ($line = <DAT>)
   {
      if ($line =~ /(\w+)\s(\w+)\s(.*)/ && !($line =~ /\#\#/))
      {
         $directory{$1} = $3;
         $owners{$1} = $2;
      }
   }
   close DAT;

   if ($ext eq ".txt")
   {
      $header[0] =~ /(\w+)\s+(\w+)/;
      $type = $1;
      $hwNum = $2;

      $header[1] =~ /\w+\.?\s+(\w+)\,\s+(\w+\s?\w+)/;
      $instr = $1;
      $class = $2;    
   }
   elsif ($ext eq ".html")
   {
      $header[1] =~ /\s+?(\w+)\s+(\w+)/;
      $type = $1;
      $hwNum = $2;

      $header[2] =~ /\s+\w+\.?\s+(\w+)\,\s+(\w+\s?\w+)/;
      $instr = $1;
      $class = $2; 
   }
   elsif ($header[2] =~ /[\*|\#]\s+(\w+)\s+(\w+)/)
   {
      $type = $1;
      $hwNum = $2;
   
      $header[3] =~ /[\*|\#]\s+\w+\.?\s+(\w+)\,\s+(\w+\s?\w+)/;
      $instr = $1;
      $class = $2;
   }
   if ($ext eq ".tar")
   {
       ## if tar file rm temp extraction dir
       rmtree("$tardir");
   }
   unless ($type && $hwNum && $class && $instr)
   {
      print "Either your file is binary or your header is incorrect!\n";
      while(1)
      {
         print "Which instructor do you have?\n";
         $i = 1;
         foreach (reverse sort keys %directory)
         {
            print "$i. $_\n";
            $pros[$i] = $_;
            $i++;
         }
         print "Enter the corresponding number: ";
         $instr = <STDIN>;
         print "\n";
         unless($instr < $i && $instr > 0)
         {
            print "try again: ";
            $instr = <STDIN>;
         }
         $newFile = $directory{$pros[$instr]};
         @listClasses = ("ecen324", "cs124", "cs165", "cs235", "cs241", "cs246",
                         "cs308", "cs345", "cs364","cs416",
                         "cs432", "cs460", "cs470", "cs490", "cs499");
         print "Which class are you taking?\n";
         $i = 1;
         foreach(@listClasses)
         {
            print "$i. $_\n";
            $i++;
         }
         print "Enter the corresponding number: ";
         $class = <STDIN>;
         print "\n";
         unless($class < $i && $class > 0)
         {
            print "try again: ";
            $class = <STDIN>;
         }
         $newFile .= "/".$listClasses[$class - 1];
         opendir (DIR, $newFile);
         @assigns = grep { not /^\.{1,2}\z/ and not /archive/} readdir DIR;
         close DIR;
         @assigns = sort @assigns;
         print "Which assignment are you turning in?\n";
         $i = 1;
         foreach(@assigns)
         {
            print "$i. $_\n";
            $i++;
         }
         print "Enter the corresponding number: ";
         $hwNum = <STDIN>;
            print "\n";
         unless($hwNum < $i && $hwNum > 0)
         {
            print "try again";
            $hwNum = <STDIN>;
         }
         $newFile .= "/".$assigns[$hwNum - 1] ."/";
         print "Submit homework to $newFile. (y/n)";
         chop (my $temp = <STDIN>);
         $temp = "\L$temp";
         
         if ($temp eq "y")
         {
            last;
         } 	  
      }

      $instr = $owners{$pros[$instr]};
      $class = $listClasses[$class - 1];
      $hwNum = $assigns[$hwNum - 1];
      return $newFile, $instr;
   }

   $instr = "\L$instr";

   $class =~ s/\s//;
   $class = "\L$class";

   $type = "\L$type";
   
   if ($type eq "homework")
   {
      $hwNum = "hw" . $hwNum;
   }
   elsif ($type eq "assignment")
   {
      $hwNum = "assign" . $hwNum;
   }
   elsif ($type eq "project")
   {
      $hwNum = "prj" . $hwNum;
   }
   elsif ($type eq "lab")
   {
      $hwNum = "lab" . $hwNum;
   }
   elsif ($type eq "test")
   {
      $hwNum = "test" . $hwNum;
   }
   else
   {
      print "Error: Header does not contain the key word 'Homework',";
      print " 'Assignment', 'Project', 'Lab', or 'Test'! Check header and resubmit.\n";
      exit(1);
   }

   if (!$directory{$instr})
   {
      print "Error: $instr is not a valid instructor!  Check header and resubmit.\n";
      exit(1);
   }

   if (!(-e ($directory{$instr} . "/" . $class . "/")))
   {
      print "Error: $class is not a valid class!  Check header and resubmit.\n";
      exit(1);
   }

   my $newFile = $directory{$instr} . "/" . $class . "/" . $hwNum . "/";

   if(!(-e $newFile))
   {
      print "Error: $hwNum is not a valid Homework Number!  Check header and resubmit.\n";
      exit(1);
   }

   print "Submit homework to $instr $class and $hwNum. (y/n)";
   chop (my $temp = <STDIN>);
   $temp = "\L$temp";

   if ($temp eq "n")
   {
      print "Check header and resubmit!\n";
      exit(1);
   }


   return $newFile, $owners{$instr};
}



##########
## Main ##
##########

my $program = shift;

if($program eq "")
{
   print "Usage: submit fileToSubmit\n";
   exit(1);
}

checkCompile($program);

####################
## Gets file path ##
####################

my $path = `pwd`;
chomp $path;
$path .= "/" . $program;
####################
## Gets user name ##
####################

my $logname = `logname`;
my $whoami = `whoami`;
chomp $logname;
chomp $whoami;
if($logname ne $whoami)
{
   print "Invalid submission. Log off and try again.\n\n";
   exit(1);
}

## must get actual directory   
my $currentDir;    
my $who = `pwd`;
$who =~ m/home\//;

chomp($current = $');#'
if($current =~ m/\//)
{    
   chomp($currentDir = $`);
}
    
else
{
   $currentDir = $current;
}


$user = $logname;
(my $submit, my $instr) = getInfo ($path);
## substitute spaces with '\\' in filename (will be removed on server side)
$path =~ s/ /\\\\/g;

################################
## Creates socket with server ##
################################

socket (SH, PF_INET, SOCK_STREAM, getprotobyname('tcp')) or die "2$!"; 
my $dest = sockaddr_in (3021, 157.201.194.254);

connect (SH, $dest) or die "Error: Server not found\n$!";
$num = length($user) + 100;
send (SH, $num, 0);
send (SH, $user . $instr . " " . $path . " " . $submit . " " . $class . " " . $currentDir . " " . $hwNum, 0);
recv (SH, $status, 128, 0);

print "\n$status\n\n";

close (SH);


