######################################################################
# Makefile for building Pythia generator for Ali_Quarkonium
# Antony Varlamov, 21.02.2025
######################################################################

PYTHIA8PATH      :=$(PYTHIA8)
# Need this to get SHAREDSUFFIX (e.g. dylib or so)
SHAREDSUFFIX=so
#-include $(PYTHIA8)/config.mk

# A few variables used in this Makefile:
EX           := main
EXE          := $(addsuffix .exe,$(EX))
STATICLIB    := $(PYTHIA8PATH)/lib/libpythia8.a
SHAREDLIB    := $(PYTHIA8PATH)/lib/libpythia8.so
DICTCXXFLAGS := -I$(PYTHIA8PATH)/include/
EXTFLAG      := -I$(ALI_QUARKONIUM)/AliEventLib/include
ROOTCXXFLAGS := $(DICTCXXFLAGS) $(shell root-config --cflags)
CXXFLAGS     := -Wall -g

# Libraries to include if GZIP support is enabled
ifeq (x$(ENABLEGZIP),xyes)
LIBGZIP=-L$(BOOSTLIBLOCATION) -lboost_iostreams -L$(ZLIBLOCATION) -lz
endif


# LDFLAGS1 for static library, LDFLAGS2 for shared library
#  -L$PYTHIA8/lib -L/etc/Pythia8/LHAPDF/lib/ -lpythia8 -lLHAPDF $(LIBGZIP)
#  -L/etc/Pythia8/pythia8308/lib -L/etc/Pythia8/LHAPDF/lib/ -lpythia8 -lLHAPDF $(LIBGZIP)
LDFLAGS1 := $(shell root-config --ldflags --glibs) \
  -L$(PYTHIA8PATH)/lib -lpythia8  $(LIBGZIP)
LDFLAGS2 := $(shell root-config --ldflags --glibs) \
  -L$(PYTHIA8PATH)/lib -lpythia8 $(LIBGZIP)


FILES_SRC =  src/main.cpp src/Init.cpp
FILES_OBJ =  $(FILES_SRC:%.cpp=%.o)
ROOT_DICT = $(ALI_QUARKONIUM)/AliEventLib/build/libpythiaDictionary.so

# Default target; make examples (but not shared dictionary)
all: $(EX)

# Rule to build hist example. Needs static PYTHIA 8 library
$(EX): $(SHAREDLIB) $(FILES_OBJ) $(ROOT_DICT)
	$(CXX) $(EXTFLAG) $(ROOTCXXFLAGS) $(FILES_OBJ) $(ROOT_DICT) -L$(ALI_QUARKONIUM)/AliEventLib/build/ -o $@.exe $(LDFLAGS1)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) $(EXTFLAG) $(ROOTCXXFLAGS) $(SHAREDLIB)

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
