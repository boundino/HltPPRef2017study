#!/bin/bash

CASES=(12 13)

##

OUTPUTNAME=(
    "D0_v33_HLT"
    "D0_v33_L1"
    "trk_v33_HLT"
    "Ds_v33_HLT_Pthat100"
    "D0_data_306550_HLT"
    "D0_data_306550_L1"
    "D0_data_306580_HLT"
    "D0_data_306580_L1"
    "trk_data_306550_HLT"
    "trk_data_306550_L1"
    "trk_data_306580_HLT"
    "trk_data_306580_L1"
    "trk_data_306550_ZB_HLT"
    "trk_data_306550_ZB_L1"
)
INPUTFILE=(
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V33_pp_20171106_prompt_D0_TuneCUETP8M1_5020GeV_pythia8_20171005_pthatweight.root"
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V33_pp_20171106_prompt_D0_TuneCUETP8M1_5020GeV_pythia8_20171005_pthatweight.root"
    "/export/d00/scratch/jwang/HLTppRef/crab_EvtMatching_V33_pp_20171106_Dijet_5020GeV_pythia8_20171005.root"
    "/export/d00/scratch/jwang/HLTppRef/crab_HLT_V33_pp_20171106_prompt_Dspt0p0_Pthat100_TuneCUETP8M1_5020GeV_pythia8_20171005.root"
    "/afs/cern.ch/work/w/wangj/public/HiForestAOD_20171114_run306550_streamPhysicsHadronsTaus.root"
    "/afs/cern.ch/work/w/wangj/public/HiForestAOD_20171114_run306550_streamPhysicsHadronsTaus.root"
    "/afs/cern.ch/work/w/wangj/public/HiForestAOD_20171114_run306580_streamPhysicsHadronsTaus.root"
    "/afs/cern.ch/work/w/wangj/public/HiForestAOD_20171114_run306580_streamPhysicsHadronsTaus.root"
    "/afs/cern.ch/work/w/wangj/public/HiForestAOD_20171114_run306550_streamPhysicsHadronsTaus.root"
    "/afs/cern.ch/work/w/wangj/public/HiForestAOD_20171114_run306550_streamPhysicsHadronsTaus.root"
    # "/eos/cms/store/group/phys_heavyions/wangj/HLT2017/HiForestAOD_20171114_run306580_ls0121_streamPhysicsHadronsTaus.root"
    # "/eos/cms/store/group/phys_heavyions/wangj/HLT2017/HiForestAOD_20171114_run306580_ls0121_streamPhysicsHadronsTaus.root"
    "/afs/cern.ch/work/w/wangj/public/HiForestAOD_20171114_run306580_ls0121_ls0202_streamPhysicsHadronsTaus.root"
    "/afs/cern.ch/work/w/wangj/public/HiForestAOD_20171114_run306580_ls0121_ls0202_streamPhysicsHadronsTaus.root"
    "/afs/cern.ch/work/w/wangj/public/HiForestAOD_20171114_run306550_streamPhysicsHIZeroBias1.root"
    "/afs/cern.ch/work/w/wangj/public/HiForestAOD_20171114_run306550_streamPhysicsHIZeroBias1.root"
)
XTITLE=(
    "leading D^{0} p_{T} (GeV/c)"
    "leading D^{0} p_{T} (GeV/c)"
    "leading track p_{T} (GeV/c)"
    "leading D_{s} p_{T} (GeV/c)"
    "leading D^{0} p_{T} (GeV/c)"
    "leading D^{0} p_{T} (GeV/c)"
    "leading D^{0} p_{T} (GeV/c)"
    "leading D^{0} p_{T} (GeV/c)"
    "leading track p_{T} (GeV/c)"
    "leading track p_{T} (GeV/c)"
    "leading track p_{T} (GeV/c)"
    "leading track p_{T} (GeV/c)"
    "leading track p_{T} (GeV/c)"
    "leading track p_{T} (GeV/c)"
)
TREENAME=(
    "Dfinder/ntDkpi"
    "Dfinder/ntDkpi"
    "ppTrack/trackTree"
    "Dfinder/ntDPhikkpi"
    "Dfinder/ntDkpi"
    "Dfinder/ntDkpi"
    "Dfinder/ntDkpi"
    "Dfinder/ntDkpi"
    "ppTrack/trackTree"
    "ppTrack/trackTree"
    "ppTrack/trackTree"
    "ppTrack/trackTree"
    "ppTrack/trackTree"
    "ppTrack/trackTree"
)
SELECTIONS=(
    "(TMath::Abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&TMath::Cos(Ddtheta)>0.9&&Dtrk1highPurity&&Dtrk1Pt>1&&TMath::Abs(Dtrk1Eta)<1.0&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.1&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer))<0.15&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&Dtrk2highPurity&&Dtrk2Pt>1&&TMath::Abs(Dtrk2Eta)<1.0&&TMath::Abs(Dtrk2PtErr/Dtrk2Pt)<0.1&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer))<0.15&&(Dtrk2PixelHit+Dtrk2StripHit)>=11"
    "(TMath::Abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&TMath::Cos(Ddtheta)>0.9&&Dtrk1highPurity&&Dtrk1Pt>1&&TMath::Abs(Dtrk1Eta)<1.0&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.1&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer))<0.15&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&Dtrk2highPurity&&Dtrk2Pt>1&&TMath::Abs(Dtrk2Eta)<1.0&&TMath::Abs(Dtrk2PtErr/Dtrk2Pt)<0.1&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer))<0.15&&(Dtrk2PixelHit+Dtrk2StripHit)>=11"
    "highPurity&&TMath::Abs(trkEta)<1.&&trkAlgo!=11&&TMath::Abs(trkPtError/trkPt)<0.1&&TMath::Abs(trkDz1/trkDzError1)<3&&TMath::Abs(trkDxy1/trkDxyError1)<3&&trkNHit>=11&&((trkChi2/trkNdof)/trkNlayer)<0.15"
    "Dgen==23333&&(TMath::Abs(Dmass-1.9685)<0.1)&&(TMath::Abs(DtktkResmass-1.01945)<0.08)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&Dtrk1highPurity&&Dtrk1Pt>1&&TMath::Abs(Dtrk1Eta)<2.0&&DRestrk1highPurity&&DRestrk1Pt>1&&TMath::Abs(DRestrk1Eta)<2.0&&DRestrk2highPurity&&DRestrk2Pt>1&&TMath::Abs(DRestrk2Eta)<2.0&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.1&&TMath::Abs(DRestrk1PtErr/DRestrk1Pt)<0.1&&TMath::Abs(DRestrk2PtErr/DRestrk2Pt)<0.1&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer))<0.15&&(Dtrk1PixelHit+Dtrk1StripHit)>=11"
    "(TMath::Abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&TMath::Cos(Ddtheta)>0.9&&Dtrk1highPurity&&Dtrk1Pt>1&&TMath::Abs(Dtrk1Eta)<1.0&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.1&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer))<0.15&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&Dtrk2highPurity&&Dtrk2Pt>1&&TMath::Abs(Dtrk2Eta)<1.0&&TMath::Abs(Dtrk2PtErr/Dtrk2Pt)<0.1&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer))<0.15&&(Dtrk2PixelHit+Dtrk2StripHit)>=11"
    "(TMath::Abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&TMath::Cos(Ddtheta)>0.9&&Dtrk1highPurity&&Dtrk1Pt>1&&TMath::Abs(Dtrk1Eta)<1.0&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.1&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer))<0.15&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&Dtrk2highPurity&&Dtrk2Pt>1&&TMath::Abs(Dtrk2Eta)<1.0&&TMath::Abs(Dtrk2PtErr/Dtrk2Pt)<0.1&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer))<0.15&&(Dtrk2PixelHit+Dtrk2StripHit)>=11"
    "(TMath::Abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&TMath::Cos(Ddtheta)>0.9&&Dtrk1highPurity&&Dtrk1Pt>1&&TMath::Abs(Dtrk1Eta)<1.0&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.1&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer))<0.15&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&Dtrk2highPurity&&Dtrk2Pt>1&&TMath::Abs(Dtrk2Eta)<1.0&&TMath::Abs(Dtrk2PtErr/Dtrk2Pt)<0.1&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer))<0.15&&(Dtrk2PixelHit+Dtrk2StripHit)>=11"
    "(TMath::Abs(Dmass-1.8696)<0.1)&&(DsvpvDistance/DsvpvDisErr)>2.5&&Dchi2cl>0.10&&TMath::Cos(Ddtheta)>0.9&&Dtrk1highPurity&&Dtrk1Pt>1&&TMath::Abs(Dtrk1Eta)<1.0&&TMath::Abs(Dtrk1PtErr/Dtrk1Pt)<0.1&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer))<0.15&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&Dtrk2highPurity&&Dtrk2Pt>1&&TMath::Abs(Dtrk2Eta)<1.0&&TMath::Abs(Dtrk2PtErr/Dtrk2Pt)<0.1&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer))<0.15&&(Dtrk2PixelHit+Dtrk2StripHit)>=11"
    "highPurity&&TMath::Abs(trkEta)<1.&&trkAlgo!=11&&TMath::Abs(trkPtError/trkPt)<0.1&&TMath::Abs(trkDz1/trkDzError1)<3&&TMath::Abs(trkDxy1/trkDxyError1)<3&&trkNHit>=11&&((trkChi2/trkNdof)/trkNlayer)<0.15"
    "highPurity&&TMath::Abs(trkEta)<1.&&trkAlgo!=11&&TMath::Abs(trkPtError/trkPt)<0.1&&TMath::Abs(trkDz1/trkDzError1)<3&&TMath::Abs(trkDxy1/trkDxyError1)<3&&trkNHit>=11&&((trkChi2/trkNdof)/trkNlayer)<0.15"
    "highPurity&&TMath::Abs(trkEta)<1.&&trkAlgo!=11&&TMath::Abs(trkPtError/trkPt)<0.1&&TMath::Abs(trkDz1/trkDzError1)<3&&TMath::Abs(trkDxy1/trkDxyError1)<3&&trkNHit>=11&&((trkChi2/trkNdof)/trkNlayer)<0.15"
    "highPurity&&TMath::Abs(trkEta)<1.&&trkAlgo!=11&&TMath::Abs(trkPtError/trkPt)<0.1&&TMath::Abs(trkDz1/trkDzError1)<3&&TMath::Abs(trkDxy1/trkDxyError1)<3&&trkNHit>=11&&((trkChi2/trkNdof)/trkNlayer)<0.15"
    "highPurity&&TMath::Abs(trkEta)<1.&&trkAlgo!=11&&TMath::Abs(trkPtError/trkPt)<0.1&&TMath::Abs(trkDz1/trkDzError1)<3&&TMath::Abs(trkDxy1/trkDxyError1)<3&&trkNHit>=11&&((trkChi2/trkNdof)/trkNlayer)<0.15"
    "highPurity&&TMath::Abs(trkEta)<1.&&trkAlgo!=11&&TMath::Abs(trkPtError/trkPt)<0.1&&TMath::Abs(trkDz1/trkDzError1)<3&&TMath::Abs(trkDxy1/trkDxyError1)<3&&trkNHit>=11&&((trkChi2/trkNdof)/trkNlayer)<0.15"
)
BRANCHNAME=(
    "Max"'$'"(Dpt*(${SELECTIONS[0]}))"
    "Max"'$'"(Dpt*(${SELECTIONS[1]}))"
    "Max"'$'"(trkPt*(${SELECTIONS[2]}))"
    "Max"'$'"(Dpt*(${SELECTIONS[3]}))"
    "Max"'$'"(Dpt*(${SELECTIONS[4]}))"
    "Max"'$'"(Dpt*(${SELECTIONS[5]}))"
    "Max"'$'"(Dpt*(${SELECTIONS[6]}))"
    "Max"'$'"(Dpt*(${SELECTIONS[7]}))"
    "Max"'$'"(trkPt*(${SELECTIONS[8]}))"
    "Max"'$'"(trkPt*(${SELECTIONS[9]}))"
    "Max"'$'"(trkPt*(${SELECTIONS[10]}))"
    "Max"'$'"(trkPt*(${SELECTIONS[11]}))"
    "Max"'$'"(trkPt*(${SELECTIONS[12]}))"
    "Max"'$'"(trkPt*(${SELECTIONS[13]}))"
)

