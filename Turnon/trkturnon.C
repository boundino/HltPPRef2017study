#include "trkbranches.h"
#include <TCanvas.h>
#include <TFile.h>
#include <iostream>
#include <iomanip>
#include <TH2F.h>
#include <TGraphAsymmErrors.h>

int maxevt = -1;
Color_t tcolor[] = {kAzure+2, kRed+2, kGreen+3, kMagenta+2, kCyan+1, kOrange+6};
void trkturnon(TString inputname, std::vector<TString> HLTcut, std::vector<TString> L1cut)
{
  if(HLTcut.size() != L1cut.size()) return;
  xjjroot::setgstyle();

  TFile* inputfile = new TFile(inputname.Data());
  TTree* hlt = (TTree*)inputfile->Get("hltbitanalysis/HltTree");
  hlt->SetBranchStatus("*",0);
  TTree* ntTrk = (TTree*)inputfile->Get("ppTrack/trackTree");
  ntTrk->SetBranchStatus("*",0);

  std::vector<int> HLTpath(HLTcut.size()); 
  for(int k=0;k<HLTcut.size();k++)
    xjjroot::setbranchaddress(hlt, HLTcut.at(k).Data(), &(HLTpath.at(k)));
  std::vector<int> L1path(HLTcut.size(), 1);
  for(int k=0;k<L1cut.size();k++)
    {
      if(L1cut.at(k)!="1") xjjroot::setbranchaddress(hlt, L1cut.at(k).Data(), &(L1path.at(k)));
    }
  settrkbranchesaddress(ntTrk);

  std::vector<TH1D*> hnorm(HLTcut.size());
  std::vector<TH1D*> hdenorm(HLTcut.size());
  std::vector<TGraphAsymmErrors*> geff(HLTcut.size());
  for(int k=0;k<HLTcut.size();k++)
    {
      hnorm[k] = new TH1D(Form("hnorm_%d",k),"",50,0,100);
      hnorm[k]->Sumw2();
      hdenorm[k] = new TH1D(Form("hdenorm_%d",k),"",50,0,100);
      hdenorm[k]->Sumw2();
      geff[k] = new TGraphAsymmErrors;
      xjjroot::setthgrstyle(geff[k], tcolor[k], 20, 1.1, kBlack);
    }
  int eventnumber = (maxevt<ntTrk->GetEntries()&&maxevt>0)?maxevt:ntTrk->GetEntries();
  for(int i=0;i<eventnumber;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<i<<" / "<<std::setw(10)<<eventnumber<<std::endl;
      hlt->GetEntry(i);
      ntTrk->GetEntry(i);
      
      float leadingtrkpt=0;
      for(int j=0;j<nTrk;j++)
        {
          if(highPurity[j]&&TMath::Abs(trkEta[j])<1.&&trkAlgo[j]!=11&&TMath::Abs(trkPtError[j]/trkPt[j])<0.1&&TMath::Abs(trkDz1[j]/trkDzError1[j])<3&&TMath::Abs(trkDxy1[j]/trkDxyError1[j])<3&&trkNHit[j]>=11&&(trkChi2[j]/trkNdof[j])/trkNlayer[j]<0.15 &&
             trkPt[j]>leadingtrkpt) {leadingtrkpt = trkPt[j];}
        }

      if(leadingtrkpt>0)
        {
          for(int k=0;k<HLTcut.size();k++)
            {
              if(L1path.at(k)==1) hdenorm[k]->Fill(leadingtrkpt);
              if(L1path.at(k)==1 && HLTpath.at(k)==1) hnorm[k]->Fill(leadingtrkpt);
            }
        }
    }
  for(int k=0;k<HLTcut.size();k++)
    geff[k]->BayesDivide(hnorm[k], hdenorm[k]);

  TH2F* hempty = new TH2F("hempty", ";leading trk p_{T} (GeV/c);Efficiency", 10, 0, 100, 10, 0, 1.0);
  xjjroot::sethempty(hempty);
  TCanvas* c = new TCanvas("c", "", 600, 600);
  hempty->Draw();
  TLegend* leg = new TLegend(0.40, 0.70-0.055*geff.size(), 0.85, 0.70);
  xjjroot::setleg(leg, 0.025);
  for(int k=0;k<geff.size();k++)
    {
      geff[k]->Draw("pesame");
      leg->AddEntry(geff[k], HLTcut[k].Data(), "pl");
    }
  leg->Draw();
  c->SaveAs("plots/htrkturnon.pdf");
}

int main()
{
  // trkturnon("/export/d00/scratch/jwang/HLTppRef/crab_EvtMatching_V14_pp_20171027_Dijet_5020GeV_pythia8_20171005.root",
  //           std::vector<TString>{"HLT_FullTracks_HighPt18_v1", "HLT_FullTracks_HighPt24_v1", "HLT_FullTracks_HighPt34_v1", "HLT_FullTracks_HighPt45_v1"},
  //           std::vector<TString>{"1", "1", "1", "1"});

  trkturnon("/export/d00/scratch/jwang/HLTppRef/crab_EvtMatching_V14_pp_20171027_Dijet_5020GeV_pythia8_20171005.root",
            std::vector<TString>{"L1_SingleJet8_Final", "L1_SingleJet16_Final", "L1_SingleJet24_Final", "L1_SingleJet32_Final", "L1_SingleJet44_Final", "L1_SingleJet60_Final"},
            std::vector<TString>{"1", "1", "1", "1", "1", "1"});
}
