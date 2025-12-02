CXX := g++

SRC := main.cpp \
  $(wildcard src/draw/*.cpp) \
	$(wildcard src/helpers/*.cpp) \
	$(wildcard src/maths/*.cpp) \
	$(wildcard src/model/*.cpp)

TARGET := a.out

$(TARGET):
	$(CXX) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)