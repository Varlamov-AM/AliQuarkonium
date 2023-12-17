#include "TLorentzVector.h"
#include <math.h>
Double_t smearP(Double_t, Double_t);

// This function generates smeared electron 4-momentum from the true one

TLorentzVector resolutionElectron(TLorentzVector pTrue){
	// Get particle mass
	Double_t Mass = pTrue.M();
	// Get true absolute 3-momentum from true 4-momentum
	Double_t p3True = pTrue.P();
	// Generated smeared absolute 3-momentum
	Double_t p3Smeared = smearP(p3True, pTrue.E());
	// Calculate smeared components of 3-vector
	Double_t pxSmeared = pTrue.Px() * p3Smeared/p3True;
	Double_t pySmeared = pTrue.Py() * p3Smeared/p3True;
	Double_t pzSmeared = pTrue.Pz() * p3Smeared/p3True;
	// if smear_type == 2 (PHOS-type smearing) calculate direction smearing
	// Calculate new energy from smeared 3-momentum and mass
	Double_t Esmeared = sqrt(p3Smeared*p3Smeared + Mass*Mass);
	// Construct new 4-momentum from smeared energy and 3-momentum
	TLorentzVector pSmeared(pxSmeared,pySmeared,pzSmeared,Esmeared);
	return pSmeared;
}
