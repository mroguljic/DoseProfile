#ifndef ProfileActionInitialization_h
#define ProfileActionInitialization_h 1

#include "G4VUserActionInitialization.hh"


class ProfileActionInitialization : public G4VUserActionInitialization
{
  public:
    ProfileActionInitialization();
    virtual ~ProfileActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif

    
