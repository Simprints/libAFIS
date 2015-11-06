## libAFIS -- Rewriting SourceAFIS in C

[![Slack Status](https://drone.io/github.com/SimPrints/libAFIS/status.png)](https://simprints-slackin.herokuapp.com/)
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
$ make libafis
~~~

Object files are created in the `Build/` directory. The library sources are compiled only but not linked.

#### Windows

- Works out of the box using Cygwin.
- You will have to add additional include directories to `\Sources` & `\Sources\Utils\Unity`
- You may have to comment out the contents of file: `\Sources\Utils\Misc\binarise.c`

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

There is a 'MinutiaeTestApp' inside TestData to test the expoted templates with SourceAFIS