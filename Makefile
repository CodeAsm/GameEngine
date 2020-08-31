CXX=g++
CXXFLAGS=-I. -Ipkg/imgui/ -Ipkg/imgui/examples/
CXXFLAGS += -g -Wall -Wformat 
LIBS += -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi 
LIBS += -lrt -lm -ldl -lxcb -lXau -lXdmcp
IMGUI=pkg/imgui/
OBJDIR=obj/
SOURCES = gameengine.cpp $(wildcard $(IMGUI)*.cpp) 
#SOURCES += pkg/imgui/imgui.cpp pkg/imgui/imgui_demo.cpp pkg/imgui/imgui_draw.cpp pkg/imgui/imgui_widgets.cpp
OBJS = $(addprefix $(OBJDIR), $(addsuffix .o, $(basename $(notdir $(SOURCES)))))
EXE = gameengine

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    # (-g)  => Enable debug symbols -O0) => Disable optimizations-DNDEBUG => Enable assertions
    CXXFLAGS  += -g -O0  -DNDEBUG
else
     CXXFLAGS += -O3
endif

$(OBJDIR)%.o:$(IMGUI)%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)%.o:%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $< -DVERSION=\"$(shell git describe --dirty --always --tags)\"

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS) -o $(EXE) 

all:$(EXE)
	@echo Build complete for Linux $(shell git describe --dirty --always --tags)
	
.PHONY: clean
clean:
	rm -rf $(EXE) $(OBJS) $(OBJDIR)
