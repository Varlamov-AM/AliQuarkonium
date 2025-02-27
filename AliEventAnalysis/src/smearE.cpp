#include "TLorentzVector.h"
#include "TRandom.h"
#include <math.h>

Double_t smearE(Double_t Etrue){
    const Double_t a = 0, b = 2.46721e-02, c = 7.90553e-03; // Energy resolution of ALICE ECAL with   0X_0
    // const Double_t a = 0, b = 2.87143e-02, c = 8.04325e-03; // Energy resolution of ALICE ECAL with 1.2X_0
    Double_t sigmaE = Etrue * sqrt(a*a/Etrue/Etrue + b*b/Etrue + c*c);
    Double_t Esmeared = gRandom->Gaus(Etrue,sigmaE);
    if (Esmeared<0) Esmeared = 0;
    return Esmeared;
}
