#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>
#include <string>

void Ntuple2hist2(char* name, char *expression,char *cutName, char *selection, char *weight, int  nbin, double min , double max, char* xtitle, char* ytitle);
void Ntuple2hist()
{
  //Ntuple2hist2("lepton_pt","lepton_pt","S2","((lepton_pt > 30) &&(nJet30>3))","(puweight*genweight)",20,0,200,"lepton pt","Events");
  //Ntuple2hist2("lepton_pt","lepton_pt","S1","((lepton_pt > 30) &&(channel==0))","(PUWeight)",20,0,200,"lepton pt","Events");
  //Ntuple2hist2("lepton_relIso","lepton_relIso","S1","((lepton_pt > 30) &&(channel==0))","(PUWeight)",10,0,0.2,"lepton relIso","Events");
  //Ntuple2hist2("lepton_pt","lepton_pt","S1","((lepton_pt > 30) &&(channel==0))","(1)",20,0,200,"lepton pt","Events");
  Ntuple2hist2("lepton_eta","lepton_eta","S1","((lepton_pt > 30) && (channel==0) ) ","(1)",10,-3,3,"lepton eta","Events");
  //Ntuple2hist2("lepton_pt","lepton_pt","S2","((lepton_pt > 30) && (channel==0) && (nJet30 >=4) ) ","(1)",20,0,200,"lepton pt","Events");
  //Ntuple2hist2("lepton_pt","lepton_pt","S1","((lepton_pt > 30))","(1)",20,0,200,"lepton pt","Events");

}
void Ntuple2hist2(char* name, char *expression,char *cutName, char *selection, char *weight, int  nbin, double min , double max, char* xtitle, char* ytitle)
{
  const int N=10;

  TFile *f[N];
  TTree *tree[N];
  TH1F *h1[N];
  char *path = "/xrootd/store/user/dygyun/Cattools/v744";
  std::string aaa[N] = {"SingleMuon_Run2015", "DYJets", "SingleTbar_tW", "SingleTbar_t", "SingleTop_t", "WJets", "WW", "WZ", "ZZ", "TT_powheg"};
  for(int i=0;i<N;i++) {
    f[i] = (TFile*) new TFile(Form("%s/vallot_%s_25ns.root",path,aaa[i].c_str()));
    tree[i] = (TTree*) f[i]->Get("ttbarSingleLepton/tree");
    h1[i] = new TH1F(Form("h1_%s_%s_%s",aaa[i].c_str(),cutName,name),"Lepton Eta",nbin,min,max);
    h1[i]->Sumw2();
    if(i==0) tree[i]->Project(Form("h1_%s_%s_%s",aaa[i].c_str(),cutName,name),expression,Form("(%s)*(1)",selection ) ); //  for DATA
    else     tree[i]->Project(Form("h1_%s_%s_%s",aaa[i].c_str(),cutName,name),expression,Form("(%s)*(%s)",selection, weight ) ); // for MC
  }

  TFile *fout = new TFile(Form("output_%s_%s.root",cutName, name),"RECREATE");
  for(int i=0;i<N;i++) {
     h1[i]->Write();
  }
  fout->Write();
}

