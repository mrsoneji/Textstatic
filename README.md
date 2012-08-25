Textstatic
==========

A non distractive-free text editor

Compiling:
----------

g++ main.cpp -o main -lguichan_sdl -lguichan -lSDL_image -L/usr/lib/x86_64-linux-gnu -lSDL
-I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -lSDL_mixer
