#define MyAnalysis_cxx
// Root > T->Process("MyAnalysis.C+")
#include "MyAnalysis.h"
#include <iostream>
#include <TH1F.h>
#include <TLatex.h>
using namespace std;
void MyAnalysis::BuildEvent() {
//void MyAnalysis::BuildEvent(int channel) {
   
   Muons.clear();
   for (int i = 0; i < NMuon; ++i) {
      MyMuon muon(Muon_Pt[i], Muon_Eta[i], Muon_Phi[i], Muon_E[i]);
      muon.SetIsolation(Muon_Iso[i]);
      muon.SetCharge(Muon_Charge[i]);
      Muons.push_back(muon);
   }
   
   Electrons.clear();
   for (int i = 0; i < NElectron; ++i) {
      MyElectron electron(Electron_Pt[i], Electron_Eta[i], Electron_Phi[i], Electron_E[i]);
      electron.SetIsolation(Electron_Iso[i]);
      electron.SetCharge(Electron_Charge[i]);
      Electrons.push_back(electron);
   }
   
   Photons.clear();
   for (int i = 0; i < NPhoton; ++i) {
      MyPhoton photon(Photon_Pt[i], Photon_Eta[i], Photon_Phi[i], Photon_E[i]);
      photon.SetIsolation(Photon_Iso[i]);
      Photons.push_back(photon);
   }
   
   Jets.clear();
   for (int i = 0; i < NJet; ++i) {
      MyJet jet(Jet_Pt[i], Jet_Eta[i], Jet_Phi[i], Jet_E[i]);
      jet.SetBTagDiscriminator(Jet_bDiscriminator[i]);
      //jet.SetJetID(Jet_ID[i]);
      Jets.push_back(jet);
   }
   //lepWn.SetXYZM(MCneutrino_px, MCneutrino_py, MCneutrino_pz, 0.0);
   mymet.SetXYZM(MET_Px, MET_Py, 0., 0.);
   
//EventWeight = PUWeight*GenWeight*weight_factor*norm_scale;

 //if(channel=0 && Semileptonic==0)  EventWeight=0.;
//if(channel==0)    EventWeight = PUWeight*GenWeight*weight_factor*norm_scale*Dileptonic; //for dileptonic
if(channel==1)    EventWeight = PUWeight*GenWeight*weight_factor*norm_scale*Semileptonic; //for semileptonic
else if (channel== 0 && Semileptonic==0)  EventWeight=0.;
//if(channel==2)    EventWeight = PUWeight*GenWeight*weight_factor*norm_scale*( (Dileptonic+Semileptonic)==0) ; //for hadronic
//if(channel==3)    EventWeight = PUWeight*GenWeight*weight_factor*norm_scale; //for all
}

void MyAnalysis::Begin(TTree * /*tree*/) {
   // The tree argument is deprecated (on PROOF 0 is passed).
   TString option = GetOption();
}

