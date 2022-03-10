BIN=libbase_jys.so
CC=g++
CFLAGS = -shared -fPIC

LIBS=-L. -lmysqlclient \
	$(BOOST)/stage/lib_linux64/libboost_thread-mt-d.a
	

INCS=-I./ -I$(BOOST) #头文件目录
	

SRCS:=$(wildcard *.cpp) #.c文件目录
COBJS:=$(SRCS:.cpp=.o)

all:$(BIN)

$(COBJS) : %.o: %.cpp
	$(CC) -c $< -o $@ $(INCS) $(CFLAGS)

$(BIN):$(COBJS)
	$(CC) -o $(BIN) $(COBJS) $(LIBS) $(CFLAGS)

clean:
	rm $(BIN) $(COBJS)

