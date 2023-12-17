#include "TLorentzVector.h"
#include <iostream>

bool IsPhotonDetectedInEMCAL(TLorentzVector p)
{
  // Check if a particle with 4-momentum p hits the EMCAL acceptance
  // |y|<0.7, 87<phi<187 degrees
  
  bool flag = false;

  double px = p.Px();
  double py = p.Py();
  double pz = p.Pz();
  double p0 = p.E();

  double y;
  if (p0>pz)
    y = 0.5*log((p0 + pz)/(p0 - pz));
  else
    y=100;
  
  double phi;
  phi = TMath::ATan2(py,px); // azimuth angle in range (-pi,+pi)
  if (phi < 0) phi += TMath::TwoPi();  // azimuth angle in range (0,+2pi)
  phi *= TMath::RadToDeg();
  
  // std::cout << "In EMCAL: phi = " <<  phi << " y = " << y << " E = " << p0 << "\n";

  if ((fabs(y) < 0.7   &&
       phi > 87.       && 
       phi < 187.      &&
       p0 > 2.0 )      ||
      (fabs(y) < 0.7   &&
       fabs(y) > 0.12  &&
       phi > 260.      &&
       phi < 327.      &&
       p0 > 2.0 )      ){
    flag = true;
  }  
  
  return flag;
}

