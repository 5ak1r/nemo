CXX := g++

SRC := main.cpp \
  $(wildcard src/draw/*.cpp) \
	$(wildcard src/math/*.cpp) \
	$(wildcard src/model/*.cpp) \
	$(wildcard src/utils/*.cpp)

TARGET := main.out

$(TARGET):
	$(CXX) $(SRC) -o $(TARGET)

run:
	make && ./main.out

clean:
	rm -f $(TARGET) *.bmp