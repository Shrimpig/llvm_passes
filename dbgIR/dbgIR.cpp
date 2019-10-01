#include "dbgIR.h"

#define endl "\n"

using namespace llvm;

char dbgIR::ID = 0;

bool dbgIR::runOnModule(Module &M) {

  for (auto & F : M) {

    errs() << F.getName() << endl;
  }

  return true;
}

static RegisterPass<dbgIR> X("dbgIR", "encoding IR debug info to file");

static void registerdbgIRPass(const PassManagerBuilder &,
    legacy::PassManagerBase &PM) {
  PM.add(new dbgIR());
}

static RegisterStandardPasses RegisterdbgIRPass(
    PassManagerBuilder::EP_OptimizerLast, registerdbgIRPass);
static RegisterStandardPasses RegisterdbgIRPass0(
    PassManagerBuilder::EP_EnabledOnOptLevel0, registerdbgIRPass);
