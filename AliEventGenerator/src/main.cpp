// Stdlib header file for input and output.
#include <iostream>

// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"
//#include "/data2/varlamov/soft/pythia8310/include/Pythia8/Pythia.h"

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

		std::vector<AliParticle> chic;
		std::vector<AliParticle> Jpsi;
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

			if (pythia.event[i].eta() >= 4.){
				continue;
			}

			if ((pythia.event[i].id() == idChic0 or
				 pythia.event[i].id() == idChic1 or
				 pythia.event[i].id() == idChic2)and 
				pythia.event[i].status() == -62){
				AliParticle tmp;
				tmp.p0 = pythia.event[i].e();
				tmp.px = pythia.event[i].px();
				tmp.py = pythia.event[i].py();
				tmp.pz = pythia.event[i].pz();
				tmp.id = pythia.event[i].id();
				tmp.number_in_event = i;
				tmp.mother_number_in_event = pythia.event[i].mother1();
				tmp.mother_id = pythia.event[tmp.mother_number_in_event].id();
				tmp.daughter_1_number_in_event = pythia.event[i].daughter1();
				tmp.daughter_2_number_in_event = pythia.event[i].daughter2();
				chic.push_back(tmp);
			}

			if (pythia.event[i].id() == idJpsi){
				AliParticle tmp;
				tmp.p0 = pythia.event[i].e();
				tmp.px = pythia.event[i].px();
				tmp.py = pythia.event[i].py();
				tmp.pz = pythia.event[i].pz();
				tmp.id = pythia.event[i].id();
				tmp.number_in_event = i;
				tmp.mother_number_in_event = pythia.event[i].mother1();
				tmp.mother_id = pythia.event[tmp.mother_number_in_event].id();
				tmp.daughter_1_number_in_event = pythia.event[i].daughter1();
				tmp.daughter_2_number_in_event = pythia.event[i].daughter2();
				Jpsi.push_back(tmp);
			}

			if (pythia.event[i].id() == idPhoton){
				AliParticle tmp;
				tmp.p0 = pythia.event[i].e();
				tmp.px = pythia.event[i].px();
				tmp.py = pythia.event[i].py();
				tmp.pz = pythia.event[i].pz();
				tmp.id = pythia.event[i].id();
				tmp.number_in_event = i;
				tmp.mother_number_in_event = pythia.event[i].mother1();
				tmp.mother_id = pythia.event[tmp.mother_number_in_event].id();
				tmp.daughter_1_number_in_event = pythia.event[i].daughter1();
				tmp.daughter_2_number_in_event = pythia.event[i].daughter2();
				photons.push_back(tmp);
			}

			if (fabs(pythia.event[i].id()) == idElectron){
				AliParticle tmp;
				tmp.p0 = pythia.event[i].e();
				tmp.px = pythia.event[i].px();
				tmp.py = pythia.event[i].py();
				tmp.pz = pythia.event[i].pz();
				tmp.id = pythia.event[i].id();
				tmp.number_in_event = i;
				tmp.mother_number_in_event = pythia.event[i].mother1();
				tmp.mother_id = pythia.event[tmp.mother_number_in_event].id();
				tmp.daughter_1_number_in_event = pythia.event[i].daughter1();
				tmp.daughter_2_number_in_event = pythia.event[i].daughter2();

				if (pythia.event[i].id() > 0){
					electrons.push_back(tmp);
				} else {
					positrons.push_back(tmp);
				}
			}

			// if (fabs(pythia.event[i].id()) == idMuon){
			// 	AliParticle tmp;
			// 	tmp.p0 = pythia.event[i].e();
			// 	tmp.px = pythia.event[i].px();
			// 	tmp.py = pythia.event[i].py();
			// 	tmp.pz = pythia.event[i].pz();
			// 	tmp.id = pythia.event[i].id();
			// 	tmp.number_in_event = i;
			// 	tmp.mother_number_in_event = pythia.event[i].mother1();
			// 	tmp.mother_id = pythia.event[tmp.mother_number_in_event].id();
			// 	tmp.daughter_1_number_in_event = pythia.event[i].daughter1();
			// 	tmp.daughter_2_number_in_event = pythia.event[i].daughter2();

			// 	if (pythia.event[i].id() > 0){
			// 		muons.push_back(tmp);
			// 	} else {
			// 		antimuons.push_back(tmp);
			// 	}
			// }

			// if (fabs(pythia.event[i].id()) == idK0L or 
			// 	fabs(pythia.event[i].id()) == idn   or 
			// 	fabs(pythia.event[i].id()) == idPin){
			// 	AliParticle tmp;
			// 	tmp.p0 = pythia.event[i].e();
			// 	tmp.px = pythia.event[i].px();
			// 	tmp.py = pythia.event[i].py();
			// 	tmp.pz = pythia.event[i].pz();
			// 	tmp.id = pythia.event[i].id();
			// 	tmp.number_in_event = i;
			// 	tmp.mother_number_in_event = pythia.event[i].mother1();
			// 	tmp.mother_id = pythia.event[tmp.mother_number_in_event].id();
			// 	tmp.daughter_1_number_in_event = pythia.event[i].daughter1();
			// 	tmp.daughter_2_number_in_event = pythia.event[i].daughter2();

			// 	neutral.push_back(tmp);
			// }

			// if (fabs(pythia.event[i].id()) == idp   or 
			// 	fabs(pythia.event[i].id()) == idPic or 
			// 	fabs(pythia.event[i].id()) == idKc){
			// 	AliParticle tmp;
			// 	tmp.p0 = pythia.event[i].e();
			// 	tmp.px = pythia.event[i].px();
			// 	tmp.py = pythia.event[i].py();
			// 	tmp.pz = pythia.event[i].pz();
			// 	tmp.id = pythia.event[i].id();
			// 	tmp.number_in_event = i;
			// 	tmp.mother_number_in_event = pythia.event[i].mother1();
			// 	tmp.mother_id = pythia.event[tmp.mother_number_in_event].id();
			// 	tmp.daughter_1_number_in_event = pythia.event[i].daughter1();
			// 	tmp.daughter_2_number_in_event = pythia.event[i].daughter2();

			// 	charged.push_back(tmp);
			// }
			
		}
		General_event->chic 	 = chic;
		General_event->Jpsi 	 = Jpsi;
		General_event->electrons = electrons;
		General_event->positrons = positrons;
		General_event->muons     = muons;
		General_event->antimuons = antimuons;
		General_event->charged   = charged;
		General_event->neutral   = neutral;
		General_event->photons   = photons;
		test_tree->Fill();
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

}
