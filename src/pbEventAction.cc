//File pbEventAction.cc
//Started by J. Sheldon, June 12, 2015
//Based on code in the rdecay02 example

#include "G4ios.hh"
//#include "pbEventActionMessenger.hh"
#include "pbEventAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UImanager.hh"
#include "G4UnitsTable.hh"
//#include "pbAnalysisManager.hh"

extern G4bool drawEvent;

pbEventAction::pbEventAction() : drawFlag("all")
{
  eventMessenger = new pbEventActionMessenger(this);
}

pbEventAction::~pbEventAction()
{
  delete eventMessenger;
}

void pbEventAction::BeginOfEventAction(const G4Event* )
{
  pbAnalysisManager::getInstance()->BeginOfEvent();
}

void pbEventAction::EndOfEventAction(const G4Event*)
{
  pbAnalysisManager::getInstance()->EndOfEvent();
}
