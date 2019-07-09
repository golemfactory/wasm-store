It is simple hello world gWASM program. Download the `hello` directory, enter it, update paths in `task.json` file
```
        "input_dir": "/home/lukaszglen/wasm_test_5/hello/in",
        "output_dir": "/home/lukaszglen/wasm_test_5/hello/out",
```
and execute the command
```
golemcli tasks create task.json
```

If datadir cannot be found, then
```
golemcli tasks create task.json --datadir=/home/lukaszglen/wasm_test_5/datadir1
```

If golemcli cannot be found, then please read Golem docs on how to use golemcli.

After a while check the output
```
cat out/subtask1/out.txt 
```

It should contain
```
hello world!
```
