// Copied & Modified from geant4 rdecay02 Example

#include "pbHistoMessenger.hh"

#include <sstream>

#include "pbHisto.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

pbHistoMessenger::pbHistoMessenger(pbHisto* manager)
:histo (manager)
{
  histoDir = new G4UIdirectory("/histo/");
  histoDir->SetGuidance("histograms control");

  factoryCmd = new G4UIcmdWithAString("/histo/fileName",this);
  factoryCmd->SetGuidance("set name for the histograms file");
  factoryCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  fileCmd = new G4UIcmdWithAString("/histo/fileType",this);
  fileCmd->SetGuidance("set type (aida, hbook or root) for the histograms file");
  fileCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  histoCmd = new G4UIcommand("/histo/setHisto",this);
  histoCmd->SetGuidance("Set bining of the histo number ih :");
  histoCmd->SetGuidance("  nbBins; valMin; valMax; unit (of vmin and vmax)");
  histoCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  //
  G4UIparameter* ih = new G4UIparameter("ih",'i',false);
  ih->SetGuidance("histo number : from 0 to MaxpbHisto");
  ih->SetParameterRange("ih>=0");
  histoCmd->SetParameter(ih);
  //
  G4UIparameter* nbBins = new G4UIparameter("nbBins",'i',false);
  nbBins->SetGuidance("number of bins");
  nbBins->SetParameterRange("nbBins>0");
  histoCmd->SetParameter(nbBins);
  //
  G4UIparameter* valMin = new G4UIparameter("valMin",'d',false);
  valMin->SetGuidance("valMin, expressed in unit");
  histoCmd->SetParameter(valMin);
  //
  G4UIparameter* valMax = new G4UIparameter("valMax",'d',false);
  valMax->SetGuidance("valMax, expressed in unit");
  histoCmd->SetParameter(valMax);
  //
  G4UIparameter* unit = new G4UIparameter("unit",'s',true);
  unit->SetGuidance("if omitted, vmin and vmax are assumed dimensionless");
  unit->SetDefaultValue("none");
  histoCmd->SetParameter(unit);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

pbHistoMessenger::~pbHistoMessenger()
{
  delete fileCmd;
  delete histoCmd;
  delete factoryCmd;
  delete histoDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void pbHistoMessenger::SetNewValue(G4UIcommand* command,G4String newValues)
{
  if (command == factoryCmd)
    histo->setFileName(newValues);

  if (command == fileCmd)
    histo->setFileType(newValues);
    
  if (command == histoCmd)
   { G4int ih,nbBins; G4double vmin,vmax; char unts[30];
     const char* t = newValues;
     std::istringstream is(t);
     is >> ih >> nbBins >> vmin >> vmax >> unts;
     G4String unit = unts;
     G4double vUnit = 1. ;
     if (unit != "none") vUnit = G4UIcommand::ValueOf(unit);
     histo->setHisto1D(ih,nbBins,vmin,vmax,vUnit);
   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
