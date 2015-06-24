//pbPrimaryGeneratorAction.cc
//File Started by J. Sheldon, June 12, 2015
//Derived from rdecay02 example code

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "pbPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
//#include "G4NuclideTable.hh"



pbPrimaryGeneratorAction::pbPrimaryGeneratorAction()
{
  /*
        //Configurables:
	int particleZ = 82; // Lead
	int particleA = 212; // Lead - 212
	int particleCharge = 0; // Lead ion charge in units of e
	double particleEnergy = 0.; // Energy, units of keV
	int particleCount = 275266; // Number of particles, units of particles
	G4ThreeVector particleMom = G4ThreeVector(0.,0.,0.);
	//End Configurables
	
	
	
	//Define gun
	
	//Open singlet ion table
	
	//Find ion
	
	//Set physics values
 */

  particleSource = new G4GeneralParticleSource();
}

pbPrimaryGeneratorAction::~pbPrimaryGeneratorAction()
{
	delete particleSource;
}

void pbPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	particleSource->GeneratePrimaryVertex(anEvent);
}
