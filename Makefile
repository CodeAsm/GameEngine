CXX=g++
CXXFLAGS=-Iinclude/ -I/usr/include -g -Wall -Wformat
LIBS=-lglfw -ldl -ltinyobjloader
OBJDIR=obj/
SOURCES = main.cpp glad.c
OBJS = $(addprefix $(OBJDIR), $(addsuffix .o, $(basename $(notdir $(SOURCES)))))
EXE = main

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    # (-g)  => Enable debug symbols -O0) => Disable optimizations -DNDEBUG => Enable assertions
    CXXFLAGS += -g -O0 -DNDEBUG
else
    CXXFLAGS += -O3
endif

$(OBJDIR)%.o: %.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)%.o: %.c
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

all: $(EXE)
	@echo Build complete

.PHONY: clean
clean:
	rm -rf $(EXE) $(OBJS) $(OBJDIR)
