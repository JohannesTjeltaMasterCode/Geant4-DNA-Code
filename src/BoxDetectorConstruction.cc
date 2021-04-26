#include "BoxDetectorConstruction.hh"

#include "G4RunManager.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4SystemOfUnits.hh"
#include "G4ProductionCuts.hh"
#include "G4Region.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4GenericMessenger.hh"


//Har null snring ka som sjer her
BoxDetectorConstruction::BoxDetectorConstruction()
: G4VUserDetectorConstruction(),
fpRegion(0),fScoringVolume(0)
  { }

//ikkje her heller
BoxDetectorConstruction::~BoxDetectorConstruction()
{ }

//konstruksjon av fysisk volume



G4VPhysicalVolume* BoxDetectorConstruction::Construct()
{
  // faa nist matrial manageren
  G4NistManager* nist =G4NistManager::Instance();

  //parameterene for mappa
  G4double env_sizeXYZ = 80*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");

  // parameterene for verden

  G4double world_sizeXYZ = 1.2*env_sizeXYZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

  //G4double target_sizeXYZ =0.5*env_sizeXYZ;
  //G4Material* target_mat = nist->FindOrBuildMaterial("G4_POLYSTYRENE");

  // splitter builder

  G4double innerRadiusW =0.*cm;
  G4double outerRadiusW =1.*cm;
  G4double lengthW =52*um;
  G4double startAngleW = 0.*deg;
  G4double spanningAngleW = 360.*deg;

  G4Material*tube_matW=nist->FindOrBuildMaterial("G4_W");


  // target builder

  G4double innerRadius =0.*cm;
  G4double outerRadius =3.*cm;
  G4double length =0.3*mm;
  G4double startAngle = 0.*deg;
  G4double spanningAngle = 365.*deg;
  G4Material*tube_mat=nist->FindOrBuildMaterial("G4_WATER");


// energy variable ring
G4double innerRadiusv =0.*cm;
G4double outerRadiusv =7.*cm;
G4double lengthv =0.*mm;
G4double startAnglev = 0.*deg;
G4double spanningAnglev = 365.*deg;


 //G4_POLYSTYRENE
  //G4cout << tube_mat;
  //
  //konstruksjon for verden
  //
  //  G4bool checkOverlaps = true;
  G4Box* solidWorld =
    new G4Box("World",                                                // navn paa verden
              0.5*world_sizeXYZ,0.5*world_sizeXYZ,0.5*world_sizeXYZ); // Storrelse paa verden

  G4LogicalVolume* logicWorld=
    new G4LogicalVolume(solidWorld,world_mat,"World");   //soliden, matreale og navnet pa logiske volumet

  G4VPhysicalVolume* physWorld =            // Den fysiske verdenen som d simuleres i
    new G4PVPlacement(0,                   // 0 betyr null rotasjon
                      G4ThreeVector(),      // Setter volumet mitt i 0,0,0 i kartesiske kordinater
                      logicWorld,           // logiske volumet til verdenen
                      "World",              // verdens navnet
                      0,                    //mor volumet
                      false,                //ikke boleanske opperatorer
                      0);       // sjekker overlapping
  //
// envilop konstruksjon

  G4Box* solidEnv =
    new G4Box("Envelope",                                                // navn paa envelope
              0.5*env_sizeXYZ,0.5*env_sizeXYZ,0.5*env_sizeXYZ);         // Storrelse paa envelope

  G4LogicalVolume* logicEnv=
    new G4LogicalVolume(solidEnv,env_mat,"Envelope");   //soliden, matreale og navnet pa logiske volumet

    new G4PVPlacement(0,                   // 0 betyr null rotasjon
                      G4ThreeVector(),      // Setter volumet mitt i 0,0,0 i kartesiske kordinater
                      logicEnv,             // logiske volumet til verdenen
                      "Envelope",           // verdens navnet
                      logicWorld,                    //mor volumet
                      false,                //ikke boleanske opperatorer
                      0);       // sjekker overlapping


// Celleskål 1/8
G4Tubs* solidTarget =
  new G4Tubs("Target",innerRadius,outerRadius,length,startAngle,spanningAngle);

G4LogicalVolume* logicTarget =
  new G4LogicalVolume(solidTarget,tube_mat,"Target");

  new G4PVPlacement(0,
                    G4ThreeVector(0,0,39.5*cm),   //38
                    logicTarget,
                    "Target",
                    logicEnv,
                    false,
                    0);
/*
G4Tubs* solidTargetv =
  new G4Tubs("enervar",innerRadiusv,outerRadiusv,lengthv,startAnglev,spanningAnglev);

G4LogicalVolume* logicTargetv =
  new G4LogicalVolume(solidTargetv,tube_mat,"enervar");

  new G4PVPlacement(0,
                  G4ThreeVector(0,0,39.2*cm),   //38
                  logicTargetv,
                  "enervar",
                  logicEnv,
                  false,
                  0);

*/


/*
G4Tubs* solidTarget2 =
  new G4Tubs("Target2",innerRadius,outerRadius,length,startAngleTar2,spanningAngleTar2);

G4LogicalVolume* logicTarget2 =
  new G4LogicalVolume(solidTarget2,tube_mat,"Target2");

  new G4PVPlacement(0,
                    G4ThreeVector(0,0,10.*cm),   //38
                    logicTarget2,
                    "Target2",
                    logicEnv,
                    false,
                        0);
*/

//TargetSensitiveDetector* sensitive = new TargetSensitiveDetector("/TargetDet");
//G4SDManager* sdManager = G4SDManager::GetSDMpointer();
//sdManager->AddNewDetector(sensitive);
//logicTarget->SetSensitiveDetector(sensitive);


//beam splitter

G4Tubs* solidSplitter =
  new G4Tubs("Splitter",innerRadiusW,outerRadiusW,lengthW,startAngleW,spanningAngleW);

G4LogicalVolume* logicSplitter =
  new G4LogicalVolume(solidSplitter,tube_matW,"Splitter");

  new G4PVPlacement(0,
                    G4ThreeVector(0,0,-39.*cm),  // -42 z
                    logicSplitter,
                    "Splitter",
                    logicEnv,
                    false,
                    0);


  fScoringVolume = logicTarget;  // setter scorevolumet til envelopen


  fpRegion = new G4Region("Target");

  G4ProductionCuts* cuts = new G4ProductionCuts();

  G4double defCut = 0.1*mm;
  cuts->SetProductionCut(defCut,"gamma");
  cuts->SetProductionCut(defCut,"e-");
  cuts->SetProductionCut(defCut,"e+");
  cuts->SetProductionCut(defCut,"proton");

  fpRegion->SetProductionCuts(cuts);
  fpRegion->AddRootLogicalVolume(logicTarget);

  return physWorld;  // returnerer den fysiske verdenen
}

//class TargetSensitiveDetector : public G4VSensitiveDetector
//{
//public:
//  TargetSensitiveDetector(G4String SDname);
//  ~TargetSensitiveDetector();

//public:
//  G4bool ProcessHits(G4Step *step,G4TouchableHistory *R0hist);
//private:

//}
