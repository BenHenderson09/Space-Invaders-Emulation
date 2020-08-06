# Space Invaders Emulation
An emulation of the original Space Invaders arcade game.

<img src="screenshots/attract_mode_home.png" width="250"> <img src="screenshots/attract_mode_demo.png" width="250"> <img src="screenshots/spaceship_flying.png" width="250">

## Details
 - Made with C++
 - Built with CMake
 - Uses a cycle accurate Intel8080 emulator I wrote 
 - Original controls are mapped to the keyboard
 - Supports all sounds
 - Dipswitches can be configured
 - Accurately timed interrupts, allowing the game to be played at the same
    speed as the original.
 
 ## Setup
 Setup is fairly simple, following the usual way of creating an executable with CMake. Run as root.
 1. `git clone https://github.com/BenHenderson09/Space-Invaders-Emulation`
 2. `mkdir -p Space-Invaders-Emulation/build && cd Space-Invaders-Emulation/build`
 3. `cmake .. && make`
 4. `./invaders`
 
 ## Dependencies
 - `Intel8080Emulator`, the emulator I wrote. It can be found [here.](https://github.com/BenHenderson09/Intel-8080-Emulator)
 - `SDL2`, used for audio and graphics.
 