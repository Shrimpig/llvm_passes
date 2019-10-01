#include "DIE.h"

#define endl "\n"

using namespace llvm;

char DIE::ID = 0;

bool DIE::runOnModule(Module &M) {

  for (auto & F : M) {

    errs() << F.getName() << endl;
  }

  return true;
}

static RegisterPass<DIE> X("DIE", "encoding IR debug info to file");

static void registerDIEPass(const PassManagerBuilder &,
    legacy::PassManagerBase &PM) {
  PM.add(new DIE());
}

static RegisterStandardPasses RegisterDIEPass(
    PassManagerBuilder::EP_OptimizerLast, registerDIEPass);
static RegisterStandardPasses RegisterDIEPass0(
    PassManagerBuilder::EP_EnabledOnOptLevel0, registerDIEPass);
