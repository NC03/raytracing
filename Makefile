.DEFAULT_GOAL := all

CXX = clang++
CPPFLAGS = -g -Wall -Werror
CXXFLAGS = -pthread
SRC = source
BIN = bin
INCLUDE = -I$(SRC)/

SRCS = vector3d.cpp triangle.cpp texturedSphere.cpp texturedPlane.cpp \
	sphere.cpp scene.cpp ray.cpp pointLight.cpp plane.cpp color.cpp \
	checkeredSphere.cpp checkeredPlane.cpp raytracing.cpp

all: raytracing

raytracing: $(patsubst %, $(BIN)/%, $(SRCS:.cpp=.o))
	$(CXX) $(CXXFLAGS) -o raytracing $(patsubst %, $(BIN)/%, $(SRCS:.cpp=.o)) $(INCLUDE)

$(BIN)/%.o: $(SRC)/%.cpp $(SRC)/%.h 
	$(CXX) $(CPPFLAGS) -c -o $@ $< $(INCLUDE)

$(BIN)/%.o: $(SRC)/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $< $(INCLUDE)

clean:
	rm -f $(BIN)/*.o

distclean: clean
	rm -f raytracing *.scene.stream

docs: $(SRC)/*.h $(SRC)/*.cpp
	doxygen Doxyfile
	make -Clatex/

test:
	@echo $(SRCS:.cpp=.o)
	@echo $(patsubst %, $(SRC)/%, $(SRCS))
	@echo $(patsubst %, $(BIN)/%, $(SRCS:.cpp=.o))
