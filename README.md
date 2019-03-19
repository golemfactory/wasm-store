# Wasm-store
This repo contains precompiled Wasm binaries of several open-source
programs that are known to successfully work with
[Wasm sandbox](https://github.com/golemfactory/sp-wasm) in
[Golem network](https://github.com/golemfactory/golem/tree/develop/apps/wasm).

Supported programs:
* [7-zip](7-zip) - 7-zip archiver
* [dcraw](dcraw) - raw image to tiff/ppm
* [flite](flite) - text-to-speech

## Running in Golem
Simply clone the repo, change the required paths in each `task.json`
for each respective program, and add to Golem using the CLI

```
$ golemcli create task task.json
```

## Contributing
We welcome contributions in the form of precompiled Wasm binaries of
other programs. However, please note that due to legal reasons, we
are not able to accept Wasm binaries of proprietary programs. In case
you are in doubt, GPL, LGPL, Apache, and MIT are all fine.

If you would like to submit a new Wasm binary, open a new PR.

If you find any problems with the existing binaries, feel free
to submit an issue.

## License
This repo is hosted under [GNU General Public License v3](LICENSE).