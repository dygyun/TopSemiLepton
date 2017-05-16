#include <TStyle.h>
#include <TTree.h>
void box_step3()
{
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetOptStat(0);

   static const int xy = 7;
  TFile* openFile[xy];
  TString inFileName[xy] = {
  "hist_Mujet_ABCD.root",
  "hist_TT_SemiLeptonic.root",
  "hist_WJets.root",
  "hist_DY.root",
  "hist_SingleTop.root",
  "hist_VV.root",
  "hist_TT_others.root"
  };

  TH2D* hmetVsIso[7];

  for(int i=0;i<7;i++)
  {
    hmetVsIso[i] = new TH2D(Form("hIso_vs_MET3_%d", i),"MET vs PFIsolation in mu+jet", 10 ,0.0, 100, 100 ,0.,0.5);
     //hIso_vs_MET[i] = new TH2D(Form("hIso_vs_MET%i",i), "PF Isolation vs #slash{E}_{T}", 30 , 0, 150, 100, 0 , 0.5 );
  }

   const Color_t colors[xy-1] = { kRed, kOrange, kYellow, kGreen, kCyan ,kBlue };
  for(int i=0;i<xy;i++){

    openFile[i]= TFile::Open(inFileName[i]);
    hmetVsIso[i]  =(TH2D*)openFile[i]->Get("hIso_vs_MET3");
  }
 TCanvas *c1= new TCanvas();
 c1->cd();
  for (int i=0;i<xy-1;i++)
  { 
  //  hmetVsIso[i]->SetFillColor(3+i);
      hmetVsIso[i+1]->SetFillColor(colors[i]);
      hmetVsIso[i+1]->SetLineColor(colors[i]);
   hmetVsIso[0]->Draw("box");
 //if (i==1)  hmetVsIso[i]->Draw("box same");
 hmetVsIso[1]->Draw("box same");
 hmetVsIso[2]->Draw("box same");
} 
   leg = new TLegend(0.75,0.75,1.0,1.);
    {
        leg->AddEntry(hmetVsIso[0],"DATA","lp");
        leg->AddEntry(hmetVsIso[1],"TTbar","lp");
        leg->AddEntry(hmetVsIso[2],"WJets","lp ");
       // leg->AddEntry(hmetVsIso[3],"DY","f");
        //leg->AddEntry(hmetVsIso[4],"SingleTop","f");
        //leg->AddEntry(hmetVsIso[5],"VV","f");
        //leg->AddEntry(hmetVsIso[6],"tt others","f");
    }
    leg->Draw();

c1->SaveAs("box_mujet_step3.png");
} 
	
