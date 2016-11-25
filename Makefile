# Target app
TARGET = app

# Sources
SRCS = $(wildcard **/*.cpp)

# Associated Objects
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

# Use clang
CXX = clang++

# Libs to load TODO: OPENGL_PATH?
LDLIBS = -lglut -lGLU -lGL -lGLEW -lm -lpthread

# C++ Flags
CXXFLAGS = -std=c++14 -Wall -O2 -g -pthread

# For linker to understand it's C++
LINK.o=$(LINK.cpp)

# Associate target app with its o file 
$(TARGET): $(OBJS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

# Autodependencies
DEPS = $(patsubst %.cpp,%.d,$(SRCS))
-include $(DEPS)
%.d: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -MM -MF $@ -MP $<

# Cleanup
clean:
	$(RM) *~ *.gch  $(TARGET) $(OBJS) $(DEPS)

.PHONY: clean
