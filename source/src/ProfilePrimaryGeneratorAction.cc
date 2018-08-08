#include "ProfilePrimaryGeneratorAction.hh"

#include "G4GeneralParticleSource.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4UnitsTable.hh"
#include "UserInput.hh"


ProfilePrimaryGeneratorAction::ProfilePrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  fParticleGun  = new G4ParticleGun();
  UserInput input;

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName=input.GetParticleType());
  fParticleGun->SetParticleDefinition(particle);

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(input.GetParticleEnergy());
  std::cout<<G4BestUnit(input.GetParticleEnergy(),"Energy") <<"\n";
}


ProfilePrimaryGeneratorAction::~ProfilePrimaryGeneratorAction()
{
  delete fParticleGun;
}


void ProfilePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-1.*cm));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}


