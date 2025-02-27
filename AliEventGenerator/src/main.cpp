// Stdlib header file for input and output.
#include <iostream>
#include <unistd.h>
#include <cstdlib>

// Pythia8 headers
#include "Pythia8/Pythia.h"

// ROOT, for histogramming.
#include "TH1.h"
#include "TH2.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// ROOT, to set random seed (Pythia random seed based on tume does not work!)
#include "TRandom.h"
#include "TMath.h"

// ROOT, for saving file.
#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "AliParticle.h"
#include "AliEvent.h"
#include "TObject.h"

class AliParticle;
class AliEvent;

using namespace Pythia8;
 

void Init(Pythia*);

void fill_AliParticle_with_pythia_particle(Pythia8::Event& event, int i, AliParticle& res){
	res.p0 = event[i].e();
	res.px = event[i].px();
	res.py = event[i].py();
	res.pz = event[i].pz();
	res.id = event[i].id();
	res.number_in_event = i;
	res.mother_number_in_event = event[i].mother1();
	res.mother_id = event[res.mother_number_in_event].id();
	res.daughter_1_number_in_event = event[i].daughter1();
	res.daughter_2_number_in_event = event[i].daughter2();
}

int main(int argc, char* argv[]) {


	// read input parameters
	printf("argc = %d, argv[0] = %s\n",argc,argv[0]);
	if (argc != 2) {
		printf("Usage: %s <nEvents>\n",argv[0]);
		printf("       <nEvents>=0 is the number of events to generate.\n");
		return 1;
	}

	char fn[1024];
	sprintf(fn, "%s", "AliEvent_class_data.root");
	TFile* outFile = new TFile(fn, "RECREATE");
	
	TTree *test_tree = new TTree("AliEvent_data", "AliEvent_class_data");
	test_tree->SetMaxTreeSize(1000000000);

	AliEvent* General_event = new AliEvent;


	test_tree->Branch("AliEvent",&General_event);
	test_tree->SetAutoSave(0);
	

	int nEvents = atoi(argv[1]);
	cout << "nEvents = " << nEvents << endl;

	//Create the ROOT application environment. 
	TApplication theApp("hist", &argc, argv);

	Pythia pythia;

	Init(&(pythia));

	cout << "List all decays of particle 10441, 20443, 445\n";
	
	pythia.particleData.list(10441);
	pythia.particleData.list(20443);
	pythia.particleData.list(445);
	pythia.particleData.list(443);
	

	//define particles id from Pythia8 


	const int idChic0        =  10441;
	const int idChic1        =  20443;
	const int idChic2        =  445;
	const int idJpsi         =  443;
	const int idElectron     =  11;
	const int idMuon         =  13;
	const int idPhoton       =  22;
	const int idK0L          =  130;
	const int idn            =  2112;
	const int idp            =  2212;
	const int idPic          =  211;
	const int idPin          =  111;
	const int idKc           =  321;
	
	int nEvent2Print = 10;

	// Begin event loop. Generate event
	
	int iEvent2Print = 0;
	
	for (int iEvent = 0; iEvent < nEvents; ++iEvent){
		if (!pythia.next()) continue;

		bool signal_event_in_data = 	0;
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
		

		//print first nEvent2Print events
		if (iEvent2Print < nEvent2Print) //pythia.event.list();
		iEvent2Print++;

		// Loop over all particles in the generated event    
		for (int i = 0; i < pythia.event.size(); ++i){

			if ((pythia.event[i].id() == idChic0 or
				 pythia.event[i].id() == idChic1 or
				 pythia.event[i].id() == idChic2)
				and 
				pythia.event[i].status() == -62){

				AliParticle chi_c;
				fill_AliParticle_with_pythia_particle(pythia.event, i, chi_c);
			
				if (pythia.event[pythia.event[i].daughter1()].id() == idJpsi and 
					pythia.event[pythia.event[i].daughter2()].id() == idPhoton){
					if (fabs(pythia.event[pythia.event[i].daughter2()].eta()) < 0.5){
						AliParticle signal_gamma;
						AliParticle jpsi;
						fill_AliParticle_with_pythia_particle(pythia.event, pythia.event[i].daughter1(), jpsi);
						fill_AliParticle_with_pythia_particle(pythia.event, pythia.event[i].daughter2(), signal_gamma);
						if (pythia.event[pythia.event[pythia.event[i].daughter1()].daughter1()].id() == idElectron and 
							pythia.event[pythia.event[pythia.event[i].daughter1()].daughter2()].id() == -idElectron){
							if (fabs(pythia.event[pythia.event[pythia.event[i].daughter1()].daughter1()].eta()) < 0.5 and 
								fabs(pythia.event[pythia.event[pythia.event[i].daughter1()].daughter2()].eta()) < 0.5){
								AliParticle signal_electron;
								AliParticle signal_positron;
								fill_AliParticle_with_pythia_particle(pythia.event, pythia.event[pythia.event[i].daughter1()].daughter1(), signal_electron);
								fill_AliParticle_with_pythia_particle(pythia.event, pythia.event[pythia.event[i].daughter1()].daughter2(), signal_positron);
								chic.push_back(chi_c);
								Jpsi.push_back(jpsi);
								signal_photons.push_back(signal_gamma);
								signal_electrons.push_back(signal_electron);
								signal_positrons.push_back(signal_positron);
								signal_event_in_data = true;
							}
						}
					}
				}
			}	

		if (pythia.event[i].id() == idElectron and pythia.event[i].pT() > 0.1 and fabs(pythia.event[i].eta()) < 0.5 and pythia.event[i].status() > 80 and pythia.event[i].status() < 92){
			AliParticle electron;
			fill_AliParticle_with_pythia_particle(pythia.event, i, electron);
			electrons.push_back(electron);
			std::cout << pythia.event[i].status() << "\n";
		}

		if (pythia.event[i].id() == -idElectron and pythia.event[i].pT() > 0.1 and fabs(pythia.event[i].eta()) < 0.5 and pythia.event[i].status() > 80 and pythia.event[i].status() < 92){
			AliParticle positron;
			fill_AliParticle_with_pythia_particle(pythia.event, i, positron);
			positrons.push_back(positron);
		}

		if (pythia.event[i].id() == idMuon and pythia.event[i].pT() > 0.1 and fabs(pythia.event[i].eta()) < 0.5 and pythia.event[i].status() > 80 and pythia.event[i].status() < 92){
			AliParticle muon;
			fill_AliParticle_with_pythia_particle(pythia.event, i, muon);
			muons.push_back(muon);
		}

		if (pythia.event[i].id() == -idMuon and pythia.event[i].pT() > 0.1 and fabs(pythia.event[i].eta()) < 0.5 and pythia.event[i].status() > 80 and pythia.event[i].status() < 92){
			AliParticle antimuon;
			fill_AliParticle_with_pythia_particle(pythia.event, i, antimuon);
			antimuons.push_back(antimuon);
		}

		if (pythia.event[i].id() == idPhoton and pythia.event[i].pT() > 0.1 and fabs(pythia.event[i].eta()) < 0.5 and pythia.event[i].status() > 80 and pythia.event[i].status() < 92){
			AliParticle photon;
			fill_AliParticle_with_pythia_particle(pythia.event, i, photon);
			photons.push_back(photon);
		}

		if ((pythia.event[i].id() == idK0L or pythia.event[i].id() == idn) and pythia.event[i].pT() > 0.1 and fabs(pythia.event[i].eta()) < 0.5 and pythia.event[i].status() > 80 and pythia.event[i].status() < 92){
			AliParticle neutralp;
			fill_AliParticle_with_pythia_particle(pythia.event, i, neutralp);
			neutral.push_back(neutralp);
		}


		if ((fabs(pythia.event[i].id()) == idKc or fabs(pythia.event[i].id()) == idp or fabs(pythia.event[i].id()) == idPic) and pythia.event[i].pT() > 0.1 and fabs(pythia.event[i].eta()) < 0.5 and pythia.event[i].status() > 80 and pythia.event[i].status() < 92){
			AliParticle chargedp;
			fill_AliParticle_with_pythia_particle(pythia.event, i, chargedp);
			charged.push_back(chargedp);
		}


    }

		General_event->signal_event_in_data = signal_event_in_data;
		General_event->chic 	            = chic;
		General_event->Jpsi 	            = Jpsi;
		General_event->signal_electrons     = signal_electrons;
		General_event->signal_positrons     = signal_positrons;
		General_event->signal_photons       = signal_photons;
		
		General_event->electrons            = electrons;
		General_event->positrons            = positrons;
		General_event->muons                = muons;
		General_event->antimuons            = antimuons;
		General_event->photons              = photons;
		General_event->charged              = charged;
		General_event->neutral              = neutral;

    if (photons.size() != 0){
  		test_tree->Fill();
    } else {continue;}

	}
      
	test_tree->Write();	
  TH1F *hCross_section_hist = new TH1F("hCross_section_hist", "xsection and ntrials data", 2, 0., 1.);


	double xsection = pythia.info.sigmaGen();
	int ntrials  = pythia.info.nAccepted();

	hCross_section_hist->SetBinContent(1, xsection);
	hCross_section_hist->SetBinContent(2, ntrials);  
	
	TFile* cross_section_data = new TFile("Cross_section_data.root", "RECREATE");
	cross_section_data->cd();

	hCross_section_hist->Write();
	cross_section_data->Close();

	
	return 0;

};
