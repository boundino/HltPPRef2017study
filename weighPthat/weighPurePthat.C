#include <iostream>
#include <iomanip>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TBranch.h>

#define MAX_GEN      6000
int weighPurePthat(TString ifname = "",
                   TString ofname = "")
{
  Bool_t isInsidebin(Float_t xpthat, Int_t i);
  std::cout<<std::endl;
  std::cout<<" -- Checking if input and output files are same"<<std::endl;
  if(ifname==ofname)
    {
      std::cout<<"    Error: Input file will be overwritten."<<std::endl;
      return 0;
    }
  std::cout<<" -- Opening unweighed sample"<<std::endl;
  TFile* inf = TFile::Open(ifname);
  TTree* ntGen = (TTree*)inf->Get("Dfinder/ntGen");
  TTree* ntHi = (TTree*)inf->Get("hiEvtAnalyzer/HiTree");
  Int_t Gsize; ntGen->SetBranchAddress("Gsize",&Gsize);
  Float_t Gpt[MAX_GEN]; ntGen->SetBranchAddress("Gpt",Gpt);
  Int_t GisSignal[MAX_GEN]; ntGen->SetBranchAddress("GisSignal",GisSignal);
  Float_t pthat; ntHi->SetBranchAddress("pthat",&pthat);

  Float_t weight[nBins],nweight[nBins];
  for(Int_t j=0;j<nBins;j++)
    {
      weight[j]=0;
      nweight[j]=0;
    }
  std::cout<<" -- Checking event number"<<std::endl;
  if(ntGen->GetEntries()!=ntHi->GetEntries())
    {
      std::cout<<"    Error: Gen tree and Hi tree have different event number."<<std::endl;
      return 0;
    }
  Int_t nentries = ntGen->GetEntries();
  std::cout<<" -- Calculating weights"<<std::endl;
  for(Int_t i=0;i<nentries;i++)
    {
      ntGen->GetEntry(i);
      ntHi->GetEntry(i);
      if(i%100000==0) std::cout<<"    Processing event "<<std::setiosflags(std::ios::left)<<std::setw(7)<<i<<" / "<<nentries<<std::endl;
      for(Int_t j=0;j<nBins;j++)
        {
          if(isInsidebin(pthat,j)) nweight[j]++;
        }
    }
  std::cout<<" -- Weight results"<<std::endl;
  for(Int_t j=0;j<nBins;j++)
    {
      if(nweight[j]==0)
        {
          std::cout<<"    Error: Weight fails."<<std::endl;
          return 0;
        }
      weight[j] = (crosssec[j]-crosssec[j+1])/nweight[j];
      std::cout<<"    Pthat"<<std::setiosflags(std::ios::left)<<std::setw(3)<<pthatBin[j]<<": "<<weight[j]<<std::endl;
    }

  std::cout<<" -- Building weight branch"<<std::endl;
  TFile* otf = TFile::Open(ofname,"update");
  TTree* ntHinew = (TTree*)otf->Get("hiEvtAnalyzer/HiTree");
  Float_t pthatweight,maxDgenpt;
  TBranch* newBr_pthatweight = ntHinew->Branch("pthatweight", &pthatweight, "pthatweight/F");
  TBranch* newBr_maxDgenpt = ntHinew->Branch("maxDgenpt", &maxDgenpt, "maxDgenpt/F");
  std::cout<<" -- Filling weight branch"<<std::endl;
  for(Int_t i=0;i<nentries;i++)
    {
      ntGen->GetEntry(i);
      ntHi->GetEntry(i);
      if(i%100000==0) std::cout<<"    Processing event "<<std::setiosflags(std::ios::left)<<std::setw(7)<<i<<" / "<<nentries<<std::endl;
      pthatweight=0;
      Float_t maxpt=0;
      for(Int_t k=0;k<Gsize;k++)
        {
          if((GisSignal[k]==genSignal[0]||GisSignal[k]==genSignal[1])&&Gpt[k]>maxpt) maxpt=Gpt[k];
        }
      maxDgenpt = maxpt;
      for(Int_t j=0;j<nBins;j++)
        {
          if(isInsidebin(pthat,j))
            {
              pthatweight = weight[j];
            }
        }
      newBr_pthatweight->Fill();
      newBr_maxDgenpt->Fill();
    }
  otf->cd("hiEvtAnalyzer");
  ntHinew->Write("", TObject::kOverwrite);

  std::cout<<" -- End"<<std::endl;
  std::cout<<std::endl;
  return 1;
}

Bool_t isInsidebin(Float_t xpthat, Int_t i)
{
  if(i>=nBins)
    {
      std::cout<<"    Error: invalid input"<<std::endl;
      return false;
    }
  if(i<(nBins-1)&&xpthat>pthatBin[i]&&xpthat<pthatBin[i+1]) return true;
  else if(i==(nBins-1)&&xpthat>pthatBin[i]) return true;
  else return false;
}

int main(int argc, char *argv[])
{
  if(argc==3)
    {
      weighPurePthat(argv[1], argv[2]);
      return 1;
    }
  else
    {
      std::cout<<"Invalid parameter number"<<std::endl;
      return 0;
    }
}
