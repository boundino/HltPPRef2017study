#!/bin/bash

INDEX=1

INPUTFILE=(
    "/export/d00/scratch/jwang/HLTppRef/crab_Evtmatching_V14_pp_20171019_prompt_D0_Pthat100_5020GeV_pythia8_20171005_fixGT.root"
    "/export/d00/scratch/jwang/HLTppRef/crab_EvtMatching_V14_pp_20171027_Dijet_5020GeV_pythia8_20171005.root"
)
TREENAME=(
    "ak4PFJetAnalyzer/t"
    "ak4PFJetAnalyzer/t"
)
SELECTIONS=(
    "1"
    "1"
)
BRANCHNAME=(
    "Max"'$'"(rawpt)"
    "Max"'$'"(genpt)"
)
OUTPUTNAME=("jet" "jet_dijet")

##
g++ turnonjetall.C $(root-config --cflags --libs) -g -o turnonjetall.exe

set -x
# ./turnonjetall.exe "${INPUTFILE[INDEX]}" "${OUTPUTNAME[INDEX]}" "${TREENAME[INDEX]}" "${BRANCHNAME[INDEX]}" "${SELECTIONS[INDEX]}" "HLT_AK4PFJet30_v15" "L1_SingleJet60_Final" "HLT_AK4PFJet50_v15" "L1_SingleJet60_Final" "HLT_AK4PFJet80_v15" "L1_SingleJet60_Final" "HLT_AK4PFJet100_v15" "L1_SingleJet60_Final"
./turnonjetall.exe "${INPUTFILE[INDEX]}" "${OUTPUTNAME[INDEX]}" "${TREENAME[INDEX]}" "${BRANCHNAME[INDEX]}" "${SELECTIONS[INDEX]}" "L1_SingleJet8_Final" "1" "L1_SingleJet16_Final" "1" "L1_SingleJet24_Final" "1" "L1_SingleJet32_Final" "1" "L1_SingleJet44_Final" "1" "L1_SingleJet60_Final" "1"
set +x


