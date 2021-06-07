##########################################################################
#                                                                        #
#   Module: Makefile                                                     #
#                                                                        #
#   Makefile for SeqCode programs                                        #
#                                                                        #
#   This file is part of the SeqCode 1.0 distribution                    #
#                                                                        #
#     Copyright (C) 2020 - Enrique BLANCO GARCIA                         #
#                                                                        #
#  This program is free software; you can redistribute it and/or modify  #
#  it under the terms of the GNU General Public License as published by  #
#  the Free Software Foundation; either version 2 of the License, or     #
#  (at your option) any later version.                                   #
#                                                                        #
#  This program is distributed in the hope that it will be useful,       #
#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
#  GNU General Public License for more details.                          #
#                                                                        #
#  You should have received a copy of the GNU General Public License     #
#  along with this program; if not, write to the Free Software           #
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.             #
##########################################################################


###########################
# 0. Compilation options  #
###########################

CC= gcc 
OPTS=-I$(INCLUDE) -O2 -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -D_CURSES_LIB=1
LOPS = -lm -lz -pthread
INCLUDE= ./include
CDIR= ./src
OBJ = ./objects

# cram
CDIR_CRAM= $(CDIR)/cram
OBJ_CRAM = $(OBJ)/cram

# htslib
CDIR_HTS= $(CDIR)/htslib
OBJ_HTS = $(OBJ)/htslib

# samtools
CDIR_SAM= $(CDIR)/samtools
OBJ_SAM = $(OBJ)/samtools

# seqcode
CDIR_SEQ= $(CDIR)/seqcode
OBJ_SEQ = $(OBJ)/seqcode


###########################
# 1. List of programs     #
###########################

ALL= all
MESS1 = mess1
MESS2 = mess2
MESS3 = mess3
MESS4 = mess4
MESS5 = mess5
MESS6 = mess6
MESS7 = mess7
MESS8 = mess8

BUILDCHIPPROFILE= buildChIPprofile
BIN_BUILDCHIPPROFILE= bin/$(BUILDCHIPPROFILE)

COMBINECHIPPROFILES= combineChIPprofiles
BIN_COMBINECHIPPROFILES= bin/$(COMBINECHIPPROFILES)

COMBINETSSMAPS= combineTSSmaps
BIN_COMBINETSSMAPS= bin/$(COMBINETSSMAPS)

COMBINETSSPLOTS= combineTSSplots
BIN_COMBINETSSPLOTS= bin/$(COMBINETSSPLOTS)

COMPUTEMAXSIGNAL=computemaxsignal
BIN_COMPUTEMAXSIGNAL= bin/$(COMPUTEMAXSIGNAL)

FINDPEAKS= findPeaks
BIN_FINDPEAKS= bin/$(FINDPEAKS)

GENOMEDISTRIBUTION= genomeDistribution
BIN_GENOMEDISTRIBUTION= bin/$(GENOMEDISTRIBUTION)

MATCHPEAKS= matchpeaks
BIN_MATCHPEAKS= bin/$(MATCHPEAKS)

MATCHPEAKSGENES= matchpeaksgenes
BIN_MATCHPEAKSGENES= bin/$(MATCHPEAKSGENES)

PROCESSMACS= processmacs
BIN_PROCESSMACS= bin/$(PROCESSMACS)

PRODUCEGENEMAPS= produceGENEmaps
BIN_PRODUCEGENEMAPS= bin/$(PRODUCEGENEMAPS)

PRODUCEGENEPLOTS= produceGENEplots
BIN_PRODUCEGENEPLOTS= bin/$(PRODUCEGENEPLOTS)

PRODUCEPEAKMAPS= producePEAKmaps
BIN_PRODUCEPEAKMAPS= bin/$(PRODUCEPEAKMAPS)

PRODUCEPEAKPLOTS= producePEAKplots
BIN_PRODUCEPEAKPLOTS= bin/$(PRODUCEPEAKPLOTS)

PRODUCETESMAPS= produceTESmaps
BIN_PRODUCETESMAPS= bin/$(PRODUCETESMAPS)

PRODUCETESPLOTS= produceTESplots
BIN_PRODUCETESPLOTS= bin/$(PRODUCETESPLOTS)

PRODUCETSSMAPS= produceTSSmaps
BIN_PRODUCETSSMAPS= bin/$(PRODUCETSSMAPS)

PRODUCETSSPLOTS= produceTSSplots
BIN_PRODUCETSSPLOTS= bin/$(PRODUCETSSPLOTS)

RECOVERCHIPLEVELS= recoverChIPlevels
BIN_RECOVERCHIPLEVELS= bin/$(RECOVERCHIPLEVELS)

SCOREPHASTCONS= scorePhastCons
BIN_SCOREPHASTCONS= bin/$(SCOREPHASTCONS)


###########################
# 2. List of objects      #
###########################

OBJS_CRAM = $(OBJ_CRAM)/cram_codecs.o $(OBJ_CRAM)/cram_decode.o $(OBJ_CRAM)/cram_encode.o $(OBJ_CRAM)/cram_index.o $(OBJ_CRAM)/cram_io.o $(OBJ_CRAM)/cram_samtools.o $(OBJ_CRAM)/cram_stats.o $(OBJ_CRAM)/files.o $(OBJ_CRAM)/md5.o $(OBJ_CRAM)/mFILE.o $(OBJ_CRAM)/open_trace_file.o $(OBJ_CRAM)/pooled_alloc.o $(OBJ_CRAM)/rANS_static.o $(OBJ_CRAM)/sam_header.o $(OBJ_CRAM)/string_alloc.o $(OBJ_CRAM)/thread_pool.o $(OBJ_CRAM)/vlen.o $(OBJ_CRAM)/zfio.o

OBJS_HTS = $(OBJ_HTS)/bgzf.o $(OBJ_HTS)/faidx.o $(OBJ_HTS)/hfile.o $(OBJ_HTS)/hfile_net.o $(OBJ_HTS)/hts.o $(OBJ_HTS)/kfunc.o $(OBJ_HTS)/knetfile.o $(OBJ_HTS)/kstring.o $(OBJ_HTS)/regidx.o $(OBJ_HTS)/sam.o $(OBJ_HTS)/synced_bcf_reader.o $(OBJ_HTS)/tbx.o $(OBJ_HTS)/vcf.o $(OBJ_HTS)/vcf_sweep.o $(OBJ_HTS)/vcfutils.o

OBJS_SAM = $(OBJ_SAM)/bam_aux.o $(OBJ_SAM)/bam.o $(OBJ_SAM)/bam_import.o $(OBJ_SAM)/bam_plbuf.o $(OBJ_SAM)/sam.o $(OBJ_SAM)/sam_header.o

