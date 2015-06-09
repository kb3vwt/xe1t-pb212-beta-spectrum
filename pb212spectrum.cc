#include "G4RunManager.hh"
#include "G4UImanager.hh"

//Project Files:
#include "chamberConstruction.hh" //Loads the X1t Geometry
#include "pbSpecPhysicsList.hh"   //Loads the Physics that we need
#include "pbSpecActionInit.hh"    //Loads our "actions"
#include "pbSpecHisto.hh"         //Loads histogram generator


int main()
{
  //Construct our Run Manager
  G4RunManager* runMan = new G4RunManager;
  //Set Required Initialization Classes
  runMan->SetUserInitialization(new chamberConstruction);
  runMan->SetUserInitialization(new pbSpecPhysicsList);
  runMan->SetUserInitialization(new pbSpecActionInit);
  
  //Initialize the Run Manager / G4 Kernel:
  runManager->Initialize();

  //Get UI Manager's pointer, set verbosity levels:
  G4UImanager* UIMan = G4UImanager::GetUIpointer();
  UIMan->ApplyCommand("/run/verbos 1");
  UIMan->ApplyCommand("/event/verbose 1");
  UIMan->ApplyCommand("/tracking/verbose 1");

  //Start Run with 'nEvents' events:
  int nEvents = 1;
  runMan->BeamOn(nEvents);

  //Terminate job:
  delete runMan;
  return 0;

}
