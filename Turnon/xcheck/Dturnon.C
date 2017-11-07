#include "Dbranches.h"
#include <TCanvas.h>
#include <TFile.h>
#include <iostream>
#include <iomanip>
#include <TH2F.h>
#include <TGraphAsymmErrors.h>
#include <TMath.h>

int maxevt = -1;
Color_t tcolor[] = {kAzure+2, kRed+2, kGreen+3, kMagenta+2, kCyan+1, kOrange+6};
void Dturnon(TString inputname, std::vector<TString> HLTcut, std::vector<TString> L1cut)
{
  if(HLTcut.size() != L1cut.size()) return;
  xjjroot::setgstyle();

  TFile* inputfile = new TFile(inputname.Data());
  TTree* hlt = (TTree*)inputfile->Get("hltbitanalysis/HltTree");
  hlt->SetBranchStatus("*",0);
  TTree* ntD = (TTree*)inputfile->Get("Dfinder/ntDkpi");
  ntD->SetBranchStatus("*",0);
  TTree* hi = (TTree*)inputfile->Get("hiEvtAnalyzer/HiTree");
  hi->SetBranchStatus("*",0);

  std::vector<int> HLTpath(HLTcut.size()); 
  for(int k=0;k<HLTcut.size();k++)
    xjjroot::setbranchaddress(hlt, HLTcut.at(k).Data(), &(HLTpath.at(k)));
  std::vector<int> L1path(HLTcut.size(), 1);
  for(int k=0;k<L1cut.size();k++)
    {
      if(L1cut.at(k)!="1") xjjroot::setbranchaddress(hlt, L1cut.at(k).Data(), &(L1path.at(k)));
    }
  setDbranchesaddress(ntD);
  Float_t pthatweight; xjjroot::setbranchaddress(hi, "pthatweight", &pthatweight);

  std::vector<TH1D*> hnorm(HLTcut.size());
  std::vector<TH1D*> hdenorm(HLTcut.size());
  std::vector<TGraphAsymmErrors*> geff(HLTcut.size());
  for(int k=0;k<HLTcut.size();k++)
    {
      hnorm[k] = new TH1D(Form("hnorm_%d",k),"",20,0,100);
      hnorm[k]->Sumw2();
      hdenorm[k] = new TH1D(Form("hdenorm_%d",k),"",20,0,100);
      hdenorm[k]->Sumw2();
      geff[k] = new TGraphAsymmErrors;
      xjjroot::setthgrstyle(geff[k], tcolor[k], 20, 1.1, kBlack);
    }
  int eventnumber = (maxevt<ntD->GetEntries()&&maxevt>0)?maxevt:ntD->GetEntries();
  for(int i=0;i<eventnumber;i++)
    {
      if(i%10000==0) std::cout<<std::setiosflags(std::ios::left)<<std::setw(10)<<i<<" / "<<std::setw(10)<<eventnumber<<std::endl;
      hlt->GetEntry(i);
      ntD->GetEntry(i);
      hi->GetEntry(i);
      
      float leadingDpt=0;
      for(int j=0;j<Dsize;j++)
        {
          if((abs(Dmass[j]-1.8696)<0.1)&&(DsvpvDistance[j]/DsvpvDisErr[j])>2.5&&Dchi2cl[j]>0.10&&TMath::Cos(Ddtheta[j])>0.9&&Dalpha[j]<0.12 &&
             Dtrk1highPurity[j]&&Dtrk1Pt[j]>1&&TMath::Abs(Dtrk1Eta[j])<1.0&&TMath::Abs(Dtrk1PtErr[j]/Dtrk1Pt[j])<0.1&&(Dtrk1Chi2ndf[j]/(Dtrk1nStripLayer[j]+Dtrk1nPixelLayer[j]))<0.15&&(Dtrk1PixelHit[j]+Dtrk1StripHit[j])>=11&&
             Dtrk2highPurity[j]&&Dtrk2Pt[j]>1&&TMath::Abs(Dtrk2Eta[j])<1.0&&TMath::Abs(Dtrk2PtErr[j]/Dtrk2Pt[j])<0.1&&(Dtrk2Chi2ndf[j]/(Dtrk2nStripLayer[j]+Dtrk2nPixelLayer[j]))<0.15&&(Dtrk2PixelHit[j]+Dtrk2StripHit[j])>=11&&
             Dpt[j]>leadingDpt) {leadingDpt = Dpt[j];}
        }

      if(leadingDpt>0)
        {
          for(int k=0;k<HLTcut.size();k++)
            {
              if(L1path.at(k)==1) hdenorm[k]->Fill(leadingDpt, pthatweight);
              if(L1path.at(k)==1 && HLTpath.at(k)==1) hnorm[k]->Fill(leadingDpt, pthatweight);
            }
        }
    }
  for(int k=0;k<HLTcut.size();k++)
    geff[k]->BayesDivide(hnorm[k], hdenorm[k]);

  TH2F* hempty = new TH2F("hempty", ";leading D p_{T} (GeV/c);Efficiency", 10, 0, 80, 10, 0, 1.0);
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
  c->SaveAs("plots/hDturnon.pdf");
}

int main()
{
  Dturnon("/export/d00/scratch/jwang/HLTppRef/crab_HLT_V14_pp_20171023_prompt_D0_5020GeV_pythia8_20171005_nocuts_pthatweight.root",
          std::vector<TString>{"HLT_DmesonPPTrackingGlobal_Dpt8_v1", "HLT_DmesonPPTrackingGlobal_Dpt15_v1", "HLT_DmesonPPTrackingGlobal_Dpt30_v1", "HLT_DmesonPPTrackingGlobal_Dpt50_v1"},
          std::vector<TString>{"L1_SingleJet16_Final", "L1_SingleJet24_Final", "L1_SingleJet32_Final", "L1_SingleJet44_Final"});
  // Dturnon("/export/d00/scratch/jwang/HLTppRef/crab_HLT_V14_pp_20171023_prompt_D0_5020GeV_pythia8_20171005_nocuts_pthatweight.root",
  //         std::vector<TString>{"L1_SingleJet8_Final", "L1_SingleJet16_Final", "L1_SingleJet24_Final", "L1_SingleJet32_Final", "L1_SingleJet44_Final", "L1_SingleJet60_Final"},
  //         std::vector<TString>{"1", "1", "1", "1", "1", "1"});
}
