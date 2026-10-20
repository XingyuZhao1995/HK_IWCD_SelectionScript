# Selection Script

Script used for IWCD event selection.

## Dependencies

ROOT.

Initialize these dependencies before install the software, example setup scripts can be found in `scripts/setup` folder.

## Installation

Standard cmake installation:
```
$ mkdir build
$ mkdir install
$ cd build
$ cmake ../ -DCMAKE_INSTALL_PREFIX=../install/
$ make install -jN
```
Once installation is done, add executable path to `PATH` so that you can run the program at any place:
```
export PATH=/path/to/package/install/bin:${PATH}
```

