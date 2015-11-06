## Data Files for Unit Tests

This directory contains data files for unit tests. Each unit test has some *input* data and some *expected* output which is generated using the original C# code. When a unit test is executed it generates some *actual* output from the input data. Then the actual output is compared to the expected output to determine if the unit test passed or failed. Each unit test can be run several times using different input data. Test data is organised in a directory structure that matches the organisation of source code modules.

Test data is saved in binary files using the following naming pattern.

* for input data: `nxxx_dy_in.dat`,
* for expected output: `nxxx_dy_exp.dat`,

where *xxx* is the serial number of test for the current module, *y* is the serial number of data (input or output) for the component under test.

For example the the `LocalHistogram_Analyze()` function has two input parameters and returns one object:

~~~
Int16Array3D LocalHistogram_Analyze(const BlockMap *blocks, const UInt8Array2D *image);
~~~

Therefore, a unit test for this function uses the following three data files: `n001_d1_in.dat`, `n001_d2_in.dat` and `n001_d1_exp.dat` representing a `BlockMap`, a `UInt8Array2D` and a `Int16Array3D` object respectively.

### Manually extracted minutiae
This folder contains minutiae that have been extracted by eye in order to be able to test against what is hopefully a full perfect (no false) set of minutiae.  There is a xlst template file that you can enter minutiae details into that will generate the hex for the ISO template.
