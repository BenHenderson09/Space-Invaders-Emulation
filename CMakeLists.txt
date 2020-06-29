project(SpaceInvadersEmulation)
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Setup header files
set(HEADER_FILES
    src/GraphicalDisplay/GraphicalDisplay.hpp
    config/GraphicalDisplayConfig.hpp)

# Setup source files
set(SOURCE_FILES
    src/invaders.cpp
    src/GraphicalDisplay/GraphicalDisplay.cpp)

# Create executable
add_executable(invaders ${SOURCE_FILES} ${HEADER_FILES})

# Add dependencies
find_library(EMU Intel8080Emulator lib)
target_link_libraries(invaders LINK_PUBLIC ${EMU})

find_library(SDL SDL2 lib)
target_link_libraries(invaders LINK_PUBLIC ${SDL})