void MyAnalysis::SlaveBegin(TTree * /*tree*/) {
   // The tree argument is deprecated (on PROOF 0 is passed).
   TString option = GetOption();

   for(int i=0; i < 5; i++){ 
     h_NVertex[i] = new TH1F(Form("h_NVertex_S%i",i), "Number of vertex", 40 , 0, 40);
     h_NVertex[i]->SetXTitle("Number of Vertices");
     h_NVertex[i]->Sumw2();
     histograms.push_back(h_NVertex[i]);
     histograms_MC.push_back(h_NVertex[i]);
    
     h_NMuon[i] = new TH1F(Form("h_NMuon_S%i",i), "Number of muons", 7, 0, 7);
     h_NMuon[i]->SetXTitle("Number of Muons");
     h_NMuon[i]->Sumw2();
     histograms.push_back(h_NMuon[i]);
     histograms_MC.push_back(h_NMuon[i]);
 
     h_MuonIso[i] = new TH1F(Form("h_MuonIso_S%i",i), "Rel Iso", 40, 0, 0.2);
     h_MuonIso[i]->SetXTitle("Rel Iso");
     h_MuonIso[i]->Sumw2();
     histograms.push_back(h_MuonIso[i]);
     histograms_MC.push_back(h_MuonIso[i]);
 
     h_WMuon_MT[i] = new TH1F(Form("h_WMuon_MT_S%i",i), "Transverse mass", 50, 0, 200);
     h_WMuon_MT[i]->SetXTitle("MT(Gev)");
     h_WMuon_MT[i]->Sumw2();
     histograms.push_back(h_WMuon_MT[i]);
     histograms_MC.push_back(h_WMuon_MT[i]);

     h_WMuon_Phi[i] = new TH1F(Form("h_WMuon_Phi_S%i",i), "DR between muon and MET", 70, 0, 3.5);
     h_WMuon_Phi[i]->SetXTitle("DR between muon and MET");
     h_WMuon_Phi[i]->Sumw2();
     histograms.push_back(h_WMuon_Phi[i]);
     histograms_MC.push_back(h_WMuon_Phi[i]);

     h_NJet[i] = new TH1F(Form("h_NJet_S%i",i), "Number of jets", 14, 0, 14);
     h_NJet[i]->SetXTitle("Number of Jets");
     h_NJet[i]->Sumw2();
     histograms.push_back(h_NJet[i]);
     histograms_MC.push_back(h_NJet[i]);

     h_NBJet[i] = new TH1F(Form("h_NBJet_S%i",i), "Number of b tagged jets", 5, 0, 5);
     h_NBJet[i]->SetXTitle("Number of b Jets");
     h_NBJet[i]->Sumw2();
     histograms.push_back(h_NBJet[i]);
     histograms_MC.push_back(h_NBJet[i]);

     h_MET[i] = new TH1F(Form("h_MET_S%i",i), "MET", 40, 0, 200);
     h_MET[i]->SetXTitle("MET");
     h_MET[i]->Sumw2();
     histograms.push_back(h_MET[i]);
     histograms_MC.push_back(h_MET[i]);

   }

}

