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
		~pbHisto();
		
		void book(); // Creates empty histogram with set parameters
		void save(); // Saves to file
                void add1D(const G4String&, const G4String&, G4int, G4double,G4double, G4double);
		void set1DHisto(); // Reparameterizes the histogram
		void fillHisto(G4double, G4double); // Fills histogram with data
		void fillTuple(G4int, G4double); // Fills tuple with data
		void addRowToTuple(); //Adds a row to the tuple
		void setFileName(const G4String& nam); // Sets file name
		const G4String& getFileName() const;  
		const G4String& FileType() const;
	
	private:
  G4String histoName;
  G4String histoType;
  G4int defaultAct;

  G4int    nHisto;
  G4int    nTuple;
  G4int    verbose;

  TFile* hfileROOT;
  std::vector<TH1D*> ROOTHisto;
  std::vector<TNtuple*>   ROOTnTup;
  std::vector< std::vector<float> > ROOTArray;
  std::vector<G4int> ROOTCol;
  TFile* ROOTHistoFile;


  pbHistoMessenger* messenger;

  G4int     active;
  std::vector<G4int>     bins;
  G4double  xmin;
  G4double  xmax;
  G4double  x1,x2;
  G4double  unit;
  G4String  id;
  G4String  title;
  G4String  tupleName;
  G4String  tupleId;
  std::vector<G4String>  tupleList;
  std::vector<G4String>  ROOTTupleList;
  G4int nb;
  G4double u;
  
	
};
