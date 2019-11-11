// -------------------------------------------------------------------------
// -----                    CbmMvdRadLength  source file                -----
// -------------------------------------------------------------------------


/*
 *
 * ____________________________________________________________________________________________
 * --------------------------------------------------------------------------------------------

 * T.Tischler for the CBM MVD collaboration

 * thanks to S. Amar-Youcef

 * ____________________________________________________________________________________________
 * --------------------------------------------------------------------------------------------
 */


// Includes from MVD
#include "CbmMvdRadLength.h"


// Includes from base
#include "FairRootManager.h"
#include "FairRadLenPoint.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "CbmMCTrack.h"

// Includes from ROOT
#include "TClonesArray.h"
#include "TGeoManager.h"
#include "TString.h"
#include "TVector3.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TLine.h"
#include "TArrow.h"

// Includes from C++
#include <iostream>
#include <iomanip>


using std::cout;
using std::endl;
using std::map;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::pair;
using std::setprecision;
using std::ios_base;
using std::vector;




// -----   Default constructor   ------------------------------------------
CbmMvdRadLength::CbmMvdRadLength()
    : FairTask("MVDRadlength")
{
    //fInputArray    = new TClonesArray("FairRadLenPoint");
    

}
// -------------------------------------------------------------------------



// -----   Standard constructor   ------------------------------------------
CbmMvdRadLength::CbmMvdRadLength(const char* name, Int_t iMode,
				 Int_t iVerbose)
: FairTask(name, iVerbose)
{
    cout << "Starting CbmMvdRadLength::CbmMvdRadLength() "<< endl;

   // fInputArray    = new TClonesArray("CbmMvdInputArray");
}


// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
CbmMvdRadLength::~CbmMvdRadLength() { }


  

// -------Init----------------------------------------------------------------------

InitStatus CbmMvdRadLength::Init() {
	

	
    cout << GetName()<<"::Init()" << endl;
  // Get input array
    FairRootManager* ioman = FairRootManager::Instance();
    if ( ! ioman ) {
	cout << "-E- " << GetName() << "::Init: No FairRootManager!" << endl;
	return kFATAL;
    }
    fInputArray = (TClonesArray*) ioman->GetObject("RadLen");
    if (!fInputArray) {Fatal(GetName(),"InputArray not found");};


    fTrackArray = (TClonesArray*) ioman->GetObject("MCTrack");
    if (!fTrackArray) {Fatal(GetName(),"TrackArray not found");};


    //---- TH1F Histogramm binning ----//
    Hbin=900;
    Hbin2D_theta=900;
    Hbin2D_theta_max=90;
    Hbin2D_theta_min=0;
    Hbin2D_phi=3600;
    Hbin2D_phi_max=180;
    Hbin2D_phi_min=-180;

    

    for(int i=0;i<4;i++)
	{
		for(int j=0;j<7;j++)
		{
			counter [i][j] = 1;

		}


	}


    //---- Histograms ----//

    fEvent=0;
    
    for(Int_t ii=0;ii<4;ii++)
    {
      for(Int_t jj=0;jj<7;jj++)
      {
        //complete acceptance
	Histo1D_Station[ii][jj] = new TH1F(Form("Histo_1D_station: %i component: %i",ii, jj),Form("Histo_1D_station: %i component: %i",ii, jj),Hbin,0,90);
	Histo1D_Station_count[ii][jj] = new TH1F(Form("Histo_1D_count_station: %i component: %i",ii, jj),Form("Histo_1D_count_station: %i component: %i",ii, jj),Hbin,0,90);
	Histo1D_Station_norm[ii]= new TH1F(Form("Histo_1D_norm_station: %i",ii),Form("Histo_1D_norm_station: %i",ii),Hbin,0,90);

        Histo1D_cvd_si_Station[ii] = new TH1F(Form("Histo_1D_norm_station: %i",ii),Form("Histo_1D_norm_station: %i",ii),Hbin,0,90);
        Histo1D_al_cvd_si_Station[ii] = new TH1F(Form("Histo_1D_norm_station: %i",ii),Form("Histo_1D_norm_station: %i",ii),Hbin,0,90);

	//inside acceptance
        Histo1D_Station_in[ii][jj] = new TH1F(Form("Histo_1D_station_in: %i component: %i",ii, jj),Form("Histo_1D_station_in: %i component: %i",ii, jj),Hbin,0,90);
	Histo1D_Station_count_in[ii][jj] = new TH1F(Form("Histo_1D_count_station_in: %i component: %i",ii, jj),Form("Histo_1D_count_station_in: %i component: %i",ii, jj),Hbin,0,90);
	Histo1D_Station_norm_in[ii]= new TH1F(Form("Histo_1D_norm_station_in: %i",ii),Form("Histo_1D_norm_station_in: %i",ii),Hbin,0,90);

        Histo1D_cvd_si_Station_in[ii] = new TH1F(Form("Histo_1D_norm_station_in: %i",ii),Form("Histo_1D_norm_station_in: %i",ii),Hbin,0,90);
        Histo1D_al_cvd_si_Station_in[ii] = new TH1F(Form("Histo_1D_norm_station_in: %i",ii),Form("Histo_1D_norm_station_in: %i",ii),Hbin,0,90);

        //outside acceptance
        Histo1D_Station_out[ii][jj] = new TH1F(Form("Histo_1D_station_out: %i component: %i",ii, jj),Form("Histo_1D_station_out: %i component: %i",ii, jj),Hbin,0,90);
	Histo1D_Station_count_out[ii][jj] = new TH1F(Form("Histo_1D_count_station_out: %i component: %i",ii, jj),Form("Histo_1D_count_station_out: %i component: %i",ii, jj),Hbin,0,90);
	Histo1D_Station_norm_out[ii]= new TH1F(Form("Histo_1D_norm_station_out: %i",ii),Form("Histo_1D_norm_station_out: %i",ii),Hbin,0,90);

        Histo1D_cvd_si_Station_out[ii] = new TH1F(Form("Histo_1D_norm_station_out: %i",ii),Form("Histo_1D_norm_station_out: %i",ii),Hbin,0,90);
        Histo1D_al_cvd_si_Station_out[ii] = new TH1F(Form("Histo_1D_norm_station_out: %i",ii),Form("Histo_1D_norm_station_out: %i",ii),Hbin,0,90);

        // theta (x ) vs phi (y)
//	Histo2D_Station[ii][jj] = new TH2F(Form("Histo_2D_station: %i component: %i",ii, jj),(Form("Histo_2D_station: %i component: %i",ii, jj)),Hbin2D_theta,Hbin2D_theta_min,Hbin2D_theta_max,Hbin2D_phi,Hbin2D_phi_min,Hbin2D_phi_max);
//	Histo2D_Station_count[ii][jj] = new TH2F(Form("Histo_2D_count_station: %i component: %i",ii, jj),(Form("Histo_2D_count_station: %i component: %i",ii, jj)),Hbin2D_theta,Hbin2D_theta_min,Hbin2D_theta_max,Hbin2D_phi,Hbin2D_phi_min,Hbin2D_phi_max);
//	Histo2D_Station_norm[ii] = new TH2F(Form("Histo_2D_norm_station: %i",ii),(Form("Histo_2D_norm_station: %i",ii)),Hbin2D_theta,Hbin2D_theta_min,Hbin2D_theta_max,Hbin2D_phi,Hbin2D_phi_min,Hbin2D_phi_max);

        // phi (x) vs theta (y)
        Histo2D_Station[ii][jj] = new TH2F(Form("Histo_2D_station: %i component: %i",ii, jj),(Form("Histo_2D_station: %i component: %i",ii, jj)),Hbin2D_phi,Hbin2D_phi_min,Hbin2D_phi_max,Hbin2D_theta,Hbin2D_theta_min,Hbin2D_theta_max);
	Histo2D_Station_count[ii][jj] = new TH2F(Form("Histo_2D_count_station: %i component: %i",ii, jj),(Form("Histo_2D_count_station: %i component: %i",ii, jj)),Hbin2D_phi,Hbin2D_phi_min,Hbin2D_phi_max,Hbin2D_theta,Hbin2D_theta_min,Hbin2D_theta_max);
	Histo2D_Station_norm[ii] = new TH2F(Form("Histo_2D_norm_station: %i",ii),(Form("Histo_2D_norm_station: %i",ii)),Hbin2D_phi,Hbin2D_phi_min,Hbin2D_phi_max,Hbin2D_theta,Hbin2D_theta_min,Hbin2D_theta_max);


      }
    }


}
// -----------------------------------------------------------------------------

InitStatus CbmMvdRadLength::ReInit(){return Init();}

