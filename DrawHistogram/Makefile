ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS  = $(shell root-config --glibs) -lMinuit

all: DrawHistogram 

DrawHistogram : DrawHistogram.cc DrawHistogram.h
	g++ -Wall -Wextra -O3 -o $@ DrawHistogram.cc $(ROOTFLAGS) $(ROOTLIBS)

clean :
	rm -f DrawHistogram *~
