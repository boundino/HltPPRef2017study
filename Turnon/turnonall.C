#include "xjjrootuti.h"
#include <TCanvas.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TH2F.h>
#include <TCut.h>
#include <iostream>

Color_t tcolor[] = {kAzure+2, kRed+2, kGreen+3, kViolet-7, kCyan+1, kCyan+3};
void turnonall(TString inputname, TString outputname, TString treename, TString branchname, TString xtitle,
               TString weight, TString Dcut, std::vector<TString> prescl, std::vector<TString> HLTcut, std::vector<TString> L1cut)
{
  if(HLTcut.size() != L1cut.size()) return;

  xjjroot::setgstyle();

  TFile* inputfile = new TFile(inputname.Data());
  // TTree* hlt = (TTree*)inputfile->Get("hltbitanalysis/HltTree");
  TTree* hlt = (TTree*)inputfile->Get("hltanalysisReco/HltTree");
  TTree* hi = (TTree*)inputfile->Get("hiEvtAnalyzer/HiTree");
  TTree* ntD = (TTree*)inputfile->Get(Form("%s",treename.Data()));
  ntD->AddFriend(hlt);
  ntD->AddFriend(hi);

  std::vector<TH1D*> hnorm(HLTcut.size());
  std::vector<TH1D*> hdenorm(HLTcut.size());
  std::vector<TGraphAsymmErrors*> geff(HLTcut.size());
  for(int i=0;i<hnorm.size();i++)
    {
      hnorm[i] = new TH1D(Form("hnorm_%d",i),"",nBin,bins);
      hnorm[i]->Sumw2();
      hdenorm[i] = new TH1D(Form("hdenorm_%d",i),"",nBin,bins);
      hdenorm[i]->Sumw2();
      ntD->Project(Form("hnorm_%d",i), branchname.Data(), TCut(Form("%s*%s",prescl[i].Data(),weight.Data()))*(TCut(L1cut[i].Data())&&TCut(HLTcut[i].Data())));
      std::cout<<hnorm[i]->GetEntries()<<std::endl;
      ntD->Project(Form("hdenorm_%d",i), branchname.Data(), TCut(weight.Data())*(TCut(L1cut[i].Data())));
      std::cout<<hdenorm[i]->GetEntries()<<std::endl;
      geff[i] = new TGraphAsymmErrors;
      geff[i]->BayesDivide(hnorm[i], hdenorm[i]);
      xjjroot::setthgrstyle(geff[i], tcolor[i], 20, 1.0, kBlack);
    }
  
  TH2F* hempty = new TH2F("hempty", Form(";%s;Efficiency",xtitle.Data()), 10, bins[0], bins[nBin], 10, 0, 1.0);
  xjjroot::sethempty(hempty);

  TCanvas* c = new TCanvas("c", "", 600, 600);
  hempty->Draw();
  gPad->SetGridx();
  TLegend* leg = new TLegend(0.40, 0.70-0.055*geff.size(), 0.85, 0.70);
  xjjroot::setleg(leg, 0.025);
  for(int i=0;i<geff.size();i++)
    {
      geff[i]->Draw("pesame");
      leg->AddEntry(geff[i], HLTcut[i].Data(), "pl");
    }
  leg->Draw();
  c->SaveAs(Form("plots/hturnon_%s.pdf",outputname.Data()));
  
}

int main(int argc, char* argv[])
{
  if((argc-8)>=3 && (argc-8)%3==0)
    {
      std::vector<TString> vPrescl;
      std::vector<TString> vHLT;
      std::vector<TString> vL1;
      for(int i=8;i<argc;i+=3)
        {
          vPrescl.push_back(argv[i]);
          vHLT.push_back(argv[i+1]);
          vL1.push_back(argv[i+2]);
        }
      turnonall(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], vPrescl, vHLT, vL1);
      return 0;
    }
  return 1;
}
