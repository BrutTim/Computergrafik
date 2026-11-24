UNAME_S := $(shell uname -s)

CXX = clang++
CXXFLAGS = -std=c++11 -Wall

ifeq ($(UNAME_S),Darwin)
    CXXFLAGS += -DGL_SILENCE_DEPRECATION
    LDFLAGS = -framework OpenGL -framework GLUT
else
    CXX = g++
    LDFLAGS = -lGL -lGLU -lglut
endif

TARGET = uebung1
SRCS = main.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
