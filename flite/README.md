flite
======

A program to convert text to speech (TTS).

* [Homepage](http://www.festvox.org/flite/)
* [Source code](http://www.festvox.org/flite/packed/flite-1.4/flite-1.4-release.tar.bz2)

## Running in Golem
```
$ golemcli tasks create wasm-store/flite/task.json
```

## Running directly in sandbox
```
$ cd wasm-store/flite
$ wasm-sandbox -I in -O out -j flite.js -w flite.wasm -o intro.wav -- intro.txt intro.wav
```

Note that the output is going to be saved at `out/intro.wav`.

## Building from source

```
$ emconfigure ./configure
$ emmake make
$ cd bin
$ mv flite flite.bc
$ emcc flite.bc -o flite.js         \
    -s BINARYEN_ASYNC_COMPILATION=0 \
    -s TOTAL_MEMORY=1073741824
```