PATHS=(
    "1 HLT_HIDmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_BptxAND_Final 1 HLT_HIDmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final 1 HLT_HIDmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final 1 HLT_HIDmesonPPTrackingGlobal_Dpt40_v1 L1_SingleJet32_Final 1 HLT_HIDmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final 1 HLT_HIDmesonPPTrackingGlobal_Dpt60_v1 L1_SingleJet60_Final"
    "1 L1_SingleJet8_BptxAND_Final 1 1 L1_SingleJet16_Final 1 1 L1_SingleJet24_Final 1 1 L1_SingleJet32_Final 1 1 L1_SingleJet44_Final 1 1 L1_SingleJet60_Final 1"
    "1 HLT_HIFullTracks_HighPt18_v1 L1_SingleJet16_Final 1 HLT_HIFullTracks_HighPt24_v1 L1_SingleJet24_Final 1 HLT_HIFullTracks_HighPt34_v1 L1_SingleJet32_Final 1 HLT_HIFullTracks_HighPt45_v1  L1_SingleJet44_Final"
    "1 HLT_HIDsPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_BptxAND_Final 1 HLT_HIDsPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final 1 HLT_HIDsPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final 1 HLT_HIDsPPTrackingGlobal_Dpt40_v1 L1_SingleJet32_Final 1 HLT_HIDsPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final 1 HLT_HIDsPPTrackingGlobal_Dpt60_v1 L1_SingleJet60_Final"
    "1 HLT_HIDmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_BptxAND_Final 1 HLT_HIDmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final 1 HLT_HIDmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final 1 HLT_HIDmesonPPTrackingGlobal_Dpt40_v1 L1_SingleJet32_Final 1 HLT_HIDmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final 1 HLT_HIDmesonPPTrackingGlobal_Dpt60_v1 L1_SingleJet60_Final"
    "1 L1_SingleJet8_BptxAND_Final 1 1 L1_SingleJet16_Final 1 1 L1_SingleJet24_Final 1 1 L1_SingleJet32_Final 1 1 L1_SingleJet44_Final 1 1 L1_SingleJet60_Final 1"
    "1 HLT_HIDmesonPPTrackingGlobal_Dpt8_v1 L1_SingleJet8_BptxAND_Final 1 HLT_HIDmesonPPTrackingGlobal_Dpt15_v1 L1_SingleJet16_Final 1 HLT_HIDmesonPPTrackingGlobal_Dpt30_v1 L1_SingleJet24_Final 1 HLT_HIDmesonPPTrackingGlobal_Dpt40_v1 L1_SingleJet32_Final 1 HLT_HIDmesonPPTrackingGlobal_Dpt50_v1 L1_SingleJet44_Final 1 HLT_HIDmesonPPTrackingGlobal_Dpt60_v1 L1_SingleJet60_Final"
    "1 L1_SingleJet8_BptxAND_Final 1 1 L1_SingleJet16_Final 1 1 L1_SingleJet24_Final 1 1 L1_SingleJet32_Final 1 1 L1_SingleJet44_Final 1 1 L1_SingleJet60_Final 1"
    "1 HLT_HIFullTracks_HighPt18_v1 L1_SingleJet16_Final 1 HLT_HIFullTracks_HighPt24_v1 L1_SingleJet24_Final 1 HLT_HIFullTracks_HighPt34_v1 L1_SingleJet32_Final 1 HLT_HIFullTracks_HighPt45_v1  L1_SingleJet44_Final"
    "1 L1_SingleJet16_Final 1 1 L1_SingleJet24_Final 1 1 L1_SingleJet32_Final 1  1 L1_SingleJet44_Final 1"
    "1 HLT_HIFullTracks_HighPt18_v1 L1_SingleJet16_Final 1 HLT_HIFullTracks_HighPt24_v1 L1_SingleJet24_Final 1 HLT_HIFullTracks_HighPt34_v1 L1_SingleJet32_Final 1 HLT_HIFullTracks_HighPt45_v1  L1_SingleJet44_Final"
    "1 L1_SingleJet16_Final 1 1 L1_SingleJet24_Final 1 1 L1_SingleJet32_Final 1 1 L1_SingleJet44_Final 1"
    "1 HLT_HIFullTracks_HighPt18_v1 L1_SingleJet16_Final 1 HLT_HIFullTracks_HighPt24_v1 L1_SingleJet24_Final 1 HLT_HIFullTracks_HighPt34_v1 L1_SingleJet32_Final 1 HLT_HIFullTracks_HighPt45_v1  L1_SingleJet44_Final"
    "1 L1_SingleJet16_Final 1 1 L1_SingleJet24_Final 1 1 L1_SingleJet32_Final 1 1 L1_SingleJet44_Final 1"
)

