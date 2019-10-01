LLVM_CONFIG ?= llvm-config
CLANG_CFL    = `$(LLVM_CONFIG) --cxxflags` -fno-rtti -fpic $(CXXFLAGS)
CLANG_LFL    = `$(LLVM_CONFIG) --ldflags` $(LDFLAGS)

all: DIE.so

DIE.so: DIE.cpp DIE.h
	$(CXX) $(CLANG_CFL) -shared $< -o $@ $(CLANG_LFL)
