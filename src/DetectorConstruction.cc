#include "DetectorConstruction.hh"
#include "G4SDManager.hh"
#include "SensitiveDetector.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    // Define materials
    G4NistManager* nist = G4NistManager::Instance();
    
    G4Element* Lu = new G4Element("Lutetium", "Lu", 71., 174.97*g/mole);
    G4Element* Y = new G4Element("Yttrium", "Y", 39., 88.905*g/mole);
    G4Element* Si = new G4Element("Silicon", "Si", 14., 28.09*g/mole);
    G4Element* O = new G4Element("Oxygen", "O", 8., 16.00*g/mole);

    G4Material* LYSO = new G4Material("LYSO", 7.1*g/cm3, 4);
    LYSO->AddElement(Lu, 9);
    LYSO->AddElement(Y, 1);
    LYSO->AddElement(Si, 5);
    LYSO->AddElement(O, 25);

    // Define scintillator properties
    G4MaterialPropertiesTable* mptLYSO = new G4MaterialPropertiesTable();
    mptLYSO->AddConstProperty("SCINTILLATIONYIELD", 32000./MeV, true);
    mptLYSO->AddConstProperty("RESOLUTIONSCALE", 1.0, true);
    mptLYSO->AddConstProperty("FASTTIMECONSTANT", 40.*ns, true);
    LYSO->SetMaterialPropertiesTable(mptLYSO);
    
    // World
    G4double world_sizeXY = 40*cm;
    G4double world_sizeZ  = 40*cm;
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
    
    G4Box* solidWorld =    
      new G4Box("World",                       //its name
                 0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
                         
    G4LogicalVolume* logicWorld =                         
      new G4LogicalVolume(solidWorld,          //its solid
                          world_mat,           //its material
                          "World");            //its name
                                    
    G4VPhysicalVolume* physWorld = 
      new G4PVPlacement(0,                     //no rotation
                        G4ThreeVector(),       //at (0,0,0)
                        logicWorld,            //its logical volume
                        "World",               //its name
                        0,                     //its mother  volume
                        false,                 //no boolean operation
                        0,                     //copy number
                        true);                 //overlaps checking

    // Scintillator
    G4double scintillator_sizeXY = 3*cm;
    G4double scintillator_sizeZ  = 14*cm;

    G4Box* solidScintillator = new G4Box("Scintillator", 0.5*scintillator_sizeXY, 0.5*scintillator_sizeXY, 0.5*scintillator_sizeZ);
    G4LogicalVolume* logicScintillator = new G4LogicalVolume(solidScintillator, LYSO, "LogicScintillator");
    new G4PVPlacement(0, G4ThreeVector(), logicScintillator, "Scintillator", logicWorld, false, 0, true);
    
    // Visualization attributes
    G4VisAttributes* worldVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0)); // White
    worldVisAtt->SetVisibility(true);
    logicWorld->SetVisAttributes(worldVisAtt);

    G4VisAttributes* scintillatorVisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5)); // Grey
    scintillatorVisAtt->SetVisibility(true);
    scintillatorVisAtt->SetForceSolid(true); // Ensure the color covers the entire volume
    logicScintillator->SetVisAttributes(scintillatorVisAtt);

    // Create and register the sensitive detector
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    SensitiveDetector* scintillatorSD = new SensitiveDetector("ScintillatorSD");
    sdManager->AddNewDetector(scintillatorSD);
    logicScintillator->SetSensitiveDetector(scintillatorSD);

    return physWorld;
}
