#ifndef ProfileSteppingAction_h
#define ProfileSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class ProfileEventAction;

class G4LogicalVolume;



class ProfileSteppingAction : public G4UserSteppingAction
{
  public:
    ProfileSteppingAction(ProfileEventAction* eventAction);
    virtual ~ProfileSteppingAction();

    virtual void UserSteppingAction(const G4Step*);

  private:
    ProfileEventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
};


#endif
