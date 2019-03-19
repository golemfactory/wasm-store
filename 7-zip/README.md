# 7-zip
A program to compress and decompress data.

* [Homepage](https://www.7-zip.org/)
* [Source code](https://sourceforge.net/projects/p7zip/files/p7zip/16.02/p7zip_16.02_src_all.tar.bz2/download)

## Running in Golem
```
$ golemcli tasks create wasm-store/7-zip/task.json
```

## Running directly in sandbox
```
$ cd wasm-store/7-zip
$ wasm-sandbox -I in -O out -j 7za.js -w 7za.wasm -o in.zip -- a in.zip in.bin
```

Note that the output is going to be saved at `out/in.zip`.

## Building from source

```
$ make CC=emcc CXX=em++
$ cd bin
$ mv 7za 7za.bc
$ emcc 7za.bc -o 7za.js             \
    -s BINARYEN_ASYNC_COMPILATION=0 \
    -s ALLOW_MEMORY_GROWTH=1        \
    -s ERROR_ON_UNDEFINED_SYMBOLS=0
```

Note that in order to compile the program with `emcc`, you need to pass
`-s ERROR_ON_UNDEFINED_SYMBOLS=0` flag to the compiler. This flag is 
required because the `getpass` symbol is missing during linking stage.
However, this also means that functionality regarding password may be restricted.
