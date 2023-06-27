# Programming Assignment 3 - Depth First Search and Strongly Connected Components of a Digraph

The file **Graph.c** has implementation of the **Graph** Data Structure with help of **List** ADT.

## Files In The Repository

1. List.c
2. Graph.c
3. Graph.h
4. FindComponents.c
5. List.h
6. GraphTest.c
7. Makefile
8. README.md


# Make commands

```
$ make clean
```

This command will make the repository clean by deleting the object file and executable file of **Graph.c**, **GraphTest.c**, **List.c** and **FindComponents.c**.


```
$ make
```

This command will just compile other C files and make the executable and object file for **GraphTest.c** and **FindComponents.c**.

## Running the program

```
$ make
```

1. This command will just compile and make the executable and object file for **GraphTest.c** and **FindComponents.c**.

```
$ ./GraphTest
```

2. This command will run the GraphTest file and show the output of Graph ADT functions.

```
$ ./FindComponents <input file> <output file>
```

3. This command will run FindPath.c and it takes **2** arguments.

## Valgrind Check

```
$ make
```

1. This command will just compile and make the executable and object file for **GraphTest.c** and **FindComponents.c**.

```
$ make checkTest
```

2. This command will show all the possible memory leaks in **GraphTest.c**.

```
$ make checkComponent
```

3. This command will show all the possible memory leaks in **FindComponents.c** (default: infile = input.txt outfile = output.txt)
