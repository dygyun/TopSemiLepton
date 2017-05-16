#ifndef PLOTTER_H_
#define PLOTTER_H_

#include <vector>
#include <string>
#include <iostream>

#include <TH1D.h>
#include <TFile.h>
#include <TStyle.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TKey.h>
#include <TClass.h>

class Plotter {
public:
  Plotter();
  virtual ~Plotter();
  void SetData(std::vector<TH1D*> v, std::string n){
    data.push_back(v);
    data_names.push_back(n);
    N_histos = v.size();
  }
  void SetData(std::vector<TH2D*> v2, std::string n){
    data.push_back(v2);
    data_names.push_back(n);
    N_histos = v2.size();
  }
        void SetData(TString name, std::string n){
               TFile * f = new TFile(Form("%s",name.Data()));
               std::vector<TH1D*> v;
               std::vector<TH2D*> v2;
               TIter next(f->GetListOfKeys()); 
               TKey *key;
               while (key = (TKey*)next() ){
                 TClass *cl = gROOT->GetClass(key->GetClassName());
                 if ( cl->InheritsFrom("TH1D")) {
                   TH1D * h = (TH1D*) key->ReadObj(); 
                   v.push_back(h);
                 }
                 else if ( cl->InheritsFrom("TH2D")) {
                   TH2D * h = (TH2D*) key->ReadObj(); 
                   v2.push_back(h);
                 }
               }
               data.push_back(v);
               data_names.push_back(n);
               N_histos = v.size();
        }

  void ClearData(){
    data.clear();
    data_names.clear();
  }
  void AddBg(std::vector<TH1D*> v, std::string n){
    bg.push_back(v);
    bg_names.push_back(n);
    N_histos = v.size();
  }
  void AddBg(std::vector<TH2D*> v2, std::string n){
    bg.push_back(v2);
    bg_names.push_back(n);
    N_histos = v2.size();
  }
        void AddBg(TString name, std::string n){
                TFile * f = new TFile(Form("%s",name.Data()));
                std::vector<TH1D*> v;
                std::vector<TH2D*> v2;
                TIter next(f->GetListOfKeys());             
                TKey *key;
                while (key = (TKey*)next() ){
                  TClass *cl = gROOT->GetClass(key->GetClassName());
                  if ( cl->InheritsFrom("TH1D")) {
                    TH1D * h = (TH1D*) key->ReadObj();
                    v.push_back(h);
                  }
                  else if ( cl->InheritsFrom("TH2D")) {
                    TH2D * h = (TH2D*) key->ReadObj();
                    v2.push_back(h);
                  }
                }
                bg.push_back(v);
                bg_names.push_back(n);
                N_histos = v.size();
        }

  void ClearBg(){
    bg.clear();
    bg_names.clear();
  }
  void AddSig(std::vector<TH1D*> v, std::string n){
    signal.push_back(v);
    signal_names.push_back(n);
    N_histos = v.size();
  }
  void AddSig(std::vector<TH2D*> v2, std::string n){
    signal.push_back(v2);
    signal_names.push_back(n);
    N_histos = v2.size();
  }
        void AddSig(TString name, std::string n){
                TFile * f = new TFile(Form("%s",name.Data()));
                std::vector<TH1D*> v;
                std::vector<TH2D*> v2;
                TIter next(f->GetListOfKeys());             
                TKey *key;
                while (key = (TKey*)next() ){
                  TClass *cl = gROOT->GetClass(key->GetClassName());
                  if ( cl->InheritsFrom("TH1D")) {
                    TH1D * h = (TH1D*) key->ReadObj();
                    v.push_back(h);
                  }
                  if ( cl->InheritsFrom("TH2D")) {
                    TH2D * h = (TH2D*) key->ReadObj();
                    v2.push_back(h);
                  }
                }

                signal.push_back(v);
                signal_names.push_back(n);
                N_histos = v.size();
        }

  void ClearSig(){
    signal.clear();
    signal_names.clear();
  }
  void Plot(std::string filename = "result.pdf");

private:
  std::vector < std::vector<TH1D*> > data;
  std::vector < std::vector<TH1D*> > bg;
  std::vector < std::vector<TH1D*> > signal;
	std::vector < std::vector<TH1D*> > qcd;

  std::vector < std::vector<TH2D*> > data;
  std::vector < std::vector<TH2D*> > bg;
  std::vector < std::vector<TH2D*> > signal;
	std::vector < std::vector<TH2D*> > qcd;

  std::vector < std::string > data_names;
  std::vector < std::string > bg_names;
  std::vector < std::string > signal_names;
	std::vector < std::string > qcd_names;

  int N_histos;

};

#endif /* PLOTTER_H_ */
