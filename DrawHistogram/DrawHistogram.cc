#include <TFile.h>
#include <TH1F.h>
#include <TTree.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TLorentzVector.h>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std ;

int main()
{
	//Load the data
	TFile *in  = TFile::Open("Zdrop_MC_vertex5.root") ;
	//create the new file to store the result
	TFile *out = new TFile("drop_MC_vertex5.root" , "recreate" ) ;
	TTree *ZCandidates ;
	

	TH1F *h1 = new TH1F("Mass" , "Mass" , 80 , 50. , 130. ) ;
	TH1F *h2 = new TH1F("M" , "M" , 80 , 50. , 130. ) ;
	TH1F *h3 = new TH1F("Z_drop" , "Z_drop" , 100 , 0. , 500. ) ;
	TH1F *h4 = new TH1F("Z_pT" , "Z_pT" , 100 , 0. , 500. ) ;
	TH1F *h5 = new TH1F("n_particles" , "n_particles" , 50 , 0. , 50. ) ;


	double Mass ;
	int n_particles ;
	double M ;
	double Z_pT ;
	double Z_drop ;

	h1 -> GetXaxis() -> SetTitle ( "Mass  (in GeV) " ) ;
	h1 -> GetYaxis() -> SetTitle ( "Number of Candidates " ) ; 
	h2 -> GetXaxis() -> SetTitle ( "Mass  (in GeV) " ) ;
	h2 -> GetYaxis() -> SetTitle ( "Number of Candidates " ) ; 
	h3 -> GetXaxis() -> SetTitle ( "Mass  (in GeV) " ) ;
	h3 -> GetYaxis() -> SetTitle ( "Number of Candidates " ) ; 
	h4 -> GetXaxis() -> SetTitle ( "Mass  (in GeV) " ) ;
	h4 -> GetYaxis() -> SetTitle ( "Number of Candidates " ) ; 
	h5 -> GetXaxis() -> SetTitle ( "Mass  (in GeV) " ) ;
	h5 -> GetYaxis() -> SetTitle ( "Number of Candidates " ) ; 


	//Load the data into Candidates
	in -> GetObject( "ZCandidates" , ZCandidates ) ;


        ZCandidates -> SetBranchAddress("Mass" , &Mass) ;
	ZCandidates -> SetBranchAddress("M" , &M ) ;
	ZCandidates -> SetBranchAddress("n_particles" , &n_particles ) ;
	ZCandidates -> SetBranchAddress("Z_pT" , &Z_pT ) ;
	ZCandidates -> SetBranchAddress("Z_drop" , &Z_drop ) ;


	//Loop all events
	for ( int evt = 0 ; evt < ZCandidates -> GetEntries() ; evt++ ) 
	{
		ZCandidates -> GetEntry(evt) ;

		h1 -> Fill(Mass) ;
		h2 -> Fill(M) ;
		h3 -> Fill(Z_drop) ;
		h4 -> Fill(Z_pT) ;
		h5 -> Fill(n_particles) ;
	}


	Double_t norm1 = h1 -> GetEntries() ; 
	h1 -> Scale(1/norm1) ;

	in -> Close() ;
	out -> Write() ;
	out -> Close() ;


}	
