ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS  = $(shell root-config --glibs) -lMinuit

all: Z_drop 

Z_drop : Z_drop.cc Z_drop.h
	g++ -Wall -Wextra -O3 -o $@ Z_drop.cc $(ROOTFLAGS) $(ROOTLIBS)

clean :
	rm -f Z_drop *~
