#include "dumpIR.h"

#define endl "\n"

using namespace llvm;

static cl::opt<bool> removeDeadFuncKnob("removeDeadFunc", cl::init(false),
    cl::desc("remove dead functions, use this only you are sure"));

char DIE::ID = 0;

void saveModule(Module &M, Twine filename) {
  int ll_fd;
  sys::fs::openFileForWrite(filename, ll_fd);
  raw_fd_ostream ll_file(ll_fd, true, true);
  M.print(ll_file, nullptr);
}

void DIE::removeDeadFunc(Module &M) {

  std::vector<Function *> AllFuncs;
  std::vector<Function *>::iterator iter, end;

  for (auto &F : M)
    AllFuncs.push_back(&F); 

  for (iter = AllFuncs.begin(), end = AllFuncs.end(); iter != end; ) {

    Function * F = *iter++;

    if (F->getName() == "main") continue;

    if (F->hasNUses(0)) 
      F->removeFromParent();
  }
}

bool DIE::runOnModule(Module &M) {

  if (removeDeadFuncKnob == true) removeDeadFunc(M);

  saveModule(M, M.getName() + ".ll");

  return true;
}

static RegisterPass<DIE> X("DIE", "encoding IR debug info to file");

static void registerDIEPass(const PassManagerBuilder &,
    legacy::PassManagerBase &PM) {
  PM.add(new DIE());
}

static RegisterStandardPasses RegisterDIEPass(
    //PassManagerBuilder::EP_OptimizerLast, registerDIEPass);
    //PassManagerBuilder::EP_EarlyAsPossible, registerDIEPass);
    PassManagerBuilder::EP_ModuleOptimizerEarly, registerDIEPass);
static RegisterStandardPasses RegisterDIEPass0(
    PassManagerBuilder::EP_EnabledOnOptLevel0, registerDIEPass);
