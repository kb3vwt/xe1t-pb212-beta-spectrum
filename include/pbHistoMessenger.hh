// Copied & modified from geant4 rdecay02 Example

#ifndef pbHistoMessenger_h
#define pbHistoMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class pbHisto;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class pbHistoMessenger: public G4UImessenger
{
  public:

   pbHistoMessenger(pbHisto* );
  ~pbHistoMessenger();

   void SetNewValue(G4UIcommand* ,G4String );

  private:

   pbHisto*                  histo;
   
   G4UIdirectory*          histoDir;   
   G4UIcmdWithAString*     factoryCmd;
   G4UIcmdWithAString*     fileCmd;
   G4UIcommand*            histoCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
