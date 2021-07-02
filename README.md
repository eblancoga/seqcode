# README of SeqCode v 1.0 

Enrique Blanco, Mar Gonzalez-Ramirez and Luciano Di Croce (CRG, 2013-2021)

`enrique.blanco at crg.eu`

## Table of Contents
1. What is SeqCode?
2. SeqCode Command Line
3. SeqCode Web Tools
4. How to Cite


## 1. What is SeqCode?

SeqCode is a family of applications designed to develop high-quality images and perform genome-wide calculations from 
high-throughput sequencing experiments. This software is presented into two distinct modes: web tools and command line. The 
website of SeqCode offers most functions to users with no previous expertise in bioinformatics, including operations on a 
selection of published ChIP-seq samples and applications to generate multiple classes of graphics from data files of the 
user. On the contrary, the standalone version of SeqCode allows bioinformaticians to run each command on any type of 
sequencing data locally in their computer. The architecture of the source code is modular and the input/output interface of 
the commands is suitable to be integrated into existing pipelines of genome analysis. SeqCode has been written in ANSI C, 
which favors the compatibility in every UNIX platform and grants a high performance and speed when analyzing sequencing 
data. Meta-plots, heatmaps, boxplots and the rest of images produced by SeqCode are internally generated using R. SeqCode 
relies on the RefSeq reference annotations and is able to deal with the genome and assembly release of every organism that 
is available from this consortium.

The SeqCode source code is accessible from GitHub at: https://github.com/eblancoga/seqcode

The SeqCode web tools are available at: http://ldicrocelab.crg.es

Selection of most relevant SeqCode applications:

* Generate profiles of sequencing data for genome browser visualizations
* Calculate the distribution of genome features from a set of genomic coordinates
* Match genomic coordinates to genes based in any catalog of RefSeq transcript annotations
* Produce high-quality aggregated plots centered around TSS, TES, TSS-TES and peak centers
* Produce heatmaps of sequencing signal intensities around TSS, TES, TSS-TES and peak centers
* Calculate the count of reads of one sequencing experiment on a set of regions
* Compare two sets of peaks or genomic regions to determine the degree of overlap between them
* Calculate the evolutionary conservation score on a set of genomic regions
* Introduce spike-in values to normalize most genome-wide analysis
* Generate boxplots with multiple graphical options to customize the final result
* Perform PCA plots, scatter-plots and heatmaps of genes based on expression or signal values
* Produce Venn diagrams for multiple sets of elements and UpSet charts
* Basic operations on lists of elements such as join, filter and fold-change analysis


## 2. SeqCode Command Line

SeqCode source code entirely written in ANSI C is freely distributed. This software is provided with a Makefile 
to generate each application as a separate binary file that runs in UNIX command line interfaces following the 
basic standards in terms of interface design and output formats. Most programs require the user to provide two files 
for the particular genome that is being analyzed: the list of chromosomes (and their sizes) and the RefSeq gene 
transcript annotations. Both files can be easily retrieved for every particular genome assembly from the UCSC 
genome browser. Commands working with sequencing data require the user to provide the mapped reads of the experiment 
(BAM or SAM format). SeqCode commands offer the verbose option (-v) to inform on the screen about the basic steps of 
the procedure. Most commands will generate a new folder containing the final results of the particular running. By 
default, this folder will be created in the working directory, although another path to save the otuput can be defined 
with the prefix option (-x). Users can customize most programs using multiple options (please, check the manual 
of each one with the option -h). Graphical outputs are produced by running R scripts that will be stored in the resulting 
folder as well. The command line release of SeqCode has no limits or restrictions in the set or the size of the input 
files that will be processed locally in the computer of the user (differently from the website that is intended to be a 
teaching resource to show the distinct modes of showing sequencing information plots).

### SETUP

#### List of Files and Folders

SeqCode source code is entirely written in ANSI C. It also integrates the source code of the 
[SAMTools in C](http://samtools.sourceforge.net/samtools-c.shtml) to read SAM/BAM files (which 
includes the BCFtools, the SAMtools and the HTSlib).

The latest full distribution release can be downloaded from GitHub:

    https://github.com/eblancoga/seqcode

This is the current list of archives and folders:

