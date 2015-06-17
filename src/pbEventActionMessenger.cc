// pbEventActionMessenger.hh
// File Created by J. Sheldon.  June 17, 2015
// Based on rdecay02 example in geant4.9.4

#include "pbEventActionMessenger.hh"

#include "pbEventAction.hh"
#include "G4UIcmdWithAString.hh"
#include "globals.hh"


pbEventActionMessenger::pbEventActionMessenger(pbEventAction* EvAct)
  :eventAction(EvAct)
{
  DrawCmd = new G4UIcmdWithAString("/event/draw",this);
  DrawCmd->SetGuidance("Draw the tracks in the event");
  DrawCmd->SetGuidance("  Choice : none, charged, all (default)");
  DrawCmd->SetParameterName("choice",true);
  DrawCmd->SetDefaultValue("all");
  DrawCmd->SetCandidates("none charged all");
  DrawCmd->AvailableForStates(G4State_Idle);
}

exrdmEventActionMessenger::~pbEventActionMessenger()
{
  delete DrawCmd;
}

void pbEventActionMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
  if(command == DrawCmd)
    {eventAction->SetDrawFlag(newValue);}

}




