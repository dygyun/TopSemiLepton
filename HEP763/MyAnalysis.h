#ifndef MyAnalysis_h
#define MyAnalysis_h

#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TSelector.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <vector>

#include "MyJet.h"
#include "MyMuon.h"
#include "MyElectron.h"
#include "MyPhoton.h"
#include <iostream>

using namespace std;
// Header file for the classes stored in the TTree if any.
// Fixed size dimensions of array or collections stored in the TTree if any.
class MyAnalysis: public TSelector {
public:
   TTree *fChain; //!pointer to the analyzed TTree or TChain
   // Declaration of leaf types
   Int_t channel;
   Int_t NBJet;
   Int_t NJet;
   Float_t Jet_Pt[10]; //[NJet]
   Float_t Jet_Eta[10]; //[NJet]
   Float_t Jet_Phi[10]; //[NJet]
   Float_t Jet_E[10]; //[NJet]
   Float_t Jet_bDiscriminator[10]; //[NJet]
   Float_t Jet_ID[10]; //[NJet]
   Int_t NMuon;
   Float_t Muon_Pt[5]; //[NMuon]
   Float_t Muon_Eta[5]; //[NMuon]
   Float_t Muon_Phi[5]; //[NMuon]
   Float_t Muon_E[5]; //[NMuon]
   Int_t Muon_Charge[5]; //[NMuon]
   Float_t Muon_Iso[5]; //[NMuon]
   Int_t NLooseMuon;
   Float_t LooseMuon_Pt[5]; //[NLooseMuon]
   Float_t LooseMuon_Eta[5]; //[NLooseMuon]
   Float_t LooseMuon_Phi[5]; //[NLooseMuon]
   Float_t LooseMuon_E[5]; //[NLooseMuon]
   Int_t LooseMuon_Charge[5]; //[NLooseMuon]
   Float_t LooseMuon_Iso[5]; //[NLooseMuon]
   Int_t NElectron;
   Float_t Electron_Pt[5]; //[NElectron]
   Float_t Electron_Eta[5]; //[NElectron]
   Float_t Electron_Phi[5]; //[NElectron]
   Float_t Electron_E[5]; //[NElectron]
   Int_t Electron_Charge[5]; //[NElectron]
   Float_t Electron_Iso[5]; //[NElectron]
   Int_t NLooseElectron;
   Float_t LooseElectron_Pt[5]; //[NLooseElectron]
   Float_t LooseElectron_Eta[5]; //[NLooseElectron]
   Float_t LooseElectron_Phi[5]; //[NLooseElectron]
   Float_t LooseElectron_E[5]; //[NLooseElectron]
   Int_t LooseElectron_Charge[5]; //[NLooseElectron]
   Float_t LooseElectron_Iso[5]; //[NLooseElectron]
 
   Int_t NPhoton;
   Float_t Photon_Pt[5]; //[NPhoton]
   Float_t Photon_Eta[5]; //[NPhoton]
   Float_t Photon_Phi[5]; //[NPhoton]
   Float_t Photon_E[5]; //[NPhoton]
   Float_t Photon_Iso[5]; //[NPhoton]
   Double_t MET;
   Double_t MET_Px;
   Double_t MET_Py;

   Float_t WMuon_MT[5];
   Float_t WMuon_Phi[5];
   Float_t WElectron_MT[5];
   Float_t WElectron_Phi[5];

   Float_t MChadronicBottom_px;
   Float_t MChadronicBottom_py;
   Float_t MChadronicBottom_pz;
   Float_t MCleptonicBottom_px;
   Float_t MCleptonicBottom_py;
   Float_t MCleptonicBottom_pz;
   Float_t MChadronicWDecayQuark_px;
   Float_t MChadronicWDecayQuark_py;
   Float_t MChadronicWDecayQuark_pz;
   Float_t MChadronicWDecayQuarkBar_px;
   Float_t MChadronicWDecayQuarkBar_py;
   Float_t MChadronicWDecayQuarkBar_pz;
   Float_t MClepton_px;
   Float_t MClepton_py;
   Float_t MClepton_pz;
   Int_t MCleptonPDGid;
   Float_t MCneutrino_px;
   Float_t MCneutrino_py;
   Float_t MCneutrino_pz;
   Int_t NPrimaryVertices;
   //Bool_t triggerIsoMu24;
   Int_t NVertex;
   Int_t Dileptonic;
   Int_t Semileptonic;
   Float_t PUWeight;
   Float_t GenWeight;
   
