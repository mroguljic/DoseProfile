#include "ProfileActionInitialization.hh"
#include "ProfilePrimaryGeneratorAction.hh"
#include "ProfileRunAction.hh"
#include "ProfileEventAction.hh"
#include "ProfileSteppingAction.hh"


ProfileActionInitialization::ProfileActionInitialization()
 : G4VUserActionInitialization()
{}


ProfileActionInitialization::~ProfileActionInitialization()
{}


void ProfileActionInitialization::BuildForMaster() const
{
  ProfileRunAction* runAction = new ProfileRunAction;
  SetUserAction(runAction);
}


void ProfileActionInitialization::Build() const
{
  SetUserAction(new ProfilePrimaryGeneratorAction);

  ProfileRunAction* runAction = new ProfileRunAction;
  SetUserAction(runAction);
  
  ProfileEventAction* eventAction = new ProfileEventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new ProfileSteppingAction(eventAction));
}  