// -----   Virtual public method Exec   ------------------------------------
void CbmMvdRadLength::Exec(Option_t* opt) {
	fEvent++;

	
	Float_t		x_mean=0;
	Float_t		y_mean=0;
	Int_t		station;
	Int_t		layer;
	Int_t		component;
	Float_t		mb	[4][7];
	bool		fuell	[4][7];



	Double_t theta, phi;
	FairRadLenPoint* point;
	

// Only one track per event
	CbmMCTrack*	track=(CbmMCTrack* ) fTrackArray->At(0);
	if(!track){printf("no tracks found!\n"); return;}
	
	Float_t px = track->GetPx();
	Float_t py = track->GetPy();
	Float_t pz = track->GetPz();
	
	theta	= (Double_t)((TMath::ATan2(TMath::Sqrt(px*px+py*py),pz)*180/TMath::Pi()));
	phi  	= (Double_t)((TMath::ATan2(py,px)*180/TMath::Pi()));
	
	Double_t entryX;
	Double_t entryPx;
	Double_t exitX;
	Double_t entryY;
	Double_t entryPy;
	Double_t exitY;
	Double_t entryZ;
	Double_t entryPz;
	Double_t exitZ;
	
	Float_t radlength;
	TString mat;
	Float_t materialbudget;
	Int_t comporder;
	
	if(fEvent%100000==0){cout<<"--"<<fEvent << "------------------"<<endl;}
	
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<7;j++)
		{
			mb		[i][j] = 0;
			fuell	[i][j] = false;
		}
	}
// ------------------------
	for(Int_t i=0; i< fInputArray->GetEntries(); i++)
	{
		point=(FairRadLenPoint* ) fInputArray->At(i);
		
		comporder=-1;
		
		entryX = point->GetX();
		exitX  = point->GetXOut();
		entryY = point->GetY();
		exitY  = point->GetYOut();
		entryZ = point->GetZ();
		exitZ  = point->GetZOut();
		
		radlength	= point->GetRadLength();
				 
		// --- ignores points out of acceptance!
		if ( (entryX>30) || (entryY>30) || (entryZ<0) || (entryZ>30) || (theta>65) ) continue;
		
		if      (entryZ<4)	{ station=4; } //Assignment station number via z-position
		else if	(entryZ<6)	{ station=0; }
		else if	(entryZ<11)	{ station=1; }
		else if	(entryZ<16)	{ station=2; }
		else if	(entryZ<21)	{ station=3; }
		else   			{ station=4; }
	
		if	(entryZ<station*5+5)	{ layer=0; } //Assignment layer
		else   				{ layer=1; }
	
		if     	(radlength<2)	{ component=0; mat="cu";} // copper
		else if	(radlength<9)	{ component=1; mat="al";} // alu
		else if	(radlength<10)	{ component=2; mat="si";} // silicon
		else if	(radlength<19)	{ component=3; mat="cvd"; radlength=12.22; } // carbon

		materialbudget = TMath::Sqrt((entryX-exitX)*(entryX-exitX)+(entryY-exitY)*(entryY-exitY)+(entryZ-exitZ)*(entryZ-exitZ))/radlength*100;
		
//		if( radlength<1000 && component!=1 && station<4 ) // no air, no alu, no beam pipe
		if( radlength<1000 && station<4 ) // no air, no beam pipe
		{
		// 	  mb[station]["component"]
			if		( mat=="cu" )
			{
				if(layer==0)	{comporder=0;}
				if(layer==1)	{comporder=6;}
			}
			else if	( mat=="si" )
			{
				if(layer==0)	{comporder=1;}
				if(layer==1)	{comporder=5;}
			}
                        else if	( mat=="al" )
			{
				if(layer==0)	{comporder=2;}
				if(layer==1)	{comporder=4;}
			}
			else if	( mat=="cvd" )
			{
				comporder=3;
			}
			else
			{
				comporder=-1;
			}

			if(comporder!=-1)
			{
				mb     	[station][comporder]+=materialbudget;
				fuell	[station][comporder]=true;
			}
		}

	}

	
	for(Int_t istation=0; istation<4; istation++)
	{
	for(Int_t ifill=0; ifill<7;ifill++)
	{
	if(fuell[istation][ifill]==true)
	{
	Histo1D_Station[istation][ifill]->Fill(theta,mb[istation][ifill]);
	Histo1D_Station_count[istation][ifill]->Fill(theta,counter[istation][ifill]);
        
	Histo1D_Station_norm[istation]->Fill(theta,0);

        //theta (x) vs phi (y)
//	Histo2D_Station[istation][ifill]->Fill(theta,phi,mb[istation][ifill]);
//	Histo2D_Station_count[istation][ifill]->Fill(theta,phi,counter[istation][ifill]);
//	Histo2D_Station_norm[istation]->Fill(theta,phi,0);

        //phi (x) vs theta (y)
	Histo2D_Station[istation][ifill]->Fill(phi,theta,mb[istation][ifill]);
	Histo2D_Station_count[istation][ifill]->Fill(phi,theta,counter[istation][ifill]);
	Histo2D_Station_norm[istation]->Fill(phi,theta,0);

	if(theta<=25)
	{
        Histo1D_Station_in[istation][ifill]->Fill(theta,mb[istation][ifill]);
	Histo1D_Station_count_in[istation][ifill]->Fill(theta,counter[istation][ifill]);
        
	Histo1D_Station_norm_in[istation]->Fill(theta,0);


	}
	else
	{
	Histo1D_Station_out[istation][ifill]->Fill(theta,mb[istation][ifill]);
	Histo1D_Station_count_out[istation][ifill]->Fill(theta,counter[istation][ifill]);
        
	Histo1D_Station_norm_out[istation]->Fill(theta,0);
	}


	}
	}
	} 
//histogramm fuellen, wenn bool auf true + um eins hoch zaehlen fuer die normieurng

}// end of exec

// -------------------------------------------------------------------------


  


