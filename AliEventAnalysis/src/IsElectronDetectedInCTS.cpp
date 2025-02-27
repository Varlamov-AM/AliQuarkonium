#include "TLorentzVector.h"

bool IsElectronDetectedInCTS(TLorentzVector p){

  bool flag = false;

  double px = p.Px();
  double py = p.Py();
  double pz = p.Pz();

  double pT = sqrt(px*px + py*py);
  double eta = 0.5*log((p.P() + pz)/(p.P() - pz));

  if (fabs(eta) < 0.8 && 
      pT >= 1.0 ){
    flag = true;
  }

  return flag;
}
