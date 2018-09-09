#include "main.h"
#include "TreeAll.h"
#include "InitAlpha.h"
#include "ScatterAlpha.h"

TreeAll myRutherfordData;
TTree* tree = new TTree("rutherfordData","A ROOT tree with Rutherford Data");

bool isExistFile(const char* FileName);

int main(int argc, char* argv[]){

  if(argc < 2){
    cout<<"Usage: main <output Dir>"<<endl;
    return 1;
  }
  string OutputDir = argv[1];
  if(!isExistFile(OutputDir.c_str())){
    cout<<"Create Output Directory: \""<<OutputDir<<"\""<<endl;
    string createDir = "mkdir "+OutputDir+"/";
    system(createDir.c_str());
  }

  string outputFile = OutputDir+"/"+"RutherfordData.root";
  TFile *fileOutput = new TFile(outputFile.c_str(),"recreate");
  if(!fileOutput->IsOpen()){
    cout<<"File: Cannot Open the Output Root File."<<endl;
    return 1;
  }
  else
    cout<<"File: Initialized the Output Root File \""<<outputFile<<"\""<<endl;

  /*Create a ROOT Tree*/
  tree->Branch("kineticEnergy",&myRutherfordData.kineticEnergy,"kineticEnergy/D");
  tree->Branch("initPosX",&myRutherfordData.initPosX,"initPosX/D");
  tree->Branch("initPosY",&myRutherfordData.initPosY,"initPosY/D");
  tree->Branch("initPosZ",&myRutherfordData.initPosZ,"initPosZ/D");
  tree->Branch("initMovX",&myRutherfordData.initMovX,"initMovX/D");
  tree->Branch("initMovY",&myRutherfordData.initMovY,"initMovY/D");
  tree->Branch("initMovZ",&myRutherfordData.initMovZ,"initMovZ/D");
  tree->Branch("targetPosX",&myRutherfordData.targetPosX,"targetPosX/D");
  tree->Branch("targetPosY",&myRutherfordData.targetPosY,"targetPosY/D");
  tree->Branch("targetPosZ",&myRutherfordData.targetPosZ,"targetPosZ/D");
  tree->Branch("targetMovX",&myRutherfordData.targetMovX,"targetMovX/D");
  tree->Branch("targetMovY",&myRutherfordData.targetMovY,"targetMovY/D");
  tree->Branch("targetMovZ",&myRutherfordData.targetMovZ,"targetMovZ/D");

  tree->Branch("noTSensorPosX",&myRutherfordData.noTSensorPosX,"noTSensorPosX/D");
  tree->Branch("noTSensorPosY",&myRutherfordData.noTSensorPosY,"noTSensorPosY/D");
  tree->Branch("noTSensorPosZ",&myRutherfordData.noTSensorPosZ,"noTSensorPosZ/D");
  tree->Branch("noTSensorPosXY",&myRutherfordData.noTSensorPosXY,"noTSensorPosXY/D");
  tree->Branch("SensorPosX",&myRutherfordData.SensorPosX,"SensorPosX/D");
  tree->Branch("SensorPosY",&myRutherfordData.SensorPosY,"SensorPosY/D");
  tree->Branch("SensorPosZ",&myRutherfordData.SensorPosZ,"SensorPosZ/D");
  tree->Branch("SensorPosXY",&myRutherfordData.SensorPosXY,"SensorPosXY/D");

  /*Fill the Tree*/
  for(int i=0;i<200000;i++){
    InitAlpha* getAlpha = new InitAlpha(50.0,0);
    getAlpha->setVector();
    myRutherfordData.kineticEnergy = 5.488;
    myRutherfordData.initPosX = getAlpha->getInitPosX();
    myRutherfordData.initPosY = getAlpha->getInitPosY();
    myRutherfordData.initPosZ = getAlpha->getInitPosZ();
    myRutherfordData.initMovX = getAlpha->getInitMovX();
    myRutherfordData.initMovY = getAlpha->getInitMovY();
    myRutherfordData.initMovZ = getAlpha->getInitMovZ();
    myRutherfordData.targetPosX = getAlpha->getTargetPosX();
    myRutherfordData.targetPosY = getAlpha->getTargetPosY();
    myRutherfordData.targetPosZ = getAlpha->getTargetPosZ();
    
    ScatterAlpha* getScatter = new ScatterAlpha(10.0,getAlpha->getTargetPosZ(),0);
    getScatter->setVector(getAlpha->getInitMovX(),getAlpha->getInitMovY(),getAlpha->getInitMovZ(),
	getAlpha->getInitE(),getAlpha->getTargetPosX(),getAlpha->getTargetPosY());
    myRutherfordData.targetMovX = getScatter->getTargetMovX();
    myRutherfordData.targetMovY = getScatter->getTargetMovY();
    myRutherfordData.targetMovZ = getScatter->getTargetMovZ();
    myRutherfordData.noTSensorPosX = getScatter->getNoTSensorPosX();
    myRutherfordData.noTSensorPosY = getScatter->getNoTSensorPosY();
    myRutherfordData.noTSensorPosZ = getScatter->getNoTSensorPosZ();
    myRutherfordData.noTSensorPosXY = getScatter->getNoTSensorPosXY();
    myRutherfordData.SensorPosX = getScatter->getSensorPosX();
    myRutherfordData.SensorPosY = getScatter->getSensorPosY();
    myRutherfordData.SensorPosZ = getScatter->getSensorPosZ();
    myRutherfordData.SensorPosXY = getScatter->getSensorPosXY();

    tree->Fill();
  }

  tree->Write();
  fileOutput->Close();
  cout<<"done!"<<endl;
  return 0;
}

bool isExistFile(const char* FileName){
   FILE *fp = fopen(FileName,"rb");
   if(fp == NULL)
     return false;
   fclose(fp);
   return true;
}
