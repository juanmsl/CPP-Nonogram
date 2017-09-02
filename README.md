# Nonogram
Project of algorithm's analisys subject, wich consist in design and develop an algorithm that resolve nonograms

## Prerequisites

To compile and excute the project all you need is to have installed OpenGL and c++ compiler, to install both of them you can use the following comands<br>
`sudo apt install freeglut3-dev` for OpenGL<br>
`sudo apt install g++` for C++ compiler

> **To compile it:** `g++ -std=c++11 *.cxx -o <Executable name> -lGL -lGLU -lglut`

> **To execute it:** `./<Executable name> <Nonogram file>`

### The nonograms files

The nonograms files follow the next template

```
<rows> <columns>
next <rows> lines
  <n> <p1> <p2> ... <pn>
next <columns> lines
  <n> <p1> <p2> ... <pn>
```
For example, the file to represent the nonogram

> ###### Nonogram 5x5
<img src="https://github.com/juanmsl/Nonogram/blob/master/Images/5x5.png" width="200px">

> ###### File for nonogram 5x5
```
5 5
1 5
1 3
1 1
2 1
1 5
2 1 1
2 2 2
2 3 1
2 2 2
2 1 1
```
