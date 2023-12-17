#include <iostream>
#include <TFile.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
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

int main(){
  
    // Create input and output root file and read TTree from input

    
    TFile* output = new TFile("output.root", "RECREATE");
    TTree* true_chic_daughters_for_GEANT4 = new TTree("signal_event_electron_positron_gamma_from_chic_with_branchings", "signal_event_electron_positron_gamma_from_chic_with_branchings");

    // TLorentzVector* electron_from_chic = new TLorentzVector();
    // TLorentzVector* positron_from_chic = new TLorentzVector();
    // TLorentzVector* gamma_from_chic = new TLorentzVector();
    double branching = 0;
    double gamma_px = 0;
    double gamma_py = 0;
    double gamma_pz = 0;
    double gamma_p0 = 0;
    double electron_px = 0;
    double electron_py = 0;
    double electron_pz = 0;
    double electron_p0 = 0;
    double positron_px = 0;
    double positron_py = 0;
    double positron_pz = 0;
    double positron_p0 = 0;

    true_chic_daughters_for_GEANT4->Branch("event_branching", &branching);

    true_chic_daughters_for_GEANT4->Branch("gamma_px", &gamma_px);
    true_chic_daughters_for_GEANT4->Branch("gamma_py", &gamma_py);
    true_chic_daughters_for_GEANT4->Branch("gamma_pz", &gamma_pz);
    true_chic_daughters_for_GEANT4->Branch("gamma_p0", &gamma_p0);

    true_chic_daughters_for_GEANT4->Branch("electron_px", &electron_px);
    true_chic_daughters_for_GEANT4->Branch("electron_py", &electron_py);
    true_chic_daughters_for_GEANT4->Branch("electron_pz", &electron_pz);
    true_chic_daughters_for_GEANT4->Branch("electron_p0", &electron_p0);

    true_chic_daughters_for_GEANT4->Branch("positron_px", &positron_px);
    true_chic_daughters_for_GEANT4->Branch("positron_py", &positron_py);
    true_chic_daughters_for_GEANT4->Branch("positron_pz", &positron_pz);
    true_chic_daughters_for_GEANT4->Branch("positron_p0", &positron_p0);

	true_chic_daughters_for_GEANT4->SetAutoSave(0);

    TChain* chain = new TChain("AliEvent_data");
    TString data_path = "~/Documents/Projects/AliQuarkonium/AliEventGenerator/";

    for (int i = 0; i <= 11; ++i){
        chain->Add(Form("%sAliEvent_class_data_%02d.root", data_path.Data(), i));
    }

    int n = chain->GetEntries();
    printf("Number of entries: %10d\n", n);

    AliEvent *General_event = 0;
    chain->SetBranchAddress("AliEvent", &General_event);
    double branchings[3] = {5.971e-2 * 1.4e-2, 5.971e-2 * 34.3e-2, 5.971e-2 * 19.0e-2};


    for (int i = 0; i < n; ++i){
        chain->GetEntry(i);
        std::vector<AliParticle> chi_cJ   = General_event->chic;
        std::vector<AliParticle> electron = General_event->electrons;
        std::vector<AliParticle> positron = General_event->positrons;
        std::vector<AliParticle> photon   = General_event->photons;

        if (i % 10000 == 0){
            printf("Handled events:%10d\n", i);
        }

        if (!chi_cJ.empty()){
            for (auto el : electron){
                if (el.mother_id == 443)
                // *electron_from_chic = el.FMomentum();
                electron_p0 = el.p0;
                electron_px = el.px;
                electron_py = el.py;
                electron_pz = el.pz;
            }
            for (auto po : positron){
                if (po.mother_id == 443)
                positron_p0 = po.p0;
                positron_px = po.px;
                positron_py = po.py;
                positron_pz = po.pz;
            }
            for (auto gam : photon){
                if (gam.mother_id == 445 or 
                    gam.mother_id == 10441 or
                    gam.mother_id == 20443){

                    int event_type = -1;

                    if (gam.mother_id == 10441){ event_type = 0;}
                    if (gam.mother_id == 20443){ event_type = 1;}
                    if (gam.mother_id == 445)  { event_type = 2;}
                
                    // *gamma_from_chic = gam.FMomentum();

                    gamma_p0 = gam.p0;
                    gamma_px = gam.px;
                    gamma_py = gam.py;
                    gamma_pz = gam.pz;
                    branching = branchings[event_type];
                }
            }
        } else {continue;}

        true_chic_daughters_for_GEANT4->Fill();

    }

    true_chic_daughters_for_GEANT4->Write();
    output->Close();
    
    // TH2D* mass_spectrum_chic = 
    //     new TH2D("mass_spectrum_chic", "mass_spectrum_chic", 
    //              100, 3.3, 3.7, 
    //              10, 0., 10.);

    // TH2D* mass_spectrum_jpsi= 
    //     new TH2D("mass_spectrum_jpsi", "mass_spectrum_jpsi", 
    //              100, 3.0, 3.2, 
    //              10, 0., 10.);

    // TH2D* mass_spectrum_epen_true = 
    //     new TH2D("mass_spectrum_epen_true", "mass_spectrum_epen_true", 
    //              100, 3.0, 3.2, 
    //              10, 0., 10.);

    // TH2D* mass_spectrum_epen_cand= 
    //     new TH2D("mass_spectrum_epen_cand", "mass_spectrum_epen_cand", 
    //              100, 2, 3.5, 
    //              10, 0., 10.);
    
    // TH2D* mass_spectrum_epen_cand_r= 
    //     new TH2D("mass_spectrum_epen_cand_r", "mass_spectrum_epen_cand_r", 
    //              100, 2, 3.5, 
    //              10, 0., 10.);

    // TH2D* mass_spectrum_signal= 
    //     new TH2D("mass_spectrum_signal", "mass_spectrum_signal", 
    //              100, 0, 0.7, 
    //              10, 0., 10.);

    // TH2D* mass_spectrum_signal_w= 
    //     new TH2D("mass_spectrum_signal_w", "mass_spectrum_signal_w", 
    //              100, 3, 4, 
    //              10, 0., 10.);

    // TH2D* mass_spectrum_signal_r= 
    //     new TH2D("mass_spectrum_signal_r", "mass_spectrum_signal_r", 
    //              100, 3, 4, 
    //              10, 0., 10.);

    // TH2D* mass_spectrum_signal_rr= 
    //     new TH2D("mass_spectrum_signal_rr", "mass_spectrum_signal_rr", 
    //              100, 0, 0.7, 
    //              10, 0., 10.);

    // TH2D* resolution= 
    //     new TH2D("resolution", "resolution", 
    //              500, 0, 20, 
    //              500, 0, 20.);

    // double branchings[3] = {5.971e-2 * 1.4e-2, 5.971e-2 * 34.3e-2, 5.971e-2 * 19.0e-2};

    // for (auto value : branchings){
    //     std::cout << value << "\n";
    // }


    // output->cd();

    // for (int ievent = 0; ievent < n; ievent++){
    
    //     if (ievent % 1000 == 0){
    //         printf("Handled events:%10d\n", ievent);
    //     }
    
    //     branch->GetEntry(ievent);
    //     std::vector<AliParticle> chi_cJ   = General_event->chic;
    //     std::vector<AliParticle> JPsi     = General_event->Jpsi;
    //     std::vector<AliParticle> electron = General_event->electrons;
    //     std::vector<AliParticle> positron = General_event->positrons;
    //     std::vector<AliParticle> photon   = General_event->photons;

    //     int event_type = -1;
    
        
    //     for (uint i = 0; i < chi_cJ.size(); ++i){
    //         mass_spectrum_chic->Fill((chi_cJ[i].FMomentum()).M(), (chi_cJ[i].FMomentum()).Pt());
    //     }

    //     for (uint i = 0; i < JPsi.size(); ++i){
    //         mass_spectrum_jpsi->Fill((JPsi[i].FMomentum()).M(), (JPsi[i].FMomentum()).Pt());
    //     }

    //     TF1* crystall_ball = new TF1("crystall_ball", CB, 0., 10., 1);

    //     for (uint i = 0; i < electron.size(); ++i){
    //         if (electron[i].mother_id == 443){
    //             for (uint j = 0; j < positron.size(); ++j){
    //                 if (positron[j].mother_id == 443){
    //                     TLorentzVector elec = electron[i].FMomentum();
    //                     TLorentzVector posi = positron[j].FMomentum();
    //                     mass_spectrum_epen_true->Fill((elec + posi).M(), (elec + posi).Pt());

    //                     TLorentzVector elec_modif = resolutionElectron(elec);
    //                     TLorentzVector posi_modif = resolutionElectron(posi);


    //                     if (IsElectronDetectedInALICE3(elec, 2) and IsElectronDetectedInALICE3(posi, 2)){
                            
    //                         mass_spectrum_epen_cand  ->Fill((elec + posi).M(), (elec + posi).Pt(), 5.971e-2);
    //                         mass_spectrum_epen_cand_r->Fill((elec_modif + posi_modif).M(), (elec_modif + posi_modif).Pt(), 5.971e-2);

    //                         for (uint k = 0; k < photon.size(); ++k){
    //                             if (photon[k].mother_id == 445 or 
    //                                 photon[k].mother_id == 10441 or
    //                                 photon[k].mother_id == 20443){

    //                                 if (photon[k].mother_id == 10441){ event_type = 0;}
    //                                 if (photon[k].mother_id == 20443){ event_type = 1;}
    //                                 if (photon[k].mother_id == 445)  { event_type = 2;}

    //                                 if (IsElectronDetectedInALICE3(photon[k].FMomentum(), 1)){
    //                                     TLorentzVector phot = photon[k].FMomentum();
    //                                     TLorentzVector phot_modif = resolutionPhoton(phot);

    //                                     // crystall_ball->SetParameter(0, photon4m.E());
    //                                     resolution->Fill(phot.E(), phot_modif.E());

    //                                     mass_spectrum_signal->Fill((elec + posi + phot_modif).M() - (elec + posi).M(), (elec + posi + phot_modif).Pt(), branchings[event_type]);
    //                                     mass_spectrum_signal_w->Fill((elec + posi + phot_modif).M(), (elec + posi + phot_modif).Pt(), branchings[event_type]);
    //                                     mass_spectrum_signal_r->Fill((elec + posi + phot).M(), (elec + posi + phot).Pt(), branchings[event_type]);
    //                                     mass_spectrum_signal_rr->Fill((elec_modif + posi_modif + phot_modif).M() - (elec_modif + posi_modif).M(), (elec_modif + posi_modif + phot_modif).Pt(), branchings[event_type]);
    //                                 }
    //                             } else { continue;}
    //                         }
    //                     }                
    //                 } else {continue;}
    //             }
    //         } else {continue;}   
    //     }
    // }

    // for (int bins = 1; bins < mass_spectrum_signal_rr->GetNbinsY(); bins++){
        
    // }

    // // 3.17484e-01, 4.13089e-01, 4.58712e-01

    // mass_spectrum_chic->Write();
    // mass_spectrum_jpsi->Write();
    // mass_spectrum_epen_true->Write();
    // mass_spectrum_epen_cand->Write();
    // mass_spectrum_epen_cand_r->Write();
    // mass_spectrum_signal->Write();
    // mass_spectrum_signal_w->Write();
    // mass_spectrum_signal_r->Write();
    // mass_spectrum_signal_rr->Write();
    // resolution->Write();

    // output->Close();
    // delete output;
}