OBJ_BUILDCHIPPROFILE= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_buildChIPprofile.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/Dictionary.o \
	$(OBJ_SEQ)/Output.o $(OBJ_SEQ)/ProcessGenome.o \
	$(OBJ_SEQ)/ReadSAMFile.o $(OBJ_SEQ)/ColorManager.o

OBJ_COMBINECHIPPROFILES= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_combineChIPprofiles.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/Dictionary.o \
	$(OBJ_SEQ)/Output.o $(OBJ_SEQ)/CombineGenomes.o \
	$(OBJ_SEQ)/ReadSAMFile.o $(OBJ_SEQ)/ColorManager.o

OBJ_COMBINETSSMAPS= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_combineTSSmaps.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/ReadRefgeneFile2.o \
	$(OBJ_SEQ)/Dictionary.o $(OBJ_SEQ)/Output.o $(OBJ_SEQ)/OutputR.o $(OBJ_SEQ)/OutputH.o \
	$(OBJ_SEQ)/CombineTargetGenesMaps.o $(OBJ_SEQ)/ReadSAMFile.o \
	$(OBJ_SEQ)/ColorManager.o

OBJ_COMBINETSSPLOTS= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_combineTSSplots.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/ReadRefgeneFile2.o \
	$(OBJ_SEQ)/Dictionary.o $(OBJ_SEQ)/Output.o $(OBJ_SEQ)/OutputR.o \
	$(OBJ_SEQ)/CombineTargetGenes.o $(OBJ_SEQ)/ReadSAMFile.o \
	$(OBJ_SEQ)/ColorManager.o

OBJ_COMPUTEMAXSIGNAL= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_computemaxsignal.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/ReadRefgeneFile2.o \
	$(OBJ_SEQ)/Dictionary.o $(OBJ_SEQ)/Output.o \
	$(OBJ_SEQ)/ReadBGFile.o $(OBJ_SEQ)/ProcessGenesMax.o

OBJ_FINDPEAKS= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_findPeaks.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/Dictionary.o \
	$(OBJ_SEQ)/Output.o $(OBJ_SEQ)/ProcessGenomePeaks.o \
	$(OBJ_SEQ)/ReadSAMFile.o

OBJ_GENOMEDISTRIBUTION= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_genomeDistribution.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/Dictionary.o \
	$(OBJ_SEQ)/Output.o $(OBJ_SEQ)/OutputR.o \
	$(OBJ_SEQ)/ReadRefgeneFileMark.o $(OBJ_SEQ)/ProcessPeaksMarks.o \
	$(OBJ_SEQ)/ColorManager.o

OBJ_MATCHPEAKS= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_matchpeaks.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/Output.o $(OBJ_SEQ)/ReadPeaksFile.o \
	$(OBJ_SEQ)/Dictionary.o $(OBJ_SEQ)/ProcessPeaksLists.o 

OBJ_PROCESSMACS= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_processmacs.o \
	$(OBJ_SEQ)/Dictionary.o $(OBJ_SEQ)/Output.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/RequestMemory.o \
	$(OBJ_SEQ)/ProcessBG.o $(OBJ_SEQ)/GetFileSize.o

OBJ_MATCHPEAKSGENES= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_matchpeaksgenes.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ProcessPeaks.o $(OBJ_SEQ)/Output.o \
	$(OBJ_SEQ)/ReadRefgeneFile.o $(OBJ_SEQ)/Dictionary.o

OBJ_PRODUCEGENEMAPS= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_produceGENEmaps.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/ReadRefgeneFile2.o \
	$(OBJ_SEQ)/Dictionary.o $(OBJ_SEQ)/Output.o $(OBJ_SEQ)/OutputR.o \
	$(OBJ_SEQ)/OutputH.o $(OBJ_SEQ)/ProcessTargetGenesGENEMaps.o \
	$(OBJ_SEQ)/ReadSAMFile.o $(OBJ_SEQ)/ColorManager.o

OBJ_PRODUCEGENEPLOTS= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_produceGENEplots.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/ReadRefgeneFile2.o \
	$(OBJ_SEQ)/Dictionary.o $(OBJ_SEQ)/Output.o $(OBJ_SEQ)/OutputR.o \
	$(OBJ_SEQ)/ProcessTargetGenesGENE.o $(OBJ_SEQ)/ReadSAMFile.o \
	$(OBJ_SEQ)/ColorManager.o

OBJ_PRODUCEPEAKMAPS= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_producePEAKmaps.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/Dictionary.o $(OBJ_SEQ)/Output.o \
	$(OBJ_SEQ)/OutputH.o $(OBJ_SEQ)/OutputR.o $(OBJ_SEQ)/ReadProcessPeaksMaps.o \
	$(OBJ_SEQ)/ReadSAMFile.o $(OBJ_SEQ)/ColorManager.o

OBJ_PRODUCEPEAKPLOTS= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_producePEAKplots.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/Dictionary.o $(OBJ_SEQ)/Output.o \
	$(OBJ_SEQ)/OutputR.o $(OBJ_SEQ)/ReadProcessPeaks.o $(OBJ_SEQ)/ReadSAMFile.o \
	$(OBJ_SEQ)/ColorManager.o

OBJ_PRODUCETESMAPS= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_produceTESmaps.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/ReadRefgeneFile2.o \
	$(OBJ_SEQ)/Dictionary.o $(OBJ_SEQ)/Output.o $(OBJ_SEQ)/OutputR.o \
	$(OBJ_SEQ)/OutputH.o $(OBJ_SEQ)/ProcessTargetGenesTESMaps.o \
	$(OBJ_SEQ)/ReadSAMFile.o $(OBJ_SEQ)/ColorManager.o

OBJ_PRODUCETESPLOTS= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_produceTESplots.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/ReadRefgeneFile2.o \
	$(OBJ_SEQ)/Dictionary.o $(OBJ_SEQ)/Output.o $(OBJ_SEQ)/OutputR.o \
	$(OBJ_SEQ)/ProcessTargetGenesTES.o $(OBJ_SEQ)/ReadSAMFile.o \
	$(OBJ_SEQ)/ColorManager.o

OBJ_PRODUCETSSMAPS= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_produceTSSmaps.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/ReadRefgeneFile2.o \
	$(OBJ_SEQ)/Dictionary.o $(OBJ_SEQ)/Output.o $(OBJ_SEQ)/OutputR.o \
	$(OBJ_SEQ)/OutputH.o $(OBJ_SEQ)/ProcessTargetGenesMaps.o \
	$(OBJ_SEQ)/ReadSAMFile.o $(OBJ_SEQ)/ColorManager.o

