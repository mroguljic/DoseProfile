#ifndef ProfilePrimaryGeneratorAction_h
#define ProfilePrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;


class ProfilePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    ProfilePrimaryGeneratorAction();    
    virtual ~ProfilePrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);         
  
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4ParticleGun*  fParticleGun;
};


#endif