* README:
General description of the software and basic instructions to run SeqCode in your computer.
* LICENSE:
Open software license (GPL version 2.0/3.0).
* Makefile:
List of rules to make the binaries of SeqCode applications.
* bin/:
Binary files to execute SeqCode applications.
* include/:
Headers and basic definitions for the source code.
* objects/:
Objects resulting from the make compilation.
* tests/:
Perl scripts to test the SeqCode binaries were successfully generated with real examples.
* src/:
SeqCode and SAMtools (BCFtools and HTSlib) source code. 

#### How to Install SeqCode

Please, run the Makefile for automatically generating the SAMtools libraries and the SeqCode binaries. 
Type `make all` to generate the set of SeqCode binary archives, which will be stored at the bin/ folder.

    > make all
    ***** Step 1. Building the CRAM library           *****
    gcc  -c -I./include -O2 -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -D_CURSES_LIB=1 ./src/cram/cram_codecs.c -o ./objects/cram/cram_codecs.o
    (...)
    ***** [OK] CRAM library sucessfully generated     *****

    ***** Step 2. Building the HTSLIB library         *****
    gcc  -c -I./include -O2 -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -D_CURSES_LIB=1 ./src/htslib/bgzf.c -o ./objects/htslib/bgzf.o
    (...)
    ***** [OK] HTSLIB library sucessfully generated   *****

    ***** Step 3. Building the SAMTOOLS library       *****
    gcc  -c -I./include -O2 -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -D_CURSES_LIB=1 ./src/samtools/bam_aux.c -o ./objects/samtools/bam_aux.o
    (...)
    ***** [OK] SAMTOOLS library sucessfully generated *****

    ***** Step 4. Building the SeqCode suite          *****
    gcc  -c -I./include -O2 -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -D_CURSES_LIB=1 ./src/seqcode/buildChIPprofile.c -o ./objects/seqcode/buildChIPprofile.o (...)
    ***** [OK] SeqCode suite successfully generated   *****

Depending on the user platform, some warning messages on the pthread library could be visualized when 
compiling the SAMtools. These messages can be safely skipped, not affecting the SeqCode applications. 
It is possible to delete previous SeqCode binaries by typing 'make clean'. Once generated, binaries can 
be integrated in the running path of your computer.

#### Testing SeqCode: scripts, inputs and outputs

The tests/ folder contain a series of Perl scripts to test the correct functioning of each SeqCode command:

      > ls tests/
      inputs
      outputs
      test_buildChIPprofile.pl
      test_combineChIPprofiles.pl
      test_combineTSSplots.pl
      test_findPeaks.pl
      test_genomeDistribution.pl
      test_matchpeaksgenes.pl
      test_matchpeaks.pl
      test_produceGENEmaps.pl
      test_produceGENEplots.pl
      test_producePEAKmaps.pl
      test_producePEAKplots.pl
      test_produceTSSmaps.pl
      test_produceTSSplots.pl
      test_recoverChIPlevels.pl

