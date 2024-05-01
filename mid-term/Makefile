# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Directories
SRCDIR = .
OBJDIR = obj

# Files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
HEADERS = $(wildcard $(SRCDIR)/*.h)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = bin

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) | $(dir $(EXECUTABLE))
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(dir $(EXECUTABLE)):
	mkdir -p $(dir $(EXECUTABLE))

clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)


.PHONY: all clean

