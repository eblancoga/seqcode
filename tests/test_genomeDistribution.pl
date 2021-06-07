#!/usr/bin/perl -w                                 
###################################################
#                                                 #
# Script test_genomeDistribution.pl               #
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
my $TOOL = "genomeDistribution";
my $PROGRAM = "bin/genomeDistribution";
my $OUTPUT_FOLDER = "tests/outputs/genomeDistribution";
my $GENOME = "tests/inputs/ChromInfo.txt";
my $GENES = "tests/inputs/refGene_sample.txt";
my $PEAKS1 = "tests/inputs/H3K4me3_mESC_sample.bed";
my $PEAKS2 = "tests/inputs/H3K27me3_mESC_sample.bed";
my $TMP_DATE = "mydate.txt";


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


## Step 1. Running the basic test to check the software is working well
my $command;
my $n_tests;
my $name;


print_mess("Stage 1.  Running the test for H3K4me3 in mESC (default plot)\n");

# building the command
$n_tests = 1;
$name = "test_".$n_tests;
$command = "$PROGRAM $verbose $GENOME $GENES $PEAKS1 $name";
print_mess("$command");
system("$command");
# remove previous instance of the folder
$command = "rm -rf $OUTPUT_FOLDER";
system("$command");
# create a new instance of the folder
$command = "mkdir $OUTPUT_FOLDER";
system("$command");
# move the results to outputs
$command = "mv test_".$n_tests."_GENOMEchart/ $OUTPUT_FOLDER/";
system("$command");
print_ok();


## Step 2. Running the basic test to check the software is working well

print_mess("Stage 2.  Running the test for H3K27me3 in mESC (default plot)\n");

# building the command
$n_tests++;
$name = "test_".$n_tests;
$command = "$PROGRAM $verbose $GENOME $GENES $PEAKS2 $name";
print_mess("$command");
system("$command");
# move the results to outputs
$command = "mv test_".$n_tests."_GENOMEchart/ $OUTPUT_FOLDER/";
system("$command");
print_ok();


## Step 3. Generate the detailed view

print_mess("Stage 3.  Running the test for H3K4me3 in mESC (detailed plot)\n");

# building the command
$n_tests++;
$name = "test_".$n_tests;
$command = "$PROGRAM $verbose -d $GENOME $GENES $PEAKS1 $name";
print_mess("$command");
system("$command");
# move the results to outputs
$command = "mv test_".$n_tests."_GENOMEchart/ $OUTPUT_FOLDER/";
system("$command");
print_ok();


## Step 4. Generate the detailed view and test the gradient of colors

print_mess("Stage 4.  Running the test for H3K4me3 in mESC (detailed plot + gradient colors)\n");

# building the command
$n_tests++;
$name = "test_".$n_tests;
$command = "$PROGRAM $verbose -d -1 darkred -g $GENOME $GENES $PEAKS1 $name";
print_mess("$command");
system("$command");
# move the results to outputs
$command = "mv test_".$n_tests."_GENOMEchart/ $OUTPUT_FOLDER/";
system("$command");
print_ok();


## Step 5. Generate the basic view and test one set of colors

print_mess("Stage 5.  Running the test for H3K4me3 in mESC (default plot + three colors)\n");

# building the command
$n_tests++;
$name = "test_".$n_tests;
$command = "$PROGRAM $verbose -1 salmon -2 cornflowerblue -3 chartreuse3 $GENOME $GENES $PEAKS1 $name";
print_mess("$command");
system("$command");
# move the results to outputs
$command = "mv test_".$n_tests."_GENOMEchart/ $OUTPUT_FOLDER/";
system("$command");
print_ok();


## Step 6. Generate the detailed view and test one set of colors

print_mess("Stage 6.  Running the test for H3K4me3 in mESC (detailed plot + seven colors)\n");

