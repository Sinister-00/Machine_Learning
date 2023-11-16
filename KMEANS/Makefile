CC := g++
SRC := $(MLINCPP_ROOT)/KMEANS/src
CFLAGS := -std=c++11
INCLUDE := $(PWD)/include/*

all: main

main: $(SRC)/kmeans.cpp
	$(CC) $(CFLAGS) $(SRC)/kmeans.cpp -o main -L$(MLINCPP_ROOT)/lib/ -I$(INCLUDE) \
	-I$(MLINCPP_ROOT)/include -ldata

clean:
	rm main