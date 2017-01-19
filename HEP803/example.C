#include "MyAnalysis.h"
#include "MyAnalysis_Sig.h"
#include "MyAnalysis_others.h"
#include "Plotter.h"
#include <iostream>
#include <TChain.h>
#include <TGraphAsymmErrors.h>
#include <string>

int main() {
   bool run = true;
 if (run) {
   float lumi = 10714.;
   //float lumi = 27640.;
   //float lumi = 29820.;
   TString dir = "/Users/dygyun/Top/v802/2016ntuple";
   TFile * fA = TFile::Open(dir+"/hep_TT_powheg.root");
   TFile * fB = TFile::Open(dir+"/hep_TT_powheg.root");
   TFile * fC = TFile::Open(dir+"/hep_WJets.root");
   TFile * fD = TFile::Open(dir+"/hep_DYJets.root");
   TFile * fE = TFile::Open(dir+"/hep_DYJets_10to50.root");
   TFile * fI = TFile::Open(dir+"/hep_SingleTop_t.root");
   TFile * fJ = TFile::Open(dir+"/hep_SingleTbar_t.root");
   TFile * fK = TFile::Open(dir+"/hep_SingleTop_tW.root");
   TFile * fL = TFile::Open(dir+"/hep_SingleTbar_tW.root");
   TFile * fN = TFile::Open(dir+"/hep_WW.root");
   TFile * fO = TFile::Open(dir+"/hep_WZ.root");
   TFile * fM = TFile::Open(dir+"/hep_ZZ.root");
   
   TH1D * hBsemi = (TH1D*) fA->Get("TopTree/EventSummary");
   TH1D * hB = (TH1D*) fB->Get("TopTree/EventSummary");
   TH1D * hC = (TH1D*) fC->Get("TopTree/EventSummary");
   TH1D * hD = (TH1D*) fD->Get("TopTree/EventSummary");
   TH1D * hE = (TH1D*) fE->Get("TopTree/EventSummary");
   TH1D * hI = (TH1D*) fI->Get("TopTree/EventSummary");
   TH1D * hJ = (TH1D*) fJ->Get("TopTree/EventSummary");
   TH1D * hK = (TH1D*) fK->Get("TopTree/EventSummary");
   TH1D * hL = (TH1D*) fL->Get("TopTree/EventSummary");
   TH1D * hN = (TH1D*) fN->Get("TopTree/EventSummary");
   TH1D * hO = (TH1D*) fO->Get("TopTree/EventSummary");
   TH1D * hM = (TH1D*) fM->Get("TopTree/EventSummary");
 
   int nevt = -1;
   MyAnalysis *A = new MyAnalysis();
   TChain* ch = new TChain("TopTree/events");
   ch->Add(Form("%s/hep_SingleMuon_Run2016FG.root",dir.Data()), nevt);
   ch->Process(A);

   MyAnalysis_others *B = new MyAnalysis_others(1,1,831.76,lumi,hB->GetBinContent(1));
   TChain* ch2 = new TChain("TopTree/events");
   ch2->Add(Form("%s/hep_TT_powheg.root",dir.Data()), nevt);
   ch2->Process(B);

   MyAnalysis_Sig *Bsemi = new MyAnalysis_Sig(1,1,831.76,lumi,hBsemi->GetBinContent(1));
   TChain* ch2semi = new TChain("TopTree/events");
   ch2semi->Add(Form("%s/hep_TT_powheg.root",dir.Data()), nevt);
ch2semi->Process(Bsemi);
  
   MyAnalysis *C = new MyAnalysis(1,1,61526.7,lumi,hC->GetBinContent(2));
   TChain* ch3 = new TChain("TopTree/events");
   ch3->Add(Form("%s/hep_WJets.root",dir.Data()),nevt);
   ch3->Process(C);
   
   MyAnalysis *D = new MyAnalysis(1,1,6025.2,lumi,hD->GetBinContent(1));
   TChain* ch4 = new TChain("TopTree/events");
   ch4->Add(Form("%s/hep_DYJets.root",dir.Data()),nevt);
   ch4->Process(D);

   MyAnalysis *E = new MyAnalysis(1,1,18610.0,lumi,hE->GetBinContent(1));
   TChain* ch5 = new TChain("TopTree/events");
   ch5->Add(Form("%s/hep_DYJets_10to50.root",dir.Data()),nevt);
   ch5->Process(E);
 
   MyAnalysis *I = new MyAnalysis(1,1,44.33,lumi,hI->GetBinContent(1));
   TChain* ch6 = new TChain("TopTree/events");
   ch6->Add(Form("%s/hep_SingleTop_t.root",dir.Data()),nevt);
   ch6->Process(I);

   MyAnalysis *J = new MyAnalysis(1,1,26.38,lumi,hJ->GetBinContent(1));
   TChain* ch7 = new TChain("TopTree/events");
   ch7->Add(Form("%s/hep_SingleTbar_t.root",dir.Data()),nevt);
   ch7->Process(J);

   MyAnalysis *K = new MyAnalysis(1,1,35.6,lumi,hK->GetBinContent(1));
   TChain* ch8 = new TChain("TopTree/events");
   ch8->Add(Form("%s/hep_SingleTop_tW.root",dir.Data()),nevt);
   ch8->Process(K);

   MyAnalysis *L = new MyAnalysis(1,1,35.6,lumi,hL->GetBinContent(1));
   TChain* ch9 = new TChain("TopTree/events");
   ch9->Add(Form("%s/hep_SingleTbar_tW.root",dir.Data()),nevt);
   ch9->Process(L);

   MyAnalysis *N = new MyAnalysis(1,1,118.7,lumi,hN->GetBinContent(1));
   TChain* ch10 = new TChain("TopTree/events");
   ch10->Add(Form("%s/hep_WW.root",dir.Data()),nevt);
   ch10->Process(N);

   MyAnalysis *O = new MyAnalysis(1,1,47.13,lumi,hO->GetBinContent(1));
   TChain* ch11 = new TChain("TopTree/events");
   ch11->Add(Form("%s/hep_WZ.root",dir.Data()),nevt);
   ch11->Process(O);
   
   MyAnalysis *M = new MyAnalysis(1,1,16.523,lumi,hM->GetBinContent(1));
   TChain* ch12 = new TChain("TopTree/events");
   ch12->Add(Form("%s/hep_ZZ.root",dir.Data()),nevt);
   ch12->Process(M);

   Plotter P;

   for(int i=0; i <6; i++)
 { // for DY
  D->histograms[i]->Add(E->histograms[i]); 
 //for single top
  I->histograms[i]->Add(J->histograms[i]); 
  I->histograms[i]->Add(K->histograms[i]); 
  I->histograms[i]->Add(L->histograms[i]); 
 // VV 
  N->histograms[i]->Add(O->histograms[i]); 
  N->histograms[i]->Add(M->histograms[i]); 
 }

   P.SetData(A->histograms, std::string("Data"));
   P.AddBg(C->histograms, std::string("W #rightarrow l#nu"));
   P.AddBg(D->histograms, std::string("Z/#gamma* #rightarrow ll"));
   P.AddBg(I->histograms, std::string("Single Top"));
   P.AddBg(N->histograms, std::string("VV"));
   P.AddBg(B->histograms, std::string("TTOthers"));
   P.AddBg(Bsemi->histograms, std::string("t#bar{t}"));
 
   P.Plot("results_th1d_FG.pdf");

   TFile * outA = TFile::Open("hist_data.root","RECREATE");
   for(int i=0; i < A->histograms.size(); i++){
     TH1D * tmp = (TH1D *) A->histograms[i];
     tmp->Write();
   }
   outA->Write();
   outA->Close();

   TFile * outB = TFile::Open("hist_TT_others.root","RECREATE");
   for(int i=0; i < B->histograms.size(); i++){
     TH1D * tmp = (TH1D *) B->histograms[i];
     tmp->Write();
   }
   outB->Write();
   outB->Close();

   TFile * outBsemi = TFile::Open("hist_TT_SemiLeptonic.root","RECREATE");
   for(int i=0; i < Bsemi->histograms.size(); i++){
     TH1D * tmp = (TH1D *) Bsemi->histograms[i];
     tmp->Write();
   }
   outBsemi->Write();
   outBsemi->Close();
/// 
 TFile * outC = TFile::Open("hist_WJets.root","RECREATE");
   for(int i=0; i < C->histograms.size(); i++){
     TH1D * tmp = (TH1D *) C->histograms[i];
     tmp->Write();
   }
   outC->Write();
   outC->Close();

   TFile * outD = TFile::Open("hist_DY.root","RECREATE");
   for(int i=0; i < D->histograms.size(); i++){
     TH1D * tmp = (TH1D *) D->histograms[i];
     tmp->Write();
    }
   outD->Write();
   outD->Close();
   
    TFile * outI = TFile::Open("hist_SingleTop.root","RECREATE");
    for(int i=0; i < I->histograms.size(); i++){
      TH1D * tmp = (TH1D *) I->histograms[i];
      tmp->Write();
    }
    outI->Write();
    outI->Close();

  TFile * outN = TFile::Open("hist_VV.root","RECREATE");
   for(int i=0; i < N->histograms.size(); i++){
     TH1D * tmp = (TH1D *) N->histograms[i];
     tmp->Write();
   }
   outN->Write();
   outN->Close();
  }
}
