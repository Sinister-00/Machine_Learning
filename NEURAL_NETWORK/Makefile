CC=g++
SRC := $(PWD)/src
CFLAGS := -std=c++11 -g 
INCLUDE_DIR := $(PWD)/include/

all: main

main : obj $(SRC)/network.cpp obj/layer.o obj/neuron.o
	$(CC) $(CFLAGS) $(SRC)/network.cpp -o main -L$(MLINCPP_ROOT)/lib/ -I$(INCLUDE_DIR) \
	-I$(MLINCPP_ROOT)/include -ldata ./obj/*.o

obj:
	if [ ! -d "./obj" ]; then mkdir obj; fi

obj/layer.o : $(SRC)/layer.cpp
	$(CC) -c $(CFLAGS) $(SRC)/layer.cpp -o obj/layer.o -I$(INCLUDE_DIR) \
	-I$(MLINCPP_ROOT)/include

obj/neuron.o : $(SRC)/neuron.cpp
	$(CC) -c $(CFLAGS) $(SRC)/neuron.cpp -o obj/neuron.o -I$(INCLUDE_DIR) \
	-I$(MLINCPP_ROOT)/include

clean :
	rm -r main obj