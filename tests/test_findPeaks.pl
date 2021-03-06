#!/usr/bin/perl -w                                 
###################################################
#                                                 #
# Script test_findPeaks.pl                        #
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
my $TOOL = "findPeaks";
my $PROGRAM = "bin/findPeaks";
my $OUTPUT_FOLDER = "tests/outputs/findPeaks";
my $GENOME = "tests/inputs/ChromInfo.txt";
my $READS = "tests/inputs/H3K4me3_sample.bam";
my $READS2 = "tests/inputs/H3_sample.bam";
my $T = 5000;
my $TMP_DATE = "mydate.txt";


## Step 0. Reading arguments
my %opt;
my $verbose;
my $start;
my $date;


(getopts('vwh',\%opt)) or print_error("parser: Problems reading options\n");

# degree of verbosity + working in demo mode (BAM of few reads)
if (exists($opt{w}))
{
    $verbose = "-vd";
}
else
{
    $verbose = "-d";
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

## Step 1. Running the basic test to check the software is working well
my $command;
my $n_tests;
my $name;
my $line;
my $n_peaks;


print_mess("Stage 1.  Running the test for H3K4me3 --chr10:5,774,999-6,225,000 (mm9)-- in mESC (T=10)\n");

# building the command
$n_tests = 1;
$name = "test_".$n_tests;
$command = "$PROGRAM $verbose -t $T $GENOME $READS $name";
print_mess("$command\n");
system("$command");
# remove previous instance of the folder
$command = "rm -rf $OUTPUT_FOLDER";
system("$command");
# create a new instance of the folder
$command = "mkdir $OUTPUT_FOLDER";
system("$command");
# move the results to outputs
$command = "mv test_".$n_tests."_findPeaks/ $OUTPUT_FOLDER/";
system("$command");
#
$command = "gzip -d $OUTPUT_FOLDER/test_1_findPeaks/test_1.bed.gz";
system("$command");

open(FILE,"$OUTPUT_FOLDER/test_1_findPeaks/test_1.bed") or print_error("File of peaks 1 cannot be opened\n");
$n_peaks = 0;
while($line=<FILE>)
{
    $n_peaks++;
}
close(FILE);
$command = "gzip $OUTPUT_FOLDER/test_1_findPeaks/test_1.bed";
system("$command");
print_mess("$n_peaks peaks have been identified");
print_ok();



## Step 2. Running the basic test to check the software is working well (H3)


print_mess("Stage 2.  Running the test for H3 --chr10:5,774,999-6,225,000 (mm9)-- in mESC (T=10)\n");

# building the command
$n_tests++;
$name = "test_".$n_tests;
$command = "$PROGRAM $verbose -t $T $GENOME $READS2 $name\n";
print_mess("$command");
system("$command");
# move the results to outputs
$command = "mv test_".$n_tests."_findPeaks/ $OUTPUT_FOLDER/";
system("$command");
#
$command = "gzip -d $OUTPUT_FOLDER/test_2_findPeaks/test_2.bed.gz";
system("$command");
open(FILE,"$OUTPUT_FOLDER/test_2_findPeaks/test_2.bed") or print_error("File of peaks 2 cannot be opened\n");
$n_peaks = 0;
while($line=<FILE>)
{
    $n_peaks++;
}
close(FILE);
$command = "gzip $OUTPUT_FOLDER/test_2_findPeaks/test_2.bed";
system("$command");
print_mess("$n_peaks peaks have been identified");
print_ok();



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
        print STDERR color("bold bright_red"),"%%%% @mess\n[EXIT]\n\n";
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
	print STDERR color("bright_yellow"), "\nSEQCODE test (test_findPeaks.pl):\n\nOPTIONS:\n-v: test verbose mode\n-w: seqcode verbose mode\n\nE.Blanco (2019)\n\n";
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
    $file_output = "$OUTPUT_FOLDER/test_1_findPeaks/test_1.bed.gz";
    print_mess("Checking output file 1: $file_output");
    if (-e $file_output)
    { print_ok_short(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }

    # 2
    $file_output = "$OUTPUT_FOLDER/test_2_findPeaks/test_2.bed.gz";
    print_mess("Checking output file 2: $file_output");
    if (-e $file_output)
    { print_ok_short(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }

}
