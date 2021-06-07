#!/usr/bin/perl -w                                 
###################################################
#                                                 #
# Script test_recoverChIPlevels.pl                #
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
my $TOOL = "recoverChIPlevels";
my $PROGRAM = "bin/recoverChIPlevels";
my $OUTPUT_FOLDER = "tests/outputs/recoverChIPlevels";
my $GENOME = "tests/inputs/ChromInfo.txt";
my $READS = "tests/inputs/H3K4me3_sample.bam";
my $READS2 = "tests/inputs/H3_sample.bam";
my $PEAKS1 = "tests/inputs/H3K4me3_mESC_sample.bed";
my $PEAKS2 = "tests/inputs/H3K27me3_mESC_sample.bed";
my $TMP_DATE = "mydate.txt";
my $R2PLOTS = "tests/inputs/Rscript_recoverChIPlevels.txt";


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


## Step 1. Running the basic test to check the software is working well (MAX, H3K4me3, H3K4me3 peaks)
my $command;
my $n_tests;
my $name;


print_mess("Stage 1.  Running the test for H3K4me3 --chr10:5,774,999-6,225,000 (mm9)-- in mESC (MAX, H3K4me3, H3K4me3 peaks)\n");

# building the command
$n_tests = 1;
$name = "test_".$n_tests;
$command = "$PROGRAM $verbose -n $GENOME $READS $PEAKS1 $name";
print_mess("$command");
system("$command");
# remove previous instance of the folder
$command = "rm -rf $OUTPUT_FOLDER";
system("$command");
# create a new instance of the folder
$command = "mkdir $OUTPUT_FOLDER";
system("$command");
# move the results to outputs
$command = "mv test_".$n_tests."_recoverChIPlevels/ $OUTPUT_FOLDER/";
system("$command");
print_ok();


## Step 2. Running the basic test to check the software is working well (MAX, H3K4me3, H3K27me3 peaks)


print_mess("Stage 2.  Running the test for H3K4me3 --chr10:5,774,999-6,225,000 (mm9)-- in mESC (MAX, H3K4me3, H3K27me3 peaks)\n");

# building the command
$n_tests++;
$name = "test_".$n_tests;
$command = "$PROGRAM $verbose -n $GENOME $READS $PEAKS2 $name";
print_mess("$command");
system("$command");
# move the results to outputs
$command = "mv test_".$n_tests."_recoverChIPlevels/ $OUTPUT_FOLDER/";
system("$command");
print_ok();


## Step 3. Running the basic test to check the software is working well (MAX, H3, H3K4me3 peaks)


print_mess("Stage 3.  Running the test for H3 --chr10:5,774,999-6,225,000 (mm9)-- in mESC (MAX, H3, H3K4me3 peaks)\n");

# building the command
$n_tests++;
$name = "test_".$n_tests;
$command = "$PROGRAM $verbose -n $GENOME $READS2 $PEAKS1 $name";
print_mess("$command");
system("$command");
# move the results to outputs
$command = "mv test_".$n_tests."_recoverChIPlevels/ $OUTPUT_FOLDER/";
system("$command");
print_ok();


## Step 4. Running the basic test to check the software is working well (MAX, H3, H3K27me3 peaks)


print_mess("Stage 4.  Running the test for H3 --chr10:5,774,999-6,225,000 (mm9)-- in mESC (MAX, H3, H3K27me3 peaks)\n");

# building the command
$n_tests++;
$name = "test_".$n_tests;
$command = "$PROGRAM $verbose -n $GENOME $READS2 $PEAKS2 $name";
print_mess("$command");
system("$command");
# move the results to outputs
$command = "mv test_".$n_tests."_recoverChIPlevels/ $OUTPUT_FOLDER/";
system("$command");
print_ok();

# generating a boxplot with 2 samples
$command = "R CMD BATCH $R2PLOTS";
print_mess("$command");
system("$command");
$command = "rm -f *Rout";
system("$command");
print_ok();


## Step 5. Finishing successful program execution
my $stop;


print_mess("Stage 5.  Finishing the test ($TOOL)\n");

# Save the ending time
$stop = time();


# confirm the PDF output files exist
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
	print STDERR color("bright_yellow"), "\nSEQCODE test (test_recoverChIPlevels.pl):\n\nOPTIONS:\n-v: test verbose mode\n-w: seqcode verbose mode\n\nE.Blanco (2019)\n\n";
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
    $file_output = "$OUTPUT_FOLDER/test_1_recoverChIPlevels/PEAKsignal_test_1.bed";
    print_mess("Checking output file 1: $file_output");
    if (-e $file_output)
    { print_ok_short(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }

    # 2
    $file_output = "$OUTPUT_FOLDER/test_2_recoverChIPlevels/PEAKsignal_test_2.bed";
    print_mess("Checking output file 2: $file_output");
    if (-e $file_output)
    { print_ok_short(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }

    # 3
    $file_output = "$OUTPUT_FOLDER/test_3_recoverChIPlevels/PEAKsignal_test_3.bed";
    print_mess("Checking output file 3: $file_output");
    if (-e $file_output)
    { print_ok_short(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }

    # 4
    $file_output = "$OUTPUT_FOLDER/test_4_recoverChIPlevels/PEAKsignal_test_4.bed";
    print_mess("Checking output file 4: $file_output");
    if (-e $file_output)
    { print_ok_short(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }

    # 4 (R2plots)
    $file_output = "$OUTPUT_FOLDER/recoverChIPlevels.pdf";
    print_mess("Checking output file 4 (2): $file_output");
    if (-e $file_output)
    { print_ok(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }
}
