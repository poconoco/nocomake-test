# Prboom to be installed on the retro Linux systems

Tested on Red Hat Linux 6.0 (1999), kernel 2.2.5

## SDL

Unpack provided [SDL-1.2-main.zip](SDL-1.2-main.zip):
```
unzip SDL-1.2-main.zip
cd SDL-1.2-main
```

Configure, build and install the SDL lib.
Depending on your system capabilities and installed libraries, you can provide
different arguments to ./configure to enable output for fbdev or svga lib. By default
it will output to x11 with no (2D) acceleration.

All or the last step execute from root:
```
./configure
make
make install
```

## Prboom

Unpack provided [PRBOOM.TGZ](PRBOOM.TGZ):

```
tar -xzvf PRBOOM.TGZ
cd prboom-2.5.0
```

Configure, build and install. All or the last step execute from root:
```
./configure --disable-gl
make
make install
```

## Get WAD file

Get a WAD file you have a license for, e.g. purchase from GOG or
use your owned legal CD or floppys.

For example, hook up the Doom2 wad:

```
/usr/local/games/prboom -iwad ~/doom2.wad
```

Enjoy!
