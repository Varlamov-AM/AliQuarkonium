#include "Pythia8/Pythia.h"
#include "TRandom.h"
using namespace Pythia8;

void Init(Pythia* pythia)
{

  TRandom rndm;

  rndm.SetSeed(0);
  int pythiaSeed = rndm.Integer(1000000);
  char processLine[80];
  sprintf(processLine, "Random:Seed = %d",pythiaSeed);

  pythia->readString("Random:setSeed = on");
  pythia->readString(processLine); 

  //Set process type and collision energy
  
  // pythia->readString("WeakSingleBoson:ffbar2gmZ = on");
  // pythia->readString("23:mMin = 2.");
  // pythia->readString("PhaseSpace:mHatMin = 2.");
  // pythia->readString("PhaseSpace:mHatMax = 4.");

  //pythia->readString("SoftQCD:all = on");
  pythia->readString("Charmonium:all  = on");
  //pythia->readString("Onia:all(3S1)  = on");
  //pythia->readString("Charmonium:states(3S1) = 443");
  //pythia->readString("Onia:all(3PJ) = on");
  pythia->readString("Beams:eCM = 13000.");

  // Switch off all Z decays but Z -> e+e-
  //pythia->readString("23:onMode = off");
  //pythia->readString("23:onIfAny = 11 -11");

  // Switch off all pi0 decays but pi0 -> gamma gamma
  //pythia->readString("111:onMode = on");
  //pythia->readString("111:offIfAny = 11 -11");

  // Switch off all J/psi decays but J/psi -> e+ e-
  pythia->readString("443:onMode = off");
  pythia->readString("443:onIfAny = 11 -11");

  // Switch off all chi_c2 decays but chi_c2 -> J/psi gamma
  pythia->readString("445:onMode = off");
  pythia->readString("445:onIfAny = 443 22");

  // Switch off all chi_c0 decays but chi_c0 -> J/psi gamma
  pythia->readString("10441:onMode = off");
  pythia->readString("10441:onIfAny = 443 22");

  // Switch off all chi_c1 decays but chi_c1 -> J/psi gamma
  pythia->readString("20443:onMode = off");
  pythia->readString("20443:onIfAny = 443 22");

  //pythia->readString("PhaseSpace:pTHatMin = 5.");

  pythia->init();

  cout << "Pythia was successfully initialized!\n";

  return;
}