// -----   Virtual method Finish   -----------------------------------------
void CbmMvdRadLength::Finish() {

    TCanvas* call= new TCanvas("RadLength_all","RadLength_all",200,200,800,500);

//    TCanvas* cmaterialbudget_2D_Station0 = new TCanvas("RadLength_materialbudget_2D_S0","RadLength_materialbudget_S0",200,200,800,500);
//    TCanvas* cmaterialbudget_2D_Station1 = new TCanvas("RadLength_materialbudget_2D_S1","RadLength_materialbudget_S1",200,200,800,500);
//    TCanvas* cmaterialbudget_2D_Station2 = new TCanvas("RadLength_materialbudget_2D_S2","RadLength_materialbudget_S2",200,200,800,500);
//    TCanvas* cmaterialbudget_2D_Station3 = new TCanvas("RadLength_materialbudget_2D_S3","RadLength_materialbudget_S3",200,200,800,500);

//    TCanvas* cmaterialbudget_Station0_CVD = new TCanvas("RadLength_materialbudget_St0_CVD","RadLength_materialbudget_St0_CVD",200,200,800,500);
//    TCanvas* cmaterialbudget_Station1_CVD = new TCanvas("RadLength_materialbudget_St1_CVD","RadLength_materialbudget_St1_CVD",200,200,800,500);
//    TCanvas* cmaterialbudget_Station2_CVD = new TCanvas("RadLength_materialbudget_St2_CVD","RadLength_materialbudget_St2_CVD",200,200,800,500);
//    TCanvas* cmaterialbudget_Station3_CVD = new TCanvas("RadLength_materialbudget_St3_CVD","RadLength_materialbudget_St3_CVD",200,200,800,500);

    TCanvas* cmaterialbudget_Station0_CVD_in_out = new TCanvas("RadLength_materialbudget_St0_CVD_in_out","RadLength_materialbudget_St0_CVD_in_out",200,200,800,500);
    TCanvas* cmaterialbudget_Station1_CVD_in_out = new TCanvas("RadLength_materialbudget_St1_CVD_in_out","RadLength_materialbudget_St1_CVD_in_out",200,200,800,500);
    TCanvas* cmaterialbudget_Station2_CVD_in_out = new TCanvas("RadLength_materialbudget_St2_CVD_in_out","RadLength_materialbudget_St2_CVD_in_out",200,200,800,500);
    TCanvas* cmaterialbudget_Station3_CVD_in_out = new TCanvas("RadLength_materialbudget_St3_CVD_in_out","RadLength_materialbudget_St3_CVD_in_out",200,200,800,500);


    //---- Start Normalisation ----//
    
    for(Int_t istation=0; istation<4; istation++)
    {
      for(Int_t ifill=0; ifill<7;ifill++)
      {
	   Histo1D_Station[istation][ifill]->Divide(Histo1D_Station_count[istation][ifill]);
	   Histo2D_Station[istation][ifill]->Divide(Histo2D_Station_count[istation][ifill]);

	   Histo1D_Station_in[istation][ifill]->Divide(Histo1D_Station_count_in[istation][ifill]);
	   Histo1D_Station_out[istation][ifill]->Divide(Histo1D_Station_count_out[istation][ifill]);
      }


    } 


    for(Int_t istation=0; istation<4; istation++)
      {
                //complete acceptance
	        Histo1D_Station_norm[istation]->Add(Histo1D_Station[istation][3]);//before [2]
		Histo1D_Station_norm[istation]->Add(Histo1D_Station[istation][0]);//before [0]
		Histo1D_Station_norm[istation]->Add(Histo1D_Station[istation][1]);//before [1]
		Histo1D_Station_norm[istation]->Add(Histo1D_Station[istation][2]);//before [-]
		Histo1D_Station_norm[istation]->Add(Histo1D_Station[istation][5]);//before [3]
		Histo1D_Station_norm[istation]->Add(Histo1D_Station[istation][6]);//before [4]
		Histo1D_Station_norm[istation]->Add(Histo1D_Station[istation][4]);//before [-]

                //-->cvd glue(al) si
                Histo1D_al_cvd_si_Station[istation]->Add(Histo1D_Station[istation][3]);//before [2]
		Histo1D_al_cvd_si_Station[istation]->Add(Histo1D_Station[istation][1]);//before [1]
		Histo1D_al_cvd_si_Station[istation]->Add(Histo1D_Station[istation][5]);//before [3]
		Histo1D_al_cvd_si_Station[istation]->Add(Histo1D_Station[istation][2]);//before [-]
                Histo1D_al_cvd_si_Station[istation]->Add(Histo1D_Station[istation][4]);//before [-]

                //-->cvd glue(al)
		Histo1D_cvd_si_Station[istation]->Add(Histo1D_Station[istation][3]);//before [2]
		Histo1D_cvd_si_Station[istation]->Add(Histo1D_Station[istation][2]);//before [-]
                Histo1D_cvd_si_Station[istation]->Add(Histo1D_Station[istation][4]);//before [-]

                //-------------

                //inside acceptance
                Histo1D_Station_norm_in[istation]->Add(Histo1D_Station_in[istation][3]);//before [2]
		Histo1D_Station_norm_in[istation]->Add(Histo1D_Station_in[istation][0]);//before [0]
		Histo1D_Station_norm_in[istation]->Add(Histo1D_Station_in[istation][1]);//before [1]
		Histo1D_Station_norm_in[istation]->Add(Histo1D_Station_in[istation][2]);//before [-]
		Histo1D_Station_norm_in[istation]->Add(Histo1D_Station_in[istation][5]);//before [3]
		Histo1D_Station_norm_in[istation]->Add(Histo1D_Station_in[istation][6]);//before [4]
		Histo1D_Station_norm_in[istation]->Add(Histo1D_Station_in[istation][4]);//before [-]

                //-->cvd glue(al) si
                Histo1D_al_cvd_si_Station_in[istation]->Add(Histo1D_Station_in[istation][3]);//before [2]
		Histo1D_al_cvd_si_Station_in[istation]->Add(Histo1D_Station_in[istation][1]);//before [1]
		Histo1D_al_cvd_si_Station_in[istation]->Add(Histo1D_Station_in[istation][5]);//before [3]
		Histo1D_al_cvd_si_Station_in[istation]->Add(Histo1D_Station_in[istation][2]);//before [-]
                Histo1D_al_cvd_si_Station_in[istation]->Add(Histo1D_Station_in[istation][4]);//before [-]

                //-->cvd glue(al)
		Histo1D_cvd_si_Station_in[istation]->Add(Histo1D_Station_in[istation][3]);//before [2]
		Histo1D_cvd_si_Station_in[istation]->Add(Histo1D_Station_in[istation][2]);//before [-]
                Histo1D_cvd_si_Station_in[istation]->Add(Histo1D_Station_in[istation][4]);//before [-]

                //-------------

                //outside acceptance
                Histo1D_Station_norm_out[istation]->Add(Histo1D_Station_out[istation][3]);//before [2]
		Histo1D_Station_norm_out[istation]->Add(Histo1D_Station_out[istation][0]);//before [0]
		Histo1D_Station_norm_out[istation]->Add(Histo1D_Station_out[istation][1]);//before [1]
		Histo1D_Station_norm_out[istation]->Add(Histo1D_Station_out[istation][2]);//before [-]
		Histo1D_Station_norm_out[istation]->Add(Histo1D_Station_out[istation][5]);//before [3]
		Histo1D_Station_norm_out[istation]->Add(Histo1D_Station_out[istation][6]);//before [4]
		Histo1D_Station_norm_out[istation]->Add(Histo1D_Station_out[istation][4]);//before [-]

                //-->cvd glue(al) si
                Histo1D_al_cvd_si_Station_out[istation]->Add(Histo1D_Station_out[istation][3]);//before [2]
		Histo1D_al_cvd_si_Station_out[istation]->Add(Histo1D_Station_out[istation][1]);//before [1]
		Histo1D_al_cvd_si_Station_out[istation]->Add(Histo1D_Station_out[istation][5]);//before [3]
		Histo1D_al_cvd_si_Station_out[istation]->Add(Histo1D_Station_out[istation][2]);//before [-]
		Histo1D_al_cvd_si_Station_out[istation]->Add(Histo1D_Station_out[istation][4]);//before [-]

                //-->cvd glue(al)
		Histo1D_cvd_si_Station_out[istation]->Add(Histo1D_Station_out[istation][3]);//before [2]
		Histo1D_cvd_si_Station_out[istation]->Add(Histo1D_Station_out[istation][2]);//before [-]
                Histo1D_cvd_si_Station_out[istation]->Add(Histo1D_Station_out[istation][4]);//before [-]



                Histo2D_Station_norm[istation]->Add(Histo2D_Station[istation][2]);
		Histo2D_Station_norm[istation]->Add(Histo2D_Station[istation][0]);
		Histo2D_Station_norm[istation]->Add(Histo2D_Station[istation][1]);
		Histo2D_Station_norm[istation]->Add(Histo2D_Station[istation][3]);
		Histo2D_Station_norm[istation]->Add(Histo2D_Station[istation][4]);
		Histo2D_Station_norm[istation]->Add(Histo2D_Station[istation][5]);
		Histo2D_Station_norm[istation]->Add(Histo2D_Station[istation][6]);
	    
      }


    //----------- Average material budget


    for(Int_t imaterial=0; imaterial<4; imaterial++)
    {
	avg_material[imaterial]=0;
        avg_material_count[imaterial]=0;
	avg_material_norm[imaterial]=0;

    }

    for(Int_t imaterial_station=0; imaterial_station<4; imaterial_station++)
    {

        for(Int_t iacceptance=0; iacceptance<=250; iacceptance++)
        {

        avg_material[imaterial_station]+=Histo1D_Station_norm_in[imaterial_station]->GetBinContent(iacceptance);

	if(Histo1D_Station_norm_in[imaterial_station]->GetBinContent(iacceptance)!=0)
        {

        avg_material_count[imaterial_station]+=1;

	}

	}
    }

    for(Int_t imaterial_div=0; imaterial_div<4; imaterial_div++)
    {
	avg_material_norm[imaterial_div]=avg_material[imaterial_div]/avg_material_count[imaterial_div];

    }

    cout << "Average material budget in the acceptance" << endl;
    cout << "Station 0:" << avg_material_norm[0] << " % x/X0" << endl;
    cout << "Station 1:" << avg_material_norm[1] << " % x/X0" << endl;
    cout << "Station 2:" << avg_material_norm[2] << " % x/X0" << endl;
    cout << "Station 3:" << avg_material_norm[3] << " % x/X0" << endl;

    //----------- Drawing Histogramms

    Float_t y_maximum=0.7;

    //---- Overview Station_0

    call->Divide(8,4);
    call->cd(1);
    Histo1D_Station[0][0]->SetTitle("Material Budget Station 0, cu, layer 0");
    Histo1D_Station[0][0]->SetFillColor(8);
    Histo1D_Station[0][0]->SetFillStyle(1001);
    Histo1D_Station[0][0]->Draw("HIST");

    call->cd(2);
    Histo1D_Station[0][1]->SetTitle("Material Budget Station 0, si, layer 0");
    Histo1D_Station[0][1]->SetFillColor(38);
    Histo1D_Station[0][1]->SetFillStyle(1001);
    Histo1D_Station[0][1]->Draw("HIST");

    call->cd(3);
    Histo1D_Station[0][2]->SetTitle("Material Budget Station 0, al, layer 0");
    Histo1D_Station[0][2]->SetFillColor(1);
    Histo1D_Station[0][2]->SetFillStyle(1001);
    Histo1D_Station[0][2]->Draw("HIST");

    call->cd(4);
    Histo1D_Station[0][3]->SetTitle("Material Budget Station 0, cvd");
    Histo1D_Station[0][3]->SetFillColor(16);
    Histo1D_Station[0][3]->SetFillStyle(1001);
    Histo1D_Station[0][3]->Draw("HIST");

    call->cd(5);
    Histo1D_Station[0][4]->SetTitle("Material Budget Station 0, al, layer 1");
    Histo1D_Station[0][4]->SetFillColor(1);
    Histo1D_Station[0][4]->SetFillStyle(1001);
    Histo1D_Station[0][4]->Draw("HIST");

    call->cd(6);
    Histo1D_Station[0][5]->SetTitle("Material Budget Station 0, si, layer 1");
    Histo1D_Station[0][5]->SetFillColor(38);
    Histo1D_Station[0][5]->SetFillStyle(1001);
    Histo1D_Station[0][5]->Draw("HIST");

    call->cd(7);
    Histo1D_Station[0][6]->SetTitle("Material Budget Station 0, cu, layer 1");
    Histo1D_Station[0][6]->SetFillColor(8);
    Histo1D_Station[0][6]->SetFillStyle(1001);
    Histo1D_Station[0][6]->Draw("HIST");

    call->cd(8);
    Histo1D_Station_norm[0]->SetTitle("Material Budget Station 0, all");
    Histo1D_Station_norm[0]->SetFillColor(8);
    Histo1D_Station_norm[0]->SetFillStyle(1001);
    Histo1D_Station_norm[0]->Draw("HIST");

    Histo1D_al_cvd_si_Station[0]->SetFillColor(38);
    Histo1D_al_cvd_si_Station[0]->SetFillStyle(1001);
    Histo1D_al_cvd_si_Station[0]->Draw("SAME HIST");

    Histo1D_cvd_si_Station[0]->SetFillColor(1);
    Histo1D_cvd_si_Station[0]->SetFillStyle(1001);
    Histo1D_cvd_si_Station[0]->Draw("SAME HIST");

    Histo1D_Station[0][3]->SetFillColor(16);
    Histo1D_Station[0][3]->SetFillStyle(1001);
    Histo1D_Station[0][3]->Draw("SAME HIST");

    //---- Overview Station_1

    call->cd(9);
    Histo1D_Station[1][0]->SetTitle("Material Budget Station 1, cu, layer 0");
    Histo1D_Station[1][0]->SetFillColor(8);
    Histo1D_Station[1][0]->SetFillStyle(1001);
    Histo1D_Station[1][0]->Draw("HIST");

    call->cd(10);
    Histo1D_Station[1][1]->SetTitle("Material Budget Station 1, si, layer 0");
    Histo1D_Station[1][1]->SetFillColor(38);
    Histo1D_Station[1][1]->SetFillStyle(1001);
    Histo1D_Station[1][1]->Draw("HIST");

    call->cd(11);
    Histo1D_Station[1][2]->SetTitle("Material Budget Station 1, al, layer 0");
    Histo1D_Station[1][2]->SetFillColor(1);
    Histo1D_Station[1][2]->SetFillStyle(1001);
    Histo1D_Station[1][2]->Draw("HIST");

    call->cd(12);
    Histo1D_Station[1][3]->SetTitle("Material Budget Station 1, cvd");
    Histo1D_Station[1][3]->SetFillColor(16);
    Histo1D_Station[1][3]->SetFillStyle(1001);
    Histo1D_Station[1][3]->Draw("HIST");

    call->cd(13);
    Histo1D_Station[1][4]->SetTitle("Material Budget Station 1, al, layer 1");
    Histo1D_Station[1][4]->SetFillColor(1);
    Histo1D_Station[1][4]->SetFillStyle(1001);
    Histo1D_Station[1][4]->Draw("HIST");

    call->cd(14);
    Histo1D_Station[1][5]->SetTitle("Material Budget Station 1, si, layer 1");
    Histo1D_Station[1][5]->SetFillColor(38);
    Histo1D_Station[1][5]->SetFillStyle(1001);
    Histo1D_Station[1][5]->Draw("HIST");

    call->cd(15);
    Histo1D_Station[1][6]->SetTitle("Material Budget Station 1, cu, layer 1");
    Histo1D_Station[1][6]->SetFillColor(8);
    Histo1D_Station[1][6]->SetFillStyle(1001);
    Histo1D_Station[1][6]->Draw("HIST");

    call->cd(16);
    Histo1D_Station_norm[1]->SetTitle("Material Budget Station 1, all");
    Histo1D_Station_norm[1]->SetFillColor(8);
    Histo1D_Station_norm[1]->SetFillStyle(1001);
    Histo1D_Station_norm[1]->Draw("HIST");

    Histo1D_al_cvd_si_Station[1]->SetFillColor(38);
    Histo1D_al_cvd_si_Station[1]->SetFillStyle(1001);
    Histo1D_al_cvd_si_Station[1]->Draw("SAME HIST");

    Histo1D_cvd_si_Station[1]->SetFillColor(1);
    Histo1D_cvd_si_Station[1]->SetFillStyle(1001);
    Histo1D_cvd_si_Station[1]->Draw("SAME HIST");

    Histo1D_Station[1][3]->SetFillColor(16);
    Histo1D_Station[1][3]->SetFillStyle(1001);
    Histo1D_Station[1][3]->Draw("SAME HIST");


    //---- Overview Station_2

    call->cd(17);
    Histo1D_Station[2][0]->SetTitle("Material Budget Station 2, cu, layer 0");
    Histo1D_Station[2][0]->SetFillColor(8);
    Histo1D_Station[2][0]->SetFillStyle(1001);
    Histo1D_Station[2][0]->Draw("HIST");

    call->cd(18);
    Histo1D_Station[2][1]->SetTitle("Material Budget Station 2, si, layer 0");
    Histo1D_Station[2][1]->SetFillColor(38);
    Histo1D_Station[2][1]->SetFillStyle(1001);
    Histo1D_Station[2][1]->Draw("HIST");

    call->cd(19);
    Histo1D_Station[2][2]->SetTitle("Material Budget Station 2, al, layer 0");
    Histo1D_Station[2][2]->SetFillColor(1);
    Histo1D_Station[2][2]->SetFillStyle(1001);
    Histo1D_Station[2][2]->Draw("HIST");

    call->cd(20);
    Histo1D_Station[2][3]->SetTitle("Material Budget Station 2, CF-TPG-CF");
    Histo1D_Station[2][3]->SetFillColor(16);
    Histo1D_Station[2][3]->SetFillStyle(1001);
    Histo1D_Station[2][3]->Draw("HIST");

    call->cd(21);
    Histo1D_Station[2][4]->SetTitle("Material Budget Station 2, al, layer 1");
    Histo1D_Station[2][4]->SetFillColor(1);
    Histo1D_Station[2][4]->SetFillStyle(1001);
    Histo1D_Station[2][4]->Draw("HIST");

    call->cd(22);
    Histo1D_Station[2][5]->SetTitle("Material Budget Station 2, si, layer 1");
    Histo1D_Station[2][5]->SetFillColor(38);
    Histo1D_Station[2][5]->SetFillStyle(1001);
    Histo1D_Station[2][5]->Draw("HIST");

    call->cd(23);
    Histo1D_Station[2][6]->SetTitle("Material Budget Station 2, cu, layer 1");
    Histo1D_Station[2][6]->SetFillColor(8);
    Histo1D_Station[2][6]->SetFillStyle(1001);
    Histo1D_Station[2][6]->Draw("HIST");

    call->cd(24);
    Histo1D_Station_norm[2]->SetTitle("Material Budget Station 2, all");
    Histo1D_Station_norm[2]->SetFillColor(8);
    Histo1D_Station_norm[2]->SetFillStyle(1001);
    Histo1D_Station_norm[2]->Draw("HIST");

    Histo1D_al_cvd_si_Station[2]->SetFillColor(38);
    Histo1D_al_cvd_si_Station[2]->SetFillStyle(1001);
    Histo1D_al_cvd_si_Station[2]->Draw("SAME HIST");

    Histo1D_cvd_si_Station[2]->SetFillColor(1);
    Histo1D_cvd_si_Station[2]->SetFillStyle(1001);
    Histo1D_cvd_si_Station[2]->Draw("SAME HIST");

    Histo1D_Station[2][3]->SetFillColor(16);
    Histo1D_Station[2][3]->SetFillStyle(1001);
    Histo1D_Station[2][3]->Draw("SAME HIST");


    //---- Overview Station_3

    call->cd(25);
    Histo1D_Station[3][0]->SetTitle("Material Budget Station 3, cu, layer 0");
    Histo1D_Station[3][0]->SetFillColor(8);
    Histo1D_Station[3][0]->SetFillStyle(1001);
    Histo1D_Station[3][0]->Draw("HIST");

    call->cd(26);
    Histo1D_Station[3][1]->SetTitle("Material Budget Station 3, si, layer 0");
    Histo1D_Station[3][1]->SetFillColor(38);
    Histo1D_Station[3][1]->SetFillStyle(1001);
    Histo1D_Station[3][1]->Draw("HIST");

    call->cd(27);
    Histo1D_Station[3][2]->SetTitle("Material Budget Station 3, al, layer 0");
    Histo1D_Station[3][2]->SetFillColor(1);
    Histo1D_Station[3][2]->SetFillStyle(1001);
    Histo1D_Station[3][2]->Draw("HIST");

    call->cd(28);
    Histo1D_Station[3][3]->SetTitle("Material Budget Station 3, CF-TPG-CF");
    Histo1D_Station[3][3]->SetFillColor(16);
    Histo1D_Station[3][3]->SetFillStyle(1001);
    Histo1D_Station[3][3]->Draw("HIST");

    call->cd(29);
    Histo1D_Station[3][4]->SetTitle("Material Budget Station 3, al, layer 1");
    Histo1D_Station[3][4]->SetFillColor(1);
    Histo1D_Station[3][4]->SetFillStyle(1001);
    Histo1D_Station[3][4]->Draw("HIST");

    call->cd(30);
    Histo1D_Station[3][5]->SetTitle("Material Budget Station 3, si, layer 1");
    Histo1D_Station[3][5]->SetFillColor(38);
    Histo1D_Station[3][5]->SetFillStyle(1001);
    Histo1D_Station[3][5]->Draw("HIST");

    call->cd(31);
    Histo1D_Station[3][6]->SetTitle("Material Budget Station 3, cu, layer 1");
    Histo1D_Station[3][6]->SetFillColor(8);
    Histo1D_Station[3][6]->SetFillStyle(1001);
    Histo1D_Station[3][6]->Draw("HIST");

    call->cd(32);
    Histo1D_Station_norm[3]->SetTitle("Material Budget Station 3, all");
    Histo1D_Station_norm[3]->SetFillColor(8);
    Histo1D_Station_norm[3]->SetFillStyle(1001);
    Histo1D_Station_norm[3]->Draw("HIST");

    Histo1D_al_cvd_si_Station[3]->SetFillColor(38);
    Histo1D_al_cvd_si_Station[3]->SetFillStyle(1001);
    Histo1D_al_cvd_si_Station[3]->Draw("SAME HIST");

    Histo1D_cvd_si_Station[3]->SetFillColor(1);
    Histo1D_cvd_si_Station[3]->SetFillStyle(1001);
    Histo1D_cvd_si_Station[3]->Draw("SAME HIST");

    Histo1D_Station[3][3]->SetFillColor(16);
    Histo1D_Station[3][3]->SetFillStyle(1001);
    Histo1D_Station[3][3]->Draw("SAME HIST");

    // Material Budget per Station
    //---- Station_0
/*
    cmaterialbudget_Station0_CVD->cd();
    Histo1D_Station_norm[0]->SetTitle("Material Budget Station 0");
    Histo1D_Station_norm[0]->SetFillColor(8);
    Histo1D_Station_norm[0]->SetFillStyle(1001);
    Histo1D_Station_norm[0]->SetMaximum(y_maximum);
    Histo1D_Station_norm[0]->GetXaxis()->SetTitle("#vartheta [#circ]");
    Histo1D_Station_norm[0]->GetYaxis()->SetTitle("x/X_{0} [\%]");
    Histo1D_Station_norm[0]->Draw("HIST");

    Histo1D_cvd_si_Station[0]->SetFillColor(38);
    Histo1D_cvd_si_Station[0]->SetFillStyle(1001);
    Histo1D_cvd_si_Station[0]->Draw("SAME HIST");

    Histo1D_Station[0][2]->SetFillColor(16);
    Histo1D_Station[0][2]->SetFillStyle(1001);
    Histo1D_Station[0][2]->Draw("SAME HIST");

    TLine* MB_limit_S0 = new TLine(5,0.3,30,0.3);
    MB_limit_S0->SetLineWidth(3);
    MB_limit_S0->SetLineColor(kRed);
    MB_limit_S0->Draw("same");

    TLine* Acceptance_S0 = new TLine(25,0,25,0.5);
    Acceptance_S0->SetLineWidth(3);
    Acceptance_S0->SetLineStyle(2);
    Acceptance_S0->SetLineColor(kBlack);
    Acceptance_S0->Draw("same");

    TLegend* legendmb_S0 = new TLegend(0.7,0.6,0.9,0.3);
    legendmb_S0->SetBorderSize(1);
    legendmb_S0->SetFillColor(0);
    legendmb_S0->SetFillStyle(1001);
    legendmb_S0->AddEntry(Histo1D_Station[0][0],"FPC","f");
    legendmb_S0->AddEntry(Histo1D_Station[0][1],"Sensors","f");
    legendmb_S0->AddEntry(Histo1D_Station[0][2],"CVD","f");
    legendmb_S0->Draw("HIST");

    //---- Station_1

    cmaterialbudget_Station1_CVD->cd();
    Histo1D_Station_norm[1]->SetTitle("Material Budget Station 1");
    Histo1D_Station_norm[1]->SetFillColor(8);
    Histo1D_Station_norm[1]->SetFillStyle(1001);
    Histo1D_Station_norm[1]->SetMaximum(y_maximum);
    Histo1D_Station_norm[1]->GetXaxis()->SetTitle("#vartheta [#circ]");
    Histo1D_Station_norm[1]->GetYaxis()->SetTitle("x/X_{0} [\%]");
    Histo1D_Station_norm[1]->Draw("HIST");

    Histo1D_cvd_si_Station[1]->SetFillColor(38);
    Histo1D_cvd_si_Station[1]->SetFillStyle(1001);
    Histo1D_cvd_si_Station[1]->Draw("SAME HIST");

    Histo1D_Station[1][2]->SetFillColor(16);
    Histo1D_Station[1][2]->SetFillStyle(1001);
    Histo1D_Station[1][2]->Draw("SAME HIST");

    TLine* MB_limit_S1 = new TLine(2,0.5,30,0.5);
    MB_limit_S1->SetLineWidth(3);
    MB_limit_S1->SetLineColor(kRed);
    MB_limit_S1->Draw("same");

    TLine* Acceptance_S1 = new TLine(25,0,25,0.6);
    Acceptance_S1->SetLineWidth(3);
    Acceptance_S1->SetLineStyle(2);
    Acceptance_S1->SetLineColor(kBlack);
    Acceptance_S1->Draw("same");

    TLegend* legendmb_S1 = new TLegend(0.7,0.6,0.9,0.3);
    legendmb_S1->SetBorderSize(1);
    legendmb_S1->SetFillColor(0);
    legendmb_S1->SetFillStyle(1001);
    legendmb_S1->AddEntry(Histo1D_Station[1][0],"FPC","f");
    legendmb_S1->AddEntry(Histo1D_Station[1][1],"Sensors","f");
    legendmb_S1->AddEntry(Histo1D_Station[1][2],"CVD","f");
    legendmb_S1->Draw("HIST");

    //---- Station_2

    cmaterialbudget_Station2_CVD->cd();
    Histo1D_Station_norm[2]->SetTitle("Material Budget Station 2");
    Histo1D_Station_norm[2]->SetFillColor(8);
    Histo1D_Station_norm[2]->SetFillStyle(1001);
    Histo1D_Station_norm[2]->SetMaximum(y_maximum);
    Histo1D_Station_norm[2]->GetXaxis()->SetTitle("#vartheta [#circ]");
    Histo1D_Station_norm[2]->GetYaxis()->SetTitle("x/X_{0} [\%]");
    Histo1D_Station_norm[2]->Draw("HIST");

    Histo1D_cvd_si_Station[2]->SetFillColor(38);
    Histo1D_cvd_si_Station[2]->SetFillStyle(1001);
    Histo1D_cvd_si_Station[2]->Draw("SAME HIST");

    Histo1D_Station[2][2]->SetFillColor(16);
    Histo1D_Station[2][2]->SetFillStyle(1001);
    Histo1D_Station[2][2]->Draw("SAME HIST");

    TLine* MB_limit_S2 = new TLine(2,0.5,30,0.5);
    MB_limit_S2->SetLineWidth(3);
    MB_limit_S2->SetLineColor(kRed);
    MB_limit_S2->Draw("same");

    TLine* Acceptance_S2 = new TLine(25,0,25,0.6);
    Acceptance_S2->SetLineWidth(3);
    Acceptance_S2->SetLineStyle(2);
    Acceptance_S2->SetLineColor(kBlack);
    Acceptance_S2->Draw("same");

    TLegend* legendmb_S2 = new TLegend(0.7,0.6,0.9,0.3);
    legendmb_S2->SetBorderSize(1);
    legendmb_S2->SetFillColor(0);
    legendmb_S2->SetFillStyle(1001);
    legendmb_S2->AddEntry(Histo1D_Station[2][0],"FPC","f");
    legendmb_S2->AddEntry(Histo1D_Station[2][1],"Sensors","f");
    legendmb_S2->AddEntry(Histo1D_Station[2][2],"CF-TPG-CF","f");
    legendmb_S2->Draw("HIST");

    //---- Station_3

    cmaterialbudget_Station3_CVD->cd();
    Histo1D_Station_norm[3]->SetTitle("Material Budget Station 3");
    Histo1D_Station_norm[3]->SetFillColor(8);
    Histo1D_Station_norm[3]->SetFillStyle(1001);
    Histo1D_Station_norm[3]->SetMaximum(y_maximum);
    Histo1D_Station_norm[3]->GetXaxis()->SetTitle("#vartheta [#circ]");
    Histo1D_Station_norm[3]->GetYaxis()->SetTitle("x/X_{0} [\%]");
    Histo1D_Station_norm[3]->Draw("HIST");

    Histo1D_cvd_si_Station[3]->SetFillColor(38);
    Histo1D_cvd_si_Station[3]->SetFillStyle(1001);
    Histo1D_cvd_si_Station[3]->Draw("SAME HIST");

    Histo1D_Station[3][2]->SetFillColor(16);
    Histo1D_Station[3][2]->SetFillStyle(1001);
    Histo1D_Station[3][2]->Draw("SAME HIST");

    TLine* MB_limit_S3 = new TLine(2,0.5,30,0.5);
    MB_limit_S3->SetLineWidth(3);
    MB_limit_S3->SetLineColor(kRed);
    MB_limit_S3->Draw("same");

    TLine* Acceptance_S3 = new TLine(25,0,25,0.6);
    Acceptance_S3->SetLineWidth(3);
    Acceptance_S3->SetLineStyle(2);
    Acceptance_S3->SetLineColor(kBlack);
    Acceptance_S3->Draw("same");

    TLegend* legendmb_S3 = new TLegend(0.7,0.6,0.9,0.3);
    legendmb_S3->SetBorderSize(1);
    legendmb_S3->SetFillColor(0);
    legendmb_S3->SetFillStyle(1001);
    legendmb_S3->AddEntry(Histo1D_Station[3][0],"FPC","f");
    legendmb_S3->AddEntry(Histo1D_Station[3][1],"Sensors","f");
    legendmb_S3->AddEntry(Histo1D_Station[3][2],"CF-TPG-CF","f");
    legendmb_S3->Draw("HIST");
*/
    //2D theta vs phi
    /*
    cmaterialbudget_2D_Station0->cd();
    Histo2D_Station_norm[0]->SetTitle("Material Budget Station 0");
    Histo2D_Station_norm[0]->GetYaxis()->SetTitle("#vartheta [#circ]");
    Histo2D_Station_norm[0]->GetXaxis()->SetTitle("#varphi [#circ]");
    Histo2D_Station_norm[0]->GetZaxis()->SetTitle("x/X_{0} [\%]");
    Histo2D_Station_norm[0]->Draw("COLZ");

    cmaterialbudget_2D_Station1->cd();
    Histo2D_Station_norm[1]->SetTitle("Material Budget Station 1");
    Histo2D_Station_norm[1]->GetYaxis()->SetTitle("#vartheta [#circ]");
    Histo2D_Station_norm[1]->GetXaxis()->SetTitle("#varphi [#circ]");
    Histo2D_Station_norm[1]->GetZaxis()->SetTitle("x/X_{0} [\%]");
    Histo2D_Station_norm[1]->Draw("COLZ");

    cmaterialbudget_2D_Station2->cd();
    Histo2D_Station_norm[2]->SetTitle("Material Budget Station 2");
    Histo2D_Station_norm[2]->GetYaxis()->SetTitle("#vartheta [#circ]");
    Histo2D_Station_norm[2]->GetXaxis()->SetTitle("#varphi [#circ]");
    Histo2D_Station_norm[2]->GetZaxis()->SetTitle("x/X_{0} [\%]");
    Histo2D_Station_norm[2]->Draw("COLZ");

    cmaterialbudget_2D_Station3->cd();
    Histo2D_Station_norm[3]->SetTitle("Material Budget Station 3");
    Histo2D_Station_norm[3]->GetYaxis()->SetTitle("#vartheta [#circ]");
    Histo2D_Station_norm[3]->GetXaxis()->SetTitle("#varphi [#circ]");
    Histo2D_Station_norm[3]->GetZaxis()->SetTitle("x/X_{0} [\%]");
    Histo2D_Station_norm[3]->Draw("COLZ");
    */


    // Material Budget per Station
    //---- Station_0
    //acceptance distribution

    cmaterialbudget_Station0_CVD_in_out->cd();
    Histo1D_Station_norm_in[0]->SetTitle("Material Budget Station 0 - chang");
    Histo1D_Station_norm_in[0]->SetFillColor(8);
    Histo1D_Station_norm_in[0]->SetFillStyle(1001);
    Histo1D_Station_norm_in[0]->SetMaximum(y_maximum);
    Histo1D_Station_norm_in[0]->GetXaxis()->SetTitle("#vartheta [#circ]");
    Histo1D_Station_norm_in[0]->GetYaxis()->SetTitle("x/X_{0} [\%]");
    Histo1D_Station_norm_in[0]->GetYaxis()->SetTitleSize(0.07);
    Histo1D_Station_norm_in[0]->GetYaxis()->SetTitleOffset(0.68);
    Histo1D_Station_norm_in[0]->GetXaxis()->SetTitleSize(0.05);
    Histo1D_Station_norm_in[0]->GetXaxis()->SetTitleOffset(1);
    Histo1D_Station_norm_in[0]->GetXaxis()->SetLabelSize(0.06);
    Histo1D_Station_norm_in[0]->GetXaxis()->SetRange(0,600);
    Histo1D_Station_norm_in[0]->GetYaxis()->SetLabelSize(0.06);
    Histo1D_Station_norm_in[0]->Draw("HIST");

    Histo1D_al_cvd_si_Station_in[0]->SetFillColor(38);
    Histo1D_al_cvd_si_Station_in[0]->SetFillStyle(1001);
    Histo1D_al_cvd_si_Station_in[0]->Draw("SAME HIST");

    Histo1D_cvd_si_Station_in[0]->SetFillColor(1);
    Histo1D_cvd_si_Station_in[0]->SetFillStyle(1001);
    Histo1D_cvd_si_Station_in[0]->Draw("SAME HIST");

    Histo1D_Station_in[0][3]->SetFillColor(16);
    Histo1D_Station_in[0][3]->SetFillStyle(1001);
    Histo1D_Station_in[0][3]->Draw("SAME HIST");

    Histo1D_Station_norm_out[0]->SetFillColor(29);
    Histo1D_Station_norm_out[0]->SetFillStyle(1001);
    Histo1D_Station_norm_out[0]->Draw("SAME HIST");

    Histo1D_al_cvd_si_Station_out[0]->SetFillColor(33);
    Histo1D_al_cvd_si_Station_out[0]->SetFillStyle(1001);
    Histo1D_al_cvd_si_Station_out[0]->Draw("SAME HIST");

    Histo1D_cvd_si_Station_out[0]->SetFillColor(15);
    Histo1D_cvd_si_Station_out[0]->SetFillStyle(1001);
    Histo1D_cvd_si_Station_out[0]->Draw("SAME HIST");

    Histo1D_Station_out[0][3]->SetFillColor(18);
    Histo1D_Station_out[0][3]->SetFillStyle(1001);
    Histo1D_Station_out[0][3]->Draw("SAME HIST");

    gPad->RedrawAxis();

    TArrow* MB_limit_S0_in_out = new TArrow(1,0.3,25,0.3,0.03,"<");//former 5 to 30
    MB_limit_S0_in_out->SetAngle(60);
    MB_limit_S0_in_out->SetLineWidth(3);
    MB_limit_S0_in_out->SetLineColor(kRed);
    MB_limit_S0_in_out->Draw();

    TLine* Acceptance_S0_in_out = new TLine(25,0,25,0.7);//former 0.5
    Acceptance_S0_in_out->SetLineWidth(3);
    Acceptance_S0_in_out->SetLineStyle(2);
    Acceptance_S0_in_out->SetLineColor(kBlack);
    Acceptance_S0_in_out->Draw();

    //phi 0-2.5
//    TLine* MB_average_S0 = new TLine(0,0.225,25,0.225);

    //phi 0-360
    TLine* MB_average_S0 = new TLine(0,0.239,25,0.239);
    MB_average_S0->SetLineWidth(3);
    MB_average_S0->SetLineStyle(2);
    MB_average_S0->SetLineColor(kRed);
    MB_average_S0->Draw();

    TLegend* legendmb_S0_in_out = new TLegend(0.55,0.4,0.9,0.9);//former 0.65,0.5
    legendmb_S0_in_out->SetBorderSize(1);
    legendmb_S0_in_out->SetFillColor(0);
    legendmb_S0_in_out->SetFillStyle(1001);
    legendmb_S0_in_out->AddEntry(Histo1D_Station[0][0],"FPC","f");
    legendmb_S0_in_out->AddEntry(Histo1D_Station[0][1],"Sensors","f");
    legendmb_S0_in_out->AddEntry(Histo1D_Station[0][2],"Glue","f");
    legendmb_S0_in_out->AddEntry(Histo1D_Station[0][3],"CVD Diamant","f");
    legendmb_S0_in_out->AddEntry(Histo1D_cvd_si_Station_out[0],"Heat sink","f");
    legendmb_S0_in_out->AddEntry((TObject*)MB_limit_S0_in_out,"Material budget target value","l");
    legendmb_S0_in_out->AddEntry((TObject*)MB_average_S0,"Average material budget","l");
    legendmb_S0_in_out->AddEntry((TObject*)Acceptance_S0_in_out,"End of geometrical acceptance","l");
    legendmb_S0_in_out->Draw("HIST");

    //---- Station_1
    //acceptance distribution

    cmaterialbudget_Station1_CVD_in_out->cd();
    Histo1D_Station_norm_in[1]->SetTitle("Material Budget Station 1");
    Histo1D_Station_norm_in[1]->SetFillColor(8);
    Histo1D_Station_norm_in[1]->SetFillStyle(1001);
    Histo1D_Station_norm_in[1]->SetMaximum(y_maximum);
    Histo1D_Station_norm_in[1]->GetXaxis()->SetTitle("#vartheta [#circ]");
    Histo1D_Station_norm_in[1]->GetYaxis()->SetTitle("x/X_{0} [\%]");
    Histo1D_Station_norm_in[1]->GetYaxis()->SetTitleSize(0.07);
    Histo1D_Station_norm_in[1]->GetYaxis()->SetTitleOffset(0.68);
    Histo1D_Station_norm_in[1]->GetXaxis()->SetTitleSize(0.05);
    Histo1D_Station_norm_in[1]->GetXaxis()->SetTitleOffset(1);
    Histo1D_Station_norm_in[1]->GetXaxis()->SetLabelSize(0.06);
    Histo1D_Station_norm_in[1]->GetXaxis()->SetRange(0,600);
    Histo1D_Station_norm_in[1]->GetYaxis()->SetLabelSize(0.06);
    Histo1D_Station_norm_in[1]->Draw("HIST");

    Histo1D_al_cvd_si_Station_in[1]->SetFillColor(38);
    Histo1D_al_cvd_si_Station_in[1]->SetFillStyle(1001);
    Histo1D_al_cvd_si_Station_in[1]->Draw("SAME HIST");

    Histo1D_cvd_si_Station_in[1]->SetFillColor(1);
    Histo1D_cvd_si_Station_in[1]->SetFillStyle(1001);
    Histo1D_cvd_si_Station_in[1]->Draw("SAME HIST");

    Histo1D_Station_in[1][3]->SetFillColor(16);
    Histo1D_Station_in[1][3]->SetFillStyle(1001);
    Histo1D_Station_in[1][3]->Draw("SAME HIST");

    Histo1D_Station_norm_out[1]->SetFillColor(29);
    Histo1D_Station_norm_out[1]->SetFillStyle(1001);
    Histo1D_Station_norm_out[1]->Draw("SAME HIST");

    Histo1D_al_cvd_si_Station_out[1]->SetFillColor(33);
    Histo1D_al_cvd_si_Station_out[1]->SetFillStyle(1001);
    Histo1D_al_cvd_si_Station_out[1]->Draw("SAME HIST");

    Histo1D_cvd_si_Station_out[1]->SetFillColor(15);
    Histo1D_cvd_si_Station_out[1]->SetFillStyle(1001);
    Histo1D_cvd_si_Station_out[1]->Draw("SAME HIST");

    Histo1D_Station_out[1][3]->SetFillColor(18);
    Histo1D_Station_out[1][3]->SetFillStyle(1001);
    Histo1D_Station_out[1][3]->Draw("SAME HIST");

    gPad->RedrawAxis();

    TArrow* MB_limit_S1_in_out = new TArrow(2.5,0.5,25,0.5,0.03,"<");// former 5,30
    MB_limit_S1_in_out->SetAngle(60);
    MB_limit_S1_in_out->SetLineWidth(3);
    MB_limit_S1_in_out->SetLineColor(kRed);
    MB_limit_S1_in_out->Draw();

    TLine* Acceptance_S1_in_out = new TLine(25,0,25,0.7);
    Acceptance_S1_in_out->SetLineWidth(3);
    Acceptance_S1_in_out->SetLineStyle(2);
    Acceptance_S1_in_out->SetLineColor(kBlack);
    Acceptance_S1_in_out->Draw();

    //phi 0-2.5
//    TLine* MB_average_S1 = new TLine(0,0.288,25,0.288);

    //phi 0-360
    TLine* MB_average_S1 = new TLine(0,0.313,25,0.313);
    MB_average_S1->SetLineWidth(3);
    MB_average_S1->SetLineStyle(2);
    MB_average_S1->SetLineColor(kRed);
    MB_average_S1->Draw();

    TLegend* legendmb_S1_in_out = new TLegend(0.55,0.4,0.9,0.9); //former 0.65,0.5
    legendmb_S1_in_out->SetBorderSize(1);
    legendmb_S1_in_out->SetFillColor(0);
    legendmb_S1_in_out->SetFillStyle(1001);
    legendmb_S1_in_out->AddEntry(Histo1D_Station[1][0],"FPC","f");
    legendmb_S1_in_out->AddEntry(Histo1D_Station[1][1],"Sensors","f");
    legendmb_S1_in_out->AddEntry(Histo1D_Station[1][2],"Glue","f");
    legendmb_S1_in_out->AddEntry(Histo1D_Station[1][3],"CVD Diamant","f");
    legendmb_S1_in_out->AddEntry(Histo1D_cvd_si_Station_out[1],"Heat sink","f");
    legendmb_S1_in_out->AddEntry((TObject*)MB_limit_S1_in_out,"Material budget target value","l");
    legendmb_S1_in_out->AddEntry((TObject*)MB_average_S1,"Average material budget","l");
    legendmb_S1_in_out->AddEntry((TObject*)Acceptance_S1_in_out,"End of geometrical acceptance","l");
    legendmb_S1_in_out->Draw("HIST");

    //---- Station_2
    //acceptance distribution

    cmaterialbudget_Station2_CVD_in_out->cd();
    Histo1D_Station_norm_in[2]->SetTitle("Material Budget Station 2");
    Histo1D_Station_norm_in[2]->SetFillColor(8);
    Histo1D_al_cvd_si_Station_in[0]->SetFillStyle(1001);
    Histo1D_Station_norm_in[2]->SetMaximum(y_maximum);
    Histo1D_Station_norm_in[2]->GetXaxis()->SetTitle("#vartheta [#circ]");
    Histo1D_Station_norm_in[2]->GetYaxis()->SetTitle("x/X_{0} [\%]");
    Histo1D_Station_norm_in[2]->GetYaxis()->SetTitleSize(0.07);
    Histo1D_Station_norm_in[2]->GetYaxis()->SetTitleOffset(0.68);
    Histo1D_Station_norm_in[2]->GetXaxis()->SetTitleSize(0.05);
    Histo1D_Station_norm_in[2]->GetXaxis()->SetTitleOffset(1);
    Histo1D_Station_norm_in[2]->GetXaxis()->SetLabelSize(0.06);
    Histo1D_Station_norm_in[2]->GetXaxis()->SetRange(0,600);
    Histo1D_Station_norm_in[2]->GetYaxis()->SetLabelSize(0.06);
    Histo1D_Station_norm_in[2]->Draw("HIST");

    Histo1D_al_cvd_si_Station_in[2]->SetFillColor(38);
    Histo1D_al_cvd_si_Station_in[2]->SetFillStyle(1001);
    Histo1D_al_cvd_si_Station_in[2]->Draw("SAME HIST");

    Histo1D_cvd_si_Station_in[2]->SetFillColor(1);
    Histo1D_cvd_si_Station_in[2]->SetFillStyle(1001);
    Histo1D_cvd_si_Station_in[2]->Draw("SAME HIST");

    Histo1D_Station_in[2][3]->SetFillColor(16);
    Histo1D_Station_in[2][3]->SetFillStyle(1001);
    Histo1D_Station_in[2][3]->Draw("SAME HIST");

    Histo1D_Station_norm_out[2]->SetFillColor(29);
    Histo1D_Station_norm_out[2]->SetFillStyle(1001);
    Histo1D_Station_norm_out[2]->Draw("SAME HIST");

    Histo1D_al_cvd_si_Station_out[2]->SetFillColor(33);
    Histo1D_al_cvd_si_Station_out[2]->SetFillStyle(1001);
    Histo1D_al_cvd_si_Station_out[2]->Draw("SAME HIST");

    Histo1D_cvd_si_Station_out[2]->SetFillColor(15);
    Histo1D_cvd_si_Station_out[2]->SetFillStyle(1001);
    Histo1D_cvd_si_Station_out[2]->Draw("SAME HIST");

    Histo1D_Station_out[2][3]->SetFillColor(18);
    Histo1D_Station_out[2][3]->SetFillStyle(1001);
    Histo1D_Station_out[2][3]->Draw("SAME HIST");

    gPad->RedrawAxis();

    TArrow* MB_limit_S2_in_out = new TArrow(2.5,0.5,25,0.5,0.03,"<");
    MB_limit_S2_in_out->SetAngle(60);
    MB_limit_S2_in_out->SetLineWidth(3);
    MB_limit_S2_in_out->SetLineColor(kRed);
    MB_limit_S2_in_out->Draw();

    TLine* Acceptance_S2_in_out = new TLine(25,0,25,0.7);
    Acceptance_S2_in_out->SetLineWidth(3);
    Acceptance_S2_in_out->SetLineStyle(2);
    Acceptance_S2_in_out->SetLineColor(kBlack);
    Acceptance_S2_in_out->Draw();

    //phi 0-2.5
//    TLine* MB_average_S2 = new TLine(0,0.436,25,0.436);

    //phi 0-360
    TLine* MB_average_S2 = new TLine(0,0.468,25,0.468);
    MB_average_S2->SetLineWidth(3);
    MB_average_S2->SetLineStyle(2);
    MB_average_S2->SetLineColor(kRed);
    MB_average_S2->Draw();

    TLegend* legendmb_S2_in_out = new TLegend(0.55,0.4,0.9,0.9);  //former 0.65,0.5
    legendmb_S2_in_out->SetBorderSize(1);
    legendmb_S2_in_out->SetFillColor(0);
    legendmb_S2_in_out->SetFillStyle(1001);
    legendmb_S2_in_out->AddEntry(Histo1D_Station[2][0],"FPC","f");
    legendmb_S2_in_out->AddEntry(Histo1D_Station[2][1],"Sensors","f");
    legendmb_S2_in_out->AddEntry(Histo1D_Station[2][2],"Glue","f");
    legendmb_S2_in_out->AddEntry(Histo1D_Station[2][3],"CF-TPG-CF","f");
    legendmb_S2_in_out->AddEntry(Histo1D_cvd_si_Station_out[2],"Heat sink","f");
    legendmb_S2_in_out->AddEntry((TObject*)MB_limit_S2_in_out,"Material budget target value","l");
    legendmb_S2_in_out->AddEntry((TObject*)MB_average_S2,"Average material budget","l");
    legendmb_S2_in_out->AddEntry((TObject*)Acceptance_S2_in_out,"End of geometrical acceptance","l");
    legendmb_S2_in_out->Draw("HIST");

    //---- Station_3
    //acceptance distribution

    cmaterialbudget_Station3_CVD_in_out->cd();
    Histo1D_Station_norm_in[3]->SetTitle("Material Budget Station 3");
    Histo1D_Station_norm_in[3]->SetFillColor(8);
    Histo1D_Station_norm_in[3]->SetFillStyle(1001);
    Histo1D_Station_norm_in[3]->SetMaximum(y_maximum);
    Histo1D_Station_norm_in[3]->GetXaxis()->SetTitle("#vartheta [#circ]");
    Histo1D_Station_norm_in[3]->GetYaxis()->SetTitle("x/X_{0} [\%]");
    Histo1D_Station_norm_in[3]->GetYaxis()->SetTitleSize(0.07);
    Histo1D_Station_norm_in[3]->GetYaxis()->SetTitleOffset(0.68);
    Histo1D_Station_norm_in[3]->GetXaxis()->SetTitleSize(0.05);
    Histo1D_Station_norm_in[3]->GetXaxis()->SetTitleOffset(1);
    Histo1D_Station_norm_in[3]->GetXaxis()->SetLabelSize(0.06);
    Histo1D_Station_norm_in[3]->GetXaxis()->SetRange(0,600);
    Histo1D_Station_norm_in[3]->GetYaxis()->SetLabelSize(0.06);
    Histo1D_Station_norm_in[3]->Draw("HIST");

    Histo1D_al_cvd_si_Station_in[3]->SetFillColor(38);
    Histo1D_al_cvd_si_Station_in[3]->SetFillStyle(1001);
    Histo1D_al_cvd_si_Station_in[3]->Draw("SAME HIST");

    Histo1D_cvd_si_Station_in[3]->SetFillColor(1);
    Histo1D_cvd_si_Station_in[3]->SetFillStyle(1001);
    Histo1D_cvd_si_Station_in[3]->Draw("SAME HIST");

    Histo1D_Station_in[3][3]->SetFillColor(16);
    Histo1D_Station_in[3][3]->SetFillStyle(1001);
    Histo1D_Station_in[3][3]->Draw("SAME HIST");

    Histo1D_Station_norm_out[3]->SetFillColor(29);
    Histo1D_Station_norm_out[3]->SetFillStyle(1001);
    Histo1D_Station_norm_out[3]->Draw("SAME HIST");

    Histo1D_al_cvd_si_Station_out[3]->SetFillColor(33);
    Histo1D_al_cvd_si_Station_out[3]->SetFillStyle(1001);
    Histo1D_al_cvd_si_Station_out[3]->Draw("SAME HIST");

    Histo1D_cvd_si_Station_out[3]->SetFillColor(15);
    Histo1D_cvd_si_Station_out[3]->SetFillStyle(1001);
    Histo1D_cvd_si_Station_out[3]->Draw("SAME HIST");

    Histo1D_Station_out[3][3]->SetFillColor(18);
    Histo1D_Station_out[3][3]->SetFillStyle(1001);
    Histo1D_Station_out[3][3]->Draw("SAME HIST");

    gPad->RedrawAxis();

    TArrow* MB_limit_S3_in_out = new TArrow(2.5,0.5,25,0.5,0.03,"<");  //former 530
    MB_limit_S3_in_out->SetAngle(60);
    MB_limit_S3_in_out->SetLineWidth(3);
    MB_limit_S3_in_out->SetLineColor(kRed);
    MB_limit_S3_in_out->Draw();

    TLine* Acceptance_S3_in_out = new TLine(25,0,25,0.7);
    Acceptance_S3_in_out->SetLineWidth(3);
    Acceptance_S3_in_out->SetLineStyle(2);
    Acceptance_S3_in_out->SetLineColor(kBlack);
    Acceptance_S3_in_out->Draw();

    //phi 0-2.5
//    TLine* MB_average_S3 = new TLine(0,0.446,25,0.446);

    //phi 0-360
    TLine* MB_average_S3 = new TLine(0,0.494,25,0.494);
    MB_average_S3->SetLineWidth(3);
    MB_average_S3->SetLineStyle(2);
    MB_average_S3->SetLineColor(kRed);
    MB_average_S3->Draw();

    TLegend* legendmb_S3_in_out = new TLegend(0.55,0.4,0.9,0.9);  //former 0.65,0.5
    legendmb_S3_in_out->SetBorderSize(1);
    legendmb_S3_in_out->SetFillColor(0);
    legendmb_S3_in_out->SetFillStyle(1001);
    legendmb_S3_in_out->AddEntry(Histo1D_Station[3][0],"FPC","f");
    legendmb_S3_in_out->AddEntry(Histo1D_Station[3][1],"Sensors","f");
    legendmb_S3_in_out->AddEntry(Histo1D_Station[3][2],"Glue","f");
    legendmb_S3_in_out->AddEntry(Histo1D_Station[3][3],"CF-TPG-CF","f");
    legendmb_S3_in_out->AddEntry(Histo1D_cvd_si_Station_out[3],"Heat sink","f");
    legendmb_S3_in_out->AddEntry((TObject*)MB_limit_S3_in_out,"Material budget target value","l");
    legendmb_S3_in_out->AddEntry((TObject*)MB_average_S3,"Average material budget","l");
    legendmb_S3_in_out->AddEntry((TObject*)Acceptance_S3_in_out,"End of geometrical acceptance","l");
    legendmb_S3_in_out->Draw("HIST");



};

	

// -------------------------------------------------------------------------



// -----   Private method Reset   ------------------------------------------
void CbmMvdRadLength::Reset() {
    

}
// -------------------------------------------------------------------------  



// -----   Private method PrintParameters   --------------------------------
void CbmMvdRadLength::PrintParameters() {

}
// -------------------------------------------------------------------------  



ClassImp(CbmMvdRadLength);
