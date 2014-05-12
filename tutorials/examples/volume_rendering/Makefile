SRCDIR = ./
BINDIR = ../../../gnulinux/bin
INCDIR = ../../../src/
CXX = c++
CXXFLAGS = -I$(SRCDIR) -I$(INCDIR) -DLINUX -Wall
LDDFLAGS = -lGL -lGLU -lglut -lGLEW -lSDL -lSDL_image -lSDL_mixer -lgloost -L$(BINDIR)/ -Wl,-rpath,.

WDIR := $(shell cd . ; pwd)
PARENTDIR := $(shell cd .. ; pwd)

TARGETNAMETMP = $(patsubst $(PARENTDIR)/%, %, $(WDIR))
TARGETNAME = $(patsubst ' '%, %, $(TARGETNAMETMP))
TARGET := $(BINDIR)/$(TARGETNAME)


SOURCES = $(wildcard $(SRCDIR)*.cpp)
OBJECTS = $(patsubst $(SRCDIR)%.cpp, %.o, $(SOURCES))
HEADERS = $(wildcard $(SRCDIR)*.h)



default: Makefile $(TARGET)
	@echo built $(TARGET)



$(TARGET): $(OBJECTS) $(HEADERS) Makefile
	$(CXX) $(LDDFLAGS) -o $@ $(LIBS) $(OBJECTS)

%.o: $(SRCDIR)%.cpp
	$(CXX) -c $< $(CXXFLAGS)




clean:
	@rm -f $(OBJECTS)
	@echo cleaned

realclean: clean
	@rm -f $(TARGET) *~
	@echo realcleaned

cleandefault: clean
cleanDebug: clean
Debug: default
Release: default