OBJ_PRODUCETSSPLOTS= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_produceTSSplots.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/ReadRefgeneFile2.o \
	$(OBJ_SEQ)/Dictionary.o $(OBJ_SEQ)/Output.o $(OBJ_SEQ)/OutputR.o \
	$(OBJ_SEQ)/ProcessTargetGenes.o $(OBJ_SEQ)/ReadSAMFile.o \
	$(OBJ_SEQ)/ColorManager.o

OBJ_RECOVERCHIPLEVELS= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_recoverChIPlevels.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/Dictionary.o $(OBJ_SEQ)/Output.o \
	$(OBJ_SEQ)/ReadProcessPeaksLevels.o $(OBJ_SEQ)/ReadSAMFile.o

OBJ_SCOREPHASTCONS= $(OBJ_SEQ)/account.o $(OBJ_SEQ)/readargv_scorePhastCons.o \
	$(OBJ_SEQ)/RequestMemory.o $(OBJ_SEQ)/RequestMemoryBin.o $(OBJ_SEQ)/GetFileSize.o \
	$(OBJ_SEQ)/ReadChrFile.o $(OBJ_SEQ)/Dictionary.o $(OBJ_SEQ)/Output.o \
	$(OBJ_SEQ)/ReadWIGFile.o $(OBJ_SEQ)/ReadPhastConsFiles.o \
	$(OBJ_SEQ)/ReadRefgeneFileMarkExons.o $(OBJ_SEQ)/ReadProcessPeaksPhastCons.o


###########################
# 3. Makefile rules       #
###########################

### CRAM

$(OBJ_CRAM)/cram_codecs.o :  $(CDIR_CRAM)/cram_codecs.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/cram_codecs.c -o $(OBJ_CRAM)/cram_codecs.o

$(OBJ_CRAM)/cram_decode.o :  $(CDIR_CRAM)/cram_decode.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/cram_decode.c -o $(OBJ_CRAM)/cram_decode.o

$(OBJ_CRAM)/cram_encode.o :  $(CDIR_CRAM)/cram_encode.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/cram_encode.c -o $(OBJ_CRAM)/cram_encode.o

$(OBJ_CRAM)/cram_index.o :  $(CDIR_CRAM)/cram_index.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/cram_index.c -o $(OBJ_CRAM)/cram_index.o

$(OBJ_CRAM)/cram_io.o :  $(CDIR_CRAM)/cram_io.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/cram_io.c -o $(OBJ_CRAM)/cram_io.o

$(OBJ_CRAM)/cram_samtools.o :  $(CDIR_CRAM)/cram_samtools.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/cram_samtools.c -o $(OBJ_CRAM)/cram_samtools.o

$(OBJ_CRAM)/cram_stats.o :  $(CDIR_CRAM)/cram_stats.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/cram_stats.c -o $(OBJ_CRAM)/cram_stats.o

$(OBJ_CRAM)/files.o :  $(CDIR_CRAM)/files.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/files.c -o $(OBJ_CRAM)/files.o

$(OBJ_CRAM)/md5.o :  $(CDIR_CRAM)/md5.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/md5.c -o $(OBJ_CRAM)/md5.o

$(OBJ_CRAM)/mFILE.o :  $(CDIR_CRAM)/mFILE.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/mFILE.c -o $(OBJ_CRAM)/mFILE.o

$(OBJ_CRAM)/open_trace_file.o :  $(CDIR_CRAM)/open_trace_file.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/open_trace_file.c -o $(OBJ_CRAM)/open_trace_file.o

$(OBJ_CRAM)/pooled_alloc.o :  $(CDIR_CRAM)/pooled_alloc.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/pooled_alloc.c -o $(OBJ_CRAM)/pooled_alloc.o

$(OBJ_CRAM)/rANS_static.o :  $(CDIR_CRAM)/rANS_static.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/rANS_static.c -o $(OBJ_CRAM)/rANS_static.o

$(OBJ_CRAM)/sam_header.o :  $(CDIR_CRAM)/sam_header.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/sam_header.c -o $(OBJ_CRAM)/sam_header.o

$(OBJ_CRAM)/string_alloc.o :  $(CDIR_CRAM)/string_alloc.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/string_alloc.c -o $(OBJ_CRAM)/string_alloc.o

$(OBJ_CRAM)/thread_pool.o :  $(CDIR_CRAM)/thread_pool.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/thread_pool.c -o $(OBJ_CRAM)/thread_pool.o

$(OBJ_CRAM)/vlen.o :  $(CDIR_CRAM)/vlen.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/vlen.c -o $(OBJ_CRAM)/vlen.o

$(OBJ_CRAM)/zfio.o :  $(CDIR_CRAM)/zfio.c
	$(CC) -c $(OPTS) $(CDIR_CRAM)/zfio.c -o $(OBJ_CRAM)/zfio.o

### HTSLIB

$(OBJ_HTS)/bgzf.o :  $(CDIR_HTS)/bgzf.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/bgzf.c -o $(OBJ_HTS)/bgzf.o

$(OBJ_HTS)/bgzip.o :  $(CDIR_HTS)/bgzip.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/bgzip.c -o $(OBJ_HTS)/bgzip.o

$(OBJ_HTS)/faidx.o :  $(CDIR_HTS)/faidx.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/faidx.c -o $(OBJ_HTS)/faidx.o

$(OBJ_HTS)/hfile.o :  $(CDIR_HTS)/hfile.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/hfile.c -o $(OBJ_HTS)/hfile.o

$(OBJ_HTS)/hfile_irods.o :  $(CDIR_HTS)/hfile_irods.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/hfile_irods.c -o $(OBJ_HTS)/hfile_irods.o

$(OBJ_HTS)/hfile_net.o :  $(CDIR_HTS)/hfile_net.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/hfile_net.c -o $(OBJ_HTS)/hfile_net.o

$(OBJ_HTS)/hts.o :  $(CDIR_HTS)/hts.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/hts.c -o $(OBJ_HTS)/hts.o

$(OBJ_HTS)/htsfile.o :  $(CDIR_HTS)/htsfile.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/htsfile.c -o $(OBJ_HTS)/htsfile.o

$(OBJ_HTS)/kfunc.o :  $(CDIR_HTS)/kfunc.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/kfunc.c -o $(OBJ_HTS)/kfunc.o

$(OBJ_HTS)/knetfile.o :  $(CDIR_HTS)/knetfile.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/knetfile.c -o $(OBJ_HTS)/knetfile.o

$(OBJ_HTS)/kstring.o :  $(CDIR_HTS)/kstring.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/kstring.c -o $(OBJ_HTS)/kstring.o

$(OBJ_HTS)/regidx.o :  $(CDIR_HTS)/regidx.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/regidx.c -o $(OBJ_HTS)/regidx.o

$(OBJ_HTS)/sam.o :  $(CDIR_HTS)/sam.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/sam.c -o $(OBJ_HTS)/sam.o

