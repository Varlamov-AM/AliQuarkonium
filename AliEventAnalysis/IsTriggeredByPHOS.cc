#include "TLorentzVector.h"

bool IsTriggeredByPHOS(TLorentzVector p, double eTrigger)
{
  bool flag = false;

  if (p.E() >= eTrigger){
    flag = true;
  }

  return flag;
}
