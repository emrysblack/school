#!/usr/bin/perl
#
# A simple DejaGNU-like test driver.
#

$project = $ARGV[0];
@testdirs = grep { -d $_ } glob ("${project}.*");

if ($#ARGV == -1 || $#testdirs == -1) {
	print "Can't find the tests.  Here are some suggestions:\n";
	my @dirs = grep { -d $_ } glob ("*.*");
	my @testdirs = grep { glob ("$_/*.test") ne ""; } @dirs;
	my %possible_projects;
	foreach my $dir (@testdirs) {
		$projpart = $dir;
		$projpart =~ s/\..*$//;
		$possible_projects{$projpart}++;
	}
	print join ("\n", keys %possible_projects);
	print "\n";
	exit 1;
}

# Names of the log files:
$testlog = "${project}.log";
$testsum = "${project}.sum";

# Delete old log files.
system ("rm -f $testlog $testsum");

# Open the log files for writing.
open (LOG, ">$testlog") or die "Can't write to $testlog: $!\n";
open (SUMMARY, ">$testsum") or die "Can't write to $testsum: $!\n";

# Subroutines to print messages to various places.
sub send_user { print STDOUT @_; }
sub send_log { print LOG @_; }
sub append_file_to_log {
  my ($filename, $banner) = @_;
  if ($banner) {
	send_log ("\n\t$banner:\n");
  }
  my $filename = $_[0];
  open (INPUT, $filename) or die "Can't read from $filename: $!\n";
  while (<INPUT>) {
    send_log ($_);
  }
  if ($banner) {
    send_log ("\n");
  }
  close INPUT;
}
sub send_summary { print SUMMARY @_; }
sub send_all { send_user (@_); send_log (@_); send_summary (@_); }

# Call an external program and return the exit code.
sub run {
  my ($cmd) = @_;
  my $status = system ($cmd);
  $status = (($status & 0xff00) >> 8);
  return $status;
}

# Print a header.
send_all ("\n\t=== ${project} tests ===\n\n");

# Zero our counters of passed/failed tests.
$npass = 0;
$nfail = 0;
$count = 0;

# Print a pass message for the given testcase, and increment the pass
# counter.
sub pass {
	my ($testcase) = @_;
	send_log ("PASS: $testcase\n");
	send_summary ("PASS: $testcase\n");
	$npass++;
}

# Print a failure message for the given testcase, and increment the failure
# counter.
sub fail {
	my ($testcase) = @_;
	send_all ("FAIL: $testcase\n");
	$nfail++;
}

# Check for differences between OUT and STDOUT, and put them in the file
# DIFFS. If there are differences, put them in the log, and fail the
# given TESTCASE, and return -1. Otherwise, return 0.
sub check_for_diffs {
	my ($out, $stdout, $diffs, $testcase) = @_;
	# Compare the output to the standard output.
	if (run ("diff -uad $out $stdout >> $diffs") != 0) {
		# If there were differences, the test is failed.
		# Save the differences in the log.
		append_file_to_log ($diffs, "DIFFERENCES ENCOUNTERED");
		fail ($testcase);
		return -1;
	}
	return 0;
}

sub load_testcase {
	my ($testcase) = @_;
	my ($ccmd, $cfiles, $cstdout, $rcmd, $rstdout);
	open (TESTCASE, $testcase) or die "Can't read from $testcase: $!\n";
	while (<TESTCASE>) {
		if (/^COMPILE COMMAND:\s*(.*)\s*$/) { $ccmd = $1; }
		elsif (/^COMPILE FILES:\s*(.*)\s*$/) { $cfiles = $1; }
		elsif (/^COMPILE OUTPUT:\s*(.*)\s*$/) { $cstdout = $1; }
		elsif (/^RUN COMMAND:\s*(.*)\s*$/) { $rcmd = $1; }
		elsif (/^RUN OUTPUT:\s*(.*)\s*$/) { $rstdout = $1; }
	}
	close TESTCASE;
	return ($ccmd, $cfiles, $cstdout, $rcmd, $rstdout);
}