Each test can be executed with the option -v to see the messages of basic information:

      > ./tests/test_produceTSSmaps.pl -v

      %%%% Starting SeqCode test for the produceTSSmaps tool by Enrique Blanco (Sun Aug 18 12:18:42 CEST 2019)

      %%%% Stage 0.  Reading options	[DONE]

      %%%% Stage 1.  Running the test for H3K4me3 --chr10-- in mESC (default plot)
      %%%% bin/produceTSSmaps  tests/inputs/ChromInfo.txt tests/inputs/refGene.txt tests/inputs/H3K4me3_chr10.bam tests/inputs/genes_chr10.txt test_1 5000	[DONE]

      %%%% Stage 2.  Running the test for H3K4me3 --chr10-- in mESC (lower resolution)
      %%%% bin/produceTSSmaps  -w 1000 tests/inputs/ChromInfo.txt tests/inputs/refGene.txt tests/inputs/H3K4me3_chr10.bam tests/inputs/genes_chr10.txt test_2 5000	[DONE]

      %%%% Stage 3.  Running the test for H3K4me3 --chr10-- in mESC (one gene, default plot)
      %%%% bin/produceTSSmaps  tests/inputs/ChromInfo.txt tests/inputs/refGene.txt tests/inputs/H3K4me3_chr10.bam tests/inputs/10genes.txt test_3 5000	[DONE]

      %%%% Stage 4.  Running the test for H3K4me3 --chr10-- in mESC (another color scheme)
      %%%% bin/produceTSSmaps  -b black -B black -H black -f darkgoldenrod1 -F darkgoldenrod1 tests/inputs/ChromInfo.txt tests/inputs/refGene.txt tests/inputs/H3K4me3_chr10.bam tests/inputs/genes_chr10.txt test_4 5000	[DONE]

      %%%% Stage 5.  Running the test for H3K4me3 --chr10-- in mESC (noise reduction plot)
      %%%% bin/produceTSSmaps  -t 0 tests/inputs/ChromInfo.txt tests/inputs/refGene.txt tests/inputs/H3K4me3_chr10.bam tests/inputs/genes_chr10.txt test_5 5000	[DONE]

      %%%% Stage 6.  Running the test for H3K4me3 --chr10-- in mESC (noise reduction plot 2)
      %%%% bin/produceTSSmaps  -t 2 tests/inputs/ChromInfo.txt tests/inputs/refGene.txt tests/inputs/H3K4me3_chr10.bam tests/inputs/genes_chr10.txt test_6 5000	[DONE]

      %%%% Stage 7.  Running the test for H3 --chr10-- in mESC (default plot)
      %%%% bin/produceTSSmaps  tests/inputs/ChromInfo.txt tests/inputs/refGene.txt tests/inputs/H3_chr10.bam tests/inputs/genes_chr10.txt test_7 5000	[DONE]

      %%%% R CMD BATCH tests/inputs/Rscript_produceTSSmaps.txt	[DONE]

      %%%% Stage 7.  Finishing the test (produceTSSmaps)
      %%%% Checking output file 1: tests/outputs/produceTSSmaps/test_1_TSSmap_5000/PlotHEATmap_test_1_5000.pdf	[OK]
      %%%% Checking output file 2: tests/outputs/produceTSSmaps/test_2_TSSmap_5000/PlotHEATmap_test_2_5000.pdf	[OK]
      %%%% Checking output file 3: tests/outputs/produceTSSmaps/test_3_TSSmap_5000/PlotHEATmap_test_3_5000.pdf	[OK]
      %%%% Checking output file 4: tests/outputs/produceTSSmaps/test_4_TSSmap_5000/PlotHEATmap_test_4_5000.pdf	[OK]
      %%%% Checking output file 5: tests/outputs/produceTSSmaps/test_5_TSSmap_5000/PlotHEATmap_test_5_5000.pdf	[OK]
      %%%% Checking output file 6: tests/outputs/produceTSSmaps/test_6_TSSmap_5000/PlotHEATmap_test_6_5000.pdf	[OK]
      %%%% Checking output file 7: tests/outputs/produceTSSmaps/test_7_TSSmap_5000/PlotHEATmap_test_7_5000.pdf	[OK]
      %%%% Checking output file 7 (2): tests/outputs/produceTSSmaps/produceTSS2maps.pdf	[DONE]

      %%%% Total running time (hours): 0.012  hours
      %%%% Total running time (minutes): 0.766  mins
      %%%% Total running time (seconds): 46  secs
      %%%% Successful termination:	[DONE]

### USAGE

SeqCode is designed to run under command-line platforms. Command-line interfaces are running environments where the 
user interacts with the computer by introducing text commands. SeqCode is able to run under Linux and Mac OS-X operating 
systems through the command-line interface of the Terminal (the shell). The final behavior of such programs can be 
configured by adding options using the symbol '-' plus the character defining such an option. The output of the program 
is usually stored into an output folder in which the user will find the resulting plots, the scripts to generate the 
plots in R (if any), and the data files. The precise location of the output folder in the path can be customized with 
the option -x (prefix). 

This is the prototype of a SeqCode call from the Terminal (the final format will depend on each SeqCode program):

      > SeqCode_command -options input_file1 ... input_fileN OutputFolderName

This is the full list of options for the command buildChIPprofile:

      > bin/buildChIPprofile -h
      
      SeqCode_v1.0             User commands            buildChIPprofile

      NAME
	    buildChIPprofile -
         a program to generate genome-wide ChIPseq/ATACseq/RNAseq profiles for genome browser visualization.

      SYNOPSIS
	    buildChIPprofile [-c <Rcolor>][-d][-l <bp>][-m][-p][-s <reads>][-w <bp>][-v][-x prefix][-h]
	    <chrom_info> <SAM file> <name>

      OUTPUT
	      One folder with one file:
	      - BedGraph profile (compressed).

      OPTIONS
	      -c : Track color (default: black).
	      -d : Demo mode for small BAM files (min number reads control off).
	      -l : Avg. fragment size (default: 150).
	      -m : Invert the score of BedGraph records.
	      -p : Using pair-end reads mapped in proper pair (default: single-end).
	      -s : Number of spike-in reads for reference-adjusted normalization.
	      -w : Window resolution (default: 100).
	      -v : Verbose. Display info messages.
	      -x : Prefix for the output folder.
	      -h : Show this help.

      SEE ALSO
	      SeqCode homepage: http://ldicrocelab.crg.es
	      GitHub source code: https://github.com/eblancoga/seqcode

      AUTHORS
	      Written by Enrique Blanco.

      SeqCode_v1.0            User commands            buildChIPprofile

