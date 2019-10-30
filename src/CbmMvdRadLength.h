// ------------------------------------------------------------------------------
// -----                    CbmMvdRadLength header file                     -----
// -----                    Created by T.Tischler (2011-2015)               -----
// ------------------------------------------------------------------------------


/** CbmMvdDigitizeL header file
 ** Read "ReadmeMvdDigitizer.pdf" for instructions
 **
 **/


#ifndef CBMMVDRADLENGTH_H
#define CBMMVDRADLENGTH_H 1

//#include "omp.h"
#include "FairTask.h"
#include "TStopwatch.h"
#include "TString.h"
#include "TMath.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TH2F.h"





class TClonesArray;
class TRandom3;
class CbmMvdGeoPar;
class CbmMvdPileupManager;
class CbmMvdStation;

using namespace std;


class CbmMvdRadLength : public FairTask
{
 
 public:

  /** Default constructor **/  
  CbmMvdRadLength();


  /** Standard constructor 
  *@param name  Task name
  *@param mode  0 = MAPS, 1 = Ideal
  **/
  CbmMvdRadLength(const char* name,
		    Int_t mode = 0, Int_t iVerbose = 1);


  /** Destructor **/
  virtual ~CbmMvdRadLength();


  /** Task execution **/
  virtual void Exec(Option_t* opt);


  /** Accessors **/
  TString  GetBranchName()    const { return fBranchName; };

  void SetBranchName(TString branchName) { fBranchName = branchName; };

  /** Intialisation **/
  virtual InitStatus Init();


  /** Reinitialisation **/
  virtual InitStatus ReInit();


  /** Virtual method Finish **/
  virtual void Finish();


  /** Register the output arrays to the IOManager **/
  //void Register();


  /** Clear the hit arrays **/
  void Reset();	 


  /** Print digitisation parameters **/
  void PrintParameters();


//protected:
public:

    // ----------   Protected data members  ------------------------------------

    
    //---- Histograms ----//

    //-- Counter --//
    TH1F* fOutputHisto1D_count;
    TH2F* fOutputHisto2D_count;
    
    //complete acceptane
    TH1F* Histo1D_Station[4][7];
    TH1F* Histo1D_Station_count[4][7];
    TH1F* Histo1D_Station_norm[4];
    TH1F* Histo1D_cvd_si_Station[4];
    TH1F* Histo1D_al_cvd_si_Station[4];

    //inside acceptance
    TH1F* Histo1D_Station_in[4][7];
    TH1F* Histo1D_Station_count_in[4][7];
    TH1F* Histo1D_Station_norm_in[4];
    TH1F* Histo1D_cvd_si_Station_in[4];
    TH1F* Histo1D_al_cvd_si_Station_in[4];


    //outside acceptance
    TH1F* Histo1D_Station_out[4][7];
    TH1F* Histo1D_Station_count_out[4][7];
    TH1F* Histo1D_Station_norm_out[4];
    TH1F* Histo1D_cvd_si_Station_out[4];
    TH1F* Histo1D_al_cvd_si_Station_out[4];

    TH1F* Histo1D_Station0_Si2;
    TH1F* Histo1D_Station0_Cu2;

    TH2F* Histo2D_Station[4][7];
    TH2F* Histo2D_Station_count[4][7];
    TH2F* Histo2D_Station_norm[4];

    //-- Complete MVD --//
    TH1F* fOutputHisto1D_Carbon;
    TH1F* fOutputHisto1D_Silicon;
    TH1F* fOutputHisto1D_Aluminium;
    TH1F* fOutputHisto1D_Copper;
    TH1F* fOutputHisto1D_all;

    TH2F* fOutputHisto2D_Carbon;
    TH2F* fOutputHisto2D_Carbon_count;
    TH2F* fOutputHisto2D_Carbon_norm;
    TH2F* fOutputHisto2D_Silicon;
    TH2F* fOutputHisto2D_Aluminium;
    TH2F* fOutputHisto2D_Copper;
    TH2F* fOutputHisto2D_1;
    TH2F* fOutputHisto2D_all;

    //-- Silicon per Station --//
    TH1F* fOutputHisto1D_Station0_Si;
    TH1F* fOutputHisto1D_Station1_Si;
    TH1F* fOutputHisto1D_Station2_Si;
    TH1F* fOutputHisto1D_Station3_Si;
	
    TH2F* fOutputHisto2D_Station0_Si;
    TH2F* fOutputHisto2D_Station1_Si;
    TH2F* fOutputHisto2D_Station2_Si;
    TH2F* fOutputHisto2D_Station3_Si;

    //Si normalisation
    TH2F* fOutputHisto2D_Station0_Si_count;

    TH2F* fOutputHisto2D_Station0_Si_norm;

   

    //-- Carbon per Station --//
    TH1F* fOutputHisto1D_Station0_C;
    TH1F* fOutputHisto1D_Station1_C;
    TH1F* fOutputHisto1D_Station2_C;
    TH1F* fOutputHisto1D_Station3_C;

