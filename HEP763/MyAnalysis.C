#define MyAnalysis_cxx
#include "MyAnalysis.h"
#include <iostream>
#include <TH1F.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH2F.h>
#include <TLatex.h>
using namespace std;
void MyAnalysis::BuildEvent() {
   
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
   mymet.SetXYZM(MET_Px, MET_Py, 0., 0.);
   
   EventWeight = PUWeight*GenWeight*weight_factor*norm_scale;
}

void MyAnalysis::Begin(TTree * /*tree*/) {
   // The tree argument is deprecated (on PROOF 0 is passed).
   TString option = GetOption();
}

void MyAnalysis::SlaveBegin(TTree * /*tree*/) {
   // The SlaveBegin() function is called after the Begin() function.
   TString option = GetOption();

   for(int i=0; i < 5; i++){ 
     hIso_vs_MET[i] = new TH2D(Form("hIso_vs_MET%i",i), "PF Isolation vs {#slash{E}_{T}}", 50 , 0, 200 , 100, 0 , 2.0 );
     hIso_vs_MET[i]->SetXTitle("#slash{E}_{T} [GeV]");
     hIso_vs_MET[i]->Sumw2();
     histograms_2D.push_back(hIso_vs_MET[i]);
     histograms_MC_2D.push_back(hIso_vs_MET[i]);
////
     h_Muon_Pt[i] = new TH1F(Form("h_Muon_Pt_S%i",i), "Muon Pt", 40, 0, 200);
     h_Muon_Pt[i]->SetXTitle("Muon Pt [GeV]");
     h_Muon_Pt[i]->Sumw2();
     histograms.push_back(h_Muon_Pt[i]);
     histograms_MC.push_back(h_Muon_Pt[i]);
    ///// 
     h_NVertex[i] = new TH1F(Form("h_NVertex_S%i",i), "Number of Vertex", 40 , 0, 40);
     h_NVertex[i]->SetXTitle("Number of Vertices");
     h_NVertex[i]->Sumw2();
     histograms.push_back(h_NVertex[i]);
     histograms_MC.push_back(h_NVertex[i]);
    
     h_NMuon[i] = new TH1F(Form("h_NMuon_S%i",i), "Number of Muons", 7, 0, 7);
     h_NMuon[i]->SetXTitle("Number of Muons");
     h_NMuon[i]->Sumw2();
     histograms.push_back(h_NMuon[i]);
     histograms_MC.push_back(h_NMuon[i]);
     //
     h_MuonIso[i] = new TH1F(Form("h_MuonIso_S%i",i), "Rel Iso", 40, 0, 0.2);
     h_MuonIso[i]->SetXTitle("Rel Isolation");
     h_MuonIso[i]->Sumw2();
     histograms.push_back(h_MuonIso[i]);
     histograms_MC.push_back(h_MuonIso[i]);
 
     h_WMuon_MT[i] = new TH1F(Form("h_WMuon_MT_S%i",i), "Transverse mass", 50, 0, 200);
     h_WMuon_MT[i]->SetXTitle("MT [GeV]");
     h_WMuon_MT[i]->Sumw2();
     histograms.push_back(h_WMuon_MT[i]);
     histograms_MC.push_back(h_WMuon_MT[i]);

     h_WMuon_Phi[i] = new TH1F(Form("h_WMuon_Phi_S%i",i), "DR between muon and MET", 70, 0, 3.5);
     h_WMuon_Phi[i]->SetXTitle("DR between muon and MET");
     h_WMuon_Phi[i]->Sumw2();
     histograms.push_back(h_WMuon_Phi[i]);
     histograms_MC.push_back(h_WMuon_Phi[i]);

     h_NJet[i] = new TH1F(Form("h_NJet_S%i",i), "Jet Multiplicity", 14, 0, 14);
     h_NJet[i]->SetXTitle("Jet Multiplicity");
     h_NJet[i]->Sumw2();
     histograms.push_back(h_NJet[i]);
     histograms_MC.push_back(h_NJet[i]);

     h_NBJet[i] = new TH1F(Form("h_NBJet_S%i",i), "b tagged Jet Multiplicity", 5, 0, 5);
     h_NBJet[i]->SetXTitle("CSVv2M  b-tagged Jet Multiplicity");
     h_NBJet[i]->Sumw2();
     histograms.push_back(h_NBJet[i]);
     histograms_MC.push_back(h_NBJet[i]);

     h_MET[i] = new TH1F(Form("h_MET_S%i",i), "MET", 40, 0, 200);
     h_MET[i]->SetXTitle("#slash{E}_{T} [GeV]");
     h_MET[i]->Sumw2();
     histograms.push_back(h_MET[i]);
     histograms_MC.push_back(h_MET[i]);

   }

}