$(OBJ_HTS)/synced_bcf_reader.o :  $(CDIR_HTS)/synced_bcf_reader.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/synced_bcf_reader.c -o $(OBJ_HTS)/synced_bcf_reader.o

$(OBJ_HTS)/tabix.o :  $(CDIR_HTS)/tabix.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/tabix.c -o $(OBJ_HTS)/tabix.o

$(OBJ_HTS)/tbx.o :  $(CDIR_HTS)/tbx.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/tbx.c -o $(OBJ_HTS)/tbx.o

$(OBJ_HTS)/vcf.o :  $(CDIR_HTS)/vcf.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/vcf.c -o $(OBJ_HTS)/vcf.o

$(OBJ_HTS)/vcf_sweep.o :  $(CDIR_HTS)/vcf_sweep.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/vcf_sweep.c -o $(OBJ_HTS)/vcf_sweep.o

$(OBJ_HTS)/vcfutils.o :  $(CDIR_HTS)/vcfutils.c
	$(CC) -c $(OPTS) $(CDIR_HTS)/vcfutils.c -o $(OBJ_HTS)/vcfutils.o

### SAMTOOLS

$(OBJ_SAM)/bam_aux.o :  $(CDIR_SAM)/bam_aux.c
	$(CC) -c $(OPTS) $(CDIR_SAM)/bam_aux.c -o $(OBJ_SAM)/bam_aux.o

$(OBJ_SAM)/bam.o :  $(CDIR_SAM)/bam.c
	$(CC) -c $(OPTS) $(CDIR_SAM)/bam.c -o $(OBJ_SAM)/bam.o

$(OBJ_SAM)/bam_import.o :  $(CDIR_SAM)/bam_import.c
	$(CC) -c $(OPTS) $(CDIR_SAM)/bam_import.c -o $(OBJ_SAM)/bam_import.o

$(OBJ_SAM)/bam_plbuf.o :  $(CDIR_SAM)/bam_plbuf.c
	$(CC) -c $(OPTS) $(CDIR_SAM)/bam_plbuf.c -o $(OBJ_SAM)/bam_plbuf.o

$(OBJ_SAM)/sam.o :  $(CDIR_SAM)/sam.c
	$(CC) -c $(OPTS) $(CDIR_SAM)/sam.c -o $(OBJ_SAM)/sam.o

$(OBJ_SAM)/sam_header.o :  $(CDIR_SAM)/sam_header.c
	$(CC) -c $(OPTS) $(CDIR_SAM)/sam_header.c -o $(OBJ_SAM)/sam_header.o

### SEQCODE

### GENERAL

$(OBJ_SEQ)/account.o :  $(CDIR_SEQ)/account.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/account.c -o $(OBJ_SEQ)/account.o

$(OBJ_SEQ)/ColorManager.o :  $(CDIR_SEQ)/ColorManager.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ColorManager.c -o $(OBJ_SEQ)/ColorManager.o

$(OBJ_SEQ)/Dictionary.o :  $(CDIR_SEQ)/Dictionary.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/Dictionary.c -o $(OBJ_SEQ)/Dictionary.o

$(OBJ_SEQ)/GetFileSize.o: $(CDIR_SEQ)/GetFileSize.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/GetFileSize.c -o $(OBJ_SEQ)/GetFileSize.o

$(OBJ_SEQ)/Output.o: $(CDIR_SEQ)/Output.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/Output.c -o $(OBJ_SEQ)/Output.o

$(OBJ_SEQ)/OutputH.o: $(CDIR_SEQ)/OutputH.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/OutputH.c -o $(OBJ_SEQ)/OutputH.o

$(OBJ_SEQ)/OutputR.o: $(CDIR_SEQ)/OutputR.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/OutputR.c -o $(OBJ_SEQ)/OutputR.o

$(OBJ_SEQ)/ReadChrFile.o : $(CDIR_SEQ)/ReadChrFile.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ReadChrFile.c -o $(OBJ_SEQ)/ReadChrFile.o

$(OBJ_SEQ)/RequestMemory.o : $(CDIR_SEQ)/RequestMemory.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/RequestMemory.c -o $(OBJ_SEQ)/RequestMemory.o

$(OBJ_SEQ)/RequestMemoryBin.o : $(CDIR_SEQ)/RequestMemoryBin.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/RequestMemoryBin.c -o $(OBJ_SEQ)/RequestMemoryBin.o

$(OBJ_SEQ)/ReadPeaksFile.o :  $(CDIR_SEQ)/ReadPeaksFile.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ReadPeaksFile.c -o $(OBJ_SEQ)/ReadPeaksFile.o

$(OBJ_SEQ)/ReadRefgeneFile.o: $(CDIR_SEQ)/ReadRefgeneFile.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ReadRefgeneFile.c -o $(OBJ_SEQ)/ReadRefgeneFile.o

$(OBJ_SEQ)/ReadRefgeneFile2.o: $(CDIR_SEQ)/ReadRefgeneFile2.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ReadRefgeneFile2.c -o $(OBJ_SEQ)/ReadRefgeneFile2.o

$(OBJ_SEQ)/ReadRefgeneFileMark.o : $(CDIR_SEQ)/ReadRefgeneFileMark.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ReadRefgeneFileMark.c -o $(OBJ_SEQ)/ReadRefgeneFileMark.o

$(OBJ_SEQ)/ReadSAMFile.o: $(CDIR_SEQ)/ReadSAMFile.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ReadSAMFile.c -o $(OBJ_SEQ)/ReadSAMFile.o

$(OBJ_SEQ)/ReadBGFile.o: $(CDIR_SEQ)/ReadBGFile.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ReadBGFile.c -o $(OBJ_SEQ)/ReadBGFile.o

### BUILDCHIPPROFILE

$(BIN_BUILDCHIPPROFILE): $(OBJ_SEQ)/$(BUILDCHIPPROFILE).o $(OBJ_BUILDCHIPPROFILE) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM)
	$(CC) $(OPTS) -o $(BIN_BUILDCHIPPROFILE) $(OBJ_SEQ)/$(BUILDCHIPPROFILE).o $(OBJ_BUILDCHIPPROFILE) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM) $(LOPS)

$(OBJ_SEQ)/$(BUILDCHIPPROFILE).o : $(CDIR_SEQ)/$(BUILDCHIPPROFILE).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(BUILDCHIPPROFILE).c -o $(OBJ_SEQ)/$(BUILDCHIPPROFILE).o 

$(OBJ_SEQ)/readargv_buildChIPprofile.o : $(CDIR_SEQ)/readargv_buildChIPprofile.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_buildChIPprofile.c -o $(OBJ_SEQ)/readargv_buildChIPprofile.o

