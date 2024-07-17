#include <G4VSensitiveDetector.hh>
#include <TH1F.h>
#include <TFile.h>
#include <TTree.h>

class SensitiveDetector : public G4VSensitiveDetector {
public:
    SensitiveDetector(const G4String& name);
    virtual ~SensitiveDetector();

    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);

private:
    TFile* file;
    TTree* tree;
    float edep;
};

