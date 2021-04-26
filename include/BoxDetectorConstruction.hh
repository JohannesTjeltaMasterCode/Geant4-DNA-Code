#ifndef BoxDetectorConstruction_h
#define BoxDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"


class G4VPhysicalVolume;
class G4LogicalVolume;

// Detector konstruksjon klasse for aa definere matrialer og geometri

class BoxDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    BoxDetectorConstruction();
    virtual ~BoxDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

    G4Region* GetTargetRegion() {return fpRegion;}

  private:

    G4Material*        fpWaterMaterial;
    G4Region*          fpRegion;

  protected:
    G4LogicalVolume* fScoringVolume;
};

#endif
