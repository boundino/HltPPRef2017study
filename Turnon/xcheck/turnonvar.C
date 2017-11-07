#include "xjjrootuti.h"
#include <TCanvas.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TH2F.h>
#include <iostream>
#include <TCut.h>

const int nBin = 10;
Color_t tcolor[] = {kAzure+2, kRed+2, kGreen+3, kMagenta+2, kCyan+1};
void turnonvar(TString inputname, TString outputname, TString treename, TString weight, TString Dcut, 
               TString branchname, TString varname, Float_t varmin, Float_t varmax, 
               std::vector<Float_t> Dptcut, std::vector<TString> HLTcut, std::vector<TString> L1cut)
{
  xjjroot::setgstyle();

  TFile* inputfile = new TFile(inputname.Data());
  TTree* hlt = (TTree*)inputfile->Get("hltbitanalysis/HltTree");
  TTree* hi = (TTree*)inputfile->Get("hiEvtAnalyzer/HiTree");
  TTree* ntD = (TTree*)inputfile->Get(Form("Dfinder/%s",treename.Data()));
  ntD->AddFriend(hlt);
  ntD->AddFriend(hi);

  std::vector<TH1D*> hnorm(HLTcut.size());
  std::vector<TH1D*> hdenorm(HLTcut.size());
  std::vector<TGraphAsymmErrors*> geff(HLTcut.size());
  for(int i=0;i<hnorm.size();i++)
    {
      hnorm[i] = new TH1D(Form("hnorm_%d",i), "", nBin, varmin, varmax);
      hnorm[i]->Sumw2();
      hdenorm[i] = new TH1D(Form("hdenorm_%d",i), "", nBin, varmin, varmax);
      hdenorm[i]->Sumw2();
      ntD->Project(Form("hnorm_%d",i), branchname.Data(), TCut(weight.Data())*(TCut(Dcut.Data())&&TCut(L1cut[i].Data())&&TCut(HLTcut[i].Data())&&Form("Dpt>%f",Dptcut[i])));
      ntD->Project(Form("hdenorm_%d",i), branchname.Data(), TCut(weight.Data())*(TCut(Dcut.Data())&&TCut(L1cut[i].Data())&&Form("Dpt>%f",Dptcut[i])));
      geff[i] = new TGraphAsymmErrors;
      geff[i]->BayesDivide(hnorm[i], hdenorm[i]);
      xjjroot::setthgrstyle(geff[i], tcolor[i], 20, 1.1, kBlack);
    }

  TH2F* hempty = new TH2F("hempty", Form(";%s;Efficiency", branchname.Data()), 10, varmin, varmax, 10, 0, 1.0);
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
  c->SaveAs(Form("plots/hvarturnon_%s_%s.pdf",outputname.Data(),varname.Data()));
  
}

int main(int argc, char* argv[])
{
  if((argc-10)>=3 && (argc-10)%3==0)
    {
      std::vector<Float_t> vDptcut;
      std::vector<TString> vHLT;
      std::vector<TString> vL1;
      for(int i=10;i<argc;)
        {
          vDptcut.push_back(atof(argv[i]));
          i++;
          vHLT.push_back(argv[i]);
          i++;
          vL1.push_back(argv[i]);
          i++;
        }
      turnonvar(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], atof(argv[8]), atof(argv[9]), vDptcut, vHLT, vL1);
      return 0;
    }
  return 1;
}