$(OBJ_SEQ)/ProcessGenome.o :  $(CDIR_SEQ)/ProcessGenome.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ProcessGenome.c -o $(OBJ_SEQ)/ProcessGenome.o

### COMBINECHIPPROFILES

$(BIN_COMBINECHIPPROFILES): $(OBJ_SEQ)/$(COMBINECHIPPROFILES).o $(OBJ_COMBINECHIPPROFILES) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM)
	$(CC) $(OPTS) -o $(BIN_COMBINECHIPPROFILES) $(OBJ_SEQ)/$(COMBINECHIPPROFILES).o $(OBJ_COMBINECHIPPROFILES) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM) $(LOPS)

$(OBJ_SEQ)/$(COMBINECHIPPROFILES).o : $(CDIR_SEQ)/$(COMBINECHIPPROFILES).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(COMBINECHIPPROFILES).c -o $(OBJ_SEQ)/$(COMBINECHIPPROFILES).o 

$(OBJ_SEQ)/readargv_combineChIPprofiles.o :  $(CDIR_SEQ)/readargv_combineChIPprofiles.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_combineChIPprofiles.c -o $(OBJ_SEQ)/readargv_combineChIPprofiles.o

$(OBJ_SEQ)/CombineGenomes.o :  $(CDIR_SEQ)/CombineGenomes.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/CombineGenomes.c -o $(OBJ_SEQ)/CombineGenomes.o

### COMBINETSSMAPS

$(BIN_COMBINETSSMAPS): $(OBJ_SEQ)/$(COMBINETSSMAPS).o $(OBJ_COMBINETSSMAPS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM)
	$(CC) $(OPTS) -o $(BIN_COMBINETSSMAPS) $(OBJ_SEQ)/$(COMBINETSSMAPS).o $(OBJ_COMBINETSSMAPS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM) $(LOPS)

$(OBJ_SEQ)/$(COMBINETSSMAPS).o : $(CDIR_SEQ)/$(COMBINETSSMAPS).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(COMBINETSSMAPS).c -o $(OBJ_SEQ)/$(COMBINETSSMAPS).o 

$(OBJ_SEQ)/readargv_combineTSSmaps.o :  $(CDIR_SEQ)/readargv_combineTSSmaps.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_combineTSSmaps.c -o $(OBJ_SEQ)/readargv_combineTSSmaps.o

$(OBJ_SEQ)/CombineTargetGenesMaps.o :  $(CDIR_SEQ)/CombineTargetGenesMaps.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/CombineTargetGenesMaps.c -o $(OBJ_SEQ)/CombineTargetGenesMaps.o

### COMBINETSSPLOTS

$(BIN_COMBINETSSPLOTS): $(OBJ_SEQ)/$(COMBINETSSPLOTS).o $(OBJ_COMBINETSSPLOTS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM)
	$(CC) $(OPTS) -o $(BIN_COMBINETSSPLOTS) $(OBJ_SEQ)/$(COMBINETSSPLOTS).o $(OBJ_COMBINETSSPLOTS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM) $(LOPS)

$(OBJ_SEQ)/$(COMBINETSSPLOTS).o : $(CDIR_SEQ)/$(COMBINETSSPLOTS).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(COMBINETSSPLOTS).c -o $(OBJ_SEQ)/$(COMBINETSSPLOTS).o 

$(OBJ_SEQ)/readargv_combineTSSplots.o :  $(CDIR_SEQ)/readargv_combineTSSplots.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_combineTSSplots.c -o $(OBJ_SEQ)/readargv_combineTSSplots.o

$(OBJ_SEQ)/CombineTargetGenes.o :  $(CDIR_SEQ)/CombineTargetGenes.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/CombineTargetGenes.c -o $(OBJ_SEQ)/CombineTargetGenes.o

### COMPUTEMAXSIGNAL

$(BIN_COMPUTEMAXSIGNAL): $(OBJ_SEQ)/$(COMPUTEMAXSIGNAL).o $(OBJ_COMPUTEMAXSIGNAL)
	$(CC) $(OPTS) -o $(BIN_COMPUTEMAXSIGNAL) $(OBJ_SEQ)/$(COMPUTEMAXSIGNAL).o $(OBJ_COMPUTEMAXSIGNAL) -lm

$(OBJ_SEQ)/$(COMPUTEMAXSIGNAL).o : $(CDIR_SEQ)/$(COMPUTEMAXSIGNAL).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(COMPUTEMAXSIGNAL).c -o $(OBJ_SEQ)/$(COMPUTEMAXSIGNAL).o 

$(OBJ_SEQ)/readargv_computemaxsignal.o :  $(CDIR_SEQ)/readargv_computemaxsignal.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_computemaxsignal.c -o $(OBJ_SEQ)/readargv_computemaxsignal.o

$(OBJ_SEQ)/ProcessGenesMax.o :  $(CDIR_SEQ)/ProcessGenesMax.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ProcessGenesMax.c -o $(OBJ_SEQ)/ProcessGenesMax.o

### FINDPEAKS

$(BIN_FINDPEAKS): $(OBJ_SEQ)/$(FINDPEAKS).o $(OBJ_FINDPEAKS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM)
	$(CC) $(OPTS) -o $(BIN_FINDPEAKS) $(OBJ_SEQ)/$(FINDPEAKS).o $(OBJ_FINDPEAKS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM) $(LOPS)

$(OBJ_SEQ)/$(FINDPEAKS).o : $(CDIR_SEQ)/$(FINDPEAKS).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(FINDPEAKS).c -o $(OBJ_SEQ)/$(FINDPEAKS).o 

$(OBJ_SEQ)/readargv_findPeaks.o :  $(CDIR_SEQ)/readargv_findPeaks.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_findPeaks.c -o $(OBJ_SEQ)/readargv_findPeaks.o

$(OBJ_SEQ)/ProcessGenomePeaks.o :  $(CDIR_SEQ)/ProcessGenomePeaks.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ProcessGenomePeaks.c -o $(OBJ_SEQ)/ProcessGenomePeaks.o

### GENOMEDISTRIBUTION

$(BIN_GENOMEDISTRIBUTION): $(OBJ_SEQ)/$(GENOMEDISTRIBUTION).o $(OBJ_GENOMEDISTRIBUTION)
	$(CC) $(OPTS) -o $(BIN_GENOMEDISTRIBUTION) $(OBJ_SEQ)/$(GENOMEDISTRIBUTION).o $(OBJ_GENOMEDISTRIBUTION) -lm

$(OBJ_SEQ)/$(GENOMEDISTRIBUTION).o : $(CDIR_SEQ)/$(GENOMEDISTRIBUTION).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(GENOMEDISTRIBUTION).c -o $(OBJ_SEQ)/$(GENOMEDISTRIBUTION).o 

