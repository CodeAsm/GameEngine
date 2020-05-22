CC=g++
CFLAGS=-I.
LIBS=-lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

all:
	$(CC) -g $(LIBS) -o gameengine gameengine.cpp -DVERSION=\"$(shell git describe --dirty --always --tags)\"
	
.PHONY: clean
clean:
	rm -f gameengine
