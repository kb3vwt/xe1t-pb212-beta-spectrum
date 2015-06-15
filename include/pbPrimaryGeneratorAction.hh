//pbPrimaryGeneratorAction.hh
//File Started by J. Sheldon, June 12, 2015
//Derived from rdecay02 example code

#ifndef pbPrimaryGeneratorAction_h
#define pbPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4GeneralParticleSource;
class G4Event;

class pbPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:
		pbPrimaryGeneratorAction();
		rmpbPrimaryGeneratorAction();
		void GeneratePrimaries(G4Event* anEvent);
		
	private:
		G4GeneralParticleSource* pb212ParticleSource;
		
};

#endif