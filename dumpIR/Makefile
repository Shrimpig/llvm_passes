CXX = clang
LLVM_CONFIG ?= llvm-config
CLANG_CFL    = `$(LLVM_CONFIG) --cxxflags` -fno-rtti -fpic $(CXXFLAGS)
CLANG_LFL    = `$(LLVM_CONFIG) --ldflags` $(LDFLAGS)

all: dumpIR.so

dumpIR.so: dumpIR.cpp dumpIR.h
	$(CXX) $(CLANG_CFL) -shared $< -o $@ $(CLANG_LFL)
