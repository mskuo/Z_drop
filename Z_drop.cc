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
	TFile *in = TFile::Open("../Rootfile/myfile_MC_2million.root");
	//create the new file to store the result
	TFile *out = new TFile("Zdrop.root" , "recreate" ) ;
	TTree *Candidates ;
	TTree *outtree = new TTree("ZCandidates" , "ZCandidates" ) ;

	//Load the data into Candidates
	in -> GetObject( "Candidates" , Candidates ) ;
        int nparticles ;
	int type[3000] ;
	int charge[3000] ;
        double e[3000] , px[3000], py[3000], pz[3000], pt[3000], eta[3000], phi[3000] ;
 
	int nvertex ;
//	double s_electron ;
	double Mass ;
	int n_particles ;

	double M ;
	double Z_pT ;
	double Z_drop ;

//	double Pt_plus ;
//	double Pt_minus ;

	//output branch
	outtree -> Branch ("Mass" , &Mass , "Mass/D" ) ;
	outtree -> Branch ("n_particles" , &n_particles , "n_particles/I" ) ;
	outtree -> Branch ("Z_drop" , &Z_drop , "Z_drop/D" ) ;	
	outtree -> Branch ("Z_pT" , &Z_pT , "Z_pT/D" ) ;
	outtree -> Branch ("M" , &M , "M/D" ) ;

	//For particles
	TLorentzVector LV_particles_variables ; 
	vector<TLorentzVector> LV_particles ;

	//For muons
	TLorentzVector LV_dimuon ; 
	vector<TLorentzVector> LV_muon_plus ;
	vector<TLorentzVector> LV_muon_minus ;

	//For electrons
	TLorentzVector LV_dielectron ; 
	vector<TLorentzVector> LV_electron_plus ;
	vector<TLorentzVector> LV_electron_minus ;


	TLorentzVector LV_jet ;

        Candidates -> SetBranchAddress("nparticles" , &nparticles) ;
	Candidates -> SetBranchAddress("type" , type ) ;
	Candidates -> SetBranchAddress("charge" , charge ) ;
	Candidates -> SetBranchAddress("e" , e ) ;
	Candidates -> SetBranchAddress("px" , px ) ;
	Candidates -> SetBranchAddress("py" , py ) ;
	Candidates -> SetBranchAddress("pz" , pz ) ;
	Candidates -> SetBranchAddress("pt" , pt ) ;
	Candidates -> SetBranchAddress("eta" , eta ) ;
	Candidates -> SetBranchAddress("phi" , phi ) ;
	Candidates -> SetBranchAddress("nvertex" , &nvertex ) ;

	//Loop all events
	for ( int evt = 0 ; evt < Candidates -> GetEntries() ; evt++ ) 
	//Loop 1000000 events
//	for ( int evt = 0 ; evt < 30000 ; evt++ ) 
	{
		Candidates -> GetEntry(evt) ;

//	if ( nvertex > 5 ) { continue ; } 

		LV_particles.clear() ;
		LV_muon_plus.clear() ;
		LV_muon_minus.clear() ;

		LV_electron_plus.clear() ;
		LV_electron_minus.clear() ;


		//Loop for all particles in an event
		for ( int i = 0 ; i < nparticles ; i++ ) 
		{
			LV_particles_variables.SetPxPyPzE  ( px[i] , py[i] , pz[i] , e[i] ) ; 
	
			if ( type[i] == 3 )
			{
				if ( pt[i] > 30. && eta[i] < 1.4 )
				{
					if ( charge[i] == 1 )
					{
						LV_muon_plus.push_back ( LV_particles_variables ) ;	
					}
	
					if ( charge[i] == -1 )
					{
						LV_muon_minus.push_back ( LV_particles_variables ) ;	
					}
				}
			}

			else if ( type[i] == 2 )
			{
				if ( pt[i] > 30. && eta[i] < 1.4 )
				{
					if ( charge[i] == 1 )
					{
						LV_electron_plus.push_back ( LV_particles_variables ) ;	
//						c_e_plus++ ;
					}
	
					if ( charge[i] == -1 )
					{
						LV_electron_minus.push_back ( LV_particles_variables ) ;	
//						c_e_minus++ ;
					}
				}
			}


			else
			{
				LV_particles.push_back ( LV_particles_variables ) ;		
			}	


		}


		for ( int i = 0 ; i < int(LV_muon_plus.size() ) ; i++ )
		{
			for ( int j = 0 ; j < int(LV_muon_minus.size() ) ; j++ )
			{
				//Z_drop
				//isolated
//				Pt_plus = 0. ;
//				Pt_minus = 0. ;
				n_particles = 0 ;
				Mass = 0. ;
				LV_jet = TLorentzVector( 0. , 0. , 0. , 0. ) ;
				M = 0. ;
				Z_pT = 0. ;

//				for ( int k = 0 ; k < int(LV_particles.size() ) ; k++ )
//				{
//					//If deltaR < .... , pt_all / pt_muon 
//					if ( LV_muon_plus[i].DeltaR(LV_particles[k] ) < 0.8 ) 
//					{
//						Pt_plus +=LV_particles[k].Pt() ;
//						LV_jet += LV_particles[k] ;
//					}
//					if ( LV_muon_minus[j].DeltaR(LV_particles[k] ) < 0.8 ) 
//					{
//						Pt_minus +=LV_particles[k].Pt() ;
//						LV_jet += LV_particles[k] ;
//					}
//						
//				}
				
//				Pt_plus = LV_muon_plus[i].Pt() / Pt_plus ;
//				Pt_minus = LV_muon_minus[j].Pt() / Pt_minus;
//				cout << "Pt_plus = " << Pt_plus << endl ;
//				cout << "Pt_minus = " << Pt_minus << endl ;

//				if ( Pt_plus < 0.3 && Pt_minus < 0.3 ) 
//				{
				LV_dimuon = LV_muon_plus[i] + LV_muon_minus[j] ;
				Mass = LV_dimuon.M() ;
				Z_pT = LV_dimuon.Pt() ;

				//select events near mass = 91.2eV
				for ( int k = 0 ; k < int(LV_particles.size() ) ; k++ )
				{
					if ( LV_dimuon.DeltaR(LV_particles[k] ) < 0.8 )
					{
						LV_jet += LV_particles[k] ;
						n_particles++ ;
					}
				}
				LV_jet += LV_dimuon ;
				M = LV_jet.M() ;
				Z_drop = ( pow(M,2) - pow(Mass,2) ) / (2*Z_pT) ;

//				cout << "M = " << M << endl ;
//				cout << "Mass = " << Mass << endl ;
//				cout << "Z_drop = " << Z_drop << endl << endl ;
				
				outtree -> Fill() ;


//				}		
			}
		}

//		for ( int i = 0 ; i < int(LV_electron_plus.size() ) ; i++ )
//		{
//			for ( int j = 0 ; j < int(LV_electron_minus.size() ) ; j++ )
//			{
//				LV_dielectron = LV_electron_plus[i] + LV_electron_minus[j] ;
//				s_electron = LV_dielectron.M() ;
//				h2 -> Fill(s_electron) ;		 
//			}
//		}
	cout << "Complete " <<  evt << "th event in " << Candidates -> GetEntries() << "events. " << endl ;  
	}
		LV_particles.clear() ;
		LV_muon_plus.clear() ;
		LV_muon_minus.clear() ;

		LV_electron_plus.clear() ;
		LV_electron_minus.clear() ;

	in -> Close() ;
	out -> Write() ;
	out -> Close() ;
}	