Bool_t MyAnalysis::Process(Long64_t entry) {
//Bool_t MyAnalysis::Process(Long64_t entry, int channel) {
   // The return value is currently not used.
   bool debug = false;
 
   ++TotalEvents;
   
   GetEntry(entry);

   if (TotalEvents % 1000000 == 0)
      cout << "Next event -----> " << TotalEvents << endl;
   
 BuildEvent();
 //  BuildEvent(channel);
   double MuonPtCut = 30.;
   double MuonEtaCut = 30.;
   double MuonRelIsoCut = 0.12;
   double ElectronPtCut = 30.;
   double ElectronEtaCut = 30.;
   double ElectronRelIsoCut = 0.12;
   //   for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
   //      cout << "pt, eta, phi, btag, id: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", " << it->IsBTagged() << ", " << it->GetJetID() //      << endl;
   //   }
   int N_IsoMuon = 0;

   int sel_mu = 0;
   int imu = 0;

   MyMuon *muon1, *muon2;
   for (vector<MyMuon>::iterator jt = Muons.begin(); jt != Muons.end(); ++jt) {
     if( Muon_Iso[imu] < MuonRelIsoCut){
       N_IsoMuon++;
       if( N_IsoMuon == 1 ) {
         muon1 = &(*jt); 
         sel_mu = imu; 
       }
       if( N_IsoMuon == 2 ) muon2 = &(*jt); 
     
      }
     imu++;
   }

   int N_IsoElectron = 0;
   
   for (int i = 0; i < NElectron; ++i) {
     if( Electron_Iso[i] < ElectronRelIsoCut){
       N_IsoElectron++;
     }
   }

   int N_VetoMuon = 0;
   
   for (int i = 0; i < NLooseMuon; ++i) {
     if( LooseMuon_Iso[i] < 0.25){
       N_VetoMuon++;
     }
   }

   int N_VetoElectron = 0;

   for (int i = 0; i < NLooseElectron; ++i) {
     if( LooseElectron_Iso[i] < 0.25){
       N_VetoElectron++;
     }
   }

   if( debug ) cout << "filling at step0..." << endl;
   //////////////////////////////
   //step 0 
   if( NMuon > 0 )
    {
     h_MuonIso[0]->Fill(Muon_Iso[0], EventWeight);
     h_NMuon[0]->Fill(N_IsoMuon, EventWeight);
     h_NVertex[0]->Fill(NVertex, EventWeight);
     h_WMuon_MT[0]->Fill( WMuon_MT[sel_mu], EventWeight);
     h_WMuon_Phi[0]->Fill( WMuon_Phi[sel_mu], EventWeight);
     h_NJet[0]->Fill(NJet, EventWeight);
     h_NBJet[0]->Fill(NBJet, EventWeight);
     h_MET[0]->Fill(MET, EventWeight);
    }

   if( debug ) cout << "filling at step1..." << endl;
   if(N_IsoMuon == 1 && N_VetoElectron == 0 && MuonPtCut )
     { //step 1
  
     h_MuonIso[1]->Fill(Muon_Iso[sel_mu], EventWeight); 
     h_NMuon[1]->Fill(N_IsoMuon, EventWeight);
     h_NVertex[1]->Fill(NVertex, EventWeight);
     h_WMuon_MT[1]->Fill( WMuon_MT[sel_mu], EventWeight);
     h_WMuon_Phi[1]->Fill( WMuon_Phi[sel_mu], EventWeight);
     h_NJet[1]->Fill(NJet, EventWeight);
     h_NBJet[1]->Fill(NBJet, EventWeight); 
     h_MET[1]->Fill(MET, EventWeight);
     
//if (N_IsoMuon > 1 ) h_Mmumu[1]->Fill((*muon1 + *muon2).M(), EventWeight);
     if( debug ) cout << "filling at step2..." << endl;
     if( NJet > 3)
     { //step 2
       h_MuonIso[2]->Fill(Muon_Iso[sel_mu], EventWeight); 
       h_NMuon[2]->Fill(N_IsoMuon, EventWeight);
       h_NVertex[2]->Fill(NVertex, EventWeight);
       h_WMuon_MT[2]->Fill( WMuon_MT[sel_mu], EventWeight);
       h_WMuon_Phi[2]->Fill( WMuon_Phi[sel_mu], EventWeight);
       h_NJet[2]->Fill(NJet, EventWeight);
       h_NBJet[2]->Fill(NBJet, EventWeight);
       h_MET[2]->Fill(MET, EventWeight);
     
//////steop3 MET
     if( debug ) cout << "filling at step3..." << endl;
     if( MET > 30){ //step 2
         h_MuonIso[3]->Fill(Muon_Iso[sel_mu], EventWeight); 
         h_NMuon[3]->Fill(N_IsoMuon, EventWeight);
         h_NVertex[3]->Fill(NVertex, EventWeight);
         h_WMuon_MT[3]->Fill( WMuon_MT[sel_mu], EventWeight);
         h_WMuon_Phi[3]->Fill( WMuon_Phi[sel_mu], EventWeight);
         h_NJet[3]->Fill(NJet, EventWeight);
         h_NBJet[3]->Fill(NBJet, EventWeight);
         h_MET[3]->Fill(MET, EventWeight);
       
    if( debug ) cout << "filling at step4..." << endl;

       if( NBJet > 1 )
       { //step 4
       h_MuonIso[4]->Fill(Muon_Iso[sel_mu], EventWeight); 
       h_NMuon[4]->Fill(N_IsoMuon, EventWeight);
       h_NVertex[4]->Fill(NVertex, EventWeight);
       h_WMuon_MT[4]->Fill( WMuon_MT[sel_mu], EventWeight);
       h_WMuon_Phi[4]->Fill( WMuon_Phi[sel_mu], EventWeight);
       h_NJet[4]->Fill(NJet, EventWeight);
       h_NBJet[4]->Fill(NBJet, EventWeight);
       h_MET[4]->Fill(MET, EventWeight);
       }// step4 
     
      } //step3
  
     }//step2
  } //step1
   if( debug ) cout << "ending event..." << endl; 
   return kTRUE;
}// Loop

void MyAnalysis::SlaveTerminate() {
   // The SlaveTerminate() function is called after all entries or objects
}
void MyAnalysis::Terminate() {
   // the results graphically or save the results to file.
}
