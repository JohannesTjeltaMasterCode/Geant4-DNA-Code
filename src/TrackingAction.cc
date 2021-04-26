

#include "TrackingAction.hh"
#include "G4Track.hh"
#include "G4VSolid.hh"
#include "G4Region.hh"
#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "G4RegionStore.hh"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackingAction::TrackingAction() :
    G4UserTrackingAction(),
    RunInitObserver(), fpTargetRegion(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackingAction::~TrackingAction()
{
    fpTargetRegion = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
    const G4ParticleDefinition* particleDefinition =
        track->GetParticleDefinition();

    if(particleDefinition == G4Electron::Definition() ||
        particleDefinition == G4Gamma::Definition())
    {
        if(fpTargetRegion == 0)
          // target region is initialized after
          //detector construction instantiation
        {
            G4Exception("TrackingAction","fpTargetRegion == 0",
                        FatalException,"No target has been found");
        }

        const G4ThreeVector& position = track->GetPosition();

        int N =  fpTargetRegion->GetNumberOfRootVolumes();
        std::vector<G4LogicalVolume*>::iterator it_logicalVolumeInRegion =
                fpTargetRegion->GetRootLogicalVolumeIterator();

        bool inside_target = false;

        for(int i = 0; i < N ; i++, it_logicalVolumeInRegion++)
        {
            EInside test_status = (*it_logicalVolumeInRegion)->GetSolid()->
                Inside(position) ;
            if(test_status == kInside)
            {
                inside_target = true;
                break;
            }
            /*
            else if (test_status == kSurface)
            {
            }
            */
        }

        if(inside_target == true)
        {
            fNParticleInTarget[particleDefinition]++;
        }
        else
        {
            fNParticleInWorld[particleDefinition]++;
        }
    }
}

void
TrackingAction::Initialize()
{
  fpTargetRegion = G4RegionStore::GetInstance()->GetRegion("Target");
}
