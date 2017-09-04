CC=g++
STD=c++11
EXE=mono
SOURCES=${wildcard *.cxx}
OBJECTS=$(SOURCES:.cxx=.o)
OGL_FLAGS=-lGL -lGLU -lglut
CC_FLAGS=-c


all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	$(CC) -std=$(STD) $(OGL_FLAGS) $(OBJECTS) -o $(EXE)

%.o: %.cxx
	$(CC) -std=$(STD) $(CC_FLAGS) $< -o $@

clean:
	rm *.o $(EXE)
