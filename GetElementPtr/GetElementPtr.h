#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {

  class GetElementPtr : public ModulePass {

    public:
      static char ID;
      GetElementPtr() : ModulePass(ID) { }

      bool runOnModule(Module &M) override;
  };
}

