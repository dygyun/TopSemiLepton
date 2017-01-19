#ifndef MYJET_H_
#define MYJET_H_

#include <TLorentzVector.h>
#include <TRandom3.h>

class MyJet: public TLorentzVector {

   public:

      MyJet();
      MyJet(double pt, double eta, double phi, double e) {
         SetPtEtaPhiE(pt, eta, phi, e);
      }
      ;
      virtual ~MyJet();

      void SetBTagDiscriminator(double x) {
         btag = x;
      }
      ;

      const double GetBTagDiscriminator() {
         return btag;
      }
      ;

      const bool IsBTagged(double th=1.74) {
         return (btag > th);
      }
      ;
   
      void SetJetID(bool id) {
         jetid = id;
      }
      ;
      
      const bool GetJetID() {
         return jetid;
      }
      ;


   private:

      double btag;
      bool jetid;

};

#endif /* MYJET_H_ */
