TARGET=main
SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)
OBJECTS=$(SOURCES:%.cpp=%.o)

all:$(TARGET)
$(TARGET):$(OBJECTS) $(HEADERS)
	@echo "Now Generating $(TARGET) ..."
	g++-10 $(OBJECTS) -o $(TARGET)
%.o:%.cpp $(HEADERS)
	@echo "Now Compiling $< ..."
	g++-10 -I. -c $< -o $@
clean:
	rm -rf *.o