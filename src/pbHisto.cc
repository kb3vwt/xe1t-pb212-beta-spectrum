//PbHisto.cc
//Started 09 June 2015 by J. Sheldon
//Derived from exrdmHisto.cc, Geant4 example rdecay02

//Include ROOT Dependencies:
#include "TROOT.h"
#include "TApplication.h"
#include "TGClient.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TH1D.h"
#include "TNtuple.h"

//Include G4 Dependencies:
#include "G4ParticleTable.hh"
#include "G4Tokenizer.hh"

//Include Project Dependencies:
#include "pbHisto.hh"
//#include "pbHistoMessenger.hh"

pbHisto::pbHisto()
{
	histoName  = "Pb212BetaSpectrum";
	histoType  = "root";
	defaultAct = 1;
	
	//Clear ROOT variables:
	ROOTHisto.clear();
	ROOTnTup.clear();
	ROOTArray.clear();
	ROOTCol.clear();
	
	//Clear Data:
	active = 0.;
	bins.clear();
	xmin = 0.;
	xmax = 0.;
	unit = 0.;
	id = 0;
	title = "";
	tupleName = "";
	tupleId = "";
	tupleList.clear();
	ROOTTupleList.clear();
	
	//Create a new Messenger:
	messenger = new pbHistoMessenger(this);
}

pbHisto::~pbHisto()
{
	delete messenger;
}

void pbHisto::book()
{
	//Create the ROOT File
	G4String ROOTFileName = histoName + G4String(".root");
	ROOTHistoFile = new TFile(ROOTFileName.c_str(),"Remade","Pb Beta Spectrum ROOT File");
	G4cout << "**ROOT File Saved as: " << ROOTFileName << "\n";
	
	//Create a single 1D Histogram in the root of the tree:
	ROOTHisto = new TH1D(0, title, bins, xmin, xmax);
	G4cout << "**Created a 1D Histogram named '" << histoName << ".\n";

	//Create an NTuple:
	ROOTTuple = new TNtuple(0,tupleName,tupleList);
	G4cout << "**Created a ROOT NTuple named '" << tupleName << ".\n";
}

void pbHisto::save()
{
	G4cout << "Note: ROOT is writing files \n";
	ROOTHistoFile->Write();
	G4cout << "Note: ROOT is closing files \n";
	ROOTHistoFile->Close();
	
	delete ROOTHistoFile;
}

/*
void pbHisto::add1D(const G4String&,const G4String&, G4int, G4double, G4double, G4double)
{
  if(verbose > 0) {
    G4cout << "New histogram will be booked: #" << id << "  <" << name
	   << "  " << nb << "  " << x1 << "  " << x2 << "  " << u
	   << G4endl;
  }
  nHisto++;
  x1 /= u;
  x2 /= u;
  active.push_back(defaultAct);
  bins.push_back(nb);
  xmin.push_back(x1);
  xmax.push_back(x2);
  unit.push_back(u);
  id.push_back(id);
  titles.push_back(name);
  ROOThisto.push_back(0);
  
}
*/


void pbHisto::set1DHisto(G4int i, G4int nb, G4double x1, G4double x2, G4double u)
{
	bins = nb;
	xmin = x1;
	xmax = x2;
	unit = u;
	G4cout << "**Histogram Parameters SET \n";
}

void pbHisto::fillHisto(G4double x, G4double w)
{
	ROOTHisto->Fill(x/unit,w);
	G4cout << "**Histogram Filled \n";
}

void pbHisto::fillTuple(G4int col, G4double x)
{
	if(ROOTnTup)
		ROOTArray[col] = float(x); //ALERT: why float and not double? Why loose precision?
	G4cout << "**ROOT Tuple Filled \n";
}

void pbHisto::addRowToTuple()
{
	float ar[4];
	for (G4int i=0; i<ROOTCol;i++)
		ar[i] = ROOTArray[i];
	
	if(ROOTnTup)
		ROOTnTup->Fill(ar);
}

void pbHisto::setFileName(const G4String& nam)
{
	histoName = nam;
}

const G4String& pbHisto::getFileName()
{
	return histoName;
}

const G4String& pbHisto::FileType()
{
	return histoType;
}
