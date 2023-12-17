######################################################################
# Makefile for building Pythia's ROOT examples.
# Axel Naumann, 2011-03-03
######################################################################

PYTHIA8      :=$(PYTHIA8PATH)
# Need this to get SHAREDSUFFIX (e.g. dylib or so)
SHAREDSUFFIX=so
#-include $(PYTHIA8)/config.mk

# A few variables used in this Makefile:
EX           := main
EXE          := $(addsuffix .exe,$(EX))
STATICLIB    := /etc/Pythia8/pythia8308/lib/libpythia8.a
SHAREDLIB    := /etc/Pythia8/pythia8308/lib/libpythia8.so
DICTCXXFLAGS := -I/etc/Pythia8/pythia8308/include
EXTFLAG      := -I/home/antony/Documents/Projects/AliQuarkonium/AliEventLib/include
ROOTCXXFLAGS := $(DICTCXXFLAGS) $(shell root-config --cflags)
CXXFLAGS     := -Wall -g

# Libraries to include if GZIP support is enabled
ifeq (x$(ENABLEGZIP),xyes)
LIBGZIP=-L$(BOOSTLIBLOCATION) -lboost_iostreams -L$(ZLIBLOCATION) -lz
endif


# LDFLAGS1 for static library, LDFLAGS2 for shared library
LDFLAGS1 := $(shell root-config --ldflags --glibs) \
  -L/etc/Pythia8/pythia8308/lib -L/etc/Pythia8/LHAPDF/lib/ -lpythia8 -lLHAPDF $(LIBGZIP)
LDFLAGS2 := $(shell root-config --ldflags --glibs) \
  -L/etc/Pythia8/pythia8308/lib -L/etc/Pythia8/LHAPDF/lib/ -lpythia8 -lLHAPDF $(LIBGZIP)

FILES_SRC =  src/main.cpp src/Init.cpp
FILES_OBJ =  $(FILES_SRC:%.cpp=%.o)
ROOT_DICT = /home/antony/Documents/Projects/AliQuarkonium/AliEventLib/build/libpythiaDictionary.so

# Default target; make examples (but not shared dictionary)
all: $(EX)

# Rule to build hist example. Needs static PYTHIA 8 library
$(EX): $(SHAREDLIB) $(FILES_OBJ) $(ROOT_DICT)
	$(CXX) $(EXTFLAG) $(ROOTCXXFLAGS) $(FILES_OBJ) $(ROOT_DICT) -o $@.exe $(LDFLAGS1)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(EXTFLAG) $(ROOTCXXFLAGS)

# Error messages if PYTHIA libraries don't exist
$(STATICLIB):
	@echo "Error: PYTHIA 8 archive library must be built"
	@false
$(SHAREDLIB):
	@echo "Error: PYTHIA 8 shared library must be built"
	@false


# Clean up
clean:
	rm -f $(EXE) $(FILES_OBJ)
