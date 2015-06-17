//PbHisto.hh
//Started 09 June 2015 by J. Sheldon
//Derived from exrdmHisto.hh, Geant4 example rdecay02

#include "globals.hh"
#include <vector>

class TFile;
class TH1D;
class TNtuple;

class pbHistoMessenger;

class pbHisto
{
	public:
	
		pbHisto();
		rmpbHisto();
		
		void book(); // Creates empty histogram with set parameters
		void save(); // Saves to file
		void set1DHisto(); // Reparameterizes the histogram
		void fillHisto(G4double, G4double); // Fills histogram with data
		void fillTuple(G4int, G4double); // Fills tuple with data
		void addRowToTuple(); //Adds a row to the tuple
		void setFileName(const G4String& nam); // Sets file name
		const G4String& getFileName() const;  
		const G4String& FileType() const;
	
	private:
		
		
	
}