    TH2F* fOutputHisto2D_Station0_C;
    TH2F* fOutputHisto2D_Station1_C;
    TH2F* fOutputHisto2D_Station2_C;
    TH2F* fOutputHisto2D_Station3_C;

//    TH2F* fOutputHisto2D_Station0_C_count;
    TH2F* fOutputHisto2D_Station0_C_norm;

    //-- CVD per Station --//
    TH1F* fOutputHisto1D_Station0_CVD;
    TH1F* fOutputHisto1D_Station1_CVD;
    TH1F* fOutputHisto1D_Station2_CVD;
    TH1F* fOutputHisto1D_Station3_CVD;

    TH1F* fOutputHisto1D_Station0_CVD_in_out;
    TH1F* fOutputHisto1D_Station1_CVD_in_out;
    TH1F* fOutputHisto1D_Station2_CVD_in_out;
    TH1F* fOutputHisto1D_Station3_CVD_in_out;

    TH2F* fOutputHisto2D_Station0_CVD;
    TH2F* fOutputHisto2D_Station1_CVD;
    TH2F* fOutputHisto2D_Station2_CVD;
    TH2F* fOutputHisto2D_Station3_CVD;

    //CVD normalisation
    TH2F* fOutputHisto2D_Station0_CVD_count;

    TH2F* fOutputHisto2D_Station0_CVD_norm;

    //-- Aluminium per Station--//
    TH1F* fOutputHisto1D_Station0_Al;
    TH1F* fOutputHisto1D_Station1_Al;
    TH1F* fOutputHisto1D_Station2_Al;
    TH1F* fOutputHisto1D_Station3_Al;

    TH2F* fOutputHisto2D_Station0_Al;
    TH2F* fOutputHisto2D_Station1_Al;
    TH2F* fOutputHisto2D_Station2_Al;
    TH2F* fOutputHisto2D_Station3_Al;

    //Al normalisation
    TH2F* fOutputHisto2D_Station0_Al_count;

    TH2F* fOutputHisto2D_Station0_Al_norm;

    //-- Copper per Station --//
    TH1F* fOutputHisto1D_Station0_Cu;
    TH1F* fOutputHisto1D_Station1_Cu;
    TH1F* fOutputHisto1D_Station2_Cu;
    TH1F* fOutputHisto1D_Station3_Cu;

    TH2F* fOutputHisto2D_Station0_Cu;
    TH2F* fOutputHisto2D_Station1_Cu;
    TH2F* fOutputHisto2D_Station2_Cu;
    TH2F* fOutputHisto2D_Station3_Cu;

    //Cu normalisation
    TH2F* fOutputHisto2D_Station0_Cu_count;

    TH2F* fOutputHisto2D_Station0_Cu_norm;

    //-- all materials per Station --//
    TH1F* fOutputHisto1D_allMat;
    TH1F* fOutputHisto1D_Station0_allMat;
    TH1F* fOutputHisto1D_Station1_allMat;
    TH1F* fOutputHisto1D_Station2_allMat;
    TH1F* fOutputHisto1D_Station3_allMat;

    TH2F* fOutputHisto2D_allMat;
    TH2F* fOutputHisto2D_Station0_allMat;
    TH2F* fOutputHisto2D_Station1_allMat;
    TH2F* fOutputHisto2D_Station2_allMat;
    TH2F* fOutputHisto2D_Station3_allMat;

    //-- Normalisation Silicon --//
//    TH1F* fOutputHisto1D_Silicon_count;
//    TH1F* fOutputHisto1D_Station0_Si_count;
//    TH1F* fOutputHisto1D_Station1_Si_count;
//    TH1F* fOutputHisto1D_Station2_Si_count;

    TH1F* fOutputHisto1D_Silicon_norm;
    TH1F* fOutputHisto1D_Station0_Si_norm;
    TH1F* fOutputHisto1D_Station1_Si_norm;
    TH1F* fOutputHisto1D_Station2_Si_norm;
    TH1F* fOutputHisto1D_Station3_Si_norm;
	
    //-- Normalisation Carbon --//
//    TH1F* fOutputHisto1D_Carbon_count;
//    TH1F* fOutputHisto1D_Station0_C_count;
//    TH1F* fOutputHisto1D_Station1_C_count;
//    TH1F* fOutputHisto1D_Station2_C_count;

    TH1F* fOutputHisto1D_Carbon_norm;
    TH1F* fOutputHisto1D_Station0_C_norm;
    TH1F* fOutputHisto1D_Station1_C_norm;
    TH1F* fOutputHisto1D_Station2_C_norm;
    TH1F* fOutputHisto1D_Station3_C_norm;

    //-- Normalisation CVD --//

    TH1F* fOutputHisto1D_CVD_norm;
    TH1F* fOutputHisto1D_Station0_CVD_norm;
    TH1F* fOutputHisto1D_Station1_CVD_norm;
    TH1F* fOutputHisto1D_Station2_CVD_norm;
    TH1F* fOutputHisto1D_Station3_CVD_norm;

