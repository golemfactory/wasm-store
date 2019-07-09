It is simple hello world gWASM program. Download the `hello` directory, enter it, update paths in `task.json` file
```
        "input_dir": "/path/to/your/working/directory/hello/in",
        "output_dir": "/path/to/your/working/directory/hello/out",
```
and execute the command
```
golemcli tasks create task.json
```

If datadir cannot be found, then
```
golemcli tasks create task.json --datadir=/path/to/your/datadir
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
