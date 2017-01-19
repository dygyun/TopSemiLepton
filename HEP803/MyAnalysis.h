#ifndef MyAnalysis_h
#define MyAnalysis_h
#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TSelector.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TH2D.h>
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
   Int_t IsMuonTrig;
   Int_t NBJet;
   Int_t NBJet_CSVT;
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
   Float_t Muon_Iso03[5]; //[NMuon]
   Int_t NLooseMuon;
   Float_t LooseMuon_Pt[5]; //[NLooseMuon]
   Float_t LooseMuon_Eta[5]; //[NLooseMuon]
   Float_t LooseMuon_Phi[5]; //[NLooseMuon]
   Float_t LooseMuon_E[5]; //[NLooseMuon]
   Int_t LooseMuon_Charge[5]; //[NLooseMuon]
   Float_t LooseMuon_Iso03[5]; //[NLooseMuon]
   Int_t NElectron;
   Float_t Electron_Pt[5]; //[NElectron]
   Float_t Electron_Eta[5]; //[NElectron]
   Float_t Electron_Phi[5]; //[NElectron]
   Float_t Electron_E[5]; //[NElectron]
   Int_t Electron_Charge[5]; //[NElectron]
   Float_t Electron_Iso03[5]; //[NElectron]
   Int_t NLooseElectron;
   Float_t LooseElectron_Pt[5]; //[NLooseElectron]
   Float_t LooseElectron_Eta[5]; //[NLooseElectron]
   Float_t LooseElectron_Phi[5]; //[NLooseElectron]
   Float_t LooseElectron_E[5]; //[NLooseElectron]
   Int_t LooseElectron_Charge[5]; //[NLooseElectron]
   Float_t LooseElectron_Iso03[5]; //[NLooseElectron]
 
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
   Float_t PUWeight;
   Float_t GenWeight;
   
   MyAnalysis(float sf = 1., float wf = 1, float Xsection = 1.0 , float lumi = 1.0, float num = 1.0,  TTree * /*tree*/= 0) :
   //MyAnalysis(float sf = 1., float wf = 1, float Xsection = 1.0 , float lumi = 1.0, TTree * /*tree*/= 0) :

   fChain(0) {
      weight_factor = wf;
     Lumi = lumi;
   Sigma = Xsection; 
   //   norm_scale = lumi/(num/Xsection);
      SF_b = sf;
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
   
   void BuildEvent();
  
   float EventWeight; 
   int TotalEvents;
   int nEvents; 
   float Lumi;
   float Sigma; 

   vector<MyJet> Jets;
   vector<MyMuon> Muons;
   vector<MyElectron> Electrons;
   vector<MyPhoton> Photons;
   
   TLorentzVector hadB, lepB, hadWq, hadWqb, lepWl, lepWn;
   TLorentzVector mymet;
   
   float weight_factor;
   float norm_scale;
   float SF_b;
  
   TH1D *h_Muon_Pt[5];
   TH1D *h_NMuon[5];
   TH1D *h_MuonIso[5];
   TH1D *h_NVertex[5];
   TH1D *h_WMuon_MT[5];
   TH1D *h_WMuon_Phi[5];
   TH1D *h_dR_LepJet[5];
   TH1D *h_NJet[5]; 
   TH1D *h_NBJet[5]; 
   TH1D *h_MET[5]; 
   TH2D *hIso_vs_MET[5];
   TH1D *h_LepJetMass[5]; 
 
   vector<TH1D*> histograms;
   vector<TH1D*> histograms_MC;
   vector<TH2D*> histograms_2D;  
   vector<TH2D*> histograms_MC_2D;  
   
};

#endif

