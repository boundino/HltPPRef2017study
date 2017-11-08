#include "evtmatching.h"
#include <TTree.h>
#include <TFile.h>
#include <TDirectory.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <TString.h>

int evtmatching(TString infforest, TString infhlt, TString outfile)
{
  TFile* fdfinder = new TFile(infforest);
  TFile* fhlt = new TFile(infhlt);

  TTree* root = (TTree*)fdfinder->Get("Dfinder/ntDkpi");
  TTree* hiroot = (TTree*)fdfinder->Get("hiEvtAnalyzer/HiTree");
  TTree* jtroot = (TTree*)fdfinder->Get("ak4PFJetAnalyzer/t");
  TTree* trkroot = (TTree*)fdfinder->Get("ppTrack/trackTree");
  TTree* hltroot = (TTree*)fhlt->Get("hltbitanalysis/HltTree");

  TFile* outf = new TFile(outfile,"recreate");
  TDirectory* droot = outf->mkdir("Dfinder","");
  TDirectory* dhiroot = outf->mkdir("hiEvtAnalyzer","");
  TDirectory* djtroot = outf->mkdir("ak4PFJetAnalyzer","");
  TDirectory* dhltroot = outf->mkdir("hltbitanalysis","");
  TDirectory* dtrkroot = outf->mkdir("ppTrack","");

  droot->cd();
  TTree* ntReco = root->CloneTree(0);
  dhiroot->cd();
  TTree* ntHi = hiroot->CloneTree(0);
  djtroot->cd();
  TTree* ntJet = jtroot->CloneTree(0);
  dhltroot->cd();
  TTree* ntHlt = hltroot->CloneTree(0);
  dtrkroot->cd();
  TTree* ntTrk = trkroot->CloneTree(0);

  setEvtDBranch(root);
  setEvtHIBranch(hiroot);
  setEvtHLTBranch(hltroot);

  std::cout<<"---- Check evt no. for three trees"<<std::endl;
  std::cout<<root->GetEntries()<<", "<<hltroot->GetEntries()<<", "<<hiroot->GetEntries()<<std::endl;
  Long64_t nentriesReco = root->GetEntries();
  Long64_t nentriesHlt = hltroot->GetEntries();
  Long64_t nentriesHi = hiroot->GetEntries();
  Int_t aRecoRunNo[nentriesReco],aRecoEvtNo[nentriesReco],aRecoLumiNo[nentriesReco];
  Int_t aHltRun[nentriesHlt],aHltEvent[nentriesHlt],aHltLumiBlock[nentriesHlt];
  Int_t aHiRun[nentriesHi],aHiEvt[nentriesHi],aHiLumi[nentriesHi];
  
  std::cout<<"---- Event reading"<<std::endl;
  Long64_t nentriesMax = (nentriesReco>nentriesHlt)?nentriesReco:nentriesHlt;
  for(Int_t i=0;i<nentriesMax;i++)
    {
      if(i%10000==0)
	{
	  std::cout<<std::setw(7)<<i<<" / "<<nentriesMax<<std::endl;
	}
      if(i<nentriesReco)
	{
	  root->GetEntry(i);
	  aRecoRunNo[i] = RecoRunNo;
	  aRecoEvtNo[i] = RecoEvtNo;
	  aRecoLumiNo[i] = RecoLumiNo;
          hiroot->GetEntry(i);
          if(RecoRunNo!=HiRun || RecoEvtNo!=HiEvt || RecoLumiNo!=HiLumi) {std::cout<<"error"<<std::endl; return 1;}
	}
      if(i<nentriesHlt)
	{
	  hltroot->GetEntry(i);
	  aHltRun[i] = HltRun;
	  aHltEvent[i] = (Int_t)HltEvent;
	  aHltLumiBlock[i] = HltLumiBlock;
	}
    }

  Int_t hltmatching[nentriesReco];
  std::ofstream fout("evtmatchingResult/evtmatching.dat");
  std::cout<<"---- Event matching"<<std::endl;
  for(Int_t ievt=0;ievt<nentriesReco;ievt++)
    {
      if(ievt%10000==0) std::cout<<std::setw(7)<<ievt<<" / "<<nentriesReco<<std::endl;
      hltmatching[ievt] = -1;
      for(Int_t jevt=0;jevt<nentriesHlt;jevt++)
	{
	  if(aRecoRunNo[ievt]==aHltRun[jevt]&&aRecoEvtNo[ievt]==aHltEvent[jevt]&&aRecoLumiNo[ievt]==aHltLumiBlock[jevt])
	    {
	      hltmatching[ievt] = jevt;
	      break;
	    }
	}
      fout<<hltmatching[ievt]<<std::endl;
    }

  std::cout<<"---- Event matching done"<<std::endl;
  std::cout<<"---- Writing hlt tree"<<std::endl;
  for(Int_t i=0;i<nentriesReco;i++)
    {
      if (i%1000==0) std::cout<<std::setiosflags(std::ios::left)<<std::setw(7)<<i<<" / "<<nentriesReco<<" HLT index: "<<hltmatching[i]<<std::endl;
      if(hltmatching[i]<0)
	{
	  continue;
	}
      root->GetEntry(i);
      droot->cd();
      ntReco->Fill();
      hiroot->GetEntry(i);
      dhiroot->cd();
      ntHi->Fill();
      jtroot->GetEntry(i);
      djtroot->cd();
      ntJet->Fill();
      trkroot->GetEntry(i);
      dtrkroot->cd();
      ntTrk->Fill();
      hltroot->GetEntry(hltmatching[i]);
      dhltroot->cd();
      ntHlt->Fill();
    }
  outf->Write();
  std::cout<<"---- Writing hlt tree done"<<std::endl;
  outf->Close();

  return 0;
}

int main(int argc, char* argv[])
{
  return evtmatching(argv[1], argv[2], argv[3]);
}
