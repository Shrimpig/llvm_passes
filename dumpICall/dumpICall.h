#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

namespace {

  class DumpICall: public ModulePass {

    public:
      static char ID;
      DumpICall() : ModulePass(ID) { }

      void dumpInst(Instruction *I);
      void dumpIt(Module &M);

      bool runOnModule(Module &M) override;
  };
}

