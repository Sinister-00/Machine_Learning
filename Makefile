
CC := g++
PATHR := Machine_Learning_in_Cpp
INLCUDE_DIR := $(PATHR)/include
SRC_DIR := $(PATHR)/src
CFLAGS := -std=c++11 -g
LIBS_DATA := libdata.so

$(info PATHR=$(PATHR))
$(info SRC_DIR=$(SRC_DIR))

all: $(LIBS_DATA)

$(LIBS_DATA): libdir objdir obj/data_handler.o obj/data.o
	$(CC) $(CFLAGS) -o $(PATHR)/lib/$(LIBS_DATA) obj/*.o
	rm -r $(PATHR)/obj

libdir:
	mkdir -p lib

objdir:
	mkdir -p obj

obj/data_handler.o: $(SRC_DIR)/data_handler.cpp
	$(CC) -fPIC $(CFLAGS) -o obj/data_handler.o -I$(INLCUDE_DIR) -c $<

obj/data.o: $(SRC_DIR)/data.cpp
	$(CC) -fPIC $(CFLAGS) -o obj/data.o -I$(INLCUDE_DIR) -c $<

clean:
	rm -r lib
	rm -r obj


# in case of error:

# g++ -c -fPIC -std=c++11 -I./include -o obj/data_handler.o ./src/data_handler.cpp

# g++ -c -fPIC -std=c++11 -I./include -o obj/data.o ./src/data.cpp        

# g++ -shared -o libdata.so obj/data_handler.o obj/data.o -fPIC