### LIST OF COMMANDS

Command | Description
--------|-------------
`buildChIPprofile` | generate sequencing data profiles for genome browser visualization.
`combineChIPprofiles` | combine two genome-wide sequencing data profiles.
`combineTSSmaps` | produce heatmaps of sequencing signal intensities from 2 samples around the TSS.
`combineTSSplots` | produce averaged meta-plots of sequencing signal intensities from 2 samples around the TSS.
`computemaxsignal` | calculate the max signal for genes in one genome-wide profile.
`findPeaks` |  find peaks in sequencing data.
`genomeDistribution` | examine the distribution of peaks within distinct genomic features.
`matchpeaks` | compare 2 lists of peaks/regions.
`matchpeaksgenes` | match peaks to genes.
`processmacs` | clean MACS BedGraph profiles.
`produceGENEmaps` | produce heatmaps of sequencing signal intensities along a meta-gene representation.
`produceGENEplots` | produce averaged smeta-plots of sequencing signal intensities along a normalized gene.
`producePEAKmaps` |  produce heatmaps of sequencing signal intensities centered in a list of peaks.
`producePEAKplots` | produce averaged meta-plots of sequencing signal intensities centered in a list of peaks.
`produceTESmaps` | produce heatmaps of sequencing signal intensities around the TES.
`produceTESplots` | produce averaged meta-plots of sequencing signal intensities around the TES.
`produceTSSmaps` | produce heatmaps of sequencing signal intensities around the TSS.
`produceTSSplots` | produce averaged meta-plots of sequencing signal intensities around the TSS.
`recoverChIPlevels` | determine the avg/max/total counts of reads in a list of regions.
`scorePhastCons`  | score genomic regions with PhastCons conservation values.

### DATA FORMATS

#### Chromosome Files

SeqCode defines the content of the genome from one file containing the name and the size of the chromosomes of the 
organism. The UCSC genome browser provides this information through the Downloads section for each genome (Annotation 
database link). Thus, users can retrieve the corresponding chromInfo.txt file for the appropriate organism. For example, 
the mouse file (mm9) is accessible from http://hgdownload.soe.ucsc.edu/goldenPath/mm9/database/chromInfo.txt.gz. These 
files must be uncompressed previously to be used with SeqCode and the name of alternative contigs (e.g. chr13_random) 
can be dismissed into the final archive.

#### Gene Models: refGene.txt

SeqCode uses the gene transcript annotations provided by the RefSeq consortium to define the location of genomic features 
on virtually any genome that is served by this project. The UCSC genome browser provides this information through the 
Downloads section for each genome (Annotation database link). Thus, users can retrieve the corresponding refGene.txt.gz 
file for the appropriate organism. For example, the mouse file (mm9) is accessible from 
http://hgdownload.soe.ucsc.edu/goldenPath/mm9/database/refGene.txt.gz. Such files must be uncompressed previously to be 
used with SeqCode (e.g. gzip -d refGene.txt.gz).

#### Sequencing reads: SAM/BAM formats

SeqCode mainly analyzes the set of mapped reads of a sequencing experiment (e.g. ChIPseq/RNAseq/ATACseq) in SAM format. 
This file format contains one line per read that is mapped, containing the location in the genome for such a read. BAM
files, which are the compressed version of SAM files, can be also provided to SeqCode. For further information, users 
can access the SAM format documentation at https://samtools.github.io/hts-specs/SAMv1.pdf.

#### BED and BedGraph formats

The location of ChIPseq peaks or any other genomic feature can be easily represented using the BED format (Browser 
Extensible Data, see the UCSC documentation for further information). In the simplest version of this format, each line 
in these files contains 4 columns: chromosome, initial position, ending position and (optionally) a name for identifying 
this element.

