void materialsimulation(int nEvents = 1000000){
  // for material budget simulation number of events = 1*10^6
  TStopwatch timer;
  timer.Start();
  gDebug=0;
  int verboseLevel = 0;

  TString inDir   = gSystem->Getenv("VMCWORKDIR");

  TString outFile = "Sim_Box_1MEvents_mvd_v17a_tr_360phi.mc.root";
  TString parFile = "Sim_Box_1MEvents_mvd_v17a_tr_360phi.params.root";

  FairLogger* logg = FairLogger::GetLogger();
  logg->SetLogScreenLevel("INFO"); // INFO DEBUG

  // Create and add detectors / load setup

  // -----  Geometry Tags  --------------------------------------------------
  TString magnetGeoTag    = "v15a";
//  TString mvdGeoTag       = "v17y";
  TString mvdGeoTag       = "v17a_tr";
//  TString mvdGeoTag       = "v17a_vx";
  // ------------------------------------------------------------------------


  // -----  Magnetic field  -------------------------------------------------
  TString fieldTag      = "v12b";
  Double_t fieldZ       = 40.;            // field centre z position
  Double_t fieldScale   =  1.;            // field scaling factor
  // ------------------------------------------------------------------------


  // -----  Create setup  ---------------------------------------------------
  CbmSetup* cbmsetup = CbmSetup::Instance();
  if ( ! cbmsetup->IsEmpty() ) {
  	std::cout << "-W- setup_mvd_test: overwriting existing setup"
  			      << cbmsetup->GetTitle() << std::endl;
  	cbmsetup->Clear();
  }
  cbmsetup->SetTitle("MVD - Only Setup");
  cbmsetup->SetModule(kMagnet, magnetGeoTag);
 
  cbmsetup->SetModule(kMvd, mvdGeoTag);

  cbmsetup->SetField(fieldTag, fieldScale, 0., 0., fieldZ);
  // ------------------------------------------------------------------------


  // -----   Screen output   ------------------------------------------------
  cbmsetup->Print();
  // ------------------------------------------------------------------------

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
