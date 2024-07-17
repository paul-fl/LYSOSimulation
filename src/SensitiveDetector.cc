#include "SensitiveDetector.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4SystemOfUnits.hh"
#include "G4Poisson.hh"
#include "G4ios.hh"  // for G4cout

SensitiveDetector::SensitiveDetector(const G4String& name) : G4VSensitiveDetector(name) {
    G4cout << "Creating ROOT file" << G4endl;
    file = new TFile("output.root", "RECREATE");
    tree = new TTree("T", "Energy deposition");
    tree->Branch("edep", &edep, "edep/F");
}

SensitiveDetector::~SensitiveDetector() {
    G4cout << "Writing and closing ROOT file" << G4endl;
    file->Write();
    file->Close();
    delete file;
}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history) {
    edep = step->GetTotalEnergyDeposit();
    G4cout << "Filling tree with edep: " << edep << G4endl;
    tree->Fill();
    return true;
}
