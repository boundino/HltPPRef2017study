#include <TTree.h>

Int_t           RecoRunNo;
Int_t           RecoLumiNo;
Int_t           RecoEvtNo;
void setEvtDBranch(TTree *root)
{
  //EvtInfo
  root->SetBranchAddress("RunNo",&RecoRunNo);
  root->SetBranchAddress("EvtNo",&RecoEvtNo);
  root->SetBranchAddress("LumiNo",&RecoLumiNo);
}
Int_t           HltRun;
ULong64_t       HltEvent;
Int_t           HltLumiBlock;
void setEvtHLTBranch(TTree* hltroot)
{
  hltroot->SetBranchAddress("Run",&HltRun);
  hltroot->SetBranchAddress("Event",&HltEvent);
  hltroot->SetBranchAddress("LumiBlock",&HltLumiBlock);
}
UInt_t           HiRun;
ULong64_t           HiEvt;
UInt_t           HiLumi;
void setEvtHIBranch(TTree* hiroot)
{
  hiroot->SetBranchAddress("run",&HiRun);
  hiroot->SetBranchAddress("evt",&HiEvt);
  hiroot->SetBranchAddress("lumi",&HiLumi);
}
