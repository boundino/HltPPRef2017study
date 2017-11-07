#!/bin/bash

CASES=(0 1 2 3 4)

##

OUTPUTNAME=(
    "D0_v33_HLT_Pthat100"
    "D0_v33_L1_Pthat100"
    "D0_v33_HLT"
    "D0_v33_L1"
    "trk_v33_HLT"
)
INPUTFILE=(
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V33_pp_20171106_prompt_D0pt0p0_Pthat100_TuneCUETP8M1_5020GeV_pythia8_20171005.root"
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V33_pp_20171106_prompt_D0pt0p0_Pthat100_TuneCUETP8M1_5020GeV_pythia8_20171005.root"
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V33_pp_20171106_prompt_D0_TuneCUETP8M1_5020GeV_pythia8_20171005_pthatweight.root"
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V33_pp_20171106_prompt_D0_TuneCUETP8M1_5020GeV_pythia8_20171005_pthatweight.root"
    "/export/d00/scratch/jwang/HLTppRef/crab_EvtMatching_V33_pp_20171106_Dijet_5020GeV_pythia8_20171005.root"
)
WEIGHT=(
    "1"
    "1"
    "pthatweight"
    "pthatweight"
    "1"
)
XTITLE=(
    "leading D^{0} p_{T} (GeV/c)"
    "leading D^{0} p_{T} (GeV/c)"
    "leading D^{0} p_{T} (GeV/c)"
    "leading D^{0} p_{T} (GeV/c)"
    "leading track p_{T} (GeV/c)"
)
TREENAME=(
    "Dfinder/ntDkpi"
    "Dfinder/ntDkpi"
    "Dfinder/ntDkpi"
    "Dfinder/ntDkpi"
    "ppTrack/trackTree"
)
SELECTIONS=(
    "(abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&TMath::Cos(Ddtheta)>0.9&&Dtrk1highPurity&&Dtrk1Pt>1&&TMath::Abs(Dtrk1Eta)<1.0&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.1&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer))<0.15&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&Dtrk2highPurity&&Dtrk2Pt>1&&TMath::Abs(Dtrk2Eta)<1.0&&TMath::Abs(Dtrk2PtErr/Dtrk2Pt)<0.1&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer))<0.15&&(Dtrk2PixelHit+Dtrk2StripHit)>=11"
    "(abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&TMath::Cos(Ddtheta)>0.9&&Dtrk1highPurity&&Dtrk1Pt>1&&TMath::Abs(Dtrk1Eta)<1.0&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.1&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer))<0.15&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&Dtrk2highPurity&&Dtrk2Pt>1&&TMath::Abs(Dtrk2Eta)<1.0&&TMath::Abs(Dtrk2PtErr/Dtrk2Pt)<0.1&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer))<0.15&&(Dtrk2PixelHit+Dtrk2StripHit)>=11"
    "(abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&TMath::Cos(Ddtheta)>0.9&&Dtrk1highPurity&&Dtrk1Pt>1&&TMath::Abs(Dtrk1Eta)<1.0&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.1&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer))<0.15&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&Dtrk2highPurity&&Dtrk2Pt>1&&TMath::Abs(Dtrk2Eta)<1.0&&TMath::Abs(Dtrk2PtErr/Dtrk2Pt)<0.1&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer))<0.15&&(Dtrk2PixelHit+Dtrk2StripHit)>=11"
    "(abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&TMath::Cos(Ddtheta)>0.9&&Dtrk1highPurity&&Dtrk1Pt>1&&TMath::Abs(Dtrk1Eta)<1.0&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.1&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer))<0.15&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&Dtrk2highPurity&&Dtrk2Pt>1&&TMath::Abs(Dtrk2Eta)<1.0&&TMath::Abs(Dtrk2PtErr/Dtrk2Pt)<0.1&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer))<0.15&&(Dtrk2PixelHit+Dtrk2StripHit)>=11"
    "highPurity&&TMath::Abs(trkEta)<1.&&trkAlgo!=11&&TMath::Abs(trkPtError/trkPt)<0.1&&TMath::Abs(trkDz1/trkDzError1)<3&&TMath::Abs(trkDxy1/trkDxyError1)<3&&trkNHit>=11&&((trkChi2/trkNdof)/trkNlayer)<0.15"
)
BRANCHNAME=(
    "Max"'$'"(Dpt*(${SELECTIONS[0]}))"
    "Max"'$'"(Dpt*(${SELECTIONS[1]}))"
    "Max"'$'"(Dpt*(${SELECTIONS[2]}))"
    "Max"'$'"(Dpt*(${SELECTIONS[3]}))"
    "Max"'$'"(trkPt*(${SELECTIONS[4]}))"
)

