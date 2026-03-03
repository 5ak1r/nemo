CXX := g++

SRC := main.cpp \
  $(wildcard external/*.c*) \
  $(wildcard src/graphics/*.cpp) \
  $(wildcard src/io/*.cpp) \
	$(wildcard src/math/*.cpp) \
	$(wildcard src/model/*.cpp) \
	$(wildcard src/utils/*.cpp)

TARGET := main.out

$(TARGET):
	$(CXX) $(SRC) -o $(TARGET) $(shell pkg-config --libs glfw3)

run:
	make && ./main.out

clean:
	rm -f $(TARGET) *.bmp