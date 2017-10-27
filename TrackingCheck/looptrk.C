#include "branches.h"
#include "xjjcuti.h"
#include <TCanvas.h>
#include <TFile.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <TGraphAsymmErrors.h>
#include <TH2F.h>

void looptrk(TString inputname, Float_t Tkptcut, Int_t maxevt=-1, Int_t printtrk=0)
{
  xjjroot::setgstyle();
  Bool_t matching(Float_t val, std::vector<float>* vval, Float_t precision);

  TFile* inputfile = new TFile(inputname.Data());
  // TTree* hlt = (TTree*)inputfile->Get("hltbitanalysis/HltTree");
  // hlt->SetBranchStatus("*",0);
  // TTree* ntDkpi = (TTree*)inputfile->Get("Dfinder/ntDkpi");
  // ntDkpi->SetBranchStatus("*",0);
  TTree* root = (TTree*)inputfile->Get("Dfinder/root");
  root->SetBranchStatus("*",0);
  setbranchesaddress_root(root);
  TTree* hltobj = (TTree*)inputfile->Get(Form("hlttktkVtxForDmesonDpt%d/saveobj",8));
  hltobj->SetBranchStatus("*",0);

  int tktkDsize; xjjroot::setbranchaddress(hltobj, "tktkDsize", &tktkDsize);
  std::vector<float>* vtktkDpt = 0; xjjroot::setbranchaddress(hltobj, "tktkDpt", &vtktkDpt);
  std::vector<float>* vtktkDeta = 0; xjjroot::setbranchaddress(hltobj, "tktkDeta", &vtktkDeta);
  std::vector<float>* vtktkDphi = 0; xjjroot::setbranchaddress(hltobj, "tktkDphi", &vtktkDphi);
  std::vector<float>* vtktkDmass = 0; xjjroot::setbranchaddress(hltobj, "tktkDmass", &vtktkDmass);
  int Tksize; xjjroot::setbranchaddress(hltobj, "Tksize", &Tksize);
  std::vector<float>* vTkpt = 0; xjjroot::setbranchaddress(hltobj, "Tkpt", &vTkpt);
  std::vector<float>* vTketa = 0; xjjroot::setbranchaddress(hltobj, "Tketa", &vTketa);
  std::vector<float>* vTkphi = 0; xjjroot::setbranchaddress(hltobj, "Tkphi", &vTkphi);

  const int nvar = 6;
  std::vector<int>* vxn = new std::vector<int>{20, 20, 20, 30, 20, 20};
  std::vector<double>* vxmin = new std::vector<double>{0, -2, -3, 0, 0, -4};
  std::vector<double>* vxmax = new std::vector<double>{150, 2, 3, 30, 500, 4};
  std::vector<std::string>* vname = new std::vector<std::string>{"pt", "eta", "phi", "algo", "d0sig", "d0"};
  std::vector<TH1D*>* vhnorm = new std::vector<TH1D*>(nvar);
  std::vector<TH1D*>* vhdenorm = new std::vector<TH1D*>(nvar);
  std::vector<TGraphAsymmErrors*>* vgeff = new std::vector<TGraphAsymmErrors*>(nvar);
  std::vector<TH2F*>* vhempty = new std::vector<TH2F*>(nvar);
  for(int k=0;k<nvar;k++)
    {
      vhnorm->at(k) = new TH1D(Form("hnorm_%s",vname->at(k).c_str()), "", vxn->at(k), vxmin->at(k), vxmax->at(k));
      vhdenorm->at(k) = new TH1D(Form("hdenorm_%s",vname->at(k).c_str()), "", vxn->at(k), vxmin->at(k), vxmax->at(k));
      vgeff->at(k) = new TGraphAsymmErrors;
      vhempty->at(k) = new TH2F(Form("hempty_%s",vname->at(k).c_str()), Form(";track %s;missing fraction in hlt",vname->at(k).c_str()), 10, vxmin->at(k), vxmax->at(k), 10, 0, 0.7);
      xjjroot::sethempty(vhempty->at(k));
    }

  if(printtrk)
    {
      std::cout<<std::endl;
      std::cout<<"Offline track ( pT > "<<Form("%.0f",Tkptcut)<<") >>>"<<std::endl;
      std::cout<<std::setiosflags(std::ios::left);
      for(int k=0;k<nvar;k++) std::cout<<std::setw(14)<<Form("trk%s",vname->at(k).c_str());
      std::cout<<std::endl;
      std::cout<<std::string(140, '-')<<std::endl;
    }
  int eventnumber = (maxevt<root->GetEntries()&&maxevt>0)?maxevt:root->GetEntries();
  for(int i=0;i<eventnumber;i++)
    {
      // hlt->GetEntry(i);
      root->GetEntry(i); 
      hltobj->GetEntry(i); 
      for(int j=0;j<TrackInfo_size;j++)
        {
          if(matching(TrackInfo_pt[j],vTkpt,2) && matching(TrackInfo_eta[j],vTketa,0.02) && matching(TrackInfo_phi[j],vTkphi,0.02)) std::cout<<xjjc::green;
          else 
            {
              vhnorm->at(0)->Fill(TrackInfo_pt[j]);
              vhnorm->at(1)->Fill(TrackInfo_eta[j]);
              vhnorm->at(2)->Fill(TrackInfo_phi[j]);
              vhnorm->at(3)->Fill(TrackInfo_originalTrkAlgo[j]);
              vhnorm->at(4)->Fill(TrackInfo_d0[j]/TrackInfo_d0error[j]);
              vhnorm->at(5)->Fill(TrackInfo_d0[j]);
              std::cout<<xjjc::red;
            }
          vhdenorm->at(0)->Fill(TrackInfo_pt[j]);
          vhdenorm->at(1)->Fill(TrackInfo_eta[j]);
          vhdenorm->at(2)->Fill(TrackInfo_phi[j]);
          vhdenorm->at(3)->Fill(TrackInfo_originalTrkAlgo[j]);
          vhdenorm->at(4)->Fill(TrackInfo_d0[j]/TrackInfo_d0error[j]);
          vhdenorm->at(5)->Fill(TrackInfo_d0[j]);
          if(printtrk) std::cout<<std::setiosflags(std::ios::left)<<std::setw(14)<<TrackInfo_pt[j]<<std::setw(14)<<TrackInfo_eta[j]<<std::setw(14)<<TrackInfo_phi[j]<<std::setw(14)<<TrackInfo_originalTrkAlgo[j]<<std::setw(14)<<TrackInfo_d0[j]/TrackInfo_d0error[j]<<std::setw(14)<<TrackInfo_d0[j];
          std::cout<<xjjc::nc;
          if(printtrk) std::cout<<std::endl;
        }
    }
  for(int k=0;k<nvar;k++)
    {
      vgeff->at(k)->BayesDivide(vhnorm->at(k), vhdenorm->at(k));
      xjjroot::setthgrstyle(vgeff->at(k), kBlack, 20, 1.1, kBlack);
      TCanvas* c = new TCanvas("c", "", 600, 600);
      vhempty->at(k)->Draw();
      vgeff->at(k)->Draw("pesame");
      c->SaveAs(Form("plots/hfmiss_%s.pdf",vname->at(k).c_str()));  
      delete c;
    }
}

Bool_t matching(Float_t val, std::vector<float>* vval, Float_t precision)
{
  for(int i=0;i<vval->size();i++)
    {
      if(TMath::Abs(val-vval->at(i))<precision) return true;
    }
  return false;
}

int main(int argc, char* argv[])
{
  if(argc==5)
    {
      looptrk(argv[1], atof(argv[2]), atoi(argv[3]), atoi(argv[4]));
      return 0;
    }
  if(argc==4)
    {
      looptrk(argv[1], atof(argv[2]), atoi(argv[3]));
      return 0;
    }
  else if(argc==3)
    {
      looptrk(argv[1], atof(argv[2]));
      return 0;
    }
  return 1;
}
