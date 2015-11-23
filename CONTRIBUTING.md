# Contributing to libAFIS

## Technical requirements

libAFIS is built using the C99 version of the C Programming Language standard. All contributions to the libAFIS repository **must** be compatible with C99.

`gcc` is currently used to compile the code. However, you should avoid relying on compiler-specific functionality in your contributions.

libAFIS is compiled with the `-Wall` flag set. Any contributions to libAFIS should **not** produce any additional warnings during compilation.

Because libAFIS is designed to support embedded devices that might have hardware limitations or restrictions, memory should be allocated and deallocated carefully. Memory leaks should be avoided completely. You can use a tool like [`valgrind`](http://valgrind.org/) to check for memory leaks.

## Making a contribution

Making a contribution to libAFIS should be managed through pull requests.

- Create a branch (based off the latest version of `master`) containing your additions to libAFIS in your own fork of the repository
- Submit a pull request to the SimPrints libAFIS repository
- The libAFIS team will then review the pull request
  - This will include providing feedback on the pull request, which may include suggestions on how to change the code
- If the libAFIS team are happy with the pull request, it will be merged

- For truly small fixes you can use the, `small-fixes` branch. Please still create a Pull Request once you're done, and do not delete the branch after it is merged.

## General contribution notes

Before making a contribution, ensure you run **all of the tests**. Any pull request that causes a test to fail should be fixed before it can be considered for merging.

Make sure that your commit messages explain exactly what the associated change is.

Keep the style of your code consistent with that of the existing codebase.

### Tests

Tests are currently written using [Unity](https://github.com/ThrowTheSwitch/Unity). If you add any tests, ensure to use Unity so the testing framework is consistent.

Every new feature should include tests to verify its behaviour. In the case of bug fixes, a test should be included to test that the bug has been fixed with the change. This will ensure regressions can be found immediately if the bug is reintroduced.