BINNING=(
    "const int nBin = 20; float bins[nBin+1]={4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100, 120, 140};"
    "const int nBin = 20; float bins[nBin+1]={4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100, 120, 140};"
    "const int nBin = 20; float bins[nBin+1]={0, 2, 4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100};"
    "const int nBin = 20; float bins[nBin+1]={4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100, 120, 140};"
    "const int nBin = 18; float bins[nBin+1]={4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100};"
    "const int nBin = 18; float bins[nBin+1]={4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100};"
    "const int nBin = 14; float bins[nBin+1]={4, 8, 15, 18, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 100};"
    "const int nBin = 14; float bins[nBin+1]={4, 8, 15, 18, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 100};"
    "const int nBin = 20; float bins[nBin+1]={0, 2, 4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100};"
    "const int nBin = 20; float bins[nBin+1]={0, 2, 4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100};"
    "const int nBin = 20; float bins[nBin+1]={0, 2, 4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100};"
    "const int nBin = 20; float bins[nBin+1]={0, 2, 4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100};"
    "const int nBin = 20; float bins[nBin+1]={0, 2, 4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100};"
    "const int nBin = 20; float bins[nBin+1]={0, 2, 4, 6, 8, 10, 12, 15, 18, 20, 24, 28, 30, 34, 40, 45, 50, 60, 70, 80, 100};"
)

##
for i in ${CASES[@]}
do
    sed '1i'"${BINNING[i]}" turnonall.C > turnonall_tmp.C
    g++ turnonall_tmp.C $(root-config --cflags --libs) -g -o turnonall_tmp.exe
    set -x
    ./turnonall_tmp.exe "${INPUTFILE[i]}" "${OUTPUTNAME[i]}" "${TREENAME[i]}" "${BRANCHNAME[i]}" "${XTITLE[i]}" "1" "${SELECTIONS[i]}" ${PATHS[i]}
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

