//File pbEventAction.hh
//Started by J. Sheldon, June 12, 2015
//Based on code in the rdecay02 example

#ifndef pbEventAction_h
#define pbEventAction_h 1

#include "G4UserEvenAction.hh"
#include "globals.hh"

class pbEventActionMessenger;

class pbEventAction : public G4UserEventAction
{
	public:
		pbEventAction();
		rmpbEventAction();
		
		void BeginofEventAction(const G4Event* anEvent);
		void EndofEventAction(const G4Event* anEvent);
		void SetDrawFlag(G4String val) {drawFlag = val;};
		
	private:
		G4String drawFlag;
		pbEventActionMessenger* eventMessenger;
};

#endif