#ifndef ScatterAlpha_H
#define ScatterAlpha_H

#include <TROOT.h>
#include <string>
#include <iostream>
#include "TreeAll.h"
#include <TRandom.h>
#include <TLorentzVector.h>
#include <vector>

using namespace std;

class ScatterAlpha{
private:
  Double_t distance; // unit: mm
  Double_t SensorPosX;
  Double_t SensorPosY;
  Double_t SensorPosZ;
  Double_t SensorPosXY;
  TLorentzVector *targetVector;
  TRandom *getR;

  Double_t noTSensorPosX;
  Double_t noTSensorPosY;
  Double_t noTSensorPosZ;
  Double_t noTSensorPosXY;

public:
  ScatterAlpha(Double_t value, Double_t targetPosZ,Int_t seed){
    distance = value;// unit: mm
    getR = new TRandom(seed);
    targetVector = new TLorentzVector();
    SensorPosZ = targetPosZ+distance;
    noTSensorPosZ = targetPosZ+distance;
  }
  virtual ~ScatterAlpha(){;}

  void oneScatter(vector<Double_t>& PVector);

  void setVector(Double_t initPx, Double_t initPy, Double_t initPz, Double_t E,
		Double_t targetPosX, Double_t targetPosY);

  Double_t getSensorPosX(){return SensorPosX;}
  Double_t getSensorPosY(){return SensorPosY;}
  Double_t getSensorPosZ(){return SensorPosZ;}
  Double_t getSensorPosXY(){return SensorPosXY;}

  Double_t getTargetMovX(){return targetVector->Px();}
  Double_t getTargetMovY(){return targetVector->Py();}
  Double_t getTargetMovZ(){return targetVector->Pz();}

  Double_t getNoTSensorPosX(){return noTSensorPosX;}
  Double_t getNoTSensorPosY(){return noTSensorPosY;}
  Double_t getNoTSensorPosZ(){return noTSensorPosZ;}
  Double_t getNoTSensorPosXY(){return noTSensorPosXY;}
};

#endif
