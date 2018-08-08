#include "ProfileDetectorConstruction.hh"
#include "ProfileActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4VModularPhysicsList.hh"
#include "G4PhysListFactory.hh"

#include "G4UImanager.hh"
#include "G4StepLimiterPhysics.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"


int main(int argc,char** argv)
{

  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  runManager->SetUserInitialization(new ProfileDetectorConstruction());

  G4PhysListFactory factory;
  G4VModularPhysicsList* physicsList;
  physicsList = factory.GetReferencePhysList("FTFP_BERT");
  physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);
    
  runManager->SetUserInitialization(new ProfileActionInitialization());

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();


  G4UImanager* UImanager = G4UImanager::GetUIpointer();


  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }
  
  delete visManager;
  delete runManager;
}