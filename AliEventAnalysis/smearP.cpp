#include "TLorentzVector.h"
#include "TRandom.h"
#include <math.h>

Double_t smearP(Double_t Ptrue, Double_t Etrue){
    const Double_t a=0.015, b=0.00; // Momentum resolution of ALICE treaking system
    Double_t sigmaP = Ptrue * sqrt(a*a + b*Ptrue*b*Ptrue);
    Double_t Psmeared = gRandom->Gaus(Ptrue,sigmaP);
    if (Psmeared<0) Psmeared = 0;
    return Psmeared;
}
