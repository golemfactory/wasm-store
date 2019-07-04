The program searches for minimal Hamiltonian path
in weighted directed graphs.

### Input file

The file `in.txt` contains graph. It is in the form of a table of integers with `n` rows and `n` columns. A field `(i,j)` gives the weight of the direct edge from `i`-th node to `j`-th node. Negative value means that the edge does not exists. All diagonal fields must be negative. Separator must be a single space.

### Execution and output

You should run multiple instances of the program. Each takes the same input file but different parameters. Each instance writes answer to the output file `out.txt`, so watch out to not override it. The output file contains the minimal Hamiltonian path the the instance found. In the first row is total weight of the path, in the second row are nodes in the order that forms the path. Negative total weight means that the instance did not find the path.

The expected positive output (content of the `out.txt` file) is like

```
4
0 3 1 2 4
```

### Parameters

The program takes two parameters. The first is a remainder `r`, the second is denominator `d`. The program searches all paths starting from any `i`-th node such that `i mod d = r`. So if you want to search Hamiltonian paths with parallel degree of `3`, you should run `3` instances with parameters `0 3`, `1 3`, `2 3`.

### Algoritm

The algorithm is naive. It searches all possible paths in DFS manner.

### Running

At first copy the directory `MinimalHamiltonianPath` to your local drive and go to this directory. And make sure that your Golem node is up and running.

Before running the example, edit the file `task.json` and update fields `input_dir` and `output_dir`.

If you make any changes to `mhp.c` file, do the following.

```
emcc -o mhp.js -s BINARYEN_ASYNC_COMPILATION=0 mhp.c
mv mhp.js in/
mv mhp.wasm in/
```

If you want to run the algorithm with the parallel degree of `3` for instance (3 Golem subtasks), you need to have the proper subdirectories in `in` directory and configured `task.json`. 

```
mkdir in/subtask3
cp in.txt in/subtask3/
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
        "js_name": "mhp.js",
        "wasm_name": "mhp.wasm",
        "input_dir": "/home/lukaszglen/wasm_test_5/t2/in",
        "output_dir": "/home/lukaszglen/wasm_test_5/t2/out",
        "subtasks": {
            "subtask1": {
                "exec_args": ["0", "3"],
                "output_file_paths": ["out.txt"]
            },
            "subtask2": {
                "exec_args": ["1", "3"],
                "output_file_paths": ["out.txt"]
            },
            "subtask3": {
                "exec_args": ["2", "3"],
                "output_file_paths": ["out.txt"]
            }
        }
    }
}
```

If you changed the graph in `in.txt` file, then you need to update this file in subtasks subdirectories.

```
cp in.txt in/subtask1/in.txt 
cp in.txt in/subtask2/in.txt 
cp in.txt in/subtask3/in.txt 
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

