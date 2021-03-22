Test
====

This directory contains integration tests ran by the [`/utility/test.sh`](../utility/test.sh) script.
These tests are mainly for testing the generators.

Python unit tests can be found in the [`/tests`](../tests) directory.


## Execution

There are a few requirements for actually running the test suite:

 * Linux
 * Python environment
 * GCC
 * glfw
 * mingw
 * wine

Depending on future generators being added there may be more. To run the complete
suite with minimal effort you can use the [`glad-test`](https://hub.docker.com/r/dav1d/glad-test/) 
Docker image:

    docker run --rm -t -v /path/to/glad:/mnt --user $(id -u):$(id -g) dav1d/glad-test