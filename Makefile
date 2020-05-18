
all:
	g++ -g -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -o gameengine gameengine.cpp -DVERSION=\"$(shell git describe --dirty --always --tags)\"
	
.PHONY: clean
clean:
	rm gameengine
