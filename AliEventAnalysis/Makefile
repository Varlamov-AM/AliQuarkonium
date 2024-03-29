######################################################################
# Makefile for building Pythia's ROOT examples.
# Axel Naumann, 2011-03-03
######################################################################

PYTHIA8      :=/data1/varlamov/soft/pythia8310
# Need this to get SHAREDSUFFIX (e.g. dylib or so)
SHAREDSUFFIX=so
#-include $(PYTHIA8)/config.mk

# A few variables used in this Makefile:
EX           := main
EXE          := $(addsuffix .exe,$(EX))
STATICLIB    := /data1/varlamov/software/pythia8310/lib/libpythia8.a
SHAREDLIB    := /data1/varlamov/software/pythia8310/lib/libpythia8.so
DICTCXXFLAGS := -I/data1/varlamov/software/pythia8310/include
EXTFLAG      := -I/data2/varlamov/projects/AliQuarkonium/AliEventLib/include
EXTSRC       := /data2/varlamov/projects/AliQuarkonium/AliEventLib/src
ROOTCXXFLAGS := $(DICTCXXFLAGS) $(shell root-config --cflags)
CXXFLAGS     := -Wall -g -std=c++17 -lstdc++fs

# Libraries to include if GZIP support is enabled
ifeq (x$(ENABLEGZIP),xyes)
LIBGZIP=-L$(BOOSTLIBLOCATION) -lboost_iostreams -L$(ZLIBLOCATION) -lz
endif


# LDFLAGS1 for static library, LDFLAGS2 for shared library
LDFLAGS1 := $(shell root-config --ldflags --glibs) \
  -L/data1/varlamov/software/pythia8310/lib -lpythia8 $(LIBGZIP)
LDFLAGS2 := $(shell root-config --ldflags --glibs) \
  -L/data1/varlamov/software/pythia8310/lib -lpythia8 $(LIBGZIP)

FILES_SRC =   TTree_data_handler.cpp $(EXTSRC)/AliEvent.cpp $(EXTSRC)/AliParticle.cpp resolutionElectron.cpp smearP.cpp resolutionPhoton.cpp smearE.cpp smearX.cpp sigmaX.cpp IsElectronDetectedInALICE3.cpp
FILES_OBJ =  $(FILES_SRC:%.cc=%.o)
#ROOT_DICT = pythiaDict.$(SHAREDSUFFIX)
ROOT_DICT = /data2/varlamov/projects/AliQuarkonium/AliEventLib/build/libpythiaDictionary.so

# Default target; make examples (but not shared dictionary)
all: $(EX)

# Rule to build hist example. Needs static PYTHIA 8 library
$(EX): $(SHAREDLIB) $(FILES_OBJ) $(ROOT_DICT)
	$(CXX) $(EXTFLAG) $(ROOTCXXFLAGS) $(FILES_OBJ) $(ROOT_DICT) -o $@.exe $(LDFLAGS1)

%.o: %.cc
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
	rm -f $(EXE) *.o
