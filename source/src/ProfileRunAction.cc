
#include "ProfileRunAction.hh"
#include "ProfilePrimaryGeneratorAction.hh"
#include "ProfileDetectorConstruction.hh"
#include "ProfileAnalysis.hh"
#include "UserInput.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <ctime>
#include <fstream>
#include <iostream>



ProfileRunAction::ProfileRunAction()
: G4UserRunAction(),
  fEdep(0.)
{ 
  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fEdep);


  long seeds[2];
  time_t systime = time(NULL);
  seeds[0] = (long) systime;
  seeds[1] = (long) (systime*G4UniformRand());
  G4Random::setTheSeeds(seeds);      

  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);


  UserInput input;

  analysisManager->CreateH1("dEdX","Dose Profile", 100, 0., input.GetDetThickness()/(1.*mm));
  analysisManager->CreateNtuple("ttree","ttree");
  analysisManager->CreateNtupleDColumn("StepZ");
  analysisManager->CreateNtupleDColumn("StepEDep");
  analysisManager->CreateNtupleDColumn("kineticEnergy");
  analysisManager->CreateNtupleDColumn("EventNumber");
  analysisManager->FinishNtuple();

}


ProfileRunAction::~ProfileRunAction()
{  
  delete G4AnalysisManager::Instance();  
}


void ProfileRunAction::BeginOfRunAction(const G4Run*)
{ 
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

  auto analysisManager = G4AnalysisManager::Instance();

  UserInput input;
  std::string fileName = input.GetTreeFileName();
  analysisManager->OpenFile(fileName);
}


void ProfileRunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables 
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  G4double edep  = fEdep.GetValue();

  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
  
  G4cout
     << G4endl
     << " The run consists of " << nofEvents << "events"
     << G4endl
     << " Deposited energy in the run, in scoring volume : " 
     << G4BestUnit(edep,"Energy")
     << G4endl
     << "------------------------------------------------------------"
     << G4endl;



  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}


void ProfileRunAction::AddEdep(G4double edep)
{
  fEdep  += edep;
}


