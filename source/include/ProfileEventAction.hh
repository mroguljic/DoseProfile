#ifndef ProfileEventAction_h
#define ProfileEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class ProfileRunAction;

class ProfileEventAction : public G4UserEventAction
{
  public:
    ProfileEventAction(ProfileRunAction* runAction);
    virtual ~ProfileEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep){ fEdep += edep; }
  private:
    ProfileRunAction* fRunAction;
    G4double     fEdep;
};


#endif

    
