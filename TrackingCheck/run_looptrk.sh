#!/bin/bash

INPUTFILE="/export/d00/scratch/jwang/HLTppRef/crab_HLT_V14_pp_20171024_prompt_D0pt0p0_Pthat100_5020GeV_pythia8_20171005_saveobj.root"

##

g++ looptrk.C $(root-config --cflags --libs) -g -o looptrk.exe
./looptrk.exe $INPUTFILE 0 

rm looptrk.exe