TARGET=libhybridsim_sst.so
HYBRID_PATH=../HybridSim
CXXFLAGS=-m64 -DNO_STORAGE -Wall -DDEBUG_BUILD -std=c++0x -I$(HYBRID_PATH) -fPIC
LIBS=-L${HYBRID_PATH} -lhybridsim -Wl,-rpath=${HYBRID_PATH}

all: lib
lib: $(TARGET)
$(TARGET): MultiChannelMemorySystem.o
	g++ -g -shared -Wl,-soname,$@ -o $@ $^ ${LIBS}
MultiChannelMemorySystem.o: MultiChannelMemorySystem.cpp DRAMSim.h MultiChannelMemoryController.h Callback.h 

clean:
	rm -rf *.o $(TARGET)
