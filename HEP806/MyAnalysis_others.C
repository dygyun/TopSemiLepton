#define MyAnalysis_others_cxx
// Root > T->Process("MyAnalysis_others.C","some options")
// Root > T->Process("MyAnalysis_others.C+")
#include "MyAnalysis_others.h"
#include <iostream>
#include <TH1D.h>
#include <TH2D.h>
#include <TLatex.h>
using namespace std;

void MyAnalysis_others::GetMuSF() {                                                                         
   TFile *MuSF     = TFile::Open("/cms/scratch/dygyun/v806/MuJet/EfficienciesAndSF_BCDEF_mujetID.root"); // IDISO mu   
   TFile *MuIsoSF  = TFile::Open("/cms/scratch/dygyun/v806/MuJet/EfficienciesAndSF_mujetIsoSF.root"); // IDISO mu   
   TFile *MuTrigSF = TFile::Open("/cms/scratch/dygyun/v806/MuJet/EfficienciesAndSF_RunBtoF_mujetTriggerSF.root"); // IDISO mu   
   h_Muid_sf       = (TH2D*)MuSF->Get("MC_NUM_TightID_DEN_genTracks_PAR_pt_eta/abseta_pt_ratio");
   h_MuIso_sf      = (TH2D*)MuIsoSF->Get("TightISO_TightID_pt_eta/abseta_pt_ratio");
   h_MuTrig_sf     = (TH2D*)MuTrigSF->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
//     cout << "test Mu Trigger SF : "<< MuTrigSF->GetName() << endl;                                          
   TFile *MuSF_GH  = TFile::Open("/cms/scratch/dygyun/v806/MuJet/EfficienciesAndSF_GH_Sep_promptReco_MC_Moriond.root"); // IDISO mu   
   TFile *MuIsoSF_GH  = TFile::Open("/cms/scratch/dygyun/v806/MuJet/EfficienciesAndSF_GH_IsoSF.root"); // IDISO mu   
   TFile *MuTrigSF_GH = TFile::Open("/cms/scratch/dygyun/v806/MuJet/EfficienciesAndSF_Period4.root"); // IDISO mu   
   h_Muid_sf_GH       = (TH2D*)MuSF_GH->Get("MC_NUM_TightID_DEN_genTracks_PAR_pt_eta/abseta_pt_ratio");         
   h_MuIso_sf_GH      = (TH2D*)MuIsoSF_GH->Get("TightISO_TightID_pt_eta/abseta_pt_ratio");         
   h_MuTrig_sf_GH     = (TH2D*)MuTrigSF_GH->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");         
   //`cout << "test MuSF File : "<< MuSF->GetName() << endl;                                         
}    

