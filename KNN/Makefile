CC := g++
SRC := $(MLINCPP_ROOT)/KNN/src
CFLAGS := -std=c++11 -DEUCLID
INCLUDE := $(MLINCPP_ROOT)/KNN/include/

all: main

main: $(SRC)/knn.cpp
	$(CC) $(CFLAGS) $(SRC)/knn.cpp -o main -L$(MLINCPP_ROOT)/lib/ -I$(INCLUDE) \
	-I$(MLINCPP_ROOT)/include -ldata

clean:
	rm main