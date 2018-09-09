#ifndef TreeAll_H
#define TreeAll_H

#include <TROOT.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <string>
#include <iostream>

using namespace std;

class TreeAll{
public: 

  TreeAll(){
  }
  virtual ~TreeAll(){;}

  // Declaration of leaf types
  Double_t kineticEnergy;
  Double_t initPosX;
  Double_t initPosY;
  Double_t initPosZ;
  Double_t initMovX;
  Double_t initMovY;
  Double_t initMovZ;

  Double_t targetPosX;
  Double_t targetPosY;
  Double_t targetPosZ;
  Double_t targetMovX;
  Double_t targetMovY;
  Double_t targetMovZ;

  Double_t noTSensorPosX;
  Double_t noTSensorPosY;
  Double_t noTSensorPosZ;
  Double_t SensorPosX;
  Double_t SensorPosY;
  Double_t SensorPosZ;

  Double_t noTSensorPosXY;
  Double_t SensorPosXY;

};

#endif
