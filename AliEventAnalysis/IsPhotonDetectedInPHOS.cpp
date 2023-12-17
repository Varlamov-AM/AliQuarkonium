#include "TMath.h"
#include "TLorentzVector.h"

bool IsPhotonDetectedInPHOS(TLorentzVector p)
{
  // Check if a particle with 4-momentum p hits the PHOS acceptance
  // |y|<0.12, 250<phi<320 degrees
  
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

  if (fabs(y) < 0.12 &&
      phi > 250.     && 
      phi < 320.     &&
      p0 > 1.0       ){
    flag = true;
  }  
  
  return flag;
}
