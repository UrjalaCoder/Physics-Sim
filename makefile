PROGRAM = psim
OBJECT_FILES = main.o Object.o
VISUALIZER_OBJECTS = Visualizer.o
CPP_OPTIONS = -std=c++17 
LINKER_OPTIONS = -lSDL2 -lGLEW -lGL
SRC_FILES = ./src/main.cpp ./src/Object.cpp
VISUALIZER_SRC = ./src/visualizer/Visualizer.cpp
GC = g++

all: $(OBJECT_FILES) $(VISUALIZER_OBJECTS)
	$(GC) -o $(PROGRAM) $(OBJECT_FILES) $(VISUALIZER_OBJECTS) $(LINKER_OPTIONS)

$(OBJECT_FILES): %.o: ./src/%.cpp
	$(GC) $(CPP_OPTIONS) -c $<

$(VISUALIZER_OBJECTS): %.o: ./src/visualizer/%.cpp
	$(GC) $(CPP_OPTIONS) -c $<

clean:
	rm -r $(OBJECT_FILES)
	rm -r $(VISUALIZER_OBJECTS)

clean_all:
	rm -r $(OBJECT_FILES) $(PROGRAM)
