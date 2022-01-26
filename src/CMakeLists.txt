cmake_minimum_required (VERSION 2.8)
project(crowdSimulation)

# required for Ogre 1.11+
set(CMAKE_CXX_STANDARD 11)

## [discover_ogre]
# The COMPONENTS part checks that OGRE was built the way we need it
# The CONFIG flag makes sure we get OGRE instead of OGRE-next
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

add_executable(crowdSimulation main.cpp)
target_link_libraries(crowdSimulation OgreBites)
