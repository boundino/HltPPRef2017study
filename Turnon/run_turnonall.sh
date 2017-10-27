#!/bin/bash

CASES=(5)

##

WEIGHT="pthatweight"
# WEIGHT="1"
OUTPUTNAME=(
    "D0_default" 
    "Ds_default" 
    "D0_Dsize1"
    "D0_nocuts" 
    "D0_L1"
    "D0_signal"
)
INPUTFILE=(
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V14_pp_20171023_prompt_D0_5020GeV_pythia8_20171005_pthatweight.root"
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V14_pp_20171023_prompt_Ds_5020GeV_pythia8_20171005_pthatweight.root"
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V14_pp_20171023_prompt_D0_5020GeV_pythia8_20171005_pthatweight.root"
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V14_pp_20171023_prompt_D0_5020GeV_pythia8_20171005_nocuts_pthatweight.root"
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V14_pp_20171023_prompt_D0_5020GeV_pythia8_20171005_pthatweight.root"
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V14_pp_20171023_prompt_D0_5020GeV_pythia8_20171005_pthatweight.root"
    # "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V14_pp_20171023_Dijet80_5020GeV_pythia8_20171005.root"
)
TREENAME=(
    "Dfinder/ntDkpi"
    "Dfinder/ntDPhikkpi"
    "Dfinder/ntDkpi"
    "Dfinder/ntDkpi"
    "Dfinder/ntDkpi"
    "Dfinder/ntDkpi"
)
SELECTIONS=(
    "(abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&Dtrk1highPurity&&Dtrk1Pt>1&&abs(Dtrk1Eta)<2.0&&Dtrk2highPurity&&Dtrk2Pt>2&&abs(Dtrk2Eta)<2.0&&TMath::Cos(Ddtheta)>0.9"
    "(abs(Dmass-1.9685)<0.1)&&(abs(DtktkResmass-1.01945)<0.08)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&Dtrk1highPurity&&Dtrk1Pt>1&&abs(Dtrk1Eta)<2.0&&DRestrk1highPurity&&DRestrk1Pt>1&&abs(DRestrk1Eta<2.0)&&DRestrk2highPurity&&DRestrk2Pt>1&&abs(DRestrk2Eta<2.0)&&TMath::Cos(Ddtheta)>0.9"
    "Dsize==1&&(abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&Dtrk1highPurity&&Dtrk1Pt>1&&abs(Dtrk1Eta)<2.0&&Dtrk2highPurity&&Dtrk2Pt>1&&abs(Dtrk2Eta)<2.0&&TMath::Cos(Ddtheta)>0.9"
    "(abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&Dtrk1highPurity&&Dtrk1Pt>1&&abs(Dtrk1Eta)<2.0&&Dtrk2highPurity&&Dtrk2Pt>1&&abs(Dtrk2Eta)<2.0&&TMath::Cos(Ddtheta)>0.9"
    "(abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&Dtrk1highPurity&&Dtrk1Pt>1&&abs(Dtrk1Eta)<2.0&&Dtrk2highPurity&&Dtrk2Pt>1&&abs(Dtrk2Eta)<2.0&&TMath::Cos(Ddtheta)>0.9"
    "Dgen==23333&&(abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.10&&Dtrk1highPurity&&Dtrk1Pt>1&&abs(Dtrk1Eta)<2.0&&Dtrk2highPurity&&Dtrk2Pt>1&&abs(Dtrk2Eta)<2.0&&TMath::Cos(Ddtheta)>0.9"
)

BRANCHNAME=(
    "Dpt"
    "Dpt"
    "Dpt"
    "Dpt"
    "Dpt"
    "Dpt"
)
PATHS=(
    "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
    "HLT_DsPPTrackingGlobal_Dpt8_v1 L1_SingleJet16_Final HLT_DsPPTrackingGlobal_Dpt15_v1 L1_SingleJet24_Final HLT_DsPPTrackingGlobal_Dpt30_v1 L1_SingleJet40_Final HLT_DsPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
    "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
    "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
    "L1_SingleJet16_Final 1 L1_SingleJet24_Final 1 L1_SingleJet40_Final 1 L1_SingleJet44_Final 1"
    "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
)

##
g++ turnonall.C $(root-config --cflags --libs) -g -o turnonall.exe

for i in ${CASES[@]}
do
    ./turnonall.exe "${INPUTFILE[i]}" "${OUTPUTNAME[i]}_${WEIGHT}" "${TREENAME[i]}" "${BRANCHNAME[i]}" "$WEIGHT" "${SELECTIONS[i]}" ${PATHS[i]}
done

rm turnonall.exe