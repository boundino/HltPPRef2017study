#include "xjjrootuti.h"
#include <TCanvas.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TH2F.h>
#include <iostream>

Color_t tcolor[] = {kAzure+2, kRed+2, kGreen+3, kMagenta+2, kCyan+1, kOrange+6};
void turnonjetall(TString inputname, TString outputname, TString treename, TString branchname, TString Dcut, std::vector<TString> HLTcut, std::vector<TString> L1cut)
{
  if(HLTcut.size() != L1cut.size()) return;

  xjjroot::setgstyle();

  TFile* inputfile = new TFile(inputname.Data());
  TTree* hlt = (TTree*)inputfile->Get("hltbitanalysis/HltTree");
  TTree* ntD = (TTree*)inputfile->Get(Form("%s",treename.Data()));
  ntD->AddFriend(hlt);

  std::vector<TH1D*> hnorm(HLTcut.size());
  std::vector<TH1D*> hdenorm(HLTcut.size());
  std::vector<TGraphAsymmErrors*> geff(HLTcut.size());
  for(int i=0;i<hnorm.size();i++)
    {
      hnorm[i] = new TH1D(Form("hnorm_%d",i),"",20,0,200);
      hnorm[i]->Sumw2();
      hdenorm[i] = new TH1D(Form("hdenorm_%d",i),"",20,0,200);
      hdenorm[i]->Sumw2();
      ntD->Project(Form("hnorm_%d",i), branchname.Data(), Form("%s&&%s&&%s",Dcut.Data(),L1cut[i].Data(),HLTcut[i].Data()));
      ntD->Project(Form("hdenorm_%d",i), branchname.Data(), Form("%s&&%s",Dcut.Data(),L1cut[i].Data()));
      geff[i] = new TGraphAsymmErrors;
      geff[i]->BayesDivide(hnorm[i], hdenorm[i]);
      xjjroot::setthgrstyle(geff[i], tcolor[i], 20, 1.1, kBlack);
    }
  
  TH2F* hempty = new TH2F("hempty", ";PF Jet p_{T} (GeV/c);Efficiency", 10, 0, 200, 10, 0, 1.0);
  xjjroot::sethempty(hempty);

  TCanvas* c = new TCanvas("c", "", 600, 600);
  hempty->Draw();
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
  std::cout<<argc<<std::endl;
  if(argc>=8 && argc%2==0)
    {
      std::vector<TString> vHLT;
      std::vector<TString> vL1;
      for(int i=6;i<argc;i+=2)
        {
          vHLT.push_back(argv[i]);
          vL1.push_back(argv[i+1]);
        }
      turnonjetall(argv[1], argv[2], argv[3], argv[4], argv[5], vHLT, vL1);
      return 0;
    }
  return 1;
}
