The program searches for SHA1 collisions. Actually, it replaces bytes at given positions in a given file in order to get desired hash.

The core source code that calculates SHA1 (`sha1.h` and `sha1.c`) comes from [here](https://github.com/clibs/sha1)

### Input file

The input file is an input binary file.

### Execution and output

You should run multiple instances of the program. Each takes the same input file but different parameters. Each instance writes an answer to the output file, so watch out to not override it. The output file contains text. Each rows contains bytes from the region and the hash of the input file.

The expected output (content of the output file) contains rows like

```
6e -> f4103261f5ec31ae0cc057f842a80bf160c6689d
86 -> 738ebd5b459d64c8395842036e7b0a0357d4209d
```

Each byte written as hexadecimal.

### Algoritm

At the beginning there is the input file. The input parameters indicates the region. It is a sequence of byte positions in the input file. The algorithm replaces bytes in the region and calculates SHA1 hash of the file. The goal is to find such bytes in the region that the hash of the file is equal the desired hash. The desired hash is an input parameter.
It is very hard to find exact match for the hash. We weaken this condition. Instead of searching exact match, the algorithm searches for matching the given pattern. The algorithm searches for all combinations of bytes in the region such that the hash of the file matches the pattern.
The algorithm is naive. It searches all possible combinations of bytes in the region.

### Parameters

The program takes five parameters. 

The first and the second parameters are for executing algorithm in parallel. They devide combinations of bytes in the region into distinct sets and each instance of the algorithm serches its own set. The first is a remainder `r`, the second is denominator `s`. If the region is of the size one, then eligible byte `b` satisfies `b mod s = r`. If the region is of the size greater than one, then two first bytes of the region matters. They satisfy `(b1*256+b2) mod s = r`. So if you want to run algorithm with parallel degree of `3`, you should run `3` instances with parameters `0 3`, `1 3`, `2 3`.

The third and fourt parameters are starting position of the region in the file (inclusive) and ending position of the region (exclusive).

The fifth parameter is the pattern. It is from 1 to 20 bytes written as hexadecimal (so it is up to 40 chars).

The sixth parameter is the name of input file.

The seventh parameter is the name of output file. It is optional. If it is not set, then the output is written to stdout.

The example set of parameters is

```
0 2 2 3 9d inline out.txt
```

### Remarks

1. If you want to find a collision i.e. the exact match, then the pattern must contain 20 bytes.
2. If you want to find a collision, then the region must be sufficiently large. On the other hand, computational complexity of the algorithm depends expotentially on the size of the region.
3. Using not exact patterns is good for the verification purpose. It is good to set such pattern that each instance of the algorithm return some results, so it can be verified that it did the job.

### Running

At first copy the directory `sha1solver` to your local drive and go to this directory. And make sure that your Golem node is up and running.

Before running the example, edit the file `task.json` and update fields `input_dir` and `output_dir`.

If you make any changes to `sha1solver.c` file, do the following.

```
emcc sha1solver.c sha1.c -o sha1solver.js -s BINARYEN_ASYNC_COMPILATION=0 -s MEMFS_APPEND_TO_TYPED_ARRAYS=1 -s ALLOW_MEMORY_GROWTH=1
mv sha1solver.js in/
mv sha1solver.wasm in/
```

If you want to run the algorithm with the parallel degree of `3` for instance (3 Golem subtasks), you need to have the proper subdirectories in `in` directory and configured `task.json`. 

```
mkdir in/subtask3
cp infile in/subtask3/
vi task.json
```

```
{
    "type": "wasm",
    "name": "wasm",
    "bid":  "1",
    "subtask_timeout": "00:10:00",
    "timeout": "00:10:00",
    "options": {
        "js_name": "sha1solver.js",
        "wasm_name": "sha1solver.wasm",
        "input_dir": "/home/lukaszglen/wasm_test_5/sha1/in",
        "output_dir": "/home/lukaszglen/wasm_test_5/sha1/out",
        "__comment": "there are three subtasks, but there will be six jobs for the verification purpose (VbR)",
        "subtasks": {
            "subtask1": {
                "exec_args": ["0", "3", "2", "3", "9d", "infile", "out.txt"],
                "output_file_paths": ["out.txt"]
            },
            "subtask2": {
                "exec_args": ["1", "3", "2", "3", "9d", "infile", "out.txt"],
                "output_file_paths": ["out.txt"]
            },
            "subtask3": {
                "exec_args": ["2", "3", "2", "3", "9d", "infile", "out.txt"],
                "output_file_paths": ["out.txt"]
            }
        }
    }
}
```

If you changed the `infile` file, then you need to update this file in subtasks subdirectories.

```
cp infile in/subtask1/infile 
cp infile in/subtask2/infile 
cp infile in/subtask3/infile 
```

To run it simply type

```
golemcli tasks create task.json
```

If `datadir` cannot be found, then

```
golemcli tasks create task.json --datadir=/home/lukaszglen/wasm_test_5/datadir1
```

If `golemcli` cannot be found, then please read Golem docs on how to use `golemcli`.

