#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"

SteppingAction::SteppingAction() : G4UserSteppingAction() {}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    // Code to execute at each step
}
