dcraw
=======

A program to convert RAW photo files to viewable *\*.ppm* files.

* [Homepage](https://www.cybercom.net/~dcoffin/dcraw/)
* [Source file](https://www.cybercom.net/~dcoffin/dcraw/dcraw.c)

## Building from source

```
emcc -o dcraw.js -lm -DNODEPS     \
  -s BINARYEN_ASYNC_COMPILATION=0 \
  -s ALLOW_MEMORY_GROWTH=1        \
  dcraw.c
```

The `-DNODEPS` compilation flag disables the following features
in `dcraw` (but makes it easier to compile):
* Decoding Red camera movies.
* Decoding compressed Kodak DC120 photos and Adobe Lossy DNGs.
* Support for color profiles.
