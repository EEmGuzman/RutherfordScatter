#include "InitAlpha.h"
#include "TMath.h"

void InitAlpha::setVector(){
  Double_t R0 = 1.0;
  Double_t x0 = 1.0;
  Double_t y0 = 1.0;
  while(TMath::Sqrt(x0*x0+y0*y0) > 1.0){
    x0 = 2.0*(getR->Uniform(1.0)-0.5);
    y0 = 2.0*(getR->Uniform(1.0)-0.5);
  }
  InitPosX = x0*R0;
  InitPosY = y0*R0;

  Double_t vz = getR->Uniform(0.995,1.0);
  Double_t vrTheta = 2.0*TMath::Pi()*getR->Uniform(1.0);
  Double_t vx = TMath::Sqrt(1.0-vz*vz)*TMath::Sin(vrTheta);
  Double_t vy = TMath::Sqrt(1.0-vz*vz)*TMath::Cos(vrTheta);
  Double_t x1 = x0+distance*vx/vz;
  Double_t y1 = y0+distance*vy/vz;
  Double_t x2 = x0+(distance+1)*vx/vz;
  Double_t y2 = y0+(distance+1)*vy/vz;
  while(TMath::Sqrt(x1*x1+y1*y1) > 1.0 || TMath::Sqrt(x2*x2+y2*y2) > 1.0){//radius: 1.mm
    vz = getR->Uniform(0.995,1.0);
    vrTheta = 2.0*TMath::Pi()*getR->Uniform(1.0);
    vx = TMath::Sqrt(1.0-vz*vz)*TMath::Sin(vrTheta);
    vy = TMath::Sqrt(1.0-vz*vz)*TMath::Cos(vrTheta);
    x1 = x0+(distance-1)*vx/vz;
    y1 = y0+(distance-1)*vy/vz;
    x2 = x0+distance*vx/vz;
    y2 = y0+distance*vy/vz;
  }
  TargetPosX = x2;
  TargetPosY = y2;

  Double_t P = 202.341;
  Double_t E = 3732.88;
  initVector->SetPxPyPzE(P*vx,P*vy,P*vz,E);
}

