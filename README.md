# Nonogram
Project of algorithm's analisys subject, wich consist in design and develop an algorithm that resolve nonograms. This is a little version of the game of Nonograms, this version have a restriction, what is that each row and column have only one number.

## Prerequisites

To compile and excute the project all you need is to have installed OpenGL and c++ compiler, to install both of them you can use the following comands<br>
`sudo apt install freeglut3-dev` for OpenGL<br>
`sudo apt install g++` for C++ compiler

## Compile and execute

**To compile it:** `g++ -std=c++11 *.cxx -o <Executable name> -lGL -lGLU -lglut`
  Or you only have to use the makefile that the project contains `make`

**To execute it:** `./<Executable name> <Nonogram file>`

## The nonogram files

The nonogram files follow the next template

```
<rows> <columns>
next <rows> lines
  <p1> <p2> <p3> ... <prows>
next <columns> lines
  <p1> <p2> <p3> ... <pcolumns>
```
For example, the file to represent the nonogram

> ###### Nonogram 5x5
<img src="https://github.com/juanmsl/Nonogram/blob/master/Images/5x5.png" width="200px">

> ###### File for nonogram 5x5
```
5 5
1 1 2 3 5
1 5 3 2 1
```
In the [Nonograms folder](https://github.com/juanmsl/Nonogram/tree/master/Nonograms) are more examples of nonogram files