$(OBJ_SEQ)/readargv_genomeDistribution.o :  $(CDIR_SEQ)/readargv_genomeDistribution.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_genomeDistribution.c -o $(OBJ_SEQ)/readargv_genomeDistribution.o

$(OBJ_SEQ)/ProcessPeaksMarks.o :  $(CDIR_SEQ)/ProcessPeaksMarks.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ProcessPeaksMarks.c -o $(OBJ_SEQ)/ProcessPeaksMarks.o

### MATCHPEAKS

$(BIN_MATCHPEAKS): $(OBJ_SEQ)/$(MATCHPEAKS).o $(OBJ_MATCHPEAKS)
	$(CC) $(OPTS) -o $(BIN_MATCHPEAKS) $(OBJ_SEQ)/$(MATCHPEAKS).o $(OBJ_MATCHPEAKS) -lm

$(OBJ_SEQ)/$(MATCHPEAKS).o : $(CDIR_SEQ)/$(MATCHPEAKS).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(MATCHPEAKS).c -o $(OBJ_SEQ)/$(MATCHPEAKS).o 

$(OBJ_SEQ)/readargv_matchpeaks.o :  $(CDIR_SEQ)/readargv_matchpeaks.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_matchpeaks.c -o $(OBJ_SEQ)/readargv_matchpeaks.o

$(OBJ_SEQ)/ProcessPeaksLists.o :  $(CDIR_SEQ)/ProcessPeaksLists.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ProcessPeaksLists.c -o $(OBJ_SEQ)/ProcessPeaksLists.o

### MATCHPEAKSGENES

$(BIN_MATCHPEAKSGENES): $(OBJ_SEQ)/$(MATCHPEAKSGENES).o $(OBJ_MATCHPEAKSGENES)
	$(CC) $(OPTS) -o $(BIN_MATCHPEAKSGENES) $(OBJ_SEQ)/$(MATCHPEAKSGENES).o $(OBJ_MATCHPEAKSGENES) -lm

$(OBJ_SEQ)/$(MATCHPEAKSGENES).o : $(CDIR_SEQ)/$(MATCHPEAKSGENES).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(MATCHPEAKSGENES).c -o $(OBJ_SEQ)/$(MATCHPEAKSGENES).o 

$(OBJ_SEQ)/readargv_matchpeaksgenes.o :  $(CDIR_SEQ)/readargv_matchpeaksgenes.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_matchpeaksgenes.c -o $(OBJ_SEQ)/readargv_matchpeaksgenes.o

$(OBJ_SEQ)/ProcessPeaks.o: $(CDIR_SEQ)/ProcessPeaks.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ProcessPeaks.c -o $(OBJ_SEQ)/ProcessPeaks.o

### PROCESSMACS

$(BIN_PROCESSMACS): $(OBJ_SEQ)/$(PROCESSMACS).o $(OBJ_PROCESSMACS)
	$(CC) $(OPTS) -o $(BIN_PROCESSMACS) $(OBJ_SEQ)/$(PROCESSMACS).o $(OBJ_PROCESSMACS) -lm

$(OBJ_SEQ)/$(PROCESSMACS).o : $(CDIR_SEQ)/$(PROCESSMACS).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(PROCESSMACS).c -o $(OBJ_SEQ)/$(PROCESSMACS).o 

$(OBJ_SEQ)/readargv_processmacs.o :  $(CDIR_SEQ)/readargv_processmacs.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_processmacs.c -o $(OBJ_SEQ)/readargv_processmacs.o

$(OBJ_SEQ)/ProcessBG.o: $(CDIR_SEQ)/ProcessBG.c $(HEADERS)
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ProcessBG.c -o $(OBJ_SEQ)/ProcessBG.o

### PRODUCEGENEMAPS

$(BIN_PRODUCEGENEMAPS): $(OBJ_SEQ)/$(PRODUCEGENEMAPS).o $(OBJ_PRODUCEGENEMAPS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM)
	$(CC) $(OPTS) -o $(BIN_PRODUCEGENEMAPS) $(OBJ_SEQ)/$(PRODUCEGENEMAPS).o $(OBJ_PRODUCEGENEMAPS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM) $(LOPS)

$(OBJ_SEQ)/$(PRODUCEGENEMAPS).o : $(CDIR_SEQ)/$(PRODUCEGENEMAPS).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(PRODUCEGENEMAPS).c -o $(OBJ_SEQ)/$(PRODUCEGENEMAPS).o 

$(OBJ_SEQ)/readargv_produceGENEmaps.o :  $(CDIR_SEQ)/readargv_produceGENEmaps.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_produceGENEmaps.c -o $(OBJ_SEQ)/readargv_produceGENEmaps.o

$(OBJ_SEQ)/ProcessTargetGenesGENEMaps.o :  $(CDIR_SEQ)/ProcessTargetGenesGENEMaps.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ProcessTargetGenesGENEMaps.c -o $(OBJ_SEQ)/ProcessTargetGenesGENEMaps.o

### PRODUCEGENEPLOTS

$(BIN_PRODUCEGENEPLOTS): $(OBJ_SEQ)/$(PRODUCEGENEPLOTS).o $(OBJ_PRODUCEGENEPLOTS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM)
	$(CC) $(OPTS) -o $(BIN_PRODUCEGENEPLOTS) $(OBJ_SEQ)/$(PRODUCEGENEPLOTS).o $(OBJ_PRODUCEGENEPLOTS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM) $(LOPS)

$(OBJ_SEQ)/$(PRODUCEGENEPLOTS).o : $(CDIR_SEQ)/$(PRODUCEGENEPLOTS).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(PRODUCEGENEPLOTS).c -o $(OBJ_SEQ)/$(PRODUCEGENEPLOTS).o 

$(OBJ_SEQ)/readargv_produceGENEplots.o :  $(CDIR_SEQ)/readargv_produceGENEplots.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_produceGENEplots.c -o $(OBJ_SEQ)/readargv_produceGENEplots.o

$(OBJ_SEQ)/ProcessTargetGenesGENE.o :  $(CDIR_SEQ)/ProcessTargetGenesGENE.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ProcessTargetGenesGENE.c -o $(OBJ_SEQ)/ProcessTargetGenesGENE.o

### PRODUCEPEAKMAPS

$(BIN_PRODUCEPEAKMAPS): $(OBJ_SEQ)/$(PRODUCEPEAKMAPS).o $(OBJ_PRODUCEPEAKMAPS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM)
	$(CC) $(OPTS) -o $(BIN_PRODUCEPEAKMAPS) $(OBJ_SEQ)/$(PRODUCEPEAKMAPS).o $(OBJ_PRODUCEPEAKMAPS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM) $(LOPS)