   // List of branches
   TBranch *b_Dileptonic;
   TBranch *b_Semileptonic; //! 
   TBranch *b_NBJet; //!
   TBranch *b_NJet; //!
   TBranch *b_Jet_Pt; //!
   TBranch *b_Jet_Eta; //!
   TBranch *b_Jet_Phi; //!
   TBranch *b_Jet_E; //!
   TBranch *b_Jet_bDiscriminator; //!
   TBranch *b_Jet_ID; //!
   TBranch *b_NMuon; //!
   TBranch *b_Muon_Pt; //!
   TBranch *b_Muon_Eta; //!
   TBranch *b_Muon_Phi; //!
   TBranch *b_Muon_E; //!
   TBranch *b_Muon_Charge; //!
   TBranch *b_Muon_Iso; //!
   TBranch *b_NLooseMuon; //!
   TBranch *b_LooseMuon_Pt; //!
   TBranch *b_LooseMuon_Eta; //!
   TBranch *b_LooseMuon_Phi; //!
   TBranch *b_LooseMuon_E; //!
   TBranch *b_LooseMuon_Charge; //!
   TBranch *b_LooseMuon_Iso; //!

   TBranch *b_NElectron; //!
   TBranch *b_Electron_Pt; //!
   TBranch *b_Electron_Eta; //!
   TBranch *b_Electron_Phi; //!
   TBranch *b_Electron_E; //!
   TBranch *b_Electron_Charge; //!
   TBranch *b_Electron_Iso; //!
   TBranch *b_NLooseElectron; //!
   TBranch *b_LooseElectron_Pt; //!
   TBranch *b_LooseElectron_Eta; //!
   TBranch *b_LooseElectron_Phi; //!
   TBranch *b_LooseElectron_E; //!
   TBranch *b_LooseElectron_Charge; //!
   TBranch *b_LooseElectron_Iso; //!


   TBranch *b_NPhoton; //!
   TBranch *b_Photon_Pt; //!
   TBranch *b_Photon_Eta; //!
   TBranch *b_Photon_Phi; //!
   TBranch *b_Photon_E; //!
   TBranch *b_Photon_Iso; //!
   TBranch *b_MET; //!
   TBranch *b_MET_Px; //!
   TBranch *b_MET_Py; //!

   TBranch *b_WMuon_MT;
   TBranch *b_WMuon_Phi;
   TBranch *b_WElectron_MT;
   TBranch *b_WElectron_Phi;

   TBranch *b_MChadronicBottom_px; //!
   TBranch *b_MChadronicBottom_py; //!
   TBranch *b_MChadronicBottom_pz; //!
   TBranch *b_MCleptonicBottom_px; //!
   TBranch *b_MCleptonicBottom_py; //!
   TBranch *b_MCleptonicBottom_pz; //!
   TBranch *b_MChadronicWDecayQuark_px; //!
   TBranch *b_MChadronicWDecayQuark_py; //!
   TBranch *b_MChadronicWDecayQuark_pz; //!
   TBranch *b_MChadronicWDecayQuarkBar_px; //!
   TBranch *b_MChadronicWDecayQuarkBar_py; //!
   TBranch *b_MChadronicWDecayQuarkBar_pz; //!
   TBranch *b_MClepton_px; //!
   TBranch *b_MClepton_py; //!
   TBranch *b_MClepton_pz; //!
   TBranch *b_MCleptonPDGid; //!
   TBranch *b_MCneutrino_px; //!
   TBranch *b_MCneutrino_py; //!
   TBranch *b_MCneutrino_pz; //!
   TBranch *b_NPrimaryVertices; //!
   //TBranch *b_triggerIsoMu24; //!
   TBranch *b_NVertex; //!
   TBranch *b_PUWeight; //!
   TBranch *b_GenWeight; //!
  
void setChannel(int channel_) { channel=channel_;}
 
