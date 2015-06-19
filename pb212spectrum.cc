#include "G4RunManager.hh"
#include "G4UImanager.hh"

//Project Files:
#include "chamberConstruction.hh"   		//Loads the X1t Geometry
#include "pbPhysicsList.hh"   				//Loads the Physics that we need
#include "pbPrimaryGeneratorAction.hh"      //Loads our primary actions
#include "pbEventAction.hh"					//Event Actions
#include "pbHisto.hh"          			    //Loads histogram generator
//#include "pbAnalysis.hh"


int main()
{
  //Construct our Run Manager
  G4RunManager* runMan = new G4RunManager;
  
  //Set Required Initialization Classes
  runMan->SetUserInitialization(new chamberConstruction);
  runMan->SetUserInitialization(new pbPhysicsList);
  runMan->SetUserInitialization(new pbPrimaryGeneratorAction);
  
  //Initialize the Run Manager / G4 Kernel:
  runMan->Initialize();

  //Get UI Manager's pointer, set verbosity levels:
  G4UImanager* UIMan = G4UImanager::GetUIpointer();
  UIMan->ApplyCommand("/run/verbos 1");
  UIMan->ApplyCommand("/event/verbose 1");
  UIMan->ApplyCommand("/tracking/verbose 1");
  
  //Set Default GPS source info
  UIMan->ApplyCommand("/");

  //Start Run with 'nEvents' events:
  int nEvents = 1;
  runMan->BeamOn(nEvents);

  //Terminate job:
  delete runMan;
  return 0;

}
