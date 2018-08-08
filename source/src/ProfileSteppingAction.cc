
#include "ProfileSteppingAction.hh"
#include "ProfileEventAction.hh"
#include "ProfileDetectorConstruction.hh"
#include "g4root.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"


ProfileSteppingAction::ProfileSteppingAction(ProfileEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}


ProfileSteppingAction::~ProfileSteppingAction()
{}


void ProfileSteppingAction::UserSteppingAction(const G4Step* step)
{
  auto analysisManager = G4AnalysisManager::Instance();
  
  if (!fScoringVolume) { 
    const ProfileDetectorConstruction* detectorConstruction
      = static_cast<const ProfileDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  
  G4double kinEnergy   = step->GetTrack()->GetDynamicParticle()->GetKineticEnergy();
  G4String pName       = step->GetTrack()->GetParticleDefinition()->GetParticleName();
  G4int    evtNumber   = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  if (volume != fScoringVolume) return;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  G4double z        = step->GetPostStepPoint()->GetPosition().z();

  fEventAction->AddEdep(edepStep);
  analysisManager->FillH1(0,z,edepStep);

  if(edepStep>0.){
      analysisManager->FillNtupleDColumn(0,z);
      analysisManager->FillNtupleDColumn(1,edepStep);
      analysisManager->FillNtupleDColumn(2,kinEnergy);
      analysisManager->FillNtupleDColumn(3,evtNumber);
  }

  analysisManager->AddNtupleRow();

}


