# special targets
.PHONY: clean
 
# no implicit rules
.SUFFIXES:

# définition des variables

CXX := g++
CXXFLAGS += -W -Wall -std=c++0x
SRCDIR := src
BUILDDIR := build
TARGET := bin/bs
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
INC := -I include
 
$(TARGET): $(OBJECTS)
	@echo " Linking..."
	$(CXX) $(OBJECTS) -o $(TARGET) 
 
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(INC) -c -o $@ $< $(CXXFLAGS)
	
clean:
	@echo " Cleaning..."; 
	$(RM) -r $(BUILDDIR) $(TARGET)
	
#tester:
	#$(CC) $(CFLAGS) test/tester.cpp $(INC) -o bin/tester

