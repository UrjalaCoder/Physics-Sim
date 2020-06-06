PROGRAM = psim
OBJECT_FILES = main.o Object.o
CPP_OPTIONS = -std=c++17
SRC_FILES = ./src/main.cpp ./src/Object.cpp
GC = g++

all: $(OBJECT_FILES)
	$(GC) -o $(PROGRAM) $(OBJECT_FILES)

$(OBJECT_FILES): %.o: ./src/%.cpp
	echo $(GC) $(CPP_OPTIONS) -c $<
	$(GC) $(CPP_OPTIONS) -c $<

clean:
	rm -r $(OBJECT_FILES)

clean_all:
	rm -r $(OBJECT_FILES) $(PROGRAM)
