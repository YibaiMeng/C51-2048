# C51 2048

A clone of the game [2048](https://play2048.co/main.css) on a C8051F020 MCU, using Peking University's custom development board.

# Usage

This program compiles on `sdcc`. Porting to Keil or other development boards should be not too diffcult. 

To compile, run `make` in the root directory. The output Intel hex `.ihx` file is `build/main.ihx`. 

To flash using a Silicon Lab's EC2 USB Debugger, with `ec2-new`(see [here](https://github.com/paragonRobotics/ec2-new])) being the flasher software, run `make flash`. You can probably use other flashers.

Most probably, you will be running this game on other development boards. You'll need to change the port configurations in `src/drivers/system.c`, and provide the relevent subroutines for the screen and keyboards you use. 

# Directory structure

```
src: source code
    drivers/: routines dealing with hardware components
    test/: tests 2048_core.c
    2048_core.c: game logic. Should contain (almost) no MCU dependent parts.
    2048_display.c: routines for drawing the gameboard on screen.
    game.c: main file, containing game logic
include: headers
res: resource files, and processing scripts
utils: misc scripts.
```


# License

The code is released into the public domain, with the exception of some subroutines for the tft screen and lcd screen, which are provided by professor Yang Yanjun and the vendor. The game's graphic design and the sound snippet belows to their original copyright owners respectively.