$(OBJ_SEQ)/$(PRODUCEPEAKMAPS).o : $(CDIR_SEQ)/$(PRODUCEPEAKMAPS).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(PRODUCEPEAKMAPS).c -o $(OBJ_SEQ)/$(PRODUCEPEAKMAPS).o 

$(OBJ_SEQ)/readargv_producePEAKmaps.o :  $(CDIR_SEQ)/readargv_producePEAKmaps.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_producePEAKmaps.c -o $(OBJ_SEQ)/readargv_producePEAKmaps.o

$(OBJ_SEQ)/ReadProcessPeaksMaps.o :  $(CDIR_SEQ)/ReadProcessPeaksMaps.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ReadProcessPeaksMaps.c -o $(OBJ_SEQ)/ReadProcessPeaksMaps.o

### PRODUCEPEAKPLOTS

$(BIN_PRODUCEPEAKPLOTS): $(OBJ_SEQ)/$(PRODUCEPEAKPLOTS).o $(OBJ_PRODUCEPEAKPLOTS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM)
	$(CC) $(OPTS) -o $(BIN_PRODUCEPEAKPLOTS) $(OBJ_SEQ)/$(PRODUCEPEAKPLOTS).o $(OBJ_PRODUCEPEAKPLOTS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM) $(LOPS)

$(OBJ_SEQ)/$(PRODUCEPEAKPLOTS).o : $(CDIR_SEQ)/$(PRODUCEPEAKPLOTS).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(PRODUCEPEAKPLOTS).c -o $(OBJ_SEQ)/$(PRODUCEPEAKPLOTS).o 

$(OBJ_SEQ)/readargv_producePEAKplots.o :  $(CDIR_SEQ)/readargv_producePEAKplots.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_producePEAKplots.c -o $(OBJ_SEQ)/readargv_producePEAKplots.o

$(OBJ_SEQ)/ReadProcessPeaks.o :  $(CDIR_SEQ)/ReadProcessPeaks.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ReadProcessPeaks.c -o $(OBJ_SEQ)/ReadProcessPeaks.o

### PRODUCETESMAPS

$(BIN_PRODUCETESMAPS): $(OBJ_SEQ)/$(PRODUCETESMAPS).o $(OBJ_PRODUCETESMAPS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM)
	$(CC) $(OPTS) -o $(BIN_PRODUCETESMAPS) $(OBJ_SEQ)/$(PRODUCETESMAPS).o $(OBJ_PRODUCETESMAPS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM) $(LOPS)

$(OBJ_SEQ)/$(PRODUCETESMAPS).o : $(CDIR_SEQ)/$(PRODUCETESMAPS).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(PRODUCETESMAPS).c -o $(OBJ_SEQ)/$(PRODUCETESMAPS).o 

$(OBJ_SEQ)/readargv_produceTESmaps.o :  $(CDIR_SEQ)/readargv_produceTESmaps.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_produceTESmaps.c -o $(OBJ_SEQ)/readargv_produceTESmaps.o

$(OBJ_SEQ)/ProcessTargetGenesTESMaps.o :  $(CDIR_SEQ)/ProcessTargetGenesTESMaps.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ProcessTargetGenesTESMaps.c -o $(OBJ_SEQ)/ProcessTargetGenesTESMaps.o

### PRODUCETESPLOTS

$(BIN_PRODUCETESPLOTS): $(OBJ_SEQ)/$(PRODUCETESPLOTS).o $(OBJ_PRODUCETESPLOTS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM)
	$(CC) $(OPTS) -o $(BIN_PRODUCETESPLOTS) $(OBJ_SEQ)/$(PRODUCETESPLOTS).o $(OBJ_PRODUCETESPLOTS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM) $(LOPS)

$(OBJ_SEQ)/$(PRODUCETESPLOTS).o : $(CDIR_SEQ)/$(PRODUCETESPLOTS).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(PRODUCETESPLOTS).c -o $(OBJ_SEQ)/$(PRODUCETESPLOTS).o 

$(OBJ_SEQ)/readargv_produceTESplots.o :  $(CDIR_SEQ)/readargv_produceTESplots.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_produceTESplots.c -o $(OBJ_SEQ)/readargv_produceTESplots.o

$(OBJ_SEQ)/ProcessTargetGenesTES.o :  $(CDIR_SEQ)/ProcessTargetGenesTES.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ProcessTargetGenesTES.c -o $(OBJ_SEQ)/ProcessTargetGenesTES.o

### PRODUCETSSMAPS

$(BIN_PRODUCETSSMAPS): $(OBJ_SEQ)/$(PRODUCETSSMAPS).o $(OBJ_PRODUCETSSMAPS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM)
	$(CC) $(OPTS) -o $(BIN_PRODUCETSSMAPS) $(OBJ_SEQ)/$(PRODUCETSSMAPS).o $(OBJ_PRODUCETSSMAPS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM) $(LOPS)

$(OBJ_SEQ)/$(PRODUCETSSMAPS).o : $(CDIR_SEQ)/$(PRODUCETSSMAPS).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(PRODUCETSSMAPS).c -o $(OBJ_SEQ)/$(PRODUCETSSMAPS).o 

$(OBJ_SEQ)/readargv_produceTSSmaps.o :  $(CDIR_SEQ)/readargv_produceTSSmaps.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_produceTSSmaps.c -o $(OBJ_SEQ)/readargv_produceTSSmaps.o

$(OBJ_SEQ)/ProcessTargetGenesMaps.o :  $(CDIR_SEQ)/ProcessTargetGenesMaps.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ProcessTargetGenesMaps.c -o $(OBJ_SEQ)/ProcessTargetGenesMaps.o

### PRODUCETSSPLOTS

$(BIN_PRODUCETSSPLOTS):  $(OBJ_SEQ)/$(PRODUCETSSPLOTS).o $(OBJ_PRODUCETSSPLOTS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM)
	$(CC) $(OPTS) -o $(BIN_PRODUCETSSPLOTS) $(OBJ_SEQ)/$(PRODUCETSSPLOTS).o $(OBJ_PRODUCETSSPLOTS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM) $(LOPS)

$(OBJ_SEQ)/$(PRODUCETSSPLOTS).o : $(CDIR_SEQ)/$(PRODUCETSSPLOTS).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(PRODUCETSSPLOTS).c -o $(OBJ_SEQ)/$(PRODUCETSSPLOTS).o 

$(OBJ_SEQ)/readargv_produceTSSplots.o :  $(CDIR_SEQ)/readargv_produceTSSplots.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_produceTSSplots.c -o $(OBJ_SEQ)/readargv_produceTSSplots.o

$(OBJ_SEQ)/ProcessTargetGenes.o :  $(CDIR_SEQ)/ProcessTargetGenes.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ProcessTargetGenes.c -o $(OBJ_SEQ)/ProcessTargetGenes.o

