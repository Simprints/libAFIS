## CAFIS -- Rewriting SourceAFIS in C

### Directory structure

`Sources/` -- C source files
`Sources/Utils/`  -- Utilities that are specific for the C implementation
`Sources/Tests/`  -- Unit tests
`Sources/Build/`  -- Object files generated after compilation
`Sources/Extraction/`, `General/`, `Matching/`, `Templates/`, ...  -- C implementation of the library. The directory structure and naming are analogous to the original C# code.

`TestData/` input data and expected output for unit tests


### Compilation

Compilation can be done using GCC and GNU make.

#### Linux

~~~
$ cd Sources
$ make cafis
~~~

Object files are created in the `Build/` directory. The library sources are compiled only but not linked.

#### Windows

Not tested but should work out of the box using Cygwin.


### Unit tests

#### Building

~~~
$ cd Sources
$ make utest
~~~

The result is an executable called `all_tests` in the `Build/` directory.

#### Running

~~~
$ cd TestData
$ ../Sources/Build/all_tests
~~~

