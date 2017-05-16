#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include <TROOT.h>
#include <TUnixSystem.h>
#include <TChain.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TString.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
using namespace std;
void met_AD_S2(){
gStyle->SetOptStat(0); // removong stat. box
   //TFile *MET_AAA = new TFile("./hist_qcd_met_AB.root");
   TFile *MET_AAA = new TFile("./hist_qcd_met_AB_S2.root");
   TFile *MET_DDD = new TFile("./hist_qcd_met_CD_S2.root");
   //TFile *MET_DDD = new TFile("./hist_qcd_met_CD.root");

  TH1D * h_MET_aaa = (TH1D*) MET_AAA -> Get("h_MET_S2");h_MET_aaa->Sumw2();
  TH1D * h_MET_ddd = (TH1D*) MET_DDD -> Get("h_MET_S2");h_MET_ddd->Sumw2();

   h_MET_aaa->Scale(1./h_MET_aaa->Integral());
   h_MET_ddd->Scale(1./h_MET_ddd->Integral());
 double KS =  h_MET_aaa->KolmogorovTest(h_MET_ddd);
   cout << "KS-Test : " << KS << endl;


TCanvas *c1 = new TCanvas();
   h_MET_aaa->SetLineColor(1);
   h_MET_aaa->SetMarkerColor(1);
   h_MET_aaa->SetMarkerStyle(20);
   h_MET_ddd->SetLineColor(2);
   h_MET_ddd->SetMarkerStyle(21);
   h_MET_ddd->SetMarkerColor(2);
   h_MET_aaa->SetTitle("(#slash{E}_{T}) in AB and CD ");
   h_MET_aaa->GetXaxis()->SetTitle("MET(GeV)");
   h_MET_aaa->GetYaxis()->SetTitle("Number of Entries");
   h_MET_aaa->Draw();
   h_MET_ddd->Draw("same");

  TLegend* leg1 = new TLegend(0.65, 0.65, 0.89, 0.85);
   leg1->AddEntry(h_MET_aaa,"#slash{E}_{T} in Region AB","pl");
   leg1->AddEntry(h_MET_ddd,"#slash{E}_{T} in Region CD","pl");
   leg1->SetLineColor(10);  leg1->SetFillColor(10);
   leg1->SetTextSize(0.03);
   leg1->Draw();

   c1->SaveAs("Met_qcdfromData_ABandCD.eps");

}

