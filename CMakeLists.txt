project(SpaceInvadersEmulation)
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Setup header files
set(HEADER_FILES
    src/GraphicalDisplay/GraphicalDisplay.hpp
    config/GraphicalDisplayConfig.hpp
    src/InteractiveDevice/InteractiveDevice.hpp
    src/Dipswitches/Dipswitches.hpp
    src/Dipswitch/Dipswitch.hpp
    src/SingleBitDipswitch/SingleBitDipswitch.hpp
    src/TwoBitDipswitch/TwoBitDipswitch.hpp
    src/ShiftRegister/ShiftRegister.hpp
    src/KeypressHandler/KeypressHandler.hpp)

# Setup source files
set(SOURCE_FILES
    src/invaders.cpp
    src/GraphicalDisplay/GraphicalDisplay.cpp
    src/InteractiveDevice/InteractiveDevice.cpp
    src/Dipswitch/Dipswitch.cpp
    src/SingleBitDipswitch/SingleBitDipswitch.cpp
    src/TwoBitDipswitch/TwoBitDipswitch.cpp
    src/ShiftRegister/ShiftRegister.cpp
    src/KeypressHandler/KeypressHandler.cpp)

# Create executable
add_executable(invaders ${SOURCE_FILES} ${HEADER_FILES})

# Add dependencies
find_package(Threads REQUIRED)
target_link_libraries(invaders LINK_PUBLIC Threads::Threads)

find_library(EMU Intel8080Emulator lib)
target_link_libraries(invaders LINK_PUBLIC ${EMU})

find_library(SDL SDL2 lib)
target_link_libraries(invaders LINK_PUBLIC ${SDL})