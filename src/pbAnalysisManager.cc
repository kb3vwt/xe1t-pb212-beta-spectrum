//Analysis Manager for Pb212 Spectrum
//Started by J. Sheldon on June 17, 2015
//Based on rdecay02 example code, provided by Geant4 collaboration

#include "pbAnalysisManager.hh"
#include "G4UnitsTable.hh"
#include "pbHisto.hh"
#include "G4ProcessTable.hh"
#include "G4RadioactiveDecay.hh"
#include <fstream>

pbAnalysisManager* pbAnalysisManager::fManager = 0;

pbAnalysisManager* pbAnalysisManager::getInstance()
{
  if(!fManager) {
    fManager = new pbAnalysisManager();
  }
  return fManager;
}
void pbAnalysisManager::dispose()
{
  delete fManager;
  fManager = 0;
}

pbAnalysisManager::pbAnalysisManager() // from example, what does this actually do?
{
  verbose = 0;
  nEvt1   = -1;
  nEvt2   = -1;
  targetThresE = 10*keV;
  detectorThresE = 10*keV;
  pulseWidth = 1.*microsecond;
  histo   = new pbHisto();
  bookHisto();
}

pbAnalysisManager::~pbAnalysisManager()
{
#define HISTDELETE
#ifdef HISTDELETE
	delete histo;
#endif
}

void pbAnalysisManager::bookHisto()
{
	histEMax = 15.0*MeV;
	histEMin = 0.0*MeV;
	histNBin = 100;
	
	histo->add1D("BS01","Beta Decay Spectrum in MeV",histNBin,histEMin,histEMax,MeV);
}

void pbAnalysisManager::BeginOfRun()
{
  histo->book();
  G4cout << "pbAnalysisManager: Histograms are booked and the run has been started" << G4endl;
  G4ProcessTable *pTable = G4ProcessTable::GetProcessTable();
  G4RadioactiveDecay * rDecay = (G4RadioactiveDecay *) pTable->FindProcess("RadioactiveDecay", "GenericIon");
  if (rDecay != NULL) {
    if (!rDecay->IsAnalogueMonteCarlo()) {
      std::vector<G4RadioactivityTable*> theTables =  rDecay->GetTheRadioactivityTables();
      for (size_t i = 0 ; i < theTables.size(); i++) {
	theTables[i]->GetTheMap()->clear();
	G4cout << " Clear the radioactivity map: 0, new size = " << theTables[i]->GetTheMap()->size() << G4endl;  
      }
    }  
  }

}

void pbAnalysisManager::EndOfRun(G4int nevent)
{
  histo->save();
  G4cout << "pbAnalysisManager: Histograms have been saved!" << G4endl;

  // Output the induced radioactivities
  //   in VR mode only
  //
  G4ProcessTable *pTable = G4ProcessTable::GetProcessTable();
  G4RadioactiveDecay * rDecay = (G4RadioactiveDecay *) pTable->FindProcess("RadioactiveDecay", "GenericIon");
  if (rDecay != NULL) {
    if (!rDecay->IsAnalogueMonteCarlo()) {
      G4String fileName = histo->getFileName() + ".activity" ;
      std::ofstream outfile (fileName, std::ios::out );
      std::vector<G4RadioactivityTable*> theTables =  rDecay->GetTheRadioactivityTables();
      for (size_t i = 0 ; i < theTables.size(); i++) {
	G4double rate;
	outfile << "Radioactivities in decay window no. " << i << G4endl;
	outfile << "Z \tA \tE \tActivity (decays/window) "<< G4endl;
	map<G4ThreeVector,G4double> *aMap = theTables[i]->GetTheMap();
	map<G4ThreeVector,G4double>::iterator iter;
	for(iter=aMap->begin(); iter != aMap->end(); iter++) {
	  rate = iter->second;
	  if ( rate < 0.) rate = 0.; // statically it can be < 0. but it's unphysical
	  outfile << iter->first.x() <<"\t"<< iter->first.y() <<"\t"<< iter->first.z() << "\t" << rate/nevent << G4endl;
	}
	outfile << G4endl;
      }
      outfile.close();
    }
  }
}

void pbAnalysisManager::BeginOfEvent()
{
	Edepo.clear();
}
