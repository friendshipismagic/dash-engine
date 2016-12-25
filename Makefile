# Target app
TARGET = app

# Sources
SRCS = $(shell find Sources -name '*.cpp')

# Associated Objects
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

# Use clang
CXX = clang++

# Libs to load TODO: OPENGL_PATH?
LDLIBS = -lSDL2 -lGLU -lGL -lGLEW -lm -lpthread

# Include directory
INCDIR = -ISources \
		 -Ithirdparty/rapidjson/include \
		 -Ithirdparty/assimp/include \
		 -Ithirdparty/easylogging

# Auto-dependencies
CPPFLAGS += -MMD -MP $(INCDIR)

# C++ Flags
CXXFLAGS = -std=c++14 -Wall -O0 -g -pthread

# For linker to understand it's C++
LINK.o=$(LINK.cpp)

# Associate target app with its o file 
$(TARGET): $(OBJS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

# Autodependencies
DEPS = $(patsubst %.cpp,%.d,$(SRCS))
-include $(DEPS)

# Cleanup
clean:
	$(RM) *~ *.gch  $(TARGET) $(OBJS) $(DEPS)

.PHONY: clean
