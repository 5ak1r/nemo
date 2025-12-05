CXX := g++

SRC := main.cpp \
  $(wildcard src/draw/*.cpp) \
	$(wildcard src/maths/*.cpp) \
	$(wildcard src/model/*.cpp) \
	$(wildcard src/utils/*.cpp)

TARGET := a.out

$(TARGET):
	$(CXX) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)