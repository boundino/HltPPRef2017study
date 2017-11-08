#!/bin/bash

INPUTFOREST="/export/d00/scratch/jwang/HLTppRef/crab_Forest_pp_20171027_Dijet80_5020GeV_pythia8_20171005.root"
INPUTHLT="/export/d00/scratch/jwang/HLTppRef/crab_HLTDIGI_V33_pp_20171106_Dijet80_TuneCUETP8M1_5020GeV_pythia8_20171005.root"
OUTPUT="/export/d00/scratch/jwang/HLTppRef/crab_EvtMatching_V33_pp_20171106_Dijet_5020GeV_pythia8_20171005.root"

rm evtmatching.exe
g++ evtmatching.C $(root-config --cflags --libs) -g -o evtmatching.exe

rm $OUTPUT
./evtmatching.exe $INPUTFOREST $INPUTHLT $OUTPUT

rm ./evtmatching.exe