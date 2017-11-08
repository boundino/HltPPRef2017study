#!/bin/bash

## pp
# Dzero prompt
sed '1iconst int nBins=6; float pthatBin[nBins]={0,5,10,20,50,100}; float crosssec[nBins+1]={6.972e+09,1.504e+09,2.124e+08,1.987e+07,5.867e+05,3.100e+04,0.}; int genSignal[2]={1,2};' weighPurePthat.C > weighPurePthat_tmp.C
INPUTFILE="/export/d00/scratch/jwang/HLTppRef/crab_HLT_V33_pp_20171106_prompt_D0_TuneCUETP8M1_5020GeV_pythia8_20171005.root"

# Ds prompt
# sed '1iconst int nBins=6; float pthatBin[nBins]={0,5,10,20,50,100}; float crosssec[nBins+1]={1.790e+09,4.136e+08,6.041e+07,5.902e+06,1.790e+05,9.634e+03,0.}; int genSignal[2]={7,8};' weighPurePthat.C > weighPurePthat_tmp.C
# INPUTFILE="/export/d00/scratch/jwang/HLTppRef/crab_HLT_V14_pp_20171023_prompt_Ds_5020GeV_pythia8_20171005.root"

###

OUTPUTFILE=${INPUTFILE%".root"}_pthatweight.root

cp -v "$INPUTFILE" "$OUTPUTFILE"
g++ weighPurePthat_tmp.C $(root-config --cflags --libs) -g -o weighPurePthat_tmp.exe 
./weighPurePthat_tmp.exe "$INPUTFILE" "$OUTPUTFILE"
rm weighPurePthat_tmp.exe

rm weighPurePthat_tmp.C
