CXX = clang
LLVM_CONFIG ?= llvm-config
CLANG_CFL    = `$(LLVM_CONFIG) --cxxflags` -fno-rtti -fpic $(CXXFLAGS)
CLANG_LFL    = `$(LLVM_CONFIG) --ldflags` $(LDFLAGS)

all: dumpICall.so

dumpICall.so: dumpICall.cpp dumpICall.h
	$(CXX) $(CLANG_CFL) -shared $< -o $@ $(CLANG_LFL)
