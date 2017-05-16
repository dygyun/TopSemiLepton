#ifndef MYMUON_H_
#define MYMUON_H_

#include <TLorentzVector.h>

class MyMuon: public TLorentzVector {

   public:

      MyMuon();
      MyMuon(double pt, double eta, double phi, double e) {
         SetPtEtaPhiE(pt, eta, phi, e);
      }
      ;
      virtual ~MyMuon();

      void SetIsolation(double x) {
         isolation = x;
      }
      ;

      void SetCharge(int q) {
         charge = q;
      }
      ;

      const double GetIsolation() {
         return isolation;
      }
      ;

      const bool IsIsolated(double relcut = 0.05) {
         return ((isolation / Pt()) < relcut);
         //return (isolation < 1.);
      }
      ;
      const int GetCharge() {
         return charge;
      }
      ;

   private:

      double isolation;
      int charge;

};

#endif /* MYMUON_H_ */
