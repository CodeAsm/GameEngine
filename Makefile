
all:
	g++ -g -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -o gameengine gameengine.cpp
	
.PHONY: clean
clean:
	rm gameengine
