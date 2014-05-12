
# base system
SRCDIR = ../../src/

# GG scenegraph
SRCDIR_GRAPH = ../../src/graph/

# GUI
SRCDIR_GUI = ../../src/gui/

# SDL sound
SRCDIR_SDLSOUND = ../../src/sdlsound/

# CONTRIB 
SRCDIR_TINYXML = ../contrib/tinyxml/
LIBDIR_TINYXML = ../bin
LIB_TINYXML    = ../bin/libtinyxml.a

CXX = c++
CXXFLAGS = -I$(SRCDIR) -I$(SRCDIR_GRAPH) -I$(SRCDIR_GUI) -I$(SRCDIR_SDLSOUND) -I$(SRCDIR_TINYXML) -DLINUX -Wall -fPIC
LDDFLAGS = -shared 

TARGET = ../bin/libgloost.so 
TARGET_STATIC = ../bin/libgloost.a 

#
SOURCES = $(wildcard $(SRCDIR)*.cpp) $(wildcard $(SRCDIR_GRAPH)*.cpp) $(wildcard $(SRCDIR_GUI)*.cpp) $(wildcard $(SRCDIR_SDLSOUND)*.cpp)
OBJECTS = $(patsubst $(SRCDIR)%.cpp, %.o, $(SOURCES))
HEADERS = $(wildcard $(SRCDIR)*.h)


default: $(TARGET) $(TARGET_STATIC)
	@echo built $(TARGET) $(TARGET_STATIC)


$(TARGET): $(LIB_TINYXML) $(OBJECTS) $(HEADERS) Makefile
	$(CXX) $(LDDFLAGS) -o $@ $(LIBS) $(OBJECTS) $(LIB_TINYXML)

$(TARGET_STATIC): $(TARGET)
	ar rc $@ $(OBJECTS)

$(LIB_TINYXML):
	cd $(SRCDIR_TINYXML) && make

%.o: $(SRCDIR)%.cpp
	$(CXX) -c $< $(CXXFLAGS)


# rules for component directories
graph/%.o: $(SRCDIR_GRAPH)%.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $(patsubst ../../src/graph/%.cpp, graph/%.o, $<)


gui/%.o: $(SRCDIR_GUI)%.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $(patsubst ../../src/gui/%.cpp, gui/%.o, $<)


sdlsound/%.o: $(SRCDIR_SDLSOUND)%.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $(patsubst ../../src/sdlsound/%.cpp, sdlsound/%.o, $<)


clean:
	@rm -f $(OBJECTS)
	@cd $(SRCDIR_TINYXML) && make clean
	@echo cleaned

realclean: clean
	@rm -f $(TARGET) $(TARGET) *~
	@cd $(SRCDIR_TINYXML) && make realclean
	@echo realcleaned



