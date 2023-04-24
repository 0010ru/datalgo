# DatAlgo

This repository contains code written in C for learning algorithms and data structures. The repository is structured as follows:

- `data/**/*.txt`: sample input data for algorithms.
- `src/**/*.c`: implementation of manipulation algorithms, including sorting and searching.
- `src/arrays/arrays.h`: header file defining functions for array manipulation algorithms.
- `build`: zsh script defining the build system for the project.

## Building and Running

To build the binary files, navigate to the root directory of the project and run the following command:

```
$ ./build
```

To run the compiled binary, run the following command from the root directory:

```
$ ./dist/arrays/main ./data/arrays/main.txt
```