SeqCode generates custom tracks for visualization in genome browsers using the BedGraph format. With this format, it is 
possible to produce distribution functions to map the location of high-throughput experiments or other features along the 
chromosomes (more information on the UCSC genome browser documentation). Basically, it is derived from the BED format by 
adding a number in the 4th column to define the height of the profile in that region.


## 3. SeqCode Web Tools

The SeqCode website offers multiple applications for the analysis of genomic data. The services are basically divided 
into: (i) SeqCode tools for the generation of graphical results from large-scale sequencing samples (NGS tools), and 
(ii) general-purpose functions (Data Sets, Gene Sets and List Ops) for the analysis of lists of genes and other elements 
that are not part of the command line core distribution.

The SeqCode web tools are available at: http://ldicrocelab.crg.es

Please, check the following link for further information on our set of web functions:

* Tutorials with practical examples preloaded and ready to be executed:
  [TUTORIALS](http://ldicrocelab.crg.es/05_Docs/webtools/tutorials.php)

Users can provide their own data file to run the following list of services with no restrictions:

* Calculate the distribution of human/mouse genome features from a set of genomic regions.
* Match genomic regions to genes based in human/mouse RefSeq transcript annotations.
* Compare two sets of peaks or genomic regions to determine the degree of overlap.
* Generate boxplots with multiple graphical options to customize the final result.
* Perform PCA plots, scatter plots and heatmaps of genes based on expression or signal values.
* Produce Venn diagrams for multiple sets of elements and UpSet charts.
* Basic operations on lists of elements such as join, filter and fold-change analysis.

The rest of functions are offered in our web site for a preselected list of ChIP-seq experiments:

* Generate profiles of sequencing data for genome browser visualizations.
* Produce high-quality aggregated plots centered around TSS, TES, TSS-TES and peak centers.
* Produce heatmaps of sequencing signal intensities around TSS, TES, TSS-TES and peak centers.
* Calculate the count of reads of one sequencing experiment on a set of regions.

The SeqCode full distribution of commands from GitHub can be locally run with no file size restrictions.


## 4. Virtualizations of SeqCode

Full distribution of SeqCode (source code and binaries) is also available for VirtualBox and Docker:

* VirtualBox appliance: http://ldicrocelab.crg.eu/06_Downloads/vmachines/index.php
* Docker container: http://ldicrocelab.crg.eu/06_Downloads/docker/index.php


## 5. How to Cite SeqCode

### Principal Citation

Please, cite the following reference when using one or more components of the SeqCode suite of software:

Productive visualization of high-throughput sequencing data using the SeqCode open portable platform.
E. Blanco, M. Gonzalez-Ramirez and L. Di Croce. 
JOURNAL (2021).

### SeqCode in the literature

* Polycomb factor Phf19 controls cell growth and differentiation towards erythroid pathway in chronic myeloid leukemia 
cells. M. García-Montolio, C. Ballare, E. Blanco, A. Gutierrez, S. Aranda, A. Gomez, C.H. Kok, D. Yeung, T.P. Hughes, 
P. Vizan and L. Di Croce. Cell and Developmental Biology 9:655201 (2021).

* Neuron type-specific increase in lamin B1 contributes to nuclear dysfunction in Huntington’s disease. R. Alcala-Vida*, 
M. Garcia-Forn*, C. Castany-Pladevall, J. Creus-Muncunill, Y. Ito, E. Blanco, A. Golbano, K. Crespí-Vázquez, A. Parry, 
G. Slater, S. Samarajiwa, S. Peiró, L. Di Croce, M. Narita and E. Pérez-Navarro. EMBO Molecular Medicine 13:e12105 (2021).

* RING1B recruits EWSR1-1 FLI1 and cooperates in the remodeling of chromatin necessary for Ewing sarcoma tumorigenesis. 
S. Sanchez-Molina, E. Figuerola-Bou, E. Blanco, M. Sanchez-Jimenez, P. Taboas, S. Gomez, C. Ballare, D.J. Garcia-Dominguez, 
E. Prada, L. Hontecillas-Prieto, A. Montero-Carcaboso, O. Tirado, I. Hernandez-Muñoz, E. de Alava, C. Lavarino, L. Di Croce 
and J. Mora. Science Advances 6: eaba3058 (2020).

*  The Polycomb-Associated Factor Phf19 Controls Hematopoietic Stem Cell State and Differentiation. P. Vizan*, 
A. Gutierrez*, I. Espejo, M. García-Montolio, M. Lange, A. Carretero, A. Lafzi, L. de Andrés-Aguayo, E. Blanco, 
R. Thambyrajah, T. Graf, H. Heyn, A. Bigas, L. Di Croce. Science Advances 6:eabb2745 (2020).

* Trans-generational epigenetic regulation associated with the amelioration of Duchenne Muscular Dystrophy. J. Martone, 
M. Lisi, F. Castagnetti, A. Rosa, V. Di Carlo, E. Blanco, A. Setti,D. Mariani, A. Colantoni, T. Santini, L. Di Croce and 
I. Bozzoni. EMBO Molecular Medicine e12063 (2020).

* PHF19 mediated regulation of proliferation and invasiveness in prostate cancer cells. P. Jain, C. Ballare, E, Blanco, 
P. Vizan and L. Di Croce. Elife 9:e51373 (2020).

* The Bivalent Genome: Characterization, Structure, and Regulation. E. Blanco, M. González-Ramírez, A. Alcaine-Colet, 
S. Aranda and L. Di Croce. Trends in Genetics 36:118-131 (2020).

* GATA2 Promotes Hematopoietic Development and Represses Cardiac Differentiation of Human Mesoderm. J. Castaño, S. Aranda, 
C. Bueno, F.J. Calero-Nieto, E. Mejia-Ramirez, J.L. Mosquera, E. Blanco, X. Wang, C. Prieto, L. Zabaleta, E. Mereu, M. Rovira, 
S. Jimenez-Delgado, D.R. Matson, H. Heyn, E.H. Bresnick, B. Gottgens, L. Di Croce, P. Menendez, A. Raya and A. Giorgetti. 
Stem Cell Reports 13:515-529 (2019).
 
* Chromatin capture links the metabolic enzyme AHCY to stem cell proliferation. S. Aranda, A. Alcaine-Colet, E. Blanco, 
E. Borras, C. Caillot, E. Sabido and L. Di Croce. Science Advances 5:3 (2019).

*  Promoter bivalency favors an open chromatin architecture in embryonic stem cells. G. Mas, E. Blanco, C. Ballare, 
M. Sanso, Y. Spill, D. Hu, Y. Aoi, F. Le Dily, A. Shilatifard, M. A. Marti-Renom and L. Di Croce. Nature Genetics 
50:1452 (2018).

* Lamin B1 mapping reveals the existence of dynamic and functional euchromatin lamin B1 domains. L. Pascual-Reguant, 
E. Blanco, S. Galan, F. Le Dily, Y. Cuartero, G. Serra-Bardenys, V. Di Carlo, A. Iturbide, J.P. Cebrià-Costa, L. Nonell, 
A. Garcia de Herreros, L. Di Croce, M. Marti-Renom and S. Peiro. Nature Communications 9:3420 (2018).

*  The Polycomb group protein CBX6 is an essential regulator of embryonic stem cell identity. A. Santanach, E. Blanco, 
H. Jiang, K.R. Molloy, M. Sansó, J. LaCava, L. Morey and Luciano Di Croce. Nature Communications 8: 1235 (2017).

*  EPOP Functionally Links Elongin and Polycomb in Pluripotent Stem Cells. M. Beringer, P. Pisano, V. Di Carlo, E. Blanco, 
Paul Chammas, P. Vizan, A. Gutierrez, S. Aranda, B. Payer, M. Wierer and L. Di Croce. Molecular Cell 64:645-658 (2016).

*  Polycomb Regulates Mesoderm Cell Fate-Specification in Embryonic Stem Cells through Activation and Repression Mechanisms. 
L. Morey, A. Santanach, E. Blanco, L. Aloia, E. Nora, B. Bruneau and L. Di Croce. Cell Stem Cell 17:300-315 (2015).

### About Us

Our lab is focused on the role of multiple epigenetic components (such as histone marks and Polycomb proteins) that govern 
the development in mouse embryonic stem cells and can be involved in the context of cancer as well. We have designed SeqCode 
in order to appropriately interpret the huge volume of information generated through genome-wide analysis based on ChIPseq, 
RNAseq or ATACseq in our group.

[WEBSITE](http://www.crg.eu/en/luciano_di_croce) 
[TWITTER](https://twitter.com/DiCroceLab?lang=en)

Software developers:
- Enrique Blanco (senior bioinformatician)
- Mar Gonzalez-Ramirez (Postdoc bioinformatician)
- Luciano Di Croce (group leader)

# END of README

