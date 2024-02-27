#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TString.h>
#include <TLorentzVector.h>
#include "AliParticle.h"
#include "AliEvent.h"
#include <vector>

class AliEvent;
class AliParticle;

TLorentzVector resolutionElectron(TLorentzVector);
TLorentzVector resolutionPhoton(TLorentzVector);
bool IsElectronDetectedInALICE3(TLorentzVector, int);

Double_t CB(Double_t*, Double_t*);
Double_t Sigmoid(Double_t);

int main(int argc, char* argv[]){

    TString source_data_path;

    if (argc != 2){
        return 0;
    } else if (argc == 2) {
        source_data_path = TString(argv[1]);
    }
    
    TFile* output_tree = new TFile("tree_for_Geant_soft_QCD.root", "RECREATE");
    output_tree->cd();
    TTree* softQCD_tree = new TTree("soft_QCD_data", "soft_QCD_data");
    softQCD_tree->SetMaxTreeSize(1000000000);
	softQCD_tree->SetAutoSave(0);

    std::vector<std::vector<double>>* event_vector = new std::vector<std::vector<double>>;

    softQCD_tree->Branch("event", &event_vector);


    TChain* chain = new TChain("AliEvent_data");

    for (int i = 0; i <= 18; ++i){
       FILE* fp = fopen(Form("%sAliEvent_class_data_%d.root", source_data_path.Data(), i), "rb");
       if (fp != NULL){
           chain->Add(Form("%sAliEvent_class_data_%d.root", source_data_path.Data(), i));
       }
    }

    std::cout << chain->GetEntries() << "\n";

    AliEvent* event = nullptr;
    
    chain->SetBranchAddress("AliEvent", &event);

    TFile* output = new TFile("output_Soft_QCD_before_Geant.root", "RECREATE");
    output->cd();

	const int idK0L          =  130;
	const int idn            =  2112;
	const int idp            =  2212;
	const int idPic          =  211;
	const int idPin          =  111;
	const int idKc           =  321;
    
    TH2D* electrons_pt_eta = new TH2D("electrons_pt_eta", "electrons_pt_eta", 1000., 0., 20., 1000, -2.5, 2.5);
    TH2D* positrons_pt_eta = new TH2D("positrons_pt_eta", "positrons_pt_eta", 1000., 0., 10.,  1000, -2.5, 2.5);
    TH2D* muons_pt_eta = new TH2D("muons_pt_eta", "muons_pt_eta", 1000., 0., 10., 1000, -2.5, 2.5);
    TH2D* antimuons_pt_eta = new TH2D("antimuons_pt_eta", "antimuons_pt_eta", 1000., 0., 10., 1000, -2.5, 2.5);
    TH2D* gamma_pt_eta = new TH2D("gamma_pt_eta", "gamma_pt_eta", 1000., 0., 10., 1000, -2.5, 2.5);
    TH2D* proton_pt_eta = new TH2D("proton_pt_eta", "proton_pt_eta", 1000., 0., 10., 1000, -2.5, 2.5);
    TH2D* kaon_pt_eta = new TH2D("kaon_pt_eta", "kaon_pt_eta", 1000., 0., 10., 1000, -2.5, 2.5);
    TH2D* pion_pt_eta = new TH2D("pion_pt_eta", "pion_pt_eta", 1000., 0., 10., 1000, -2.5, 2.5);
    TH2D* kaonl_pt_eta = new TH2D("kaonl_pt_eta", "kaonl_pt_eta", 1000., 0., 10., 1000, -2.5, 2.5);
    TH2D* neutron_pt_eta = new TH2D("neutron_pt_eta", "neutron_pt_eta", 1000., 0., 10., 1000, -2.5, 2.5);
    electrons_pt_eta->Sumw2();
    positrons_pt_eta->Sumw2();
    muons_pt_eta->Sumw2();
    antimuons_pt_eta->Sumw2();
    gamma_pt_eta->Sumw2();
    proton_pt_eta->Sumw2();
    kaon_pt_eta->Sumw2();
    pion_pt_eta->Sumw2();
    kaonl_pt_eta->Sumw2();
    neutron_pt_eta->Sumw2();

    TH2D* electrons_p_e = new TH2D("electrons_p_e", "electrons_p_e", 1000, 0., 20., 1000., 0., 20.);
    TH2D* positrons_p_e = new TH2D("positrons_p_e", "positrons_p_e", 1000, 0., 20., 1000., 0., 20.);
    TH2D* muons_p_e = new TH2D("muons_p_e", "muons_p_e", 1000, 0., 20., 1000., 0., 20.);
    TH2D* antimuons_p_e = new TH2D("antimuons_p_e", "antimuons_p_e", 1000, 0., 20., 1000., 0., 20.);
    TH2D* gamma_p_e = new TH2D("gamma_p_e", "gamma_p_e", 1000, 0., 20., 1000., 0., 20.);
    TH2D* proton_p_e = new TH2D("proton_p_e", "proton_p_e", 1000, 0., 20., 1000., 0., 20.);
    TH2D* kaon_p_e = new TH2D("kaon_p_e", "kaon_p_e", 1000, 0., 20., 1000., 0., 20.);
    TH2D* pion_p_e = new TH2D("pion_p_e", "pion_p_e", 1000, 0., 20., 1000., 0., 20.);
    TH2D* kaonl_p_e = new TH2D("kaonl_p_e", "kaonl_p_e", 1000, 0., 20., 1000., 0., 20.);
    TH2D* neutron_p_e = new TH2D("neutron_p_e", "neutron_p_e", 1000, 0., 20., 1000., 0., 20.);
    electrons_p_e->Sumw2();
    positrons_p_e->Sumw2();
    muons_p_e->Sumw2();
    antimuons_p_e->Sumw2();
    gamma_p_e->Sumw2();
    proton_p_e->Sumw2();
    kaon_p_e->Sumw2();
    pion_p_e->Sumw2();
    kaonl_p_e->Sumw2();
    neutron_p_e->Sumw2();



    for (int i = 0; i < chain->GetEntries(); ++i){

        event_vector->clear();
        chain->GetEntry(i);

        if (i % 10000 == 0){
            printf(Form("Handled events: %07d of %07d\n", i, chain->GetEntries()));
        }

        bool signal_event_in_data = event->signal_event_in_data;
        std::vector<AliParticle> chic = event->chic;
        std::vector<AliParticle> Jpsi = event->Jpsi;
        std::vector<AliParticle> signal_electrons = event->signal_electrons;
        std::vector<AliParticle> signal_positrons = event->signal_positrons;
        std::vector<AliParticle> signal_photons = event->signal_photons;
        
        std::vector<AliParticle> electrons = event->electrons;
        std::vector<AliParticle> positrons = event->positrons;
        std::vector<AliParticle> muons = event->muons;
        std::vector<AliParticle> antimuons = event->antimuons;
        std::vector<AliParticle> photons = event->photons;
        std::vector<AliParticle> charged = event->charged;
        std::vector<AliParticle> neutral = event->neutral;       

        for (auto elec : electrons){
            electrons_pt_eta->Fill(elec.FMomentum().Pt(), elec.FMomentum().Eta());
            electrons_p_e->Fill(elec.FMomentum().P(), elec.FMomentum().E());
            if (fabs(elec.FMomentum().Eta()) < 2.){
                std::vector<double> tmp = {elec.p0, elec.px, elec.py, elec.pz, elec.id};
                event_vector->push_back(tmp);
            }
        }

        for (auto posi : positrons){
            positrons_pt_eta->Fill(posi.FMomentum().Pt(), posi.FMomentum().Eta());
            positrons_p_e->Fill(posi.FMomentum().P(), posi.FMomentum().E());
            if (fabs(posi.FMomentum().Eta()) < 2.){
                std::vector<double> tmp = {posi.p0, posi.px, posi.py, posi.pz, posi.id};
                event_vector->push_back(tmp);
            }
        }

        for (auto muon : muons){
            muons_pt_eta->Fill(muon.FMomentum().Pt(), muon.FMomentum().Eta());
            muons_p_e->Fill(muon.FMomentum().P(), muon.FMomentum().E());
            if (fabs(muon.FMomentum().Eta()) < 2.){
                std::vector<double> tmp = {muon.p0, muon.px, muon.py, muon.pz, muon.id};
                event_vector->push_back(tmp);
            }
        }

        for (auto antimuon : antimuons){
            antimuons_pt_eta->Fill(antimuon.FMomentum().Pt(), antimuon.FMomentum().Eta());
            antimuons_p_e->Fill(antimuon.FMomentum().P(), antimuon.FMomentum().E());
            if (fabs(antimuon.FMomentum().Eta()) < 2.){
                std::vector<double> tmp = {antimuon.p0, antimuon.px, antimuon.py, antimuon.pz, antimuon.id};
                event_vector->push_back(tmp);
            }
        }

        for (auto gamma : photons){
            gamma_pt_eta->Fill(gamma.FMomentum().Pt(), gamma.FMomentum().Eta());
            gamma_p_e->Fill(gamma.FMomentum().P(), gamma.FMomentum().E());
            if (fabs(gamma.FMomentum().Eta()) < 2.){
                std::vector<double> tmp = {gamma.p0, gamma.px, gamma.py, gamma.pz, gamma.id};
                event_vector->push_back(tmp);
            }
        }

        for (auto charg : charged){
            if (charg.id == idp){
                proton_pt_eta->Fill(charg.FMomentum().Pt(), charg.FMomentum().Eta());
                proton_p_e->Fill(charg.FMomentum().P(), charg.FMomentum().E());
            }
            if (charg.id == idKc){
                kaon_pt_eta->Fill(charg.FMomentum().Pt(), charg.FMomentum().Eta());
                kaon_p_e->Fill(charg.FMomentum().P(), charg.FMomentum().E());
            }
            if (charg.id == idPic){
                pion_pt_eta->Fill(charg.FMomentum().Pt(), charg.FMomentum().Eta());
                pion_p_e->Fill(charg.FMomentum().P(), charg.FMomentum().E());
            }
            if (fabs(charg.FMomentum().Eta()) < 2.){
                std::vector<double> tmp = {charg.p0, charg.px, charg.py, charg.pz, charg.id};
                event_vector->push_back(tmp);
            }
        }
        for (auto neutr : neutral){
            if (neutr.id == idn){
                neutron_pt_eta->Fill(neutr.FMomentum().Pt(), neutr.FMomentum().Eta());
                neutron_p_e->Fill(neutr.FMomentum().P(), neutr.FMomentum().E());
            }
            if (neutr.id == idK0L){
                kaonl_pt_eta->Fill(neutr.FMomentum().Pt(), neutr.FMomentum().Eta());
                kaonl_p_e->Fill(neutr.FMomentum().P(), neutr.FMomentum().E());
            }
            if (fabs(neutr.FMomentum().Eta()) < 2.){
                std::vector<double> tmp = {neutr.p0, neutr.px, neutr.py, neutr.pz, neutr.id};
                event_vector->push_back(tmp);
            }
        }
        softQCD_tree->Fill();
    }

    electrons_pt_eta->Write();
    positrons_pt_eta->Write();
    muons_pt_eta->Write();
    antimuons_pt_eta->Write();  
    gamma_pt_eta->Write();
    proton_pt_eta->Write();
    kaon_pt_eta->Write();
    pion_pt_eta->Write();
    neutron_pt_eta->Write();
    kaonl_pt_eta->Write();

    electrons_p_e->Write();
    positrons_p_e->Write();
    muons_p_e->Write();
    antimuons_p_e->Write();  
    gamma_p_e->Write();
    proton_p_e->Write();
    kaon_p_e->Write();
    pion_p_e->Write();
    neutron_p_e->Write();
    kaonl_p_e->Write();
    
    output->Close();

    output_tree->cd();
    softQCD_tree->Write();

    return 0;
}
