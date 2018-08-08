#include "ProfileEventAction.hh"
#include "ProfileRunAction.hh"
#include "ProfileAnalysis.hh"


#include "G4Event.hh"
#include "G4RunManager.hh"


ProfileEventAction::ProfileEventAction(ProfileRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.)
{} 


ProfileEventAction::~ProfileEventAction()
{}


void ProfileEventAction::BeginOfEventAction(const G4Event*)
{  
  fEdep = 0.;
}


void ProfileEventAction::EndOfEventAction(const G4Event*)
{   

  fRunAction->AddEdep(fEdep);

}

