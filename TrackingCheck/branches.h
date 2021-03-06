#include "xjjrootuti.h"
#define MAX_XB       20000
#define MAX_TRACK    6000

int     RunNo;
int     EvtNo;
int     LumiNo;
int     Dsize;
float   PVx;
float   PVy;
float   PVz;
float   PVxE;
float   PVyE;
float   PVzE;
float   PVnchi2;
float   PVchi2;
float   BSx;
float   BSy;
float   BSz;
float   BSxErr;
float   BSyErr;
float   BSzErr;
float   BSdxdz;
float   BSdydz;
float   BSdxdzErr;
float   BSdydzErr;
float   BSWidthX;
float   BSWidthXErr;
float   BSWidthY;
float   BSWidthYErr;
//DInfo
int     Dindex[MAX_XB];
int     Dtype[MAX_XB];
float   Dmass[MAX_XB];
float   D_unfitted_mass[MAX_XB];
float   Dpt[MAX_XB];
float   D_unfitted_pt[MAX_XB];
float   Deta[MAX_XB];
float   Dphi[MAX_XB];
float   Dy[MAX_XB];
float   DvtxX[MAX_XB];
float   DvtxY[MAX_XB];
float   DvtxZ[MAX_XB];
float   Dd0[MAX_XB];
float   Dd0Err[MAX_XB];
float   Ddxyz[MAX_XB];
float   DdxyzErr[MAX_XB];
float   Dchi2ndf[MAX_XB];
float   Dchi2cl[MAX_XB];
float   Ddtheta[MAX_XB];
float   Dlxy[MAX_XB];
float   Dalpha[MAX_XB];
float   DsvpvDistance[MAX_XB];
float   DsvpvDisErr[MAX_XB];
float   DsvpvDistance_2D[MAX_XB];
float   DsvpvDisErr_2D[MAX_XB];
float   Ddca[MAX_XB];
float   DlxyBS[MAX_XB];
float   DlxyBSErr[MAX_XB];
float   DMaxDoca[MAX_XB];
float   DMaxTkPt[MAX_XB];
float   DMinTkPt[MAX_XB];

float   Dtrk1Pt[MAX_XB];
float   Dtrk2Pt[MAX_XB];
float   Dtrk1Eta[MAX_XB];
float   Dtrk2Eta[MAX_XB];
float   Dtrk1Phi[MAX_XB];
float   Dtrk2Phi[MAX_XB];
int     Dtrk1Algo[MAX_XB];
int     Dtrk2Algo[MAX_XB];
int     Dtrk1originalAlgo[MAX_XB];
int     Dtrk2originalAlgo[MAX_XB];
bool    Dtrk1highPurity[MAX_XB];
bool    Dtrk2highPurity[MAX_XB];

