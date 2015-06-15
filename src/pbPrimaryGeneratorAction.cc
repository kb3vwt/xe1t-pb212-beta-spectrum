//pbPrimaryGeneratorAction.cc
//File Started by J. Sheldon, June 12, 2015
//Derived from rdecay02 example code

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "pbPrimaryGeneratorAction.hh"

pbPrimaryGeneratorAction::pbPrimaryGeneratorAction()
{
	pb212ParticleSource = new G4GeneralParticleSource();
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