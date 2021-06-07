#!/usr/bin/perl -w                                 
###################################################
#                                                 #
# Script test_matchpeaks.pl                       #
#                                                 #
#                                                 #
# by Enrique Blanco (2019)                        #
###################################################

use strict;
use Getopt::Std;
use Term::ANSIColor;


#DEFINEs
my $TRUE = 1;
my $FALSE = 0;
my $TOOL = "matchpeaks";
my $PROGRAM = "bin/matchpeaks";
my $OUTPUT_FOLDER = "tests/outputs/matchpeaks";
my $PEAKS1 = "tests/inputs/H3K4me3_chr10.bed";
my $PEAKS2 = "tests/inputs/H3K27me3_chr10.bed";
my $TMP_DATE = "mydate.txt";
my $TMP_STDERR = "mystderr.txt";


## Step 0. Reading arguments
my %opt;
my $verbose;
my $start;
my $date;


(getopts('vwh',\%opt)) or print_error("parser: Problems reading options\n");

if (exists($opt{w}))
{
    $verbose = "-v";
}
else
{
    $verbose = "";
}

# Save the date
$date = get_date();

print_mess("Starting SeqCode test for the $TOOL tool by Enrique Blanco ($date)\n\n");
print_mess("Stage 0.  Reading options");

my $n_files;
$n_files = $#ARGV+1;
($n_files == 0) or print_error("No arguments are required but $n_files are provided!\n");

# Save the starting time
$start = time();

print_help();
print_ok();
##


## Step 1. Running the basic test to check the software is working well (H3K4me3+H3K27me3 peaks)
my $command;
my $n_tests;
my $name;
my ($descriptionA,$descriptionB);
my $file;
my $line;
my $n_lines;


print_mess("Stage 1.  Running the test for H3K4me3-H3K27me3 overlap in mESC (H3K4me3+H3K27me3 peaks, chr10)\n");

# remove previous instance of the folder
$command = "rm -rf $OUTPUT_FOLDER";
system("$command");
# create a new instance of the folder
$command = "mkdir $OUTPUT_FOLDER";
system("$command");

# building the command
$n_tests = 1;
$name = "test_".$n_tests.".txt";
$descriptionA = "test_".$n_tests."A";
$descriptionB = "test_".$n_tests."B";

if ($verbose eq "")
{
    $command = "$PROGRAM -v $PEAKS1 $PEAKS2 $descriptionA $descriptionB 2> $TMP_STDERR";
}
else
{
    $command = "$PROGRAM -v $PEAKS1 $PEAKS2 $descriptionA $descriptionB 2> $TMP_STDERR";
    system("$command");
    $command = "cat $TMP_STDERR";
}
print_mess("$command\n");
system("$command");
# move the results to outputs
$command = "mv test_1A_test_1B_matchpeaks $OUTPUT_FOLDER/";
system("$command");
#
$n_lines = 0;
open(FILE,"$TMP_STDERR") or print_error("File of information 1 cannot be opened\n");
while($line=<FILE>)
{
    if ($line =~ /intersected/)
    {
	if ($n_lines<3)
	{
	    print_mess($line);
	}
	else
	{
	    chomp($line);
	    print_mess($line);
	}
	$n_lines++;
    }
}
close(FILE);
print_ok();
# move the stderr information to outputs
$command = "mv $TMP_STDERR $OUTPUT_FOLDER/test_1A_test_1B_matchpeaks";
system("$command");
#


## Step 2. Running the test to check the software is working well (H3K4me3+H3K27me3 peaks, overlap=1000 bp)


print_mess("Stage 2.  Running the test for H3K4me3-H3K27me3 overlap in mESC (H3K4me3+H3K27me3 peaks, chr10, overlap (at least) = 1000 bp)\n");

# building the command
$n_tests++;
$name = "test_".$n_tests.".txt";
$descriptionA = "test_".$n_tests."A";
$descriptionB = "test_".$n_tests."B";


if ($verbose eq "")
{
    $command = "$PROGRAM -v -l 1000 $PEAKS1 $PEAKS2 $descriptionA $descriptionB 2> $TMP_STDERR";
}
else
{
    $command = "$PROGRAM -v -l 1000 $PEAKS1 $PEAKS2 $descriptionA $descriptionB 2> $TMP_STDERR";
    system("$command");
    $command = "cat $TMP_STDERR";
}
print_mess("$command\n");
system("$command");
# move the results to outputs
$command = "mv test_2A_test_2B_matchpeaks $OUTPUT_FOLDER/";
system("$command");
#
$n_lines = 0;
open(FILE,"$TMP_STDERR") or print_error("File of information 2 cannot be opened\n");
while($line=<FILE>)
{
    if ($line =~ /intersected/)
    {
	if ($n_lines<3)
	{
	    print_mess($line);
	}
	else
	{
	    chomp($line);
	    print_mess($line);
	}
	$n_lines++;
    }
}
close(FILE);
print_ok();
# move the stderr information to outputs
$command = "mv $TMP_STDERR $OUTPUT_FOLDER/test_2A_test_2B_matchpeaks";
system("$command");
#


## Step 3. Finishing successful program execution
my $stop;


print_mess("Stage 3.  Finishing the test ($TOOL)\n");

# Save the ending time
$stop = time();


# confirm the output files exist
check_files();

# final time output
print_mess("Total running time (hours):",int((($stop-$start)/3600)*1000)/1000," hours\n");
print_mess("Total running time (minutes):",int((($stop-$start)/60)*1000)/1000," mins\n");
print_mess("Total running time (seconds):",int(($stop-$start)*1000)/1000," secs\n");
print_mess("Successful termination:");

print_ok();
exit(0);
##


############ Subroutines

sub print_mess
{
        my @mess = @_;

        print STDERR color("bright_yellow"),"%%%% @mess" if (exists($opt{v}) || exists($opt{w}));
	print STDERR color("reset");
}

sub print_error
{
        my @mess = @_;

	print "\n";
        print STDERR color("bright_red"),"%%%% @mess\n[EXIT]\n\n";
	print STDERR color("reset");
	exit();
}

sub print_ok
{
    if (exists($opt{v}) || exists($opt{w}))
    {
	print STDERR color("bold blue"), "\t[DONE]\n\n";
	print STDERR color("reset");
    }
}

sub print_ok_short
{
    if (exists($opt{v}) || exists($opt{w}))
    {
	print STDERR color("bold blue"), "\t[OK]\n";
	print STDERR color("reset");
    }
}

sub print_help
{
    if (exists($opt{h}))
    {
	print STDERR color("bright_yellow"), "\nSEQCODE test (test_matchpeaks.pl):\n\nOPTIONS:\n-v: test verbose mode\n-w: seqcode verbose mode\n\nE.Blanco (2019)\n\n";
	print STDERR color("reset");

        exit(0);
    }

}

sub get_date
{
    my $line;
    my $command;
    my $date;

    
    $command = "date > $TMP_DATE";
    system($command);
    (open(FILE,$TMP_DATE)) or print_error("FILE $TMP_DATE for time data can not be opened");
    while($line=<FILE>)
    {
	chomp($line);
	$date = $line;
    }
    close(FILE);

    $command = "rm -f $TMP_DATE";
    system($command);
    
    return($date);
}

sub check_files
{
    my $file_output;


    # 1
    $file_output = "$OUTPUT_FOLDER/test_1A_test_1B_matchpeaks";
    print_mess("Checking output dir 1: $file_output");
    if (-e $file_output)
    { print_ok_short(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }

    # 2
    $file_output = "$OUTPUT_FOLDER/test_2A_test_2B_matchpeaks";
    print_mess("Checking output dir 2: $file_output");
    if (-e $file_output)
    { print_ok_short(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }
}
