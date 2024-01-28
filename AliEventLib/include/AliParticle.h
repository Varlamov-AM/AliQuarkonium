#include <iostream>
#include "TObject.h"
#include "TMath.h"
#include "TLorentzVector.h"
#pragma once

class AliParticle: public TObject{

public:

    double px;
    double py;
    double pz;
    double p0;
    int    id;
    int    number_in_event;
    int    mother_id;
    int    mother_number_in_event;
    int    daughter_1_number_in_event;
    int    daughter_2_number_in_event;

    AliParticle(){};
    virtual ~AliParticle(){};
    
    TLorentzVector FMomentum(){
        TLorentzVector res = TLorentzVector(px, py, pz, p0);
        return res;
    }

    int Number_of_daughters(){
        return daughter_2_number_in_event - daughter_1_number_in_event + 1;
    }
  
    ClassDef(AliParticle, 2);
};
