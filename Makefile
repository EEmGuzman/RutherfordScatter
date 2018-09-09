ROOTCONFIG	= $(ROOTSYS)/bin/root-config
CINT		= $(ROOTSYS)/bin/rootcint

ROOTLIBS	= $(shell $(ROOTCONFIG) --libs)
ROOTGLIBS	= $(shell $(ROOTCONFIG) --glibs)
ROOTCFLAGS	= $(shell $(ROOTCONFIG) --cflags)

CXX		= g++
LD		= g++
CXXFLAGS	= -Wall $(ROOTCFLAGS) -Iinclude/ -g
GLIBS		= -L/usr/X11R6/lib -IXpm -IX11 $(ROOTGLIBS)
LIBS		= $(ROOTLIBS) -IMinuit

all: rutherfordScatter.exe

clean:
	rm -rf obj/* rutherfordScatter.exe;

obj/%.o : src/%.cpp include/%.h
	mkdir -p obj/; $(CXX) $(CXXFLAGS) -c $< -o $@

rutherfordScatter.exe: obj/ScatterAlpha.o obj/InitAlpha.o obj/main.o
	$(LD)	$(ROOTCFLAGS) $(LIBS) $(ROOTLIBS) obj/ScatterAlpha.o obj/InitAlpha.o obj/main.o -o $@
