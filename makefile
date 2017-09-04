COMPILER=g++
STD_VERSION=c++11
EXECUTABLE_NAME=mono
OPENGL_FLAGS=-lGL -lGLU -lglut

all: nonogram

nonogram: *.cxx
	$(COMPILER) -std=$(STD_VERSION) *.cxx -o $(EXECUTABLE_NAME) $(OPENGL_FLAGS)

clean:
	rm $(EXECUTABLE_NAME)
