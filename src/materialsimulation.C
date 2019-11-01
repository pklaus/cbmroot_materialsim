void materialsimulation(int nEvents = 1000000){
  // for material budget simulation number of events = 1*10^6
  TStopwatch timer;
  timer.Start();
  gDebug=0;
  int verboseLevel = 0;

  //Simulation requires:
  // MVD model as root geometry
  // Pipe geometry pipe_standard_tobias.geo
  // in cbmroot/mvd/ - folder
  // CbmMvdRadLength.cxx and CbmMvdRadLength.h need to be present
  // in CbmMvd.cxx in sequence "CheckIfSensitive" the activation of active sensor parts should be set

  TString inDir   = gSystem->Getenv("VMCWORKDIR");

  TString outFile = "Sim_Box_1MEvents_mvd_15a_360phi.mc.root";
  TString parFile = "Sim_Box_1MEvents_mvd_15a_360phi.params.root";

  FairLogger* logg = FairLogger::GetLogger();
  logg->SetLogScreenLevel("INFO"); // INFO DEBUG

  // Create and add detectors / load setup
  gROOT->LoadMacro(inDir + "/geometry/setup/setup_mvd_only.C");
  gInterpreter->ProcessLine("setup_mvd_only()");
  CbmSetup* cbmsetup = CbmSetup::Instance();
  /*cbmsetup->RemoveModule(kSts);
  cbmsetup->RemoveModule(kRich);
  cbmsetup->RemoveModule(kTrd);
  cbmsetup->RemoveModule(kTof);
  cbmsetup->RemoveModule(kPsd);*/

  FairRunSim *fRun = new FairRunSim();

  // set the MC version used
  fRun->SetName("TGeant3");

  fRun->SetOutputFile(outFile);

  // Set Material file Name
  fRun->SetMaterials("media.geo");

  // -----   Create and register modules   ----------------------------------
  TString macroName = inDir + "/macro/run/modules/registerSetup.C";
  std::cout << "Loading macro " << macroName << std::endl;
  gROOT->LoadMacro(macroName);
  gROOT->ProcessLine("registerSetup()");
  // ------------------------------------------------------------------------


  // Create and Set Event Generator
  //-------------------------------

  FairPrimaryGenerator* primGen = new FairPrimaryGenerator();

  // use BoxGenerator to simulate neutrinos for material budget calculation
  FairBoxGenerator *fBox1 = new FairBoxGenerator(14, 1);
  fBox1->SetXYZ(0., 0.,0.);
  fBox1->SetPRange(10.0, 10.0);
  fBox1->SetThetaRange(0., 180.);
  //fBox1->SetPhiRange(0., 2.5);
  //fBox1->SetPhiRange(0., 360);
  fBox1->SetPhiRange(0, 360);
  //fBox1->SetPhiRange(0., 2.5);
  fBox1->SetCosTheta();
  primGen->AddGenerator(fBox1);

  fRun->SetGenerator(primGen);

  // to be switched on in case of neutrino simulations for material budget
  fRun->SetRadLenRegister(kTRUE);

  Int_t iVerbose=0;

  fRun->Init();

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
  //fRun->SetTrackingDebugMode(false);
  fRun->Run(nEvents);

  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  printf("RealTime=%f seconds, CpuTime=%f seconds\n",rtime,ctime);
}