# Run each test.
foreach my $testdir (@testdirs) {
	send_all ("Running tests in $testdir ...\n");
	my @testcases = grep { -f $_ } glob ("$testdir/*.test");

	TEST: foreach my $testcase (@testcases) {
		# Set up the temporary files.
		$count++;
		my $tmpfile = "/tmp/run-tests-$$-$count";
		my $cout = "${tmpfile}.cout";
		my $rout = "${tmpfile}.rout";
		my $cdiffs = "${tmpfile}.cdiffs";
		my $rdiffs = "${tmpfile}.rdiffs";
		my @tmpfiles = ($cout, $rout, $cdiffs, $rdiffs);

		# Load the parameters for this testcase.
		my ($ccmd, $cfiles, $cstdout, $rcmd, $rstdout)
			= load_testcase ($testcase);

		# Run the compiler.
		if ($ccmd && $cfiles) {
			unlink $cout;
			# Compile each file using CCMD.
			foreach my $cfile (split (" ", $cfiles)) {
				my $cmd = "$ccmd $testdir/$cfile >> $cout 2>&1";
				send_log ("\t$cmd\n");
				run ($cmd);
			}
			# Save the compiler output in the log.
			append_file_to_log ($cout, "OUTPUT FROM COMPILER");
			if ($cstdout) {
				if (check_for_diffs ($cout, "$testdir/$cstdout", $cdiffs, $testcase) < 0) {
					unlink @tmpfiles;
					next TEST;
				}
			}
		}

		# Run the produced program.
		if ($rcmd) {
			unlink $rout;
			my $cmd = "$rcmd >> $rout 2>&1";
			send_log ("\t$cmd\n");
			run ($cmd);
			# Save the output in the log.
			append_file_to_log ($cout, "OUTPUT FROM COMPILED PROGRAM");
			if ($rstdout) {
				if (check_for_diffs ($rout, "$testdir/$rstdout", $rdiffs, $testcase) < 0) {
					unlink @tmpfiles;
					next TEST;
				}
			}
		}

		# If we got here, the test passed.
		pass ($testcase);

		# Clean up our temporary files.
		unlink @tmpfiles;
	}
}

# Print summary of passed/failed tests.
send_all ("\n\t=== ${project} summary ===\n\n");
if ($npass != 0) {
	send_all ("\t$npass tests passed\n");
}
if ($nfail != 0) {
	send_all ("\t$nfail tests failed\n");
}

# All done.
close (LOG);
close (SUMMARY);
exit ($nfail > 0);

__END__

=head1 NAME

runTests.pl -- a simple DejaGNU-like test driver

=head1 SYNOPSIS

runTests.pl PROJECTNAME

=head1 DESCRIPTION

runTests.pl is a simple driver for testing compilers. It can compare
the output of the compiler against a known correct output (the "standard
output"), and it can compare the output of the compiled program against
a known correct output (the "standard program output").

Each test is described by a file whose name has the ".test" extension.

=head1 EXAMPLES

Running the test driver is straightforward: "runTests.pl foo" runs all
the tests in directories named "foo.*" (that is, all the tests named
"foo.*/*.test".)

Tests that examine the compiler output are structured as follows: Let's
say you have a program called "foo.c" and it has a syntax error. You
want to make sure that the compiler, called "mycompiler", prints "syntax
error". You create two files, one called "foo.std" and the other called
"foo.test".  "foo.std" is the standard output, and it should just contain
"syntax error".   "foo.test" describes the test to runTests.pl, and it
should contain these lines:

	COMPILE COMMAND: mycompiler
	COMPILE FILES: foo.c
	COMPILE OUTPUT: foo.std

Put foo.c, foo.std, and foo.test in a directory called mycompiler.tests.
Then run "runTests.pl mycompiler".  runTests.pl will run the command
"mycompiler mycompiler.tests/foo.c" and make sure using diff(1) that the
output is the same as the contents of the file "mycompiler.tests/foo.std".

Tests that examine the compiled program's output are structured similarly.
The *.test file contains lines like the following:

	RUN COMMAND: xyz
	RUN OUTPUT: xyz.run.std

Assuming you add these lines to "foo.test" as above, runTests.pl will run
the command "xyz" by itself after running the compile test, and it will
compare the output to the file "mycompiler.tests/xyz.run.std".

If you have a RUN test and a COMPILE test in the same .test file, the
RUN test always runs after the COMPILE test. It is perfectly OK to have
only a COMPILE test or only a RUN test in a .test file.

Note that if your compiler produces a binary in the "mycompiler.tests"
directory, you'll have to specify its pathname explicitly on the "RUN
COMMAND" line.

=head1 EXIT STATUS

runTests.pl exits with a nonzero error code if it cannot find any tests to
run, or if any of the tests fail. Otherwise, it exits with error code 0.

=head1 FILES

F<*.test> - Files that describe a single test.

F<foo.*> - Directories that contain tests for the program "foo".

F<foo.log> - Log file produced that contains the test output for each test,
and differences from the standard output for each test, as well as a
PASS or FAIL statement for each test, and finally a count of the number
of passed or failed tests.

F<foo.sum> - Summary file produced that contains only a PASS or FAIL
statement for each test, and a count of the number of passed or
failed tests.

=head1 SECURITY

runTests.pl does not safeguard the user against testing untrusted code. 

=head1 DIAGNOSTICS

	Can't find the tests.  Here are some suggestions: ...

This means that runTests.pl looked for files named PROJECTNAME.*/*.test
but couldn't find any. Perhaps you made a typo when entering PROJECTNAME
on the command line, or perhaps you didn't enter a PROJECTNAME at all. If
runTests.pl prints out any suggestions, try using them for PROJECTNAME.

	FAIL: xyz.tests/foobar.test

This means that the test named xyz.tests/foobar.test failed, either
because the compiler output didn't match the standard output, or the
program output didn't match the standard program output.

=head1 SEE ALSO

L<runtest(1)>, L<diff(1)>, L<perl(1)>.

=head1 AUTHOR

Written by Brian Gaeke in January 2003.