#ifdef MyAnalysis_cxx
void MyAnalysis::Init(TTree *tree)
{
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);
   
   fChain->SetBranchAddress("IsMuonTrig", &IsMuonTrig);
   fChain->SetBranchAddress("NBJet", &NBJet);
   fChain->SetBranchAddress("NBJet_CSVT", &NBJet_CSVT);
   fChain->SetBranchAddress("NJet", &NJet);
   fChain->SetBranchAddress("Jet_Pt", Jet_Pt);
   fChain->SetBranchAddress("Jet_Eta", Jet_Eta);
   fChain->SetBranchAddress("Jet_Phi", Jet_Phi);
   fChain->SetBranchAddress("Jet_E", Jet_E);
   fChain->SetBranchAddress("Jet_bDiscriminator", Jet_bDiscriminator);

   fChain->SetBranchAddress("NMuon", &NMuon);
   fChain->SetBranchAddress("Muon_Pt", Muon_Pt);
   fChain->SetBranchAddress("Muon_Eta", Muon_Eta);
   fChain->SetBranchAddress("Muon_Phi", Muon_Phi);
   fChain->SetBranchAddress("Muon_E", Muon_E);
   fChain->SetBranchAddress("Muon_Charge", Muon_Charge);
   fChain->SetBranchAddress("Muon_Iso03", Muon_Iso03);

   fChain->SetBranchAddress("NLooseMuon", &NLooseMuon);
   fChain->SetBranchAddress("LooseMuon_Pt", LooseMuon_Pt);
   fChain->SetBranchAddress("LooseMuon_Eta", LooseMuon_Eta);
   fChain->SetBranchAddress("LooseMuon_Phi", LooseMuon_Phi);
   fChain->SetBranchAddress("LooseMuon_E", LooseMuon_E);
   fChain->SetBranchAddress("LooseMuon_Charge", LooseMuon_Charge);
   fChain->SetBranchAddress("LooseMuon_Iso03", LooseMuon_Iso03);

   fChain->SetBranchAddress("NElectron", &NElectron);
   fChain->SetBranchAddress("Electron_Pt", Electron_Pt);
   fChain->SetBranchAddress("Electron_Eta", Electron_Eta);
   fChain->SetBranchAddress("Electron_Phi", Electron_Phi);
   fChain->SetBranchAddress("Electron_E", Electron_E);
   fChain->SetBranchAddress("Electron_Charge", Electron_Charge);
   fChain->SetBranchAddress("Electron_Iso03", Electron_Iso03);
   fChain->SetBranchAddress("NLooseElectron", &NLooseElectron);
   fChain->SetBranchAddress("LooseElectron_Pt", LooseElectron_Pt);
   fChain->SetBranchAddress("LooseElectron_Eta", LooseElectron_Eta);
   fChain->SetBranchAddress("LooseElectron_Phi", LooseElectron_Phi);
   fChain->SetBranchAddress("LooseElectron_E", LooseElectron_E);
   fChain->SetBranchAddress("LooseElectron_Charge", LooseElectron_Charge);
   fChain->SetBranchAddress("LooseElectron_Iso03", LooseElectron_Iso03);

   fChain->SetBranchAddress("MET", &MET);
   fChain->SetBranchAddress("MET_Px", &MET_Px);
   fChain->SetBranchAddress("MET_Py", &MET_Py);

   fChain->SetBranchAddress("WMuon_MT", &WMuon_MT);
   fChain->SetBranchAddress("WMuon_Phi", &WMuon_Phi);
   fChain->SetBranchAddress("WElectron_MT", &WElectron_MT);
   fChain->SetBranchAddress("WElectron_Phi", &WElectron_Phi);

   fChain->SetBranchAddress("NVertex", &NVertex);
   fChain->SetBranchAddress("PUWeight", &PUWeight);
   fChain->SetBranchAddress("GenWeight", &GenWeight);
   
TFile * f = ((TChain *) fChain)->GetFile();
   //const char * name = ((TChain *) fChain)->GetFile()->GetName();
   //cout << "name = " << name << endl;
   TH1D * hevt = (TH1D*) f->Get("TopTree/EventSummary");
   nEvents = hevt->GetBinContent(2);

   TotalEvents = 0;
   EventWeight = 1.0;
}

Bool_t MyAnalysis::Notify()
{
   return kTRUE;
}
#endif // #ifdef MyAnalysis_cxx
