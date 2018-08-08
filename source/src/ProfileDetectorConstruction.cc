#include "ProfileDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4SubtractionSolid.hh"
#include "UserInput.hh"
#include "G4UserLimits.hh"


ProfileDetectorConstruction::ProfileDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{}


ProfileDetectorConstruction::~ProfileDetectorConstruction()
{ }


G4VPhysicalVolume* ProfileDetectorConstruction::Construct()
{  
  UserInput input;
  G4NistManager* nist    = G4NistManager::Instance();
  G4bool checkOverlaps   = true;
  G4double world_sizeXY  = 50.0*cm;
  G4double world_sizeZ   = 50.0*cm;
  G4Material* world_mat  = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* silicon    = nist->FindOrBuildMaterial("G4_Si");
  G4ThreeVector origin   = G4ThreeVector(0.*cm, 0.*cm, 0.*cm);

  G4Box* solidWorld = new G4Box("World", 0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ); 
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");  
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, origin, logicWorld, "World", 0, false, 0, checkOverlaps);
                

  G4double detHz = input.GetDetThickness()/2.0;
  
  G4Box* detSolid = new G4Box("Detector", 0.5*20.0*cm, 0.5*20.0*cm, detHz); 
  G4LogicalVolume* detLogic = new G4LogicalVolume(detSolid, silicon, "Detector");  
  new G4PVPlacement(0, G4ThreeVector(0.,0.,detHz), detLogic, "Detector", logicWorld, false, 0, checkOverlaps);

  fScoringVolume = detLogic;


  G4double maxStep = 0.001*mm;
  fStepLimit = new G4UserLimits(maxStep);
  detLogic->SetUserLimits(fStepLimit);

  return physWorld;
}

