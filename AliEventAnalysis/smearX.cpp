#include "TRandom.h"
#include <math.h>

Double_t smearX(Double_t xTrue, Double_t E){
	const Double_t a = 0.096, b = 0.229; // PPR vol.II, tab.5.17
	Double_t sigmaX = sqrt(a*a + b*b/E);
	Double_t xSmeared = gRandom->Gaus(xTrue,sigmaX);
	return xSmeared;
}
