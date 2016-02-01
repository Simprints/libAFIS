## libAFIS -- Posix port using autotools (autoconfig, automake)

The package is ready for auto-configuration. It needs to be bootstrapped in
ordrt to be available for compilation on any Posix system - at least
configuration should work (sources might not be ported, yet).

Cross-compiling stubs are also ready. It relies on the particular
auto-configured "./boot" sub-tree always providing configuration for the local
C compiler. The main tree runs under the tool chain for whatever target system
is configured, e.g. --host=x86_64-w64-mingw32 (not supported yet, though).

### tl;dr

On Debian install

	sudo -s apt-get install autoconf automake

and then run on the command line

	./Build debug
	make test

Clean up again with

	./Build clobber

### Bootstrap

Apart form the C compiler tool chain you need additional tools in order to
generate a regular distributable package that can be auto configured. Under
Debian, these tools are installed via

	sudo -s apt-get install autoconf automake libtool

which also pulls in autotools-dev automatically. In order to generate the
distributable package do

	./Build config

on the command line.

### Configuration for a distributable package

On the command line run standard code configuration and generation commands
like

	./configure
	make
	make test
	make clean
	...

You may try

	make help

which prints information about some local target extensions. There are some
short cuts available using the ./Build script. Run

	./Build 

without any options to see a help page (not all options are fully implemented.)
Do not use the "clobber" option unless you need to reset the package into
bootstrap state.

## Resetting package into bootstrap state

On the command line run

	/Build clobber

## libAFIS -- Rewriting SourceAFIS in C

[![Slack Status](https://simprints-slackin.herokuapp.com/badge.svg)](https://simprints-slackin.herokuapp.com/)
[![Build Status](https://drone.io/github.com/SimPrints/libAFIS/status.png)](https://drone.io/github.com/SimPrints/libAFIS/latest)

### Directory structure

- `Sources/` -- C source files
- `Sources/Utils/`  -- Utilities that are specific for the C implementation
- `Sources/Tests/`  -- Unit tests
- `Sources/Build/`  -- Object files generated after compilation
- `Sources/Extraction/`, `General/`, `Matching/`, `Templates/`, ...  -- C implementation of the library. The directory structure and naming are analogous to the original C# code.
- `TestData/` input data and expected output for unit tests

### Compilation

Compilation can be done using GCC and GNU make.

#### Linux

~~~
$ cd Sources
$ make -f no-makefile libafis
~~~

Object files are created in the `Build/` directory. The library sources are compiled only but not linked.

#### Mac
To get `make` and `gcc` installed run: `xcode-select --install` in a terminal window. Then the linux instructions apply.
You will need to install, `Autoconf`, `Automake` & `Libtool`. You can use this [script](https://gist.github.com/jellybeansoup/4192307). 

#### Windows

- Works out of the box using Cygwin.

### Editing

The easiest way to get up and running is with [Sublime](http://sublimetext.com/)
- You can then use [Package Control](https://packagecontrol.io/installation)
- Which will help you get [C Improved](https://packagecontrol.io/packages/C%20Improved)

### Tests
#### Unit Tests

##### Building

~~~
$ cd Sources
$ make utest
~~~

The result is an executable called `all_tests` in the `Build/` directory.

##### Running

~~~
$ Sources/Build/all_tests ../TestData
~~~

### Checking for memory leaks and other problems

#### Valgrind

You can check for memory leaks using [`valgrind`](http://valgrind.org/).

Once you've built using `make`, run the tests/program in your console, but prefix the command with the `valgrind` options like this:

~~~
$ valgrind --leak-check=full --log-file="valgrind.log" -v ./Build/all_tests ../TestData/
~~~

This will make `valgrind` run a memory check on the tests and save its result to the file `valgrind.log`. This will include the amount of `alloc`'s and `free`'s, along with information on any memory which might have leaked. It also includes the total amount of heap memory allocated while the program was running.

#### Clang scan-build

If you have `clang` installed, you can use [`scan-build`](http://clang-analyzer.llvm.org/scan-build.html) to perform static analysis on the code. It generates a html report which you can view for any problems it might have found with the code.

~~~
$ scan-build -V make libafis
~~~

This will generate a html report for you after building libAFIS and open a web browser for you with the generated report open.

#### Template Tests

There is a 'MinutiaeTestApp' inside TestData to test the exported templates with SourceAFIS.
