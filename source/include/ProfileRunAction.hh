#ifndef ProfileRunAction_h
#define ProfileRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;


class ProfileRunAction : public G4UserRunAction
{
  public:
    ProfileRunAction();
    virtual ~ProfileRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddEdep (G4double edep); 

  private:
    G4Accumulable<G4double> fEdep;
};

#endif

