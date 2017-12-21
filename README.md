# Connect X

Connect X is a scallable Connect 4 application. You can choose how many players
can play, the game board dimensions and how many adjacent discs are needed for
a win.

## Build the project

Basically, `g++` is used for building Connect X. However, other program (such as
`make` or `doxygen` are used in a complete build. This section will help you
understand the build process for Connect X and guide you through the build steps.

### Supported OS

Only Ubuntu is officially supported. The program may work under other OSes, but
as of now, no OS other than Ubuntu has been officially used for testing. The
following steps assume that you work on a machine running a relatively up-to-date
version of Ubuntu.

### Prerequesties

The following software are needed to perform a complete build:

### Building

Once everything is installed, move to `cxinit` directory and copy the `init.mk`
file to the project's root directory. To do so, open a terminal and enter:

```
cp init.mk ..
```
Using your favorite text editor, open the file `init.mk` and populate the `SRC_ROOT`
and `BIN_ROOT` variables. The `SRC_ROOT` variable should hold the path to the root
directory of your copy of the Connect X repository. The `BIN_ROOT` variable should
hold the path to the directory that is going to contain all the executables produded
by the build. Once this is done, save the file and move up to the repository's root
directory:

```
cd ..
```
You should now be able to build the project:

```
make
```
Note that you can build any module of the project by feeding `make` the desired
module name. For example, if I want to build only the `cxbase` library, I can
invoke:

```
make cxbase
```
and if I want only the documentation, I can invoke:

```
make cxbasedoc
```
Refer to the repository main `Makefile` to know all the module names.