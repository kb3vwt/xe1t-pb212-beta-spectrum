//pbPrimaryGeneratorAction.cc
//File Started by J. Sheldon, June 12, 2015
//Derived from rdecay02 example code

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "pbPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4NuclideTable.hh"

pbPrimaryGeneratorAction::pbPrimaryGeneratorAction()
{
	//Configurables:
	int particleZ = 82; // Lead
	int particleA = 212 // Lead - 212
	int particleLevel = 0;
	
	double particleEnergy = 0.;
	G4ThreeVector particleMom = G4ThreeVector(0.,0.,0.);
	//End Configurables
	
	//Define GPS:
	pb212ParticleSource = new G4GeneralParticleSource();
	
	//Open table of nuclides:
	G4NuclideTable* NuclideTable = G4NuclideTable:: GetNuclideTable();
	
	//Find particle
	G4ParticleDefinition* decayingParticle = NuclideTable->GetIsotopeByIsoLvl(particleZ,particleA,particleLevel);
	
	//Find nuclide values for Pb-212, give to GPS:
	pb212ParticleSource->SetParticleDefinition(decayingParticle)
	pb212ParticleSource->SetParticleMomentumDirection(particleMom);
	pb212ParticleSource->SetParticleEnergy(particleEnergy);
	
	
	
	pb212ParticleSource->SetParticleDefinition(beta)
}

pbPrimaryGeneratorAction::rmpbPrimaryGeneratorAction()
{
	delete pb212ParticleSource;
}

void pbPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	pb212ParticleSource->GeneratePrimaryVertex(anEvent);
}