#!/bin/bash

NEVT=$4
INPUTFILE="/export/d00/scratch/jwang/HLTppRef/crab_HLT_V14_pp_20171024_prompt_D0pt0p0_Pthat100_5020GeV_pythia8_20171005_saveobj.root"
SETUP="$1 $2 $3"
PRINTTRK=0

##

g++ loopcand.C $(root-config --cflags --libs) -g -o loopcand.exe
./loopcand.exe $INPUTFILE $SETUP $NEVT $PRINTTRK

rm loopcand.exe