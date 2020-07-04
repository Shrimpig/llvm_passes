#include "dumpIR.h"

#define endl "\n"

using namespace llvm;

char DIE::ID = 0;

void saveModule(Module &M, Twine filename) {
  int ll_fd;
  sys::fs::openFileForWrite(filename, ll_fd,
      sys::fs::F_RW | sys::fs::F_Text);
  raw_fd_ostream ll_file(ll_fd, true, true);
  M.print(ll_file, nullptr);
}

bool DIE::runOnModule(Module &M) {

  saveModule(M, M.getName() + ".ll");

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