 MyAnalysis(float sf = 1., float wf = 1, float Xsection = 1.0 , float lumi = 1.0, float num = 1.0, TTree * /*tree*/= 0) :
 // MyAnalysis(float sf = 1., float wf = 1, float Xsection = 1.0 , float lumi = 1.0, float num = 1.0, TTree * =0, int channel_) :
   fChain(0) {
      weight_factor = wf;
      norm_scale = lumi/(num/Xsection);
      SF_b = sf;
     // channel = channel_; 
   }

   virtual ~MyAnalysis() {
   }
   virtual Int_t Version() const {
      return 2;
   }
   virtual void Begin(TTree *tree);
   virtual void SlaveBegin(TTree *tree);
   virtual void Init(TTree *tree);
   virtual Bool_t Notify();
  // virtual Bool_t Process(Long64_t entry, int channel);
  virtual Bool_t Process(Long64_t entry);
   virtual Int_t GetEntry(Long64_t entry, Int_t getall = 0) {
      return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0;
   }
   virtual void SetOption(const char *option) {
      fOption = option;
   }
   virtual void SetObject(TObject *obj) {
      fObject = obj;
   }
   virtual void SetInputList(TList *input) {
      fInput = input;
   }
   virtual TList *GetOutputList() const {
      return fOutput;
   }
   virtual void SlaveTerminate();
   virtual void Terminate();
   
  //void BuildEvent(int channel);
  void BuildEvent();
  
   float EventWeight; 
   int TotalEvents;
   vector<MyJet> Jets;
   vector<MyMuon> Muons;
   vector<MyElectron> Electrons;
   vector<MyPhoton> Photons;
   
   TLorentzVector hadB, lepB, hadWq, hadWqb, lepWl, lepWn;
   TLorentzVector mymet;
   
   float weight_factor;
   float norm_scale;
   float SF_b;
  // int channel;
 
   TH1F *h_Muon_Pt[5];
   TH1F *h_NMuon[5];
   TH1F *h_MuonIso[5];
   TH1F *h_NVertex[5];
   TH1F *h_WMuon_MT[5];
   TH1F *h_WMuon_Phi[5];
   TH1F *h_NJet[5]; 
   TH1F *h_NBJet[5]; 
   TH1F *h_MET[5]; 
/*
   TH1F *h_Mmumu[4];
   TH1F *h_NMuon[4];
   TH1F *h_MuonIso[4];
   TH1F *h_NVertex[4];
   TH1F *h_WMuon_MT[4];
   TH1F *h_WMuon_Phi[4];
   TH1F *h_NJet[4]; 
   TH1F *h_NBJet[4]; 
   TH1F *h_MET[4]; 
  */
   vector<TH1F*> histograms;
   vector<TH1F*> histograms_MC;
   
};

#endif

