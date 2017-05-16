void qcd_MT(){

TString dir = "/Users/dygyun/Top/HEP_v764";

TFile * data      = TFile::Open(dir+"/hist_data.root");
TFile * ttbar     = TFile::Open(dir+"/hist_TT_SemiLeptonic.root");
TFile * WJets     = TFile::Open(dir+"/hist_WJets.root");
TFile * DYJets    = TFile::Open(dir+"/hist_DY.root");
TFile * SingleT   = TFile::Open(dir+"/hist_SingleTop.root");
TFile * VV        = TFile::Open(dir+"/hist_VV.root");
TFile * TT_others = TFile::Open(dir+"/hist_TT_others.root");
//////////////////////////////////
TH1F * h_data_S1    = (TH1F*) data    -> Get("h_WMuon_MT_S1");
TH1F * h_ttbar_S1   = (TH1F*) ttbar   -> Get("h_WMuon_MT_S1");
TH1F * h_WJets_S1   = (TH1F*) WJets   -> Get("h_WMuon_MT_S1");
TH1F * h_DYJets_S1   = (TH1F*) DYJets  -> Get("h_WMuon_MT_S1");
TH1F * h_SingleT_S1 = (TH1F*) SingleT -> Get("h_WMuon_MT_S1");
TH1F * h_VV_S1      = (TH1F*) VV      ->  Get("h_WMuon_MT_S1");
TH1F * h_others_S1  = (TH1F*) TT_others->  Get("h_WMuon_MT_S1");

TH1F * h_data_S2    = (TH1F*) data    -> Get("h_WMuon_MT_S2");
TH1F * h_ttbar_S2   = (TH1F*) ttbar   -> Get("h_WMuon_MT_S2");
TH1F * h_WJets_S2   = (TH1F*) WJets   -> Get("h_WMuon_MT_S2");
TH1F * h_DYJets_S2   = (TH1F*) DYJets  -> Get("h_WMuon_MT_S2");
TH1F * h_SingleT_S2 = (TH1F*) SingleT -> Get("h_WMuon_MT_S2");
TH1F * h_VV_S2      = (TH1F*) VV      ->  Get("h_WMuon_MT_S2");
TH1F * h_others_S2  = (TH1F*) TT_others->  Get("h_WMuon_MT_S2");

TH1F * h_data_S3    = (TH1F*) data    -> Get("h_WMuon_MT_S3");
TH1F * h_ttbar_S3   = (TH1F*) ttbar   -> Get("h_WMuon_MT_S3");
TH1F * h_WJets_S3   = (TH1F*) WJets   -> Get("h_WMuon_MT_S3");
TH1F * h_DYJets_S3   = (TH1F*) DYJets  -> Get("h_WMuon_MT_S3");
TH1F * h_SingleT_S3 = (TH1F*) SingleT -> Get("h_WMuon_MT_S3");
TH1F * h_VV_S3      = (TH1F*) VV      ->  Get("h_WMuon_MT_S3");
TH1F * h_others_S3  = (TH1F*) TT_others->  Get("h_WMuon_MT_S3");

TH1F * h_data_S4    = (TH1F*) data    -> Get("h_WMuon_MT_S4");
TH1F * h_ttbar_S4   = (TH1F*) ttbar   -> Get("h_WMuon_MT_S4");
TH1F * h_WJets_S4   = (TH1F*) WJets   -> Get("h_WMuon_MT_S4");
TH1F * h_DYJets_S4   = (TH1F*) DYJets  -> Get("h_WMuon_MT_S4");
TH1F * h_SingleT_S4 = (TH1F*) SingleT -> Get("h_WMuon_MT_S4");
TH1F * h_VV_S4      = (TH1F*) VV      ->  Get("h_WMuon_MT_S4");
TH1F * h_others_S4  = (TH1F*) TT_others->  Get("h_WMuon_MT_S4");
/////////
TFile * output = new TFile("./hist_qcd_WMuon_MT.root","recreate");

TCanvas * c1 = new TCanvas();
c1->cd();
h_data_S1->Add(h_ttbar_S1,-1);
h_data_S1->Add(h_WJets_S1,-1);
h_data_S1->Add(h_DYJets_S1,-1);
h_data_S1->Add(h_SingleT_S1,-1);
h_data_S1->Add(h_VV_S1,-1);
h_data_S1->Add(h_others_S1,-1);

h_data_S1->Write();
h_data_S1->SetName("QCD_WMuon_MT_S1");
////// step 2
h_data_S2->Add(h_ttbar_S2,-1);
h_data_S2->Add(h_WJets_S2,-1);
h_data_S2->Add(h_DYJets_S2,-1);
h_data_S2->Add(h_SingleT_S2,-1);
h_data_S2->Add(h_VV_S2,-1);
h_data_S2->Add(h_others_S2,-1);

h_data_S2->Write();
h_data_S2->SetName("QCD_WMuon_MT_S2");
////// step 3
h_data_S3->Add(h_ttbar_S3,-1);
h_data_S3->Add(h_WJets_S3,-1);
h_data_S3->Add(h_DYJets_S3,-1);
h_data_S3->Add(h_SingleT_S3,-1);
h_data_S3->Add(h_VV_S3,-1);
h_data_S3->Add(h_others_S3,-1);

h_data_S3->Write();
h_data_S3->SetName("QCD_WMuon_MT_S3");
/// step 4
h_data_S4->Add(h_ttbar_S4,-1);
h_data_S4->Add(h_WJets_S4,-1);
h_data_S4->Add(h_DYJets_S4,-1);
h_data_S4->Add(h_SingleT_S4,-1);
h_data_S4->Add(h_VV_S4,-1);
h_data_S4->Add(h_others_S4,-1);

h_data_S4->Write();
h_data_S4->SetName("QCD_WMuon_MT_S4");

output->Close();
}