# building the command
$n_tests++;
$name = "test_".$n_tests;
$command = "$PROGRAM $verbose -d -1 salmon -2 cornflowerblue -3 chartreuse3 -4 violet -5 skyblue -6 grey -7 white $GENOME $GENES $PEAKS1 $name";
print_mess("$command");
system("$command");
# move the results to outputs
$command = "mv test_".$n_tests."_GENOMEchart/ $OUTPUT_FOLDER/";
system("$command");
print_ok();


## Step 7. Generate the promoter view (flanking area: 2500 bp)

print_mess("Stage 7.  Running the test for H3K4me3 in mESC (detailed plot + promoter view, 2.5 Kbp around TSS)\n");

# building the command
$n_tests++;
$name = "test_".$n_tests;
$command = "$PROGRAM $verbose -s 2500 $GENOME $GENES $PEAKS1 $name";
print_mess("$command");
system("$command");
# move the results to outputs
$command = "mv test_".$n_tests."_GENOMEchart/ $OUTPUT_FOLDER/";
system("$command");
print_ok();


## Step 8. Generate the promoter view (flanking area: 500 bp)

print_mess("Stage 8.  Running the test for H3K4me3 in mESC (detailed plot + promoter view, 0.5 Kbp around TSS)\n");

# building the command
$n_tests++;
$name = "test_".$n_tests;
$command = "$PROGRAM $verbose -s 500 $GENOME $GENES $PEAKS1 $name";
print_mess("$command");
system("$command");
# move the results to outputs
$command = "mv test_".$n_tests."_GENOMEchart/ $OUTPUT_FOLDER/";
system("$command");
print_ok();


## Step 9. Finishing successful program execution
my $stop;


print_mess("Stage 9.  Finishing the test ($TOOL)\n");

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
	print STDERR color("bright_yellow"), "\nSEQCODE test (test_genomeDistribution.pl):\n\nOPTIONS:\n-v: test verbose mode\n-w: seqcode verbose mode\n\nE.Blanco (2019)\n\n";
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
    $file_output = "$OUTPUT_FOLDER/test_1_GENOMEchart/PlotGENOMEchart_test_1.pdf";
    print_mess("Checking output file 1: $file_output");
    if (-e $file_output)
    { print_ok_short(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }

    # 2
    $file_output = "$OUTPUT_FOLDER/test_2_GENOMEchart/PlotGENOMEchart_test_2.pdf";
    print_mess("Checking output file 2: $file_output");
    if (-e $file_output)
    { print_ok_short(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }

    # 3
    $file_output = "$OUTPUT_FOLDER/test_3_GENOMEchart/PlotGENOMEchart_test_3.pdf";
    print_mess("Checking output file 3: $file_output");
    if (-e $file_output)
    { print_ok_short(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }

    # 4
    $file_output = "$OUTPUT_FOLDER/test_4_GENOMEchart/PlotGENOMEchart_test_4.pdf";
    print_mess("Checking output file 4: $file_output");
    if (-e $file_output)
    { print_ok_short(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }

    # 5
    $file_output = "$OUTPUT_FOLDER/test_5_GENOMEchart/PlotGENOMEchart_test_5.pdf";
    print_mess("Checking output file 5: $file_output");
    if (-e $file_output)
    { print_ok_short(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }

    # 6
    $file_output = "$OUTPUT_FOLDER/test_6_GENOMEchart/PlotGENOMEchart_test_6.pdf";
    print_mess("Checking output file 6: $file_output");
    if (-e $file_output)
    { print_ok_short(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }

    # 7
    $file_output = "$OUTPUT_FOLDER/test_7_GENOMEchart/PlotGENOMEchart_test_7.pdf";
    print_mess("Checking output file 7: $file_output");
    if (-e $file_output)
    { print_ok_short(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }

    # 8
    $file_output = "$OUTPUT_FOLDER/test_8_GENOMEchart/PlotGENOMEchart_test_8.pdf";
    print_mess("Checking output file 8: $file_output");
    if (-e $file_output)
    { print_ok(); }
    else
    { print_error("$file_output is not found. Check the verbose output for errors"); }
}
