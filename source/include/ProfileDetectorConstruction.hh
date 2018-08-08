#ifndef ProfileDetectorConstruction_h
#define ProfileDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4UserLimits;

class ProfileDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    ProfileDetectorConstruction();
    virtual ~ProfileDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }


    private:
    G4UserLimits* fStepLimit;


  protected:
    G4LogicalVolume*  fScoringVolume;
};


#endif

