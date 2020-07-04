LLVM_CONFIG ?= llvm-config
CLANG_CFL    = `$(LLVM_CONFIG) --cxxflags` -fno-rtti -fpic $(CXXFLAGS)
CLANG_LFL    = `$(LLVM_CONFIG) --ldflags` $(LDFLAGS)

all: GetElementPtr.so

GetElementPtr.so: GetElementPtr.cpp GetElementPtr.h
	$(CXX) $(CLANG_CFL) -shared $< -o $@ $(CLANG_LFL)
