# LYSO scintillator simulation (Geant4)

Geant4 simulation of a 3 x 3 x 14 cm LYSO crystal (Lu9 Y Si5 O25 composition, density 7.1 g/cm3, light yield 32,000 photons/MeV, 40 ns decay time) hit by 4 GeV positive muons. Uses EM standard, decay and optical physics; a sensitive detector records the energy deposited per event to a ROOT tree (`output.root`).

Written during my summer 2024 research placement at KEK (Japan) on the COMET experiment, to learn Geant4 scintillator simulation.

## Build and run
```
mkdir build && cd build
cmake .. && make
./LYSOSimulation        # interactive, uses vis.mac
```
Requires Geant4 (with optical physics) and ROOT.
