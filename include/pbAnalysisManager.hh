//Analysis Manager for Pb212 Spectrum
//Started by J. Sheldon on June 17, 2015
//Based on rdecay02 example code, provided by Geant4 collaboration


#ifndef pbAnalysisManager_h
#define pbAnalysisManager_h 1

#include "globals.hh"
#include "pbEnergyDeposition.hh"
#include <vector>

class pbHisto;
class pbAnalysisManager
{
	public:
		static pbAnalysisManager* getInstance();
		static void dispose();
		
	private:
		pbAnalysisManager();
		~pbAnalysisManager();
	
	public:
		void bookHisto();

		void BeginOfRun();
		void EndOfRun(G4int);

		void BeginOfEvent();
		void EndOfEvent();

		void AddParticle(G4double, G4double, G4double, G4double);
		void AddIsotope(G4double, G4double, G4double);
		void AddEnergy(G4double, G4double, G4double);

		void SetVerbose(G4int val) {verbose = val;};
		G4int GetVerbose() const {return verbose;};

		void SetFirstEventToDebug(G4int val) {nEvt1 = val;};
		G4int FirstEventToDebug() const {return nEvt1;};
		void SetLastEventToDebug(G4int val) {nEvt2 = val;};
		G4int LastEventToDebug() const {return nEvt2;};

		void SetMaxEnergyforHisto(G4double val) {histEMax = val;};
		G4double  GetMaxEnergyforHisto() const {return histEMax;};
		void SetMinEnergyforHisto(G4double val) {histEMin = val;};
		G4double  GetMinEnergyforHisto() const {return histEMin;};
		void SetNumBinforHisto(G4int val) {histNBin = val;};
		G4int  GeNumBinforHisto() const {return histNBin;};

		void SetThresholdEnergyforTarget(G4double val) {targetThresE = val;};
		G4double GetThresholdEnergyforTarget () const {return targetThresE;};
		void SetThresholdEnergyforDetector(G4double val) {detectorThresE = val;};
		G4double GetThresholdEnergyforDetector () const {return detectorThresE;};
		void SetPulseWidth(G4double val) {pulseWidth = val;};
		G4double GetPulseWidth () const {return pulseWidth;};
		  
	private:
		static pbAnalysisManager* fManager;
		G4int verbose;
		G4int nEvt1;
		G4int nEvt2; 

		G4double histEMax;
		G4double histEMin;
		G4int histNBin;
	
		G4double targetThresE;
		G4double detectorThresE;
		G4double pulseWidth;
		
		std::vector <pbEnergyDeposition> Edepo;
		pbHisto*  histo;
};




#endif