### RECOVERCHIPLEVELS

$(BIN_RECOVERCHIPLEVELS): $(OBJ_SEQ)/$(RECOVERCHIPLEVELS).o $(OBJ_RECOVERCHIPLEVELS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM)
	$(CC) $(OPTS) -o $(BIN_RECOVERCHIPLEVELS) $(OBJ_SEQ)/$(RECOVERCHIPLEVELS).o $(OBJ_RECOVERCHIPLEVELS) $(OBJS_CRAM) $(OBJS_HTS) $(OBJS_SAM) $(LOPS)

$(OBJ_SEQ)/$(RECOVERCHIPLEVELS).o : $(CDIR_SEQ)/$(RECOVERCHIPLEVELS).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(RECOVERCHIPLEVELS).c -o $(OBJ_SEQ)/$(RECOVERCHIPLEVELS).o 

$(OBJ_SEQ)/readargv_recoverChIPlevels.o :  $(CDIR_SEQ)/readargv_recoverChIPlevels.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_recoverChIPlevels.c -o $(OBJ_SEQ)/readargv_recoverChIPlevels.o

$(OBJ_SEQ)/ReadProcessPeaksLevels.o :  $(CDIR_SEQ)/ReadProcessPeaksLevels.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ReadProcessPeaksLevels.c -o $(OBJ_SEQ)/ReadProcessPeaksLevels.o

### SCOREPHASTCONS

$(BIN_SCOREPHASTCONS): $(OBJ_SEQ)/$(SCOREPHASTCONS).o $(OBJ_SCOREPHASTCONS)
	$(CC) $(OPTS) -o $(BIN_SCOREPHASTCONS) $(OBJ_SEQ)/$(SCOREPHASTCONS).o $(OBJ_SCOREPHASTCONS) -lm

$(OBJ_SEQ)/$(SCOREPHASTCONS).o : $(CDIR_SEQ)/$(SCOREPHASTCONS).c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/$(SCOREPHASTCONS).c -o $(OBJ_SEQ)/$(SCOREPHASTCONS).o 

$(OBJ_SEQ)/readargv_scorePhastCons.o :  $(CDIR_SEQ)/readargv_scorePhastCons.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/readargv_scorePhastCons.c -o $(OBJ_SEQ)/readargv_scorePhastCons.o

$(OBJ_SEQ)/ReadPhastConsFiles.o :  $(CDIR_SEQ)/ReadPhastConsFiles.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ReadPhastConsFiles.c -o $(OBJ_SEQ)/ReadPhastConsFiles.o

$(OBJ_SEQ)/ReadWIGFile.o :  $(CDIR_SEQ)/ReadWIGFile.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ReadWIGFile.c -o $(OBJ_SEQ)/ReadWIGFile.o

$(OBJ_SEQ)/ReadRefgeneFileMarkExons.o :  $(CDIR_SEQ)/ReadRefgeneFileMarkExons.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ReadRefgeneFileMarkExons.c -o $(OBJ_SEQ)/ReadRefgeneFileMarkExons.o

$(OBJ_SEQ)/ReadProcessPeaksPhastCons.o :  $(CDIR_SEQ)/ReadProcessPeaksPhastCons.c
	$(CC) -c $(OPTS) $(CDIR_SEQ)/ReadProcessPeaksPhastCons.c -o $(OBJ_SEQ)/ReadProcessPeaksPhastCons.o


###########################
# 4. Makefile global rules#
###########################

mess1:
	@echo "***** Step 1. Building the CRAM library           *****"
mess2:
	@echo "***** [OK] CRAM library sucessfully generated     *****\n"
mess3:
	@echo "***** Step 2. Building the HTSLIB library         *****"
mess4:
	@echo "***** [OK] HTSLIB library sucessfully generated   *****\n"
mess5:
	@echo "***** Step 3. Building the SAMTOOLS library       *****"
mess6:
	@echo "***** [OK] SAMTOOLS library sucessfully generated *****\n"
mess7:
	@echo "***** Step 4. Building the SeqCode suite          *****"
mess8:
	@echo "***** [OK] SeqCode suite successfully generated   *****\n"

$(ALL):	$(MESS1) \
	$(OBJS_CRAM) \
	$(MESS2) \
	$(MESS3) \
	$(OBJS_HTS) \
	$(MESS4) \
	$(MESS5) \
	$(OBJS_SAM) \
	$(MESS6) \
	$(MESS7) \
	$(BIN_BUILDCHIPPROFILE) \
	$(BIN_COMBINECHIPPROFILES) \
	$(BIN_COMBINETSSMAPS) \
	$(BIN_COMBINETSSPLOTS) \
	$(BIN_COMPUTEMAXSIGNAL) \
	$(BIN_FINDPEAKS) \
	$(BIN_GENOMEDISTRIBUTION) \
	$(BIN_MATCHPEAKS) \
	$(BIN_MATCHPEAKSGENES) \
	$(BIN_PROCESSMACS) \
	$(BIN_PRODUCEGENEMAPS) \
	$(BIN_PRODUCEGENEPLOTS) \
	$(BIN_PRODUCEPEAKMAPS) \
	$(BIN_PRODUCEPEAKPLOTS) \
	$(BIN_PRODUCETESMAPS) \
	$(BIN_PRODUCETESPLOTS) \
	$(BIN_PRODUCETSSMAPS) \
	$(BIN_PRODUCETSSPLOTS) \
	$(BIN_RECOVERCHIPLEVELS) \
	$(BIN_SCOREPHASTCONS) \
	$(MESS8) \

clean:
	rm -f $(OBJ_CRAM)/*.o $(OBJ_HTS)/*.o $(OBJ_SAM)/*.o $(OBJ_SEQ)/*.o $(BIN_BUILDCHIPPROFILE) $(BIN_COMBINECHIPPROFILES) $(BIN_COMBINETSSMAPS) $(BIN_COMBINETSSPLOTS) $(BIN_COMPUTEMAXSIGNAL) $(BIN_FINDPEAKS) $(BIN_GENOMEDISTRIBUTION) $(BIN_MATCHPEAKS) $(BIN_MATCHPEAKSGENES) $(BIN_PROCESSMACS) $(BIN_PRODUCEGENEMAPS) $(BIN_PRODUCEGENEPLOTS) $(BIN_PRODUCEPEAKMAPS) $(BIN_PRODUCEPEAKPLOTS) $(BIN_PRODUCETESMAPS) $(BIN_PRODUCETESPLOTS) $(BIN_PRODUCETSSMAPS) $(BIN_PRODUCETSSPLOTS) $(BIN_RECOVERCHIPLEVELS) $(BIN_SCOREPHASTCONS) *~ $(INCLUDE)/*/*~ $(CDIR_SEQ)/*~