Bool_t MyAnalysis::Process(Long64_t entry) {
   // The return value is currently not used.
   bool debug = false;
 
   ++TotalEvents;
   
   GetEntry(entry);

   if (TotalEvents % 1000000 == 0)
      cout << "Next event -----> " << TotalEvents << endl;
   
   BuildEvent();
   double Muon_PtCut = 30.;
   double MuonEtaCut = 30.;
   double MuonRelIsoCut = 0.12;
   double ElectronPtCut = 30.;
   double ElectronEtaCut = 30.;
   double ElectronRelIsoCut = 0.12;
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
     hIso_vs_MET[0]->Fill(MET, Muon_Iso[0], EventWeight);
     h_Muon_Pt[0]->Fill(Muon_Pt[sel_mu], EventWeight);
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
   if( NMuon == 1 && N_VetoElectron == 0 && Muon_PtCut )
     { //step 1
     hIso_vs_MET[1]->Fill(MET, Muon_Iso[sel_mu], EventWeight);
     h_Muon_Pt[1]->Fill(Muon_Pt[sel_mu], EventWeight);
     h_MuonIso[1]->Fill(Muon_Iso[sel_mu], EventWeight); 
     h_NMuon[1]->Fill(N_IsoMuon, EventWeight);
     h_NVertex[1]->Fill(NVertex, EventWeight);
     h_WMuon_MT[1]->Fill( WMuon_MT[sel_mu], EventWeight);
     h_WMuon_Phi[1]->Fill( WMuon_Phi[sel_mu], EventWeight);
     h_NJet[1]->Fill(NJet, EventWeight);
     h_NBJet[1]->Fill(NBJet, EventWeight); 
     h_MET[1]->Fill(MET, EventWeight);
     if( debug ) cout << "filling at step2..." << endl;
     if( NJet > 3)
     { //step 2
       hIso_vs_MET[2]->Fill(MET, Muon_Iso[sel_mu], EventWeight);
       h_Muon_Pt[2]->Fill(Muon_Pt[sel_mu], EventWeight);
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
         hIso_vs_MET[3]->Fill(MET, Muon_Iso[sel_mu], EventWeight);
         h_Muon_Pt[3]->Fill(Muon_Pt[sel_mu], EventWeight);
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
         hIso_vs_MET[4]->Fill(MET, Muon_Iso[sel_mu], EventWeight);
         h_Muon_Pt[4]->Fill(Muon_Pt[sel_mu], EventWeight);
         h_MuonIso[4]->Fill(Muon_Iso[sel_mu], EventWeight); 
         h_NMuon[4]->Fill(N_IsoMuon, EventWeight);
         h_NVertex[4]->Fill(NVertex, EventWeight);
         h_WMuon_MT[4]->Fill( WMuon_MT[sel_mu], EventWeight);
         h_WMuon_Phi[4]->Fill( WMuon_Phi[sel_mu], EventWeight);
         h_NJet[4]->Fill(NJet, EventWeight);
         h_NBJet[4]->Fill(NBJet, EventWeight);
         h_MET[4]->Fill(MET, EventWeight);
      } //step4
  
     }//step3
    }//step2
  } //step1
   if( debug ) cout << "ending event..." << endl; 
   return kTRUE;
}

void MyAnalysis::SlaveTerminate() {
   // The SlaveTerminate() function is called after all entries or objects
}
void MyAnalysis::Terminate() {
   // The Terminate() function is the last function to be called during
}
