/**
 ** minimal setup for MVD tests
 **/


void setup_mvd_only()
{

  // -----  Geometry Tags  --------------------------------------------------
  TString magnetGeoTag    = "v15a";
  TString mvdGeoTag       = "v17y";
  // ------------------------------------------------------------------------


  // -----  Magnetic field  -------------------------------------------------
  TString fieldTag      = "v12b";
  Double_t fieldZ       = 40.;            // field centre z position
  Double_t fieldScale   =  1.;            // field scaling factor
  // ------------------------------------------------------------------------


  // -----  Create setup  ---------------------------------------------------
  CbmSetup* setup = CbmSetup::Instance();
  if ( ! setup->IsEmpty() ) {
  	std::cout << "-W- setup_mvd_test: overwriting existing setup"
  			      << setup->GetTitle() << std::endl;
  	setup->Clear();
  }
  setup->SetTitle("MVD - Only Setup");
  setup->SetModule(kMagnet, magnetGeoTag);
 
  setup->SetModule(kMvd, mvdGeoTag);

  setup->SetField(fieldTag, fieldScale, 0., 0., fieldZ);
  // ------------------------------------------------------------------------


  // -----   Screen output   ------------------------------------------------
  setup->Print();
  // ------------------------------------------------------------------------

}
