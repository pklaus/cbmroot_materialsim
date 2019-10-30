// --------------------------------------------------------------------------
//
// Macro for material analysis
//
// verify transformation process of CADtoROOT
//
// check material budget values of individual MVD stations
//
// (Tobias Tischler 2011 - 2015)
// --------------------------------------------------------------------------



void materialanalysis(Int_t nEvents = 1000000) {

gROOT->Reset();
gROOT->SetStyle("Plain");
gStyle->SetPalette(1);
gStyle->SetOptStat(0);

  // ========================================================================
  //          Adjust this part according to your requirements

  // Verbosity level (0=quiet, 1=event level, 2=track level, 3=debug)
  Int_t iVerbose = 0;

  // Input file = Output file materialsimulation macro
  TString inFile = "Sim_Box_1MEvents_mvd_15a_360phi.mc.root";
  
  // Parameter file = Output file materialsimulation macro
  TString parFile ="Sim_Box_1MEvents_mvd_15a_360phi.params.root";
  
  // Output file = Material budget 
  TString outFile ="Sim_Box_1MEvents_mvd_15a_360phi.radlen.root";


  TList *parFileList = new TList();

  TString paramDir = gSystem->Getenv("VMCWORKDIR");
  paramDir += "/parameters";

 

  // In general, the following parts need not be touched
  // ========================================================================


  // ----    Debug option   -------------------------------------------------
  gDebug = 0;
  // ------------------------------------------------------------------------


  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  timer.Start();
  // ------------------------------------------------------------------------


  // -----   Reconstruction run   -------------------------------------------
  FairRunAna *run = new FairRunAna();
  run->SetInputFile(inFile);
  run->SetOutputFile(outFile);
  // ------------------------------------------------------------------------




  // =========================================================================
  // ===             Detector Response Simulation (Digitiser)              ===
  // ===                          (where available)                        ===
  // =========================================================================


 
 
   CbmMvdRadLength* radlen = new CbmMvdRadLength("Test", 0, iVerbose);

   cout << "Adding Task:  CbmMvdRadLength... " << endl;
   run->AddTask(radlen);
   cout << "Addtask done" << endl;

  // -----  Parameter database   --------------------------------------------
   //TString stsDigi = gSystem->Getenv("VMCWORKDIR");
   //stsDigi += "/parameters/sts/";
   //stsDigi += stsDigiFile;
    CbmFieldConst *fMagField1=new CbmFieldConst();
  fMagField1->SetField(0, 0 ,0 ); // values are in kG
  // MinX=-75, MinY=-40,MinZ=-12 ,MaxX=75, MaxY=40 ,MaxZ=124 );  // values are in cm
  fMagField1->SetFieldRegion(-74, -39 ,-22 , 74, 39 , 160 );

   FairRuntimeDb* rtdb = run->GetRuntimeDb();
   FairParRootFileIo* parIo1 = new FairParRootFileIo();
   CbmFieldPar* fieldPar = (CbmFieldPar*) rtdb->getContainer("CbmFieldPar");
   fieldPar->SetParameters(fMagField1);
   fieldPar->setChanged();
   fieldPar->setInputVersion(run->GetRunId(),1);

   parIo1->open(parFile.Data());

   rtdb->setFirstInput(parIo1);

   rtdb->saveOutput();


  cout << "ReadyForInit" << endl;
  // -----   Intialise and run   --------------------------------------------
  run->Init();
  cout << "Starting run" << endl;
  run->Run(0, nEvents);
  // ------------------------------------------------------------------------


  // -----   Finish   -------------------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  cout << endl << endl;
  cout << "Macro finished succesfully." << endl;
  cout << "Output file is " << outFile << endl;
  cout << "Parameter file is " << parFile << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << endl;
  cout << endl;
  // ------------------------------------------------------------------------

  cout << " Test passed" << endl;
	cout << " All ok " << endl;
}
