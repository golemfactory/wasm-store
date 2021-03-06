# Wasm-store
A curated list of precompiled Wasm binaries of
programs that are known to successfully work with
[Wasm sandbox](https://github.com/golemfactory/sp-wasm) in
[Golem](https://github.com/golemfactory/golem).
The list includes applications located directly in this repo,
as well as links that point to external sources.
The applications can either be in a raw, Wasm format, or (preferably) they can be augmented with a GUI/CLI for the user's convenience.
Using raw Wasm binaries implies that the user has to be able to prepare the corresponding `task.json` and the required folder structure themselves, and be able to directly connect with their Golem client (e.g., via the use of the [Golem CLI](https://github.com/golemfactory/golem-client)). 
Therefore, as such, this approach requires some technical knowledge of the Golem's internals.
See [here](https://docs.golem.network/#/Products/Brass-Beta/gWASM)
to learn how to launch a Wasm task in Golem.
The applications augmented with a GUI/CLI are naturally more user friendly,
because they handle communication with Golem node.
Having said that, there currently is no generic way of preparing such a GUI/CLI. There are some examples however. See the [g-flite](https://github.com/golemfactory/g-flite) app for instance.

The list of applications with GUI/CLI:
* [g-flite](https://github.com/golemfactory/g-flite) - text-to-speech

The list of applications with GUI/CLI that are using gwasm-runner (which is still under development, refer to [gwasm-runner](https://github.com/golemfactory/gwasm-runner) as a framework for fast gWASM applications development):
* [hello-gwasm-runner](https://github.com/golemfactory/hello-gwasm-runner) - a "hello world" style app for `gwasm-runner`
* [gudot](https://github.com/golemfactory/gudot) - PoC that uses experimental FHE to calculate regresion line
* [mandelbrot](https://github.com/golemfactory/mandelbrot) - renders fractal

The list of raw applications:
* [7-zip](7-zip) - 7-zip archiver
* [dcraw](dcraw) - raw image to tiff/ppm
* [flite](flite) - text-to-speech
* [Minimal Hamiltonian Path](MinimalHamiltonianPath) - searches for minimal Hamiltonian path in weighted directed graphs
* [SHA 1 Solver](sha1solver) - searches for collisions of sha1

## Cloning the repo
When cloning the repo, remember to set up [git-lfs](https://git-lfs.github.com) for this
repo on your machine. Usually, this can be accomplished as follows:

```
$ git clone https://github.com/golemfactory/wasm-store
$ cd wasm-store
$ git lfs install
$ git lfs pull
```

## Contributing
We welcome contributions in the form of links to precompiled Wasm binaries of
other programs. If you would like to submit such a link, do not hesitate to open a new PR.
Your repo should contain README file and license. 
If it is a raw Wasm binary, it should follow the guidelines below.
For apps augmented with GUI/CLI, the requirements are more relaxed and not set in stone, with the only must-have: good user experience :-)

## Directories structure
When contributing an application in a raw Wasm format, please make sure that the submitted link adheres to the
structure expected by Wasm task in Golem. That is, we're looking for dir structure similar
to the following

```
.
|-- task.json
|-- README.md
|-- LICENSE
|-- input_dir
|   |-- program.js
|   |-- program.wasm
|   |-- subtask1
|   |   |-- input_file_1_1
|   |   `-- input_file_1_2
|   `-- subtask2
|       |-- input_file_2_1
|       `-- input_file_2_2
`-- output_dir
    |-- subtask1
    |   |-- output_file_1_1
    |   `-- output_file_1_2
    `-- subtask2
        |-- output_file_2_1
        `-- output_file_2_2
```
where the `task.json` would consist of

```json
{
    "type": "wasm", 
    "name": "program", 
    "bid":  1,
    "subtask_timeout": "00:10:00",
    "timeout": "00:10:00",
    "options": {
        "js_name": "program.js",
        "wasm_name": "program.wasm",
        "input_dir": "<abs_path_to_the_repo>/input_dir",
        "output_dir": "<abs_path_to_the_repo>/output_dir",
        "__comment": "there are two subtasks, but there will be four jobs for the verification purpose (VbR)",
        "subtasks": {
            "subtask1": {
                "exec_args": ["arg1_1", "arg1_2"],
                "output_file_paths": ["output_file_1_1", "output_file_1_2"]
            },
            "subtask2": {
                "exec_args": ["arg2_1", "arg2_2"],
                "output_file_paths": ["output_file_2_1", "output_file_2_2"]
            }
        }
    }
}
```
For an example, see for example how [7-zip](7-zip) is set up in this repo.

Of course, if anything is unclear or you find some inconsistencies, please
do submit a new issue and we'll make sure it's sorted asap.
