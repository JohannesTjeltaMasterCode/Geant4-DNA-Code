//#ifndef BoxPrimaryGeneratorAction_h
//#define BoxPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"


class G4ParticleGun;
class G4Event;
class G4Box;

class BoxPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    BoxPrimaryGeneratorAction();
    virtual ~BoxPrimaryGeneratorAction();

    //Metode fra baseklassene
    virtual void GeneratePrimaries(G4Event*);

    // metode for å komme til partikkel gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

  private:
    G4ParticleGun* fParticleGun;
    G4Box* fEnvelopeBox;
};
