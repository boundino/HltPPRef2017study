#include <TTree.h>
#include "xjjrootuti.h"
#define MAXTRACKS 60000

// -- rec tracks --
int nTrk;
float trkEta[MAXTRACKS];
float trkPhi[MAXTRACKS];
float trkPt[MAXTRACKS];
float trkPtError[MAXTRACKS];
unsigned char trkNHit[MAXTRACKS];
unsigned char trkNlayer[MAXTRACKS];
float trkChi2[MAXTRACKS];
unsigned char trkNdof[MAXTRACKS];
float trkDz[MAXTRACKS];
float trkDz1[MAXTRACKS];               // dZ to the highest pt vertex
float trkDz2[MAXTRACKS];               // dZ to the highest mult vertex
float trkDzError[MAXTRACKS];
float trkDzError1[MAXTRACKS];
float trkDzError2[MAXTRACKS];
float trkDxy[MAXTRACKS];
float trkDxyBS[MAXTRACKS];
float trkDxy1[MAXTRACKS];              // d0 to the highest pt vertex
float trkDxy2[MAXTRACKS];              // d0 to the highest mult vertex
float trkDxyError[MAXTRACKS];
float trkDxyErrorBS[MAXTRACKS];
float trkDxyError1[MAXTRACKS];
float trkDxyError2[MAXTRACKS];
float trkVx[MAXTRACKS];
float trkVy[MAXTRACKS];
float trkVz[MAXTRACKS];
bool  trkFake[MAXTRACKS];
unsigned char trkAlgo[MAXTRACKS];
unsigned char trkOriginalAlgo[MAXTRACKS];
float trkMVA[MAXTRACKS];
bool trkMVALoose[MAXTRACKS];
bool trkMVATight[MAXTRACKS];
bool highPurity[MAXTRACKS];

void settrkbranchesaddress(TTree* nt)
{
  xjjroot::setbranchaddress(nt, "nTrk", &nTrk);;
  xjjroot::setbranchaddress(nt, "trkEta", trkEta);;
  xjjroot::setbranchaddress(nt, "trkPhi", trkPhi);;
  xjjroot::setbranchaddress(nt, "trkPt", trkPt);;
  xjjroot::setbranchaddress(nt, "trkPtError", trkPtError);;
  xjjroot::setbranchaddress(nt, "trkNHit", trkNHit);;
  xjjroot::setbranchaddress(nt, "trkNlayer", trkNlayer);;
  xjjroot::setbranchaddress(nt, "trkChi2", trkChi2);;
  xjjroot::setbranchaddress(nt, "trkNdof", trkNdof);;
  xjjroot::setbranchaddress(nt, "trkDz", trkDz);;
  xjjroot::setbranchaddress(nt, "trkDz1", trkDz1);;
  xjjroot::setbranchaddress(nt, "trkDz2", trkDz2);
  xjjroot::setbranchaddress(nt, "trkDzError", trkDzError);
  xjjroot::setbranchaddress(nt, "trkDzError1", trkDzError1);;
  xjjroot::setbranchaddress(nt, "trkDzError2", trkDzError2);;
  xjjroot::setbranchaddress(nt, "trkDxy", trkDxy);;
  xjjroot::setbranchaddress(nt, "trkDxyBS", trkDxyBS);;
  xjjroot::setbranchaddress(nt, "trkDxy1", trkDxy1);
  xjjroot::setbranchaddress(nt, "trkDxy2", trkDxy2);
  xjjroot::setbranchaddress(nt, "trkDxyError", trkDxyError);
  xjjroot::setbranchaddress(nt, "trkDxyErrorBS", trkDxyErrorBS);;
  xjjroot::setbranchaddress(nt, "trkDxyError1", trkDxyError1);;
  xjjroot::setbranchaddress(nt, "trkDxyError2", trkDxyError2);;
  xjjroot::setbranchaddress(nt, "trkVx", trkVx);;
  xjjroot::setbranchaddress(nt, "trkVy", trkVy);;
  xjjroot::setbranchaddress(nt, "trkVz", trkVz);;
  xjjroot::setbranchaddress(nt, "trkFake", trkFake);;
  xjjroot::setbranchaddress(nt, "trkAlgo", trkAlgo);;
  xjjroot::setbranchaddress(nt, "trkOriginalAlgo", trkOriginalAlgo);;
  xjjroot::setbranchaddress(nt, "trkMVA", trkMVA);;
  xjjroot::setbranchaddress(nt, "trkMVALoose", trkMVALoose);;
  xjjroot::setbranchaddress(nt, "trkMVATight", trkMVATight);;
  xjjroot::setbranchaddress(nt, "highPurity", highPurity);;
}
