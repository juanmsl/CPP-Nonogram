# Nonogram
Project of algorithm's analisys subject, wich consist in design and develop an algorithm that resolve nonograms. This is the full version of the project, all that implies an algorithm solution nonograms

## Prerequisites

To compile and excute the project all you need is to have installed OpenGL and c++ compiler, to install both of them you can use the following comands<br>
`sudo apt install freeglut3-dev` for OpenGL<br>
`sudo apt install g++` for C++ compiler

## Compile and execute

**To compile it:**
```
g++ -std=c++11 *.cxx -o <Executable name> -lGL -lGLU -lglut
```

Or you only have to use the makefile that the project contains

```
make
```

**To execute it:**
```
./<Executable name> <Nonogram file>
```

## The nonogram files

The nonogram files follow the next template, the two first numbers `r` and `c` represent the rows and columns or the nonogram.
Each of the next `r` lines, contains a number `n`, what is the number that each row contains, the next `n` numbers are the number of the row.
As same as rows, the next `c` lines, contains the same structure that describes each column.

```
<r> <c>
  <n1> <p1> <p2> ... <pn1>
  <n2> <p1> <p2> ... <pn2>
  <n3> <p1> <p2> ... <pn3>
  ...
  <nr> <p1> <p2> ... <pnr>
  
  <n1> <p1> <p2> ... <pn1>
  <n2> <p1> <p2> ... <pn2>
  <n3> <p1> <p2> ... <pn3>
  ...
  <nc> <p1> <p2> ... <pnc>
```
For example, the file to represent the nonogram

> ###### Nonogram 5x5
<img src="https://github.com/juanmsl/Nonogram/blob/FullGame/Images/5x5.png" width="200px">

> ###### File for nonogram 5x5
```
5 5
1 5
1 3
1 1
2 1 1
1 5
2 1 1
2 2 2
2 3 1
2 2 2
2 1 1
```
In the [Nonograms folder](https://github.com/juanmsl/Nonogram/tree/FullGame/Nonograms) are more examples of nonogram files
