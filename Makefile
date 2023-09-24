CXX = g++
CXXFLAGS = -std=c++11

SRCS = ECTextViewImp.cpp ECEditorTest.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = editor

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
