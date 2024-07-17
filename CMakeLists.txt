cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# Project name
project(LYSOSimulation)

# Find Geant4 package, with UI and Vis support
find_package(Geant4 REQUIRED ui_all vis_all)

# Find ROOT package
find_package(ROOT REQUIRED)

# Include Geant4's macros
include(${Geant4_USE_FILE})

# Include ROOT's macros
include(${ROOT_USE_FILE})

# Set the directories for header and source files
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Add the executable
add_executable(LYSOSimulation main.cc ${sources})

# Link the executable to the Geant4 and ROOT libraries
target_link_libraries(LYSOSimulation ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

# Install the executable
install(TARGETS LYSOSimulation DESTINATION bin)