PATHS=(
    "HLT_HIDmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_BptxAND_Final HLT_HIDmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_HIDmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_HIDmesonPPTrackingGlobal_Dpt40_v1 L1_SingleJet32_Final HLT_HIDmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final HLT_HIDmesonPPTrackingGlobal_Dpt60_v1 L1_SingleJet60_Final"
    "L1_SingleJet8_BptxAND_Final 1 L1_SingleJet16_Final 1 L1_SingleJet24_Final 1 L1_SingleJet32_Final 1 L1_SingleJet44_Final 1 L1_SingleJet60_Final 1"
    "HLT_HIDmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_BptxAND_Final HLT_HIDmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_HIDmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_HIDmesonPPTrackingGlobal_Dpt40_v1 L1_SingleJet32_Final HLT_HIDmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final HLT_HIDmesonPPTrackingGlobal_Dpt60_v1 L1_SingleJet60_Final"
    "L1_SingleJet8_BptxAND_Final 1 L1_SingleJet16_Final 1 L1_SingleJet24_Final 1 L1_SingleJet32_Final 1 L1_SingleJet44_Final 1 L1_SingleJet60_Final 1"
    "HLT_HIFullTracks_HighPt18_v1 L1_SingleJet16_Final HLT_HIFullTracks_HighPt24_v1 L1_SingleJet24_Final HLT_HIFullTracks_HighPt34_v1 L1_SingleJet32_Final HLT_HIFullTracks_HighPt45_v1  L1_SingleJet44_Final"
)

BINNING=(
    "const int nBin = 20; float bins[nBin+1]={4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100, 120, 140};"
    "const int nBin = 20; float bins[nBin+1]={4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100, 120, 140};"
    "const int nBin = 20; float bins[nBin+1]={4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100, 120, 140};"
    "const int nBin = 20; float bins[nBin+1]={4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100, 120, 140};"
    "const int nBin = 20; float bins[nBin+1]={0, 2, 4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100};"
)

##
for i in ${CASES[@]}
do
    sed '1i'"${BINNING[i]}" turnonall.C > turnonall_tmp.C
    g++ turnonall_tmp.C $(root-config --cflags --libs) -g -o turnonall_tmp.exe
    set -x
    ./turnonall_tmp.exe "${INPUTFILE[i]}" "${OUTPUTNAME[i]}_${WEIGHT[i]}" "${TREENAME[i]}" "${BRANCHNAME[i]}" "${XTITLE[i]}" "${WEIGHT[i]}" "${SELECTIONS[i]}" ${PATHS[i]}
    set +x
    rm turnonall_tmp.exe
    rm turnonall_tmp.C
done


# PATHS=(
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
#     "L1_SingleJet8_Final 1 L1_SingleJet16_Final 1 L1_SingleJet24_Final 1 L1_SingleJet32_Final 1 L1_SingleJet44_Final 1 L1_SingleJet60_Final 1"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_BptxAND_copy_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt40_v1 L1_SingleJet32_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt60_v1 L1_SingleJet60_Final"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_BptxAND_copy_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt40_v1 L1_SingleJet32_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt60_v1 L1_SingleJet60_Final"
#     "HLT_DmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_BptxAND_copy_Final HLT_DmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_DmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_DmesonPPTrackingGlobal_Dpt40_v1 L1_SingleJet32_Final HLT_DmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet40_Final HLT_DmesonPPTrackingGlobal_Dpt60_v1 L1_SingleJet60_Final"
#     "HLT_HIDmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_BptxAND_Final HLT_HIDmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final HLT_HIDmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final HLT_HIDmesonPPTrackingGlobal_Dpt40_v1 L1_SingleJet32_Final HLT_HIDmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final HLT_HIDmesonPPTrackingGlobal_Dpt60_v1 L1_SingleJet60_Final"
# )

