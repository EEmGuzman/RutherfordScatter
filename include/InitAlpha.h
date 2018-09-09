#ifndef InitAlpha_H
#define InitAlpha_H

#include <TROOT.h>
#include <string>
#include <iostream>
#include "TreeAll.h"
#include <TRandom.h>
#include <TLorentzVector.h>

using namespace std;

class InitAlpha{
private:
  Double_t distance; // unit: mm
  Double_t InitPosX;
  Double_t InitPosY;
  Double_t InitPosZ;
  Double_t TargetPosX;
  Double_t TargetPosY;
  Double_t TargetPosZ;
  TLorentzVector *initVector;
  TRandom *getR;

public:
  InitAlpha(Double_t value, Int_t seed){
    distance = value;// unit: mm
    getR = new TRandom(seed);
    initVector = new TLorentzVector();
    InitPosZ = 0.0;
    TargetPosZ = distance;
  }
  virtual ~InitAlpha(){;}

  void setVector();
  
  Double_t getInitPosX(){return InitPosX;}
  Double_t getInitPosY(){return InitPosY;}
  Double_t getInitPosZ(){return InitPosZ;}
  Double_t getTargetPosX(){return TargetPosX;}
  Double_t getTargetPosY(){return TargetPosY;}
  Double_t getTargetPosZ(){return TargetPosZ;}

  Double_t getInitMovX(){return initVector->Px();}
  Double_t getInitMovY(){return initVector->Py();}
  Double_t getInitMovZ(){return initVector->Pz();}
  Double_t getInitE(){return initVector->E();}
};

#endif
