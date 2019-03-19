dcraw
=======

A program to convert RAW photo files to viewable *\*.ppm* files.

* [Homepage](https://www.cybercom.net/~dcoffin/dcraw/)
* [Source file](https://www.cybercom.net/~dcoffin/dcraw/dcraw.c)

## Running in Golem
```
$ golemcli tasks create wasm-store/dcraw/task.json
```

## Running directly in sandbox
```
$ cd wasm-store/dcraw
$ wasm-sandbox -I in -O out -j dcraw.js -w dcraw.wasm -o example.ppm -- example.crw
```

Note that the output is going to be saved at `out/example.ppm`.

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
