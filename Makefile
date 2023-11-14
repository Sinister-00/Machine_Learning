CC := g++
INCLUDE_DIR := $(MLINCPP_ROOT)/include
SRC_DIR := $(MLINCPP_ROOT)/src
CFLAGS := -std=c++11 -g
LIB_DATA := libdata.so

all: libdir objdir $(LIB_DATA)

$(LIB_DATA): obj/data_handler.o obj/data.o obj/common.o
	$(CC) $(CFLAGS) -shared -o $(MLINCPP_ROOT)/lib/$(LIB_DATA) obj/*.o
	# rm -r $(MLINCPP_ROOT)/obj

libdir:
	mkdir -p $(MLINCPP_ROOT)/lib

objdir:
	mkdir -p $(MLINCPP_ROOT)/obj

obj/data_handler.o: $(SRC_DIR)/data_handler.cpp
	$(CC) -fPIC $(CFLAGS) -o obj/data_handler.o -I$(INCLUDE_DIR) -c $(SRC_DIR)/data_handler.cpp

obj/data.o: $(SRC_DIR)/data.cpp
	$(CC) -fPIC $(CFLAGS) -o obj/data.o -I$(INCLUDE_DIR) -c $(SRC_DIR)/data.cpp

obj/common.o: $(SRC_DIR)/common.cpp
	$(CC) -fPIC $(CFLAGS) -o obj/common.o -I$(INCLUDE_DIR) -c $(SRC_DIR)/common.cpp

clean:
	rm -r $(MLINCPP_ROOT)/lib
	rm -r $(MLINCPP_ROOT)/obj
# before running make
# use this command to export the MLINCPP_ROOT
# export MLINCPP_ROOT=/home/username/MLinCpp