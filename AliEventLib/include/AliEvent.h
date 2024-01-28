#include <iostream>
#include "TObject.h"
#include "TMath.h"
#include "AliParticle.h"
#include <vector>
#pragma once

class AliEvent: public TObject{
	public:

	bool signal_event_in_data;
	std::vector<AliParticle> chic;
	std::vector<AliParticle> Jpsi;
	std::vector<AliParticle> signal_electrons;
	std::vector<AliParticle> signal_positrons;
	std::vector<AliParticle> signal_photons;
	
	std::vector<AliParticle> electrons;
	std::vector<AliParticle> positrons;
	std::vector<AliParticle> muons;
	std::vector<AliParticle> antimuons;
	std::vector<AliParticle> photons;
	std::vector<AliParticle> charged;
	std::vector<AliParticle> neutral;
	
	AliEvent(){};
	virtual ~AliEvent(){};

	ClassDef(AliEvent, 2);
};
