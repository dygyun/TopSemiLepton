#include "TH1F.h"
#include "TFile.h"
#include "TCanvas.h"
#include "THStack.h"
#include <stdio.h>
#include <iostream>
void stackplot(const int cutStep, const char* histName, const char* histXtitle)
{
   gStyle->SetOptStat(0);
   static const int xy = 10;
   TFile *f[xy];
 f[0]   = new TFile("hist_data.root");
 f[1]   = new TFile("hist_TT_SemiLeptonic.root");
 f[2]   = new TFile("hist_WJets.root");
 f[3]   = new TFile("hist_DY.root");
 f[6]   = new TFile("hist_QCD.root");
 f[7]   = new TFile("hist_SingleTop.root");
 f[8]   = new TFile("hist_TT_others.root");
 f[9]   = new TFile("hist_VV.root");
   const fileName[xy-1] = { TT_SemiLeptonic, WJets, DY, QCD, SingleTop, TT_others, VV };
   const histName[xy-1] = { h_Muon_Pt};
   TH1F *h_Muon_Pt[xy];
   TH1F *hEvent[xy];
   /// Define histogram ////
   for (int i = 0; i < xy; ++i)
   {
      h_Muon_Pt[i]  = (TH1F*) f[i]->Get(Form("S%d/%s",cutStep, histName) )->h_Muon_Pt(Form("hist_%d",i) );
   }
 cout << "Test--------" <<endl;
   const Color_t colors[xy-1] = { kGreen+2, kGreen+1, kYellow, kAzure, kAzure, kMagenta, kMagenta+2 ,kRed+2, kRed+1 };

   for ( int i = 0; i < xy-1; ++i )
   {
      h_Muon_Pt[1]->SetLineColor(colors[i]);
      //h_Muon_Pt[1]->Scale(Luminosity);
   }
  // h_Muon_Pt[0]->Scale(hEvent[0]->GetBinContent(3)/h_Muon_Pt[0]->Integral());
   h_Muon_Pt[0]->SetMarkerStyle(20);
   h_Muon_Pt[0]->SetMarkerColor(kBlack);

   h_Muon_Pt[0]->GetXaxis()->SetTitle(histXtitle);
   h_Muon_Pt[0]->GetYaxis()->SetTitle("Entries");
///
   THStack *hs_lpt1 = new THStack("hs_lpt1","MuStack");
   for (int i = 0; i < xy-1; ++i)
   {
      hs_lpt1->Add(h_Muon_Pt[i+1]);
   }
/////////////////   
TCanvas *c1 = new TCanvas("c1","confirm"); c1->SetLogy();
   c1->cd();
   h_Muon_Pt[0]->Draw("E1p");
   hs_lpt1->Draw("same,hist");
   h_Muon_Pt[1]->Draw("same,E1p");
  // h_Muon_Pt[0]->Draw("same,E1p");

  c1->SaveAs(Form("hist_S%d_%s.eps",cutStep, histName));
   /////////////////////////////////////////////////////
}
