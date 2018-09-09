#include "ScatterAlpha.h"
#include "TMath.h"

void ScatterAlpha::oneScatter(vector<Double_t>& PVector){

  /*Atom Scattering*/
  // get value of b
  Double_t x = getR->Uniform(-144.0, 144.0);
  Double_t y = getR->Uniform(-144.0, 144.0);
  Double_t d = TMath::Sqrt(x*x+y*y);
  Double_t constantValue = 48.26;//constant value of F(theta,d)
  Double_t theta = 2.0*TMath::ATan(1.0/(constantValue*d));
  Double_t phi = 0.0;
  if(x>0 && y>0) phi = TMath::ATan(y/x);
  else if(x>0 && y<0) phi = TMath::ATan(y/x);
  else if(x<0 && y>0) phi = TMath::ATan(y/x)-TMath::Pi()/2;
  else phi = TMath::ATan(y/x)+TMath::Pi()/2;

  Double_t theta_y = TMath::ASin(PVector[0]/PVector[3]);
  Double_t theta_x = TMath::ASin(PVector[1]/TMath::Sqrt(PVector[1]*PVector[1]+PVector[2]*PVector[2]));
  Double_t ppz = PVector[3]*TMath::Cos(theta);
  Double_t ppx = PVector[3]*TMath::Sin(theta)*TMath::Cos(phi);
  Double_t ppy = PVector[3]*TMath::Sin(theta)*TMath::Sin(phi);

  // get P vector by Rotation Matrix
  Double_t realPx = ppx*TMath::Cos(theta_y)+ppz*TMath::Sin(theta_y);
  Double_t realPy = ppy*TMath::Cos(theta_x)-ppx*TMath::Sin(theta_y)*TMath::Sin(theta_x)
                +ppz*TMath::Cos(theta_y)*TMath::Sin(theta_x);
  Double_t realPz = ppz*TMath::Cos(theta_y)*TMath::Cos(theta_x)-ppy*TMath::Sin(theta_x)
                -ppx*TMath::Sin(theta_y)*TMath::Cos(theta_x);

  PVector[0] = realPx;
  PVector[1] = realPy;
  PVector[2] = realPz;

}

void ScatterAlpha::setVector(Double_t initPx, Double_t initPy, Double_t initPz, Double_t E,
                Double_t targetPosX, Double_t targetPosY){
  TLorentzVector *initVector = new TLorentzVector();
  initVector->SetPxPyPzE(initPx,initPy,initPz,E);
  noTSensorPosX = targetPosX + distance*initVector->Px()/initVector->Pz();
  noTSensorPosY = targetPosY + distance*initVector->Py()/initVector->Pz();
  noTSensorPosXY = TMath::Sqrt(noTSensorPosX*noTSensorPosX+noTSensorPosY*noTSensorPosY);

  /*have scatterings in Au with 1um thickness*/
  vector<Double_t> realPVector;
  realPVector.push_back(initVector->Px());
  realPVector.push_back(initVector->Py());
  realPVector.push_back(initVector->Pz());
  realPVector.push_back(initVector->P());
  for(int i=0;i<3472;i++)
    oneScatter(realPVector);

  targetVector->SetPxPyPzE(realPVector[0],realPVector[1],realPVector[2],E);
  SensorPosX = targetPosX + distance*targetVector->Px()/targetVector->Pz();
  SensorPosY = targetPosY + distance*targetVector->Py()/targetVector->Pz();
  SensorPosXY = TMath::Sqrt(SensorPosX*SensorPosX+SensorPosY*SensorPosY);
}