#ifdef MyAnalysis_cxx
void MyAnalysis::Init(TTree *tree)
{
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);
   
   fChain->SetBranchAddress("Dileptonic", &Dileptonic, &b_Dileptonic);
   fChain->SetBranchAddress("Semileptonic", &Semileptonic, &b_Semileptonic);
   fChain->SetBranchAddress("NBJet", &NBJet, &b_NBJet);
   fChain->SetBranchAddress("NJet", &NJet, &b_NJet);
   fChain->SetBranchAddress("Jet_Pt", Jet_Pt, &b_Jet_Pt);
   fChain->SetBranchAddress("Jet_Eta", Jet_Eta, &b_Jet_Eta);
   fChain->SetBranchAddress("Jet_Phi", Jet_Phi, &b_Jet_Phi);
   fChain->SetBranchAddress("Jet_E", Jet_E, &b_Jet_E);
   fChain->SetBranchAddress("Jet_bDiscriminator", Jet_bDiscriminator, &b_Jet_bDiscriminator);
   //fChain->SetBranchAddress("Jet_ID", Jet_ID, &b_Jet_ID);
   fChain->SetBranchAddress("NMuon", &NMuon, &b_NMuon);
   fChain->SetBranchAddress("Muon_Pt", Muon_Pt, &b_Muon_Pt);
   fChain->SetBranchAddress("Muon_Eta", Muon_Eta, &b_Muon_Eta);
   fChain->SetBranchAddress("Muon_Phi", Muon_Phi, &b_Muon_Phi);
   fChain->SetBranchAddress("Muon_E", Muon_E, &b_Muon_E);
   fChain->SetBranchAddress("Muon_Charge", Muon_Charge, &b_Muon_Charge);
   fChain->SetBranchAddress("Muon_Iso", Muon_Iso, &b_Muon_Iso);
   fChain->SetBranchAddress("NLooseMuon", &NLooseMuon, &b_NLooseMuon);
   fChain->SetBranchAddress("LooseMuon_Pt", LooseMuon_Pt, &b_LooseMuon_Pt);
   fChain->SetBranchAddress("LooseMuon_Eta", LooseMuon_Eta, &b_LooseMuon_Eta);
   fChain->SetBranchAddress("LooseMuon_Phi", LooseMuon_Phi, &b_LooseMuon_Phi);
   fChain->SetBranchAddress("LooseMuon_E", LooseMuon_E, &b_LooseMuon_E);
   fChain->SetBranchAddress("LooseMuon_Charge", LooseMuon_Charge, &b_LooseMuon_Charge);
   fChain->SetBranchAddress("LooseMuon_Iso", LooseMuon_Iso, &b_LooseMuon_Iso);

   fChain->SetBranchAddress("NElectron", &NElectron, &b_NElectron);
   fChain->SetBranchAddress("Electron_Pt", Electron_Pt, &b_Electron_Pt);
   fChain->SetBranchAddress("Electron_Eta", Electron_Eta, &b_Electron_Eta);
   fChain->SetBranchAddress("Electron_Phi", Electron_Phi, &b_Electron_Phi);
   fChain->SetBranchAddress("Electron_E", Electron_E, &b_Electron_E);
   fChain->SetBranchAddress("Electron_Charge", Electron_Charge, &b_Electron_Charge);
   fChain->SetBranchAddress("Electron_Iso", Electron_Iso, &b_Electron_Iso);
   fChain->SetBranchAddress("NLooseElectron", &NLooseElectron, &b_NLooseElectron);
   fChain->SetBranchAddress("LooseElectron_Pt", LooseElectron_Pt, &b_LooseElectron_Pt);
   fChain->SetBranchAddress("LooseElectron_Eta", LooseElectron_Eta, &b_LooseElectron_Eta);
   fChain->SetBranchAddress("LooseElectron_Phi", LooseElectron_Phi, &b_LooseElectron_Phi);
   fChain->SetBranchAddress("LooseElectron_E", LooseElectron_E, &b_LooseElectron_E);
   fChain->SetBranchAddress("LooseElectron_Charge", LooseElectron_Charge, &b_LooseElectron_Charge);
   fChain->SetBranchAddress("LooseElectron_Iso", LooseElectron_Iso, &b_LooseElectron_Iso);
   

   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("MET_Px", &MET_Px, &b_MET_Px);
   fChain->SetBranchAddress("MET_Py", &MET_Py, &b_MET_Py);

   fChain->SetBranchAddress("WMuon_MT", &WMuon_MT, &b_WMuon_MT);
   fChain->SetBranchAddress("WMuon_Phi", &WMuon_Phi, &b_WMuon_Phi);
   fChain->SetBranchAddress("WElectron_MT", &WElectron_MT, &b_WElectron_MT);
   fChain->SetBranchAddress("WElectron_Phi", &WElectron_Phi, &b_WElectron_Phi);

   fChain->SetBranchAddress("NVertex", &NVertex, &b_NVertex);
   fChain->SetBranchAddress("PUWeight", &PUWeight, &b_PUWeight);
   fChain->SetBranchAddress("GenWeight", &GenWeight, &b_GenWeight);
   
   TotalEvents = 0;
   EventWeight = 1.0; } 
Bool_t MyAnalysis::Notify()
{
   return kTRUE;
}

#endif // #ifdef MyAnalysis_cxx
