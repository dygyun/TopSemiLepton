#ifndef MYELECTRON_H_
#define MYELECTRON_H_

#include <TLorentzVector.h>

class MyElectron: public TLorentzVector {

   public:

      MyElectron();
      MyElectron(double pt, double eta, double phi, double e) {
         SetPtEtaPhiE(pt, eta, phi, e);
      }
      ;
      virtual ~MyElectron();

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
      const bool IsIsolated() {
         return (isolation < 1.);
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

#endif /* MYELECTRON_H_ */