Double_t CB(Double_t * x, Double_t * par)
    {
        
    Double_t m = 0.923126 * par[0] - 0.0190108;
    Double_t s = (-0.000333094 * par[0] * par[0] + 0.0167971 * par[0] + 0.0282983);
    Double_t n = Sigmoid(par[0]*10);
    Double_t a = 1;
    Double_t dx = (x[0]-m)/s ;
    if(dx>-a)
        return TMath::Exp(-dx*dx/2.);
    else{
        Double_t A=TMath::Power((n/TMath::Abs(a)),n)*TMath::Exp(-a*a/2) ;
        Double_t B=n/TMath::Abs(a)-TMath::Abs(a) ;
        return A*TMath::Power((B-dx),-n);
    }
}


Double_t Sigmoid(Double_t x)
{

    double par[6];

    par[0] = 139.619;
    par[1] = 0.346921;
    par[2] = -17.4609;
    par[3] = 7.24141;
    par[4] = 0.0172638;
    par[5] = 6.97298;


    if (x < par[5]){ 
        return par[0]/(1 + par[1] * TMath::Exp(par[2] * (x - par[3]))) + par[4]*TMath::Exp(x);
    } else {
        return par[0]/(1 + par[1] * TMath::Exp(par[2] * (x - par[3])));
    }
}