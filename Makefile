TARGET=libhybridsim_sst.so
HYBRID_PATH=../HybridSim
CXXFLAGS=-m64 -DNO_STORAGE -Wall -DDEBUG_BUILD -std=c++0x -I$(HYBRID_PATH) -fPIC -pedantic
LIBS=-L${HYBRID_PATH} -lhybridsim -Wl,-rpath=${HYBRID_PATH}

all: lib
lib: $(TARGET)
$(TARGET): MultiChannelMemorySystem.o
	g++ -g -shared -Wl,-soname,$@ -o $@ $^ ${LIBS}
MultiChannelMemorySystem.o: MultiChannelMemorySystem.cpp SST_HybridSim.h MultiChannelMemorySystem.h Callback.h 

main:main.o
	g++ -g main.o -o main -L./ -lhybridsim_sst -Wl,-rpath=./

clean:
	rm -rf *.o $(TARGET) main