void setbranchesaddress(TTree* dnt)
{
  xjjroot::setbranchaddress(dnt, "RunNo", &RunNo);
  xjjroot::setbranchaddress(dnt, "EvtNo", &EvtNo);
  xjjroot::setbranchaddress(dnt, "LumiNo", &LumiNo);
  xjjroot::setbranchaddress(dnt, "Dsize", &Dsize);
  xjjroot::setbranchaddress(dnt, "PVx", &PVx);
  xjjroot::setbranchaddress(dnt, "PVy", &PVy);
  xjjroot::setbranchaddress(dnt, "PVz", &PVz);
  xjjroot::setbranchaddress(dnt, "PVnchi2", &PVnchi2);
  xjjroot::setbranchaddress(dnt, "BSx", &BSx);
  xjjroot::setbranchaddress(dnt, "BSy", &BSy);
  xjjroot::setbranchaddress(dnt, "BSz", &BSz);
  xjjroot::setbranchaddress(dnt, "PVxE", &PVxE);
  xjjroot::setbranchaddress(dnt, "PVyE", &PVyE);
  xjjroot::setbranchaddress(dnt, "PVzE", &PVzE);
  xjjroot::setbranchaddress(dnt, "BSxErr", &BSxErr);
  xjjroot::setbranchaddress(dnt, "BSyErr", &BSyErr);
  xjjroot::setbranchaddress(dnt, "BSzErr", &BSzErr);
  xjjroot::setbranchaddress(dnt, "BSdxdz", &BSdxdz);
  xjjroot::setbranchaddress(dnt, "BSdydz", &BSdydz);
  xjjroot::setbranchaddress(dnt, "BSdxdzErr", &BSdxdzErr);
  xjjroot::setbranchaddress(dnt, "BSdydzErr", &BSdydzErr);
  xjjroot::setbranchaddress(dnt, "BSWidthX", &BSWidthX);
  xjjroot::setbranchaddress(dnt, "BSWidthXErr", &BSWidthXErr);
  xjjroot::setbranchaddress(dnt, "BSWidthY", &BSWidthY);
  xjjroot::setbranchaddress(dnt, "BSWidthYErr", &BSWidthYErr);        

  //DInfo
  xjjroot::setbranchaddress(dnt, "Dindex", Dindex);
  xjjroot::setbranchaddress(dnt, "Dtype", Dtype);
  xjjroot::setbranchaddress(dnt, "Dmass", Dmass);
  xjjroot::setbranchaddress(dnt, "D_unfitted_mass", D_unfitted_mass);
  xjjroot::setbranchaddress(dnt, "Dpt", Dpt);
  xjjroot::setbranchaddress(dnt, "D_unfitted_pt", D_unfitted_pt);
  xjjroot::setbranchaddress(dnt, "Deta", Deta);
  xjjroot::setbranchaddress(dnt, "Dphi", Dphi);
  xjjroot::setbranchaddress(dnt, "Dy", Dy);
  xjjroot::setbranchaddress(dnt, "DvtxX", DvtxX);
  xjjroot::setbranchaddress(dnt, "DvtxY", DvtxY);
  xjjroot::setbranchaddress(dnt, "DvtxZ", DvtxZ);
  xjjroot::setbranchaddress(dnt, "Dd0", Dd0);
  xjjroot::setbranchaddress(dnt, "Dd0Err", Dd0Err);
  xjjroot::setbranchaddress(dnt, "Ddxyz", Ddxyz);
  xjjroot::setbranchaddress(dnt, "DdxyzErr", DdxyzErr);
  xjjroot::setbranchaddress(dnt, "Dchi2ndf", Dchi2ndf);
  xjjroot::setbranchaddress(dnt, "Dchi2cl", Dchi2cl);
  xjjroot::setbranchaddress(dnt, "Ddtheta", Ddtheta);
  xjjroot::setbranchaddress(dnt, "Dlxy", Dlxy);
  xjjroot::setbranchaddress(dnt, "Dalpha", Dalpha);
  xjjroot::setbranchaddress(dnt, "DsvpvDistance", DsvpvDistance);
  xjjroot::setbranchaddress(dnt, "DsvpvDisErr", DsvpvDisErr);
  xjjroot::setbranchaddress(dnt, "DsvpvDistance_2D", DsvpvDistance_2D);
  xjjroot::setbranchaddress(dnt, "DsvpvDisErr_2D", DsvpvDisErr_2D);
  xjjroot::setbranchaddress(dnt, "Ddca", Ddca);
  xjjroot::setbranchaddress(dnt, "DlxyBS", DlxyBS);
  xjjroot::setbranchaddress(dnt, "DlxyBSErr", DlxyBSErr);
  xjjroot::setbranchaddress(dnt, "DMaxDoca", DMaxDoca);
  xjjroot::setbranchaddress(dnt, "DMaxTkPt", DMaxTkPt);
  xjjroot::setbranchaddress(dnt, "DMinTkPt", DMinTkPt);

  xjjroot::setbranchaddress(dnt, "Dtrk1Pt", Dtrk1Pt);
  xjjroot::setbranchaddress(dnt, "Dtrk2Pt", Dtrk2Pt);
  xjjroot::setbranchaddress(dnt, "Dtrk1Eta", Dtrk1Eta);
  xjjroot::setbranchaddress(dnt, "Dtrk2Eta", Dtrk2Eta);
  xjjroot::setbranchaddress(dnt, "Dtrk1Phi", Dtrk1Phi);
  xjjroot::setbranchaddress(dnt, "Dtrk2Phi", Dtrk2Phi);
  xjjroot::setbranchaddress(dnt, "Dtrk1Algo", Dtrk1Algo);
  xjjroot::setbranchaddress(dnt, "Dtrk2Algo", Dtrk2Algo);
  xjjroot::setbranchaddress(dnt, "Dtrk1originalAlgo", Dtrk1originalAlgo);
  xjjroot::setbranchaddress(dnt, "Dtrk2originalAlgo", Dtrk2originalAlgo);
  xjjroot::setbranchaddress(dnt, "Dtrk1highPurity", Dtrk1highPurity);
  xjjroot::setbranchaddress(dnt, "Dtrk2highPurity", Dtrk2highPurity);

}


int TrackInfo_size;
float TrackInfo_pt[MAX_TRACK];
float TrackInfo_eta[MAX_TRACK];
float TrackInfo_phi[MAX_TRACK];
int TrackInfo_trkAlgo[MAX_TRACK];
int TrackInfo_originalTrkAlgo[MAX_TRACK];
bool TrackInfo_highPurity[MAX_TRACK];
float TrackInfo_d0[MAX_TRACK];
float TrackInfo_d0error[MAX_TRACK];

void setbranchesaddress_root(TTree* root)
{
  xjjroot::setbranchaddress(root, "TrackInfo.size", &TrackInfo_size);
  xjjroot::setbranchaddress(root, "TrackInfo.pt", TrackInfo_pt);
  xjjroot::setbranchaddress(root, "TrackInfo.eta", TrackInfo_eta);
  xjjroot::setbranchaddress(root, "TrackInfo.phi", TrackInfo_phi);
  xjjroot::setbranchaddress(root, "TrackInfo.trkAlgo", TrackInfo_trkAlgo);
  xjjroot::setbranchaddress(root, "TrackInfo.originalTrkAlgo", TrackInfo_originalTrkAlgo);
  xjjroot::setbranchaddress(root, "TrackInfo.highPurity", TrackInfo_highPurity);
  xjjroot::setbranchaddress(root, "TrackInfo.d0", TrackInfo_d0);
  xjjroot::setbranchaddress(root, "TrackInfo.d0error", TrackInfo_d0error);
}
