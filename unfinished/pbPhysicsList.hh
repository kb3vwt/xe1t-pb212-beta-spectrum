#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class pbPhysicsList: public G4VUserPhysicsList
{
	public:
		pbPhysicsList();
		virtual ~pbPhysicsList();
		
		void ConstructParticle();
		void ConstructProcess();
		
		void SetCuts();
	
	private:
		void ConstructDecay();
		void ConstructEM();
	
};

#endif
