#include "branches.h"
#include "xjjcuti.h"
#include <TCanvas.h>
#include <TFile.h>
#include <iostream>
#include <iomanip>
#include <TVector3.h>
#include <fstream>

void loopcand(TString inputname, Int_t HLTcut, Float_t Dptcut, Float_t Tkptcut, Int_t maxevt=-1, Int_t printtrk=0)
{
  xjjroot::setgstyle();
  Bool_t matching(Float_t val, std::vector<float>* vval, Float_t precision);

  TFile* inputfile = new TFile(inputname.Data());
  TTree* hlt = (TTree*)inputfile->Get("hltbitanalysis/HltTree");
  hlt->SetBranchStatus("*",0);
  TTree* ntDkpi = (TTree*)inputfile->Get("Dfinder/ntDkpi");
  ntDkpi->SetBranchStatus("*",0);
  TTree* hltobj = (TTree*)inputfile->Get(Form("hlttktkVtxForDmesonDpt%d/saveobj",HLTcut));
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


  int HLTpath; xjjroot::setbranchaddress(hlt,Form("HLT_DmesonPPTrackingGlobal_Dpt%d_v1",HLTcut), &HLTpath);
  setbranchesaddress(ntDkpi);

  std::vector<int> inpass;

  std::cout<<std::endl;
  std::cout<<"Offline D ( pT > "<<Form("%.0f",Dptcut)<<" ) but not fire "<<Form("HLT_DmesonPPTrackingGlobal_Dpt%d_v1",HLTcut)<<" >>>"<<std::endl;
  std::cout<<std::setiosflags(std::ios::left)<<std::setw(14)<<"evt"<<std::setw(14)<<"Dpt"<<std::setw(14)<<"Dtrk1Pt"<<std::setw(14)<<"Dtrk1Eta"<<std::setw(14)<<"Dtrk1Phi"<<std::setw(14)<<"Dtrk1Algo"<<std::setw(14)<<"Dtrk2Pt"<<std::setw(14)<<"Dtrk2Eta"<<std::setw(14)<<"Dtrk2Phi"<<std::setw(14)<<"Dtrk2Algo"<<std::endl;
  std::cout<<std::string(140, '-')<<std::endl;

  int eventnumber = (maxevt<ntDkpi->GetEntries()&&maxevt>0)?maxevt:ntDkpi->GetEntries();
  for(int i=0;i<eventnumber;i++)
    {
      hlt->GetEntry(i);
      ntDkpi->GetEntry(i); 
      hltobj->GetEntry(i); 
      int flag=0;
      for(int j=0;j<Dsize;j++)
        {
          if(!((abs(Dmass[j]-1.8696)<0.1)&&(DsvpvDistance[j]/DsvpvDisErr[j])>2.5&&Dchi2cl[j]>0.10&&Dalpha[j]<0.12&&Dtrk1highPurity[j]&&Dtrk1Pt[j]>1&&abs(Dtrk1Eta[j])<2.0&&Dtrk2highPurity[j]&&Dtrk2Pt[j]>1&&abs(Dtrk2Eta[j])<2.0)) continue;
          if(Dpt[j] > Dptcut && !HLTpath)
            {
              std::cout<<std::setiosflags(std::ios::left)<<std::setw(14)<<i<<std::setw(14)<<Dpt[j];
              if(matching(Dtrk1Pt[j],vTkpt,2) && matching(Dtrk1Eta[j],vTketa,0.02) && matching(Dtrk1Phi[j],vTkphi,0.02))
                std::cout<<std::setiosflags(std::ios::left)<<xjjc::green<<std::setw(14)<<Dtrk1Pt[j]<<std::setw(14)<<Dtrk1Eta[j]<<std::setw(14)<<Dtrk1Phi[j]<<std::setw(14)<<Dtrk1originalAlgo[j]<<xjjc::nc;
              else
                std::cout<<std::setiosflags(std::ios::left)<<xjjc::red<<std::setw(14)<<Dtrk1Pt[j]<<std::setw(14)<<Dtrk1Eta[j]<<std::setw(14)<<Dtrk1Phi[j]<<std::setw(14)<<Dtrk1originalAlgo[j]<<xjjc::nc;
              if(matching(Dtrk2Pt[j],vTkpt,2) && matching(Dtrk2Eta[j],vTketa,0.02) && matching(Dtrk2Phi[j],vTkphi,0.02))
                std::cout<<std::setiosflags(std::ios::left)<<xjjc::green<<std::setw(14)<<Dtrk2Pt[j]<<std::setw(14)<<Dtrk2Eta[j]<<std::setw(14)<<Dtrk2Phi[j]<<std::setw(14)<<Dtrk2originalAlgo[j]<<xjjc::nc;
              else
                std::cout<<std::setiosflags(std::ios::left)<<xjjc::red<<std::setw(14)<<Dtrk2Pt[j]<<std::setw(14)<<Dtrk2Eta[j]<<std::setw(14)<<Dtrk2Phi[j]<<std::setw(14)<<Dtrk2originalAlgo[j]<<xjjc::nc;
              std::cout<<std::endl;
              flag++;
            }
        }
      if(flag>0) inpass.push_back(i);
    }

  if(printtrk>0)
    {
      std::cout<<std::endl;
      std::cout<<"Online Tracks ( pT > "<<Form("%.0f",Tkptcut)<<" ) >>>"<<std::endl;
      std::cout<<std::setiosflags(std::ios::left)<<std::setw(14)<<"evt"<<std::setw(14)<<"Tkpt"<<std::setw(14)<<"Tketa"<<std::setw(14)<<"Tkphi"<<std::endl;
      std::cout<<std::string(50, '-')<<std::endl;
      for(int i=0;i<inpass.size();i++)
        {
          hltobj->GetEntry(inpass.at(i));
          if(Tksize!=vTkpt->size()) {std::cout<<"error"<<std::endl; return;}
          for(int k=0;k<Tksize;k++)
            {
              if(vTkpt->at(k)>Tkptcut)
                {
                  std::cout<<std::setiosflags(std::ios::left)<<std::setw(14)<<inpass.at(i)<<std::setw(14)<<vTkpt->at(k)<<std::setw(14)<<vTketa->at(k)<<std::setw(14)<<vTkphi->at(k)<<std::endl;         
                }
            }
          std::cout<<std::string(50, '-')<<std::endl;
        }
    }
  std::cout<<std::endl;
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
  loopcand(argv[1], atoi(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5]));
}