void MyAnalysis_others::BuildEvent() {
   
   Muons.clear();
   for (int i = 0; i < NMuon; ++i) {
      MyMuon muon(Muon_Pt[i], Muon_Eta[i], Muon_Phi[i], Muon_E[i]);
      muon.SetIsolation(Muon_Iso03[i]);
      muon.SetCharge(Muon_Charge[i]);
      Muons.push_back(muon);
   }
   Electrons.clear();
   for (int i = 0; i < NElectron; ++i) {
      MyElectron electron(Electron_Pt[i], Electron_Eta[i], Electron_Phi[i], Electron_E[i]);
      electron.SetIsolation(Electron_Iso03[i]);
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
   //hadB.SetXYZM(MChadronicBottom_px, MChadronicBottom_py, MChadronicBottom_pz, 4.8);
   mymet.SetXYZM(MET_Px, MET_Py, 0., 0.);
  
   if( Lumi == 1 ){ norm_scale = 1.0; }
   else{ norm_scale = Lumi/(nEvents/Sigma);}

   EventWeight = CSVWeight*PUWeight*GenWeight*weight_factor*norm_scale;
   Acc_EventWeight = CSVWeight*PUWeight*GenWeight;
   
}

void MyAnalysis_others::Begin(TTree * /*tree*/) {
   // The Begin() function is called at the start of the query.
   TString option = GetOption();
   cout << "Process " << option << endl;
 GetMuSF();
}

void MyAnalysis_others::SlaveBegin(TTree * /*tree*/) {
   // The SlaveBegin() function is called after the Begin() function.
   TString option = GetOption();

   for(int i=0; i < 5; i++){ 
     
     h_Muon_Pt[i] = new TH1D(Form("h_Muon_Pt_S%i",i), "Muon Pt", 40, 0, 200);
     h_Muon_Pt[i]->SetXTitle("Muon Pt [GeV]");
     h_Muon_Pt[i]->Sumw2();
     histograms.push_back(h_Muon_Pt[i]);
     histograms_MC.push_back(h_Muon_Pt[i]);

     h_PUWeight[i] = new TH1D(Form("h_PUWeight_S%i",i), "PileUp Weight", 50 , 0, 2.5);
     h_PUWeight[i]->SetXTitle("PU Weight");
     h_PUWeight[i]->Sumw2();
     histograms.push_back(h_PUWeight[i]);
     histograms_MC.push_back(h_PUWeight[i]); 
     
     h_NVertex[i] = new TH1D(Form("h_NVertex_S%i",i), "Number of vertex", 70 , 0, 70);
     h_NVertex[i]->SetXTitle("Number of Vertex");
     h_NVertex[i]->Sumw2();
     histograms.push_back(h_NVertex[i]);
     histograms_MC.push_back(h_NVertex[i]);
    
     h_NMuon[i] = new TH1D(Form("h_NMuon_S%i",i), "Number of muons", 7, 0, 7);
     h_NMuon[i]->SetXTitle("Muon Multiplicity");
     h_NMuon[i]->Sumw2();
     histograms.push_back(h_NMuon[i]);
     histograms_MC.push_back(h_NMuon[i]);
 
     h_MuonIso[i] = new TH1D(Form("h_MuonIso_S%i",i), "Relative Isolation", 40, 0, 0.2);
     h_MuonIso[i]->SetXTitle("Relative Isolation (GeV)");
     h_MuonIso[i]->Sumw2();
     histograms.push_back(h_MuonIso[i]);
     histograms_MC.push_back(h_MuonIso[i]);
 
     h_WMuon_MT[i] = new TH1D(Form("h_WMuon_MT_S%i",i), "Transverse mass", 50, 0, 200);
     h_WMuon_MT[i]->SetXTitle("MT(Gev)");
     h_WMuon_MT[i]->Sumw2();
     histograms.push_back(h_WMuon_MT[i]);
     histograms_MC.push_back(h_WMuon_MT[i]);

     h_dR_LepJet[i] = new TH1D(Form("h_dR_LepJet_S%i",i), "DR between muon and Jet", 50, 0, 5);
     h_dR_LepJet[i]->SetXTitle("DR between muon and Jet");
     h_dR_LepJet[i]->Sumw2();
     histograms.push_back(h_dR_LepJet[i]);
     histograms_MC.push_back(h_dR_LepJet[i]);

     h_NJet[i] = new TH1D(Form("h_NJet_S%i",i), "Number of jets", 14, 0, 14);
     h_NJet[i]->SetXTitle("Jet Multiplicity");
     h_NJet[i]->Sumw2();
     histograms.push_back(h_NJet[i]);
     histograms_MC.push_back(h_NJet[i]);

     h_NBJet[i] = new TH1D(Form("h_NBJet_S%i",i), "Number of b tagged jets", 9, 0, 9);
     h_NBJet[i]->SetXTitle("b-tagged Jet Multiplicity (CSVM)");
     h_NBJet[i]->Sumw2();
     histograms.push_back(h_NBJet[i]);
     histograms_MC.push_back(h_NBJet[i]);

     h_MET[i] = new TH1D(Form("h_MET_S%i",i), "MET", 40, 0, 200);
     h_MET[i]->SetXTitle("MET");
     h_MET[i]->Sumw2();
     histograms.push_back(h_MET[i]);
     histograms_MC.push_back(h_MET[i]);

     h_LepJetMass[i] = new TH1D(Form("h_LepJetMass_S%i",i), "Lepton+Jet invariant Mass", 50, 0, 300);
     h_LepJetMass[i]->SetXTitle("Lepton + jet Mass [GeV]");
     h_LepJetMass[i]->Sumw2();
     histograms.push_back(h_LepJetMass[i]);
     histograms_MC.push_back(h_LepJetMass[i]);
     
     h_nAccMuon[i] = new TH1D(Form("h_nAccMuon_S%i",i), "Number of Accepted muons", 7, 0, 7);
     h_nAccMuon[i]->SetXTitle("Accepeted Muon Multiplicity");
     h_nAccMuon[i]->Sumw2();
     histograms.push_back(h_nAccMuon[i]);
     histograms_MC.push_back(h_nAccMuon[i]);
   }

}

Bool_t MyAnalysis_others::Process(Long64_t entry) {
   // The Process() function is called for each entry in the tree (or possibly
   bool debug = false;
 
   ++TotalEvents;
   
   GetEntry(entry);

   if (TotalEvents % 1000000 == 0)
      cout << "Next event -----> " << TotalEvents << endl;
   
   BuildEvent();
  if ( SemiLeptonic == 0 ) {

   double MuonPtCut = 30.;
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
     if( Muon_Iso03[imu] < MuonRelIsoCut){
       N_IsoMuon++;
       if( N_IsoMuon == 1 ) {
         muon1 = &(*jt); 
         sel_mu = imu; 
       }
       if( N_IsoMuon == 2 ) muon2 = &(*jt); 
     }
     imu++;
   }
//////////////////////////////////
   MyMuon testMuon ;
   double dr_LepJet =-999;
//   ////////////Jet dR  jet cleaning///
   bool cleanJet = false;
   int n_noncleanedJet = 0;
   int NJet_tmp = 0;
   for (vector<MyJet>::iterator jt = Jets.begin(); jt != Jets.end(); ++jt) 
   {
      MyJet *gjet;
      gjet= &(*jt); 
      
      if(N_IsoMuon == 1)
      {
         dr_LepJet =  gjet->DeltaR( testMuon );
       //   cout << "dR" << dr_LepJet  << endl;  
      }
      if(dr_LepJet > 0.4) 
      {
         NJet_tmp++;
      }
      else { n_noncleanedJet++;}
   }
  if ( n_noncleanedJet == 0 ) {cleanJet = true;}
   //   cout << "Jetcleaning:" << cleanJet << endl;
//////////

   int N_IsoElectron = 0;
   
   for (int i = 0; i < NElectron; ++i) {
     if( Electron_Iso03[i] < ElectronRelIsoCut){
       N_IsoElectron++;
     }
   }

   int N_VetoMuon = 0;
   
   for (int i = 0; i < NLooseMuon; ++i) {
     if( LooseMuon_Iso03[i] < 0.25){
       N_VetoMuon++;
     }
   }

   int N_VetoElectron = 0;

   for (int i = 0; i < NLooseElectron; ++i) {
     if( LooseElectron_Iso03[i] < 0.25){
       N_VetoElectron++;
     }
   }

   if( debug ) cout << "filling at step0..." << endl;

   if(!IsMuonTrig) return kTRUE;
   //////////////////////////////
   //step 0 
   if( NMuon == 1 ){
     h_Muon_Pt[0]->Fill(Muon_Pt[sel_mu], EventWeight);
     h_MuonIso[0]->Fill(Muon_Iso03[0], EventWeight);
     h_NMuon[0]->Fill(N_IsoMuon, EventWeight);
     //h_nAccMuon[0]->Fill(N_IsoMuon, Acc_EventWeight);
     h_NVertex[0]->Fill(NVertex, EventWeight);
       h_PUWeight[0]->Fill(PUWeight, 1);
     h_WMuon_MT[0]->Fill( WMuon_MT[sel_mu], EventWeight);
     h_dR_LepJet[0]->Fill( dr_LepJet, EventWeight);
     h_NJet[0]->Fill(NJet, EventWeight);
     h_NBJet[0]->Fill(NBJet, EventWeight);
     h_MET[0]->Fill(MET, EventWeight);
   }
//
   if( debug ) cout << "filling at step1..." << endl;
   if( cleanJet && N_IsoMuon == 1 && N_VetoMuon && ( MuonPtCut ) ){ //step 1
   //if( cleanJet && N_IsoMuon == 1 && N_VetoElectron == 0 &&  ( MuonPtCut ) ){ //step 1
   float lumi    = 35867.059982506; 
   float lumi_BF = 16146.177653168; 
   float lumi_GH = 19720.882329338; 
     double mupt = -999;
     if ( Muon_Pt[sel_mu] > 120 ){ mupt = 119.9;}
     else { mupt = Muon_Pt[sel_mu];}
     int xbin = h_Muid_sf->GetXaxis()->FindBin(abs(Muon_Eta[sel_mu]));
     int ybin = h_Muid_sf->GetYaxis()->FindBin(mupt);
     int xIsobin = h_MuIso_sf->GetXaxis()->FindBin(abs(Muon_Eta[sel_mu]));
     int yIsobin = h_MuIso_sf->GetYaxis()->FindBin(mupt);
     double musf    = h_Muid_sf->GetBinContent(xbin,ybin);
     double muIsosf = h_MuIso_sf->GetBinContent(xIsobin,yIsobin);
     if ( Muon_Pt[sel_mu] > 500 ){ mupt = 499.9;}
     else { mupt = Muon_Pt[sel_mu];}
     int xTrigbin = h_MuTrig_sf->GetXaxis()->FindBin(abs(Muon_Eta[sel_mu]));
     int yTrigbin = h_MuTrig_sf->GetYaxis()->FindBin(mupt);
     double muTrigsf = h_MuTrig_sf->GetBinContent(xTrigbin,yTrigbin);
   // For GH     cout << "mu Trig sf : " <<  muTrigsf << endl;
     if ( Muon_Pt[sel_mu] > 120 ){ mupt = 119.9;}
     else { mupt = Muon_Pt[sel_mu];}
     int xbin_GH = h_Muid_sf_GH->GetXaxis()->FindBin(abs(Muon_Eta[sel_mu]));
     int ybin_GH = h_Muid_sf_GH->GetYaxis()->FindBin(mupt);
     int xIsobin_GH = h_MuIso_sf_GH->GetXaxis()->FindBin(abs(Muon_Eta[sel_mu]));
     int yIsobin_GH = h_MuIso_sf_GH->GetYaxis()->FindBin(mupt);
     double musf_GH     = h_Muid_sf_GH->GetBinContent(xbin_GH,ybin_GH);
     double muIsosf_GH  = h_MuIso_sf_GH->GetBinContent(xIsobin_GH,yIsobin_GH);
     if ( Muon_Pt[sel_mu] > 500 ){ mupt = 499.9;}
     else { mupt = Muon_Pt[sel_mu];}
     int xTrigbin_GH = h_MuTrig_sf_GH->GetXaxis()->FindBin(abs(Muon_Eta[sel_mu]));
     int yTrigbin_GH = h_MuTrig_sf_GH->GetYaxis()->FindBin(mupt);
     double muTrigsf_GH = h_MuTrig_sf_GH->GetBinContent(xTrigbin_GH,yTrigbin_GH);
/////////////Combine BF to GH
     double musf_tot     = musf*(lumi_BF/lumi)+musf_GH*(lumi_GH/lumi);
     double muIsosf_tot  = muIsosf*(lumi_BF/lumi)+muIsosf_GH*(lumi_GH/lumi);
     double muTrigsf_tot = muTrigsf*(lumi_BF/lumi)+muTrigsf_GH*(lumi_GH/lumi);
     
     EventWeight     = muTrigsf_tot*muIsosf_tot*musf_tot*EventWeight; 
     Acc_EventWeight = muTrigsf_tot*muIsosf_tot*musf_tot*Acc_EventWeight; 
     //Acc_EventWeight = muTrigsf*muIsosf*musf*Acc_EventWeight; 
 
     h_Muon_Pt[1]->Fill(Muon_Pt[sel_mu], EventWeight);
     h_MuonIso[1]->Fill(Muon_Iso03[sel_mu], EventWeight); 
     h_NMuon[1]->Fill(N_IsoMuon, EventWeight);
     //h_nAccMuon[1]->Fill(N_IsoMuon, Acc_EventWeight);
     h_NVertex[1]->Fill(NVertex, EventWeight);
       h_PUWeight[1]->Fill(PUWeight, 1);
     h_WMuon_MT[1]->Fill( WMuon_MT[sel_mu], EventWeight);
     h_dR_LepJet[1]->Fill( dr_LepJet, EventWeight);
     h_NJet[1]->Fill(NJet, EventWeight);
     h_NBJet[1]->Fill(NBJet, EventWeight); 
     h_MET[1]->Fill(MET, EventWeight);
   //  if (N_IsoMuon > 1 ) h_Mmumu[1]->Fill((*muon1 + *muon2).M(), EventWeight);
     if( debug ) cout << "filling at step2..." << endl;
     if( NJet > 3){ //step 2
         double dR_ = +999;
         std::vector<TLorentzVector> Jet;
         std::vector<TLorentzVector> bJet;
         TLorentzVector jet; 

         for(int ijet=0; ijet < NJet; ijet++)    
         {
           jet.SetPtEtaPhiE( Jet_Pt[ijet],Jet_Eta[ijet],Jet_Phi[ijet],Jet_E[ijet] );
           if (jet.Pt()>30)
           {
           Jet.push_back(jet);
             if ( dR_ > jet.DeltaR(*muon1))
             {
               dR_ = jet.DeltaR(*muon1);
             } 
             //    NJets++;
           }
      }   //end of ijet NJet for loop
  
           if (dR_ < 999)  h_LepJetMass[2]->Fill( ((*muon1) + (jet)).M(), EventWeight);
              //  h_LepJetMass[2]->Fill( ((*muon1) + (*jet)).M(), EventWeight);
            h_Muon_Pt[2]->Fill(Muon_Pt[sel_mu], EventWeight);
            h_MuonIso[2]->Fill(Muon_Iso03[sel_mu], EventWeight); 
            h_NMuon[2]->Fill(N_IsoMuon, EventWeight);
            //h_nAccMuon[2]->Fill(N_IsoMuon, Acc_EventWeight);
            h_NVertex[2]->Fill(NVertex, EventWeight);
            h_WMuon_MT[2]->Fill( WMuon_MT[sel_mu], EventWeight);
            h_dR_LepJet[2]->Fill( dr_LepJet, EventWeight);
            h_NJet[2]->Fill(NJet, EventWeight);
            h_NBJet[2]->Fill(NBJet, EventWeight);
            h_MET[2]->Fill(MET, EventWeight);
 
                  if( debug ) cout << "filling at step3..." << endl;
  
                  if( MET > 30 ){ //step 3
                    h_Muon_Pt[3]->Fill(Muon_Pt[sel_mu], EventWeight);
                    h_MuonIso[3]->Fill(Muon_Iso03[sel_mu], EventWeight); 
                    h_NMuon[3]->Fill(N_IsoMuon, EventWeight);
                    //h_nAccMuon[3]->Fill(N_IsoMuon, Acc_EventWeight);
                    h_NVertex[3]->Fill(NVertex, EventWeight);
                    h_WMuon_MT[3]->Fill( WMuon_MT[sel_mu], EventWeight);
                    h_dR_LepJet[3]->Fill( dr_LepJet, EventWeight);
                    h_NJet[3]->Fill(NJet, EventWeight);
                    h_NBJet[3]->Fill(NBJet, EventWeight);
                    h_MET[3]->Fill(MET, EventWeight);
                    h_LepJetMass[3]->Fill( ((*muon1) + (jet)).M(), EventWeight);
  
                           if( NBJet > 1 ){ 
                             h_Muon_Pt[4]->Fill(Muon_Pt[sel_mu], EventWeight);
                             h_MuonIso[4]->Fill(Muon_Iso03[sel_mu], EventWeight);
                             h_NMuon[4]->Fill(N_IsoMuon, EventWeight);
                             //h_nAccMuon[4]->Fill(N_IsoMuon, Acc_EventWeight);
                             h_NVertex[4]->Fill(NVertex, EventWeight);
                             h_WMuon_MT[4]->Fill( WMuon_MT[sel_mu], EventWeight);
                             h_dR_LepJet[4]->Fill( dr_LepJet, EventWeight);
                             h_NJet[4]->Fill(NJet, EventWeight);
                             h_NBJet[4]->Fill(NBJet, EventWeight);
                             h_MET[4]->Fill(MET, EventWeight);
                             h_LepJetMass[4]->Fill( ((*muon1) + (jet)).M(), EventWeight);
                           } // step4
                  } //step3
          } //step2
   }//step1
   if( debug ) cout << "ending event..." << endl; 
   } // semileptonic
   return kTRUE;
}

void MyAnalysis_others::SlaveTerminate() {
}
void MyAnalysis_others::Terminate() {
   // The Terminate() function is the last function to be called during
}
