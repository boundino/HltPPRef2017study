#!/bin/bash

iSAMPLE=2
iVAR=(0 5)

WEIGHT="pthatweight"
VARS=(
    "DsvpvDistance/DsvpvDisErr decaylength 2.0 30.0"
    "Dalpha alpha 0 0.12"
    "Dmass Dmass 1.75 1.97"
    "DlxyBS/DlxyBSErr lxyBSsig 0.0 20.0"
    "Dchi2cl chi2cl 0 1.0"
    "Dy Dy -2 2"
    "Dtrk1Eta Dtrk1Eta -2 2"
    "Dtrk2Eta Dtrk2Eta -2 2"
    "TMath::Cos(Ddtheta) costheta 0.8 1"
)

OUTPUTNAME=(
    "D0_default" 
    "D0_nocuts" 
    "Ds_default" 
)
INPUTFILE=(
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V14_pp_20171023_prompt_D0_5020GeV_pythia8_20171005_pthatweight.root"
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V14_pp_20171023_prompt_D0_5020GeV_pythia8_20171005_nocuts_pthatweight.root"
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V14_pp_20171023_prompt_Ds_5020GeV_pythia8_20171005_pthatweight.root"
)
TREENAME=(
    "ntDkpi"
    "ntDkpi"
    "ntDPhikkpi"
)
SELECTIONS=(
    "(abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&Dtrk1highPurity&&Dtrk1Pt>1&&abs(Dtrk1Eta)<2.0&&Dtrk2highPurity&&Dtrk2Pt>1&&abs(Dtrk2Eta)<2.0&&TMath::Cos(Ddtheta)>0.9"
    "(abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&Dtrk1highPurity&&Dtrk1Pt>1&&abs(Dtrk1Eta)<2.0&&Dtrk2highPurity&&Dtrk2Pt>1&&abs(Dtrk2Eta)<2.0&&TMath::Cos(Ddtheta)>0.9"
    "(abs(Dmass-1.9685)<0.1)&&(abs(DtktkResmass-1.01945)<0.08)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&Dtrk1highPurity&&Dtrk1Pt>1&&abs(Dtrk1Eta)<2.0&&DRestrk1highPurity&&DRestrk1Pt>1&&abs(DRestrk1Eta<2.0)&&DRestrk2highPurity&&DRestrk2Pt>1&&abs(DRestrk2Eta<2.0)&&TMath::Cos(Ddtheta)>0.9"
)
PATHDS=(
    "Dmeson"
    "Dmeson"
    "Ds"
)

#
PATHS=(
    "8 HLT_${PATHDS[iSAMPLE]}PPTrackingGlobal_Dpt8_v1 L1_SingleJet16_Final"
    "15 HLT_${PATHDS[iSAMPLE]}PPTrackingGlobal_Dpt15_v1 L1_SingleJet24_Final"
    "30 HLT_${PATHDS[iSAMPLE]}PPTrackingGlobal_Dpt30_v1 L1_SingleJet40_Final"
    "50 HLT_${PATHDS[iSAMPLE]}PPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
)

##
g++ turnonvar.C $(root-config --cflags --libs) -g -o turnonvar.exe
for i in ${iVAR[@]}
do
    ./turnonvar.exe "${INPUTFILE[iSAMPLE]}" "${OUTPUTNAME[iSAMPLE]}_${WEIGHT}" "${TREENAME[iSAMPLE]}" "${WEIGHT}" "${SELECTIONS[iSAMPLE]}" ${VARS[i]} ${PATHS[0]} ${PATHS[1]} ${PATHS[2]} ${PATHS[3]}
done

# PATHS=(
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
#     "HLT_DsPPTrackingGlobal_Dpt8_v1 L1_SingleJet16_Final HLT_DsPPTrackingGlobal_Dpt15_v1 L1_SingleJet24_Final HLT_DsPPTrackingGlobal_Dpt30_v1 L1_SingleJet40_Final HLT_DsPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
#     "HLT_DsPPTrackingGlobal_Dpt8_v1 L1_SingleJet16_Final HLT_DsPPTrackingGlobal_Dpt15_v1 L1_SingleJet24_Final HLT_DsPPTrackingGlobal_Dpt30_v1 L1_SingleJet40_Final HLT_DsPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
# )

rm turnonvar.exe



