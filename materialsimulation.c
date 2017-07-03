
void materialsimulation(){
  TStopwatch timer;
  timer.Start();
  gDebug=0;
  int verboseLevel = 0;

  //Simulation requires:
  // MVD model as root geometry
  // Pipe geometry pipe_standard_tobias.geo
  // in cbmroot/mvd/ - folder
  // 	CbmMvdRadLength.cxx and CbmMvdRadLength.h need to be present
  //	in CbmMvd.cxx in sequence "CheckIfSensitive" the activation of active sensor parts should be set

  
  
  
// for material budget simulation number of events = 1*10^6
  Int_t nEvents = 1000000;


// for UrQMD simulations to verify the transformation process: number of events = 50
//  Int_t nEvents = 50;


  TString inDir   = gSystem->Getenv("VMCWORKDIR");
  TString inFile  = inDir + "/input/urqmd.ftn14";
  TString inFile  = "/d/cbm03/urqmd/auau/25gev/centr/urqmd.auau.25gev.centr.0000.ftn14";
  TString outDir  = "data";

// Define output folder and file name


  TString outFile = "/u/tischler/frankfurtCAD/MVD_PhD/Sim_Box_1MEvents_mvd_15a_360phi.mc.root";
  TString parFile = "/u/tischler/frankfurtCAD/MVD_PhD/Sim_Box_1MEvents_mvd_15a_360phi.params.root";

//  TString outFile = "/u/tischler/frankfurtCAD/MVD_PhD/Urqmd_5Events_Sept15_mvd_15a.mc.root";
//  TString parFile = "/u/tischler/frankfurtCAD/MVD_PhD/Urqmd_5Events_Sept15_mvd_15a.params.root";

  //!!!! MVD_14_v2108 = correct acceptance for Station 2 !!!!!
  //!!!! mvd_v15b     = 4 stations, stations 1/1/2/3 at 8,12,16,20 cm downstream !!!!!
  //!!!! mvd_v18a     = MVD at mCBM, 2 stations, prototype and presto at 5 and 10 cm downstream !!!!!

  
  // ----  Load libraries   -------------------------------------------------
  gROOT->LoadMacro("$VMCWORKDIR/gconfig/basiclibs.C");
  basiclibs();
  gSystem->Load("libGeoBase");
  gSystem->Load("libParBase");
  gSystem->Load("libBase");
  gSystem->Load("libCbmBase");
  gSystem->Load("libCbmData");
  gSystem->Load("libField");
  gSystem->Load("libGen");
  gSystem->Load("libPassive");
  gSystem->Load("libMvd");

  FairRunSim *fRun = new FairRunSim();

  // set the MC version used
  // ------------------------
  fRun->SetName("TGeant3");

  fRun->SetOutputFile(outFile);

  // Set Material file Name
  //-----------------------
  fRun->SetMaterials("media.geo");

  // Create and add detectors
  //-------------------------
  FairModule *Cave= new CbmCave("CAVE");
  Cave->SetGeometryFileName("cave.geo");
  fRun->AddModule(Cave); 

  FairModule *Pipe= new CbmPipe("PIPE");
  Pipe->SetGeometryFileName("pipe/pipe_standard_tobias.geo");
  fRun->AddModule(Pipe);

  FairDetector *Mvd = new CbmMvd("MVD", kTRUE);//kTRUE);
//  Mvd->SetGeometryFileName("mvd/mvd_v15a.geo.root");
//  Mvd->SetGeometryFileName("mvd/mvd_v15b.geo.root");
//  Mvd->SetGeometryFileName("mvd/mvd_v18a.geo.root");
  Mvd->SetMotherVolume("pipevac1");
  Mvd->SetVerboseLevel(verboseLevel);
  fRun->AddModule(Mvd);

      
 // Create and Set Event Generator
 //-------------------------------

  FairPrimaryGenerator* primGen = new FairPrimaryGenerator();

// use UrQMD to check transformation process
//  FairUrqmdGenerator*  urqmdGen = new FairUrqmdGenerator(inFile);
//  primGen->AddGenerator(urqmdGen);

  

// use BoxGenerator to simulate neutrinos for material budget calculation
  FairBoxGenerator *fBox1 = new FairBoxGenerator(14, 1);
     fBox1->SetXYZ(0.,0.,0.);
     fBox1->SetPRange(10.0,10.0);
     fBox1->SetThetaRange(0.,180.);
//   fBox1->SetPhiRange(0.,2.5);
//   fBox1->SetPhiRange(0.,360);
     fBox1->SetPhiRange(0,360);
//   fBox1->SetPhiRange(0.,2.5);
     fBox1->SetCosTheta();
     primGen->AddGenerator(fBox1);

    fRun->SetGenerator(primGen);

// to be switched on in case of neutrino simulations for material budget
   fRun->SetRadLenRegister(kTRUE);

   Int_t iVerbose=0;

   fRun->Init();
   

  CbmFieldConst *fMagField1=new CbmFieldConst();
  fMagField1->SetField(0, 0 ,0 ); // values are in kG
  // MinX=-75, MinY=-40,MinZ=-12 ,MaxX=75, MaxY=40 ,MaxZ=124 );  // values are in cm
  fMagField1->SetFieldRegion(-74, -39 ,-22 , 74, 39 , 160 );
   

  // Fill the Parameter containers for this run
  //-------------------------------------------

  FairRuntimeDb *rtdb=fRun->GetRuntimeDb();
  Bool_t kParameterMerged=kTRUE;
  FairParRootFileIo* output=new FairParRootFileIo(kParameterMerged);
  output->open(parFile);
  rtdb->setOutput(output);
  rtdb->saveOutput();
  rtdb->print();

  // Transport nEvents
  // -----------------
  //  fRun->SetTrackingDebugMode(false);
  fRun->Run(nEvents);

  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  printf("RealTime=%f seconds, CpuTime=%f seconds\n",rtime,ctime);
}

