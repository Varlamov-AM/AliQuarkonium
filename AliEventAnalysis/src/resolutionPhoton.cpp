#include "TLorentzVector.h"
#include "TRandom.h"
#include <math.h>
Double_t smearE(Double_t);
Double_t sigmaX(Double_t);

// This function generates smeared photon 4-momentum from the true one

TLorentzVector resolutionPhoton(TLorentzVector pTrue){
    const Double_t rPHOS = 460; // PHOS distance from beam interaction point
    // const Double_t rPHOS = 150; // ANGHIE CALO distance from beam interaction point
    // Get particle mass
    Double_t Etrue = pTrue.E();
    // Get true energy from true 4-momentum and smear this energy
    Double_t Esmeared = smearE(pTrue.E());
    // Smear direction of 3-vector
    Double_t phi   = pTrue.Phi()   + gRandom->Gaus(0.,sigmaX(Etrue)/rPHOS);
    Double_t theta = pTrue.Theta() + gRandom->Gaus(0.,sigmaX(Etrue)/rPHOS);
    // Calculate smeared components of 3-vector
    Double_t pxSmeared = Esmeared*TMath::Cos(phi)*TMath::Sin(theta);
    Double_t pySmeared = Esmeared*TMath::Sin(phi)*TMath::Sin(theta);
    Double_t pzSmeared = Esmeared*TMath::Cos(theta);
    // Construct new 4-momentum from smeared energy and 3-momentum
    TLorentzVector pSmeared(pxSmeared,pySmeared,pzSmeared,Esmeared);
    return pSmeared;
}