    //-- Normalisation Aluminium --//
//    TH1F* fOutputHisto1D_Aluminium_count;
//    TH1F* fOutputHisto1D_Station0_Al_count;
//    TH1F* fOutputHisto1D_Station1_Al_count;
//    TH1F* fOutputHisto1D_Station2_Al_count;

    TH1F* fOutputHisto1D_Aluminium_norm;
    TH1F* fOutputHisto1D_Station0_Al_norm;
    TH1F* fOutputHisto1D_Station1_Al_norm;
    TH1F* fOutputHisto1D_Station2_Al_norm;
    TH1F* fOutputHisto1D_Station3_Al_norm;
	
    //-- Normalisation Copper --//
//    TH1F* fOutputHisto1D_Copper_count;
//    TH1F* fOutputHisto1D_Station0_Cu_count;
//    TH1F* fOutputHisto1D_Station1_Cu_count;
//    TH1F* fOutputHisto1D_Station2_Cu_count;

    TH1F* fOutputHisto1D_Copper_norm;
    TH1F* fOutputHisto1D_Station0_Cu_norm;
    TH1F* fOutputHisto1D_Station1_Cu_norm;
    TH1F* fOutputHisto1D_Station2_Cu_norm;
    TH1F* fOutputHisto1D_Station3_Cu_norm;
  
    //-- Normalisation all materials --//
//    TH1F* fOutputHisto1D_allMat_count;
//    TH1F* fOutputHisto1D_Station0_allMat_count;
//    TH1F* fOutputHisto1D_Station1_allMat_count;
//    TH1F* fOutputHisto1D_Station2_allMat_count;

    TH2F* fOutputHisto2D_Station0_all_norm;

    TH2F* fOutputHisto2D_Station0_all_divide;

    TH1F* fOutputHisto1D_allMat_norm;
    TH1F* fOutputHisto1D_Station0_allMat_norm;
    TH1F* fOutputHisto1D_Station1_allMat_norm;
    TH1F* fOutputHisto1D_Station2_allMat_norm;
    TH1F* fOutputHisto1D_Station3_allMat_norm;

    TH1F* fOutputHisto1D_allMat_CVD_norm;
    TH1F* fOutputHisto1D_Station0_allMat_CVD_norm;
    TH1F* fOutputHisto1D_Station1_allMat_CVD_norm;
    TH1F* fOutputHisto1D_Station2_allMat_CVD_norm;
    TH1F* fOutputHisto1D_Station3_allMat_CVD_norm;
	
    //-- Silcion Carbon --//
    TH1F* fOutputHisto1D_Si_C_norm;
    TH1F* fOutputHisto1D_Station0_Si_C_norm;
    TH1F* fOutputHisto1D_Station1_Si_C_norm;
    TH1F* fOutputHisto1D_Station2_Si_C_norm;
    TH1F* fOutputHisto1D_Station3_Si_C_norm;
	
    TH2F* fOutputHisto2D_Station0_Si_C_norm;

    //-- Silcion CVD --//
    TH1F* fOutputHisto1D_Si_CVD_norm;
    TH1F* fOutputHisto1D_Station0_Si_CVD_norm;
    TH1F* fOutputHisto1D_Station1_Si_CVD_norm;
    TH1F* fOutputHisto1D_Station2_Si_CVD_norm;
    TH1F* fOutputHisto1D_Station3_Si_CVD_norm;

    //-- Silicon Carbon Aluminium --//
    TH1F* fOutputHisto1D_Si_C_Al_norm;
    TH1F* fOutputHisto1D_Station0_Si_C_Al_norm;
    TH1F* fOutputHisto1D_Station1_Si_C_Al_norm;
    TH1F* fOutputHisto1D_Station2_Si_C_Al_norm;
    TH1F* fOutputHisto1D_Station3_Si_C_Al_norm;
	
    //-- Silicon CVD Aluminium --//
    TH1F* fOutputHisto1D_Si_CVD_Al_norm;
    TH1F* fOutputHisto1D_Station0_Si_CVD_Al_norm;
    TH1F* fOutputHisto1D_Station1_Si_CVD_Al_norm;
    TH1F* fOutputHisto1D_Station2_Si_CVD_Al_norm;
    TH1F* fOutputHisto1D_Station3_Si_CVD_Al_norm;

    TClonesArray* fInputArray;
    TClonesArray* fTrackArray;
    TString fBranchName;


private:
    Int_t fEvent;
    Int_t Hbin;
    Int_t Hbin2D_theta;
    Int_t Hbin2D_phi;
    Int_t Hbin2D_theta_max;
    Int_t Hbin2D_theta_min;
    Int_t Hbin2D_phi_max;
    Int_t Hbin2D_phi_min;
    Int_t counter[4][7];
    Float_t avg_material[4];
    Float_t avg_material_count[4];
    Float_t avg_material_norm[4];
//    Float_t avg_material_abs[4];

  ClassDef(CbmMvdRadLength,1);
    
};
    
    
#endif   		     
