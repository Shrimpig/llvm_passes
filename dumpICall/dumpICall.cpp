#include "dumpICall.h"

#define endl "\n"

using namespace llvm;

char DumpICall::ID = 0;

void DumpICall::dumpInst(Instruction *I) {

  const DebugLoc &location = I->getDebugLoc();

  if (location) location.print(errs());
}

void DumpICall::dumpIt(Module &M) {

  std::vector<Function *> AllFuncs;
  std::vector<Function *>::iterator iter, end;

  for (auto &F : M)
    for (auto &BB : F)
      for (auto &I : BB) {
        if (CallInst *CI = dyn_cast<CallInst>(&I)) {
          if (CI->getCalledFunction() == nullptr)
            dumpInst(&I);
        } else if (InvokeInst *II = dyn_cast<InvokeInst>(&I)) {
          if (II->getCalledFunction() == nullptr)
            dumpInst(&I);
        }
      }

}

bool DumpICall::runOnModule(Module &M) {

  dumpIt(M);

  return true;
}

static RegisterPass<DumpICall> X("DumpICall", "encoding IR debug info to file");

static void registerDumpICallPass(const PassManagerBuilder &,
    legacy::PassManagerBase &PM) {
  PM.add(new DumpICall());
}

static RegisterStandardPasses RegisterDumpICallPass(
    PassManagerBuilder::EP_OptimizerLast, registerDumpICallPass);
    //PassManagerBuilder::EP_EarlyAsPossible, registerDumpICallPass);
    //PassManagerBuilder::EP_ModuleOptimizerEarly, registerDumpICallPass);
static RegisterStandardPasses RegisterDumpICallPass0(
    PassManagerBuilder::EP_EnabledOnOptLevel0, registerDumpICallPass);
