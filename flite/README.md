flite
======

A program to convert text to speech (*TTS*).

* [Homepage](http://www.festvox.org/flite/)
* [Source code](http://www.festvox.org/flite/packed/flite-1.4/flite-1.4-release.tar.bz2)

## Compilation

```
emconfigure ./configure
```
```
emmake make
```
```
cd bin
```
```
mv flite flite.bc
```
```
emcc flite.bc -o flite.js         \
  -s BINARYEN_ASYNC_COMPILATION=0 \
  -s TOTAL_MEMORY=1073741824
```

## Invocation

```bash
./wasm-sandbox -I in -O out -j flite.js \
    -w flite.wasm -o intro.wav -- intro.txt intro.wav
```