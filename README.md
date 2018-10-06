# SnackbarOS

### What is this?
Snackbar is my weekend time wasting project. Currently it targets the x86 arch but I might move to ARM later since I've 
been wanting to work on raspberry pi baremetal for a while. No promises.

## Building

### Prerequisites
* [Netwide Assembler](https://www.nasm.us/)
* genisoimage (part of [cdrtools](https://www.archlinux.org/packages/community/x86_64/cdrtools/) on Arch-linux)
* [Bochs](http://bochs.sourceforge.net/) (you can use qemu, but you'll have to configure it yourself)
* Masochist mindset

### Cross-compiler
First and foremost, you will need a cross-compiler. You can find the build instructions for it on [osdev](https://wiki.osdev.org/GCC_Cross-Compiler)
(grab some popcorn and a few gallon of soda cuz compiling a cross-compiler is one hell of a screen time journey)

<sup><sup><sup>or you can just download an existing build & show some mercy to whatever hair left on your head </sup></sup></sup>
 
### Bochs Config
All of the bochs configuration files are in the ```bochs``` folder.
Be sure to edit ```romimage``` & ```vgaimage``` paths according to your installation and OS.

The ```debug.rc``` file is used to tell bochs to continue execution instead of dropping into interactive debugger as soon as in starts.

### Make
Edit makefile and set ```BIN_DIR``` to your cross-compiler
s bin directory.
Once that's done, you can finally start building

```
make run
```

This will build the OS, do all the necessary setups and startup bochs with snackbarOS iso inserted.
You can find the OS iso, kernel elf file and all object files in the ```build``` directory once the build finishes.

**_Be aware, ```make clean``` will delete the build directory_**
### Contributing
If you value your sanity, don't. Look for better hobbies. If not then I guess we will meet in a psychiatric ward someday ~

## Authors
* Planning: Me.
* Developing: Also me.
* Testing: Hey look, its me again!

## Acknowledgement
* Hat tip to James Molly, the cool people at OSDev forum & OSDev subreddit, OSDev wiki, Erik Helin, Adam Renberg and last but not least, Brandon Fresen.


## Log
* 27/9/18: A messy hello world OS (newlines, tabs, colored text supported)
* 28/9/18: An attempt to properly structure the project. Moved ```outb```, ```inw```, ```inb``` to ```common.h```
* 29/9/18: Finally setup a i686-elf cross compiler & improve the makefile, start using gcc ```stdint.h``` instead of makeshift ```ministdint.h```
* 30/9/18: A proper README with some build instructions. More rearrangements. Moved kernel level I/O functions to ```kstdio.h```,
separated VGA methods and declarations to ```vga.h```, starting work on standard ```string.h```
* 1/10/18: Implemented ```memcpy```, ```memcmp```
* 2/10/18: Implemented ```itoa```
* 6/10/18: Implemented serial output interface. Added simple `serial_printf` for formatted debug printing 