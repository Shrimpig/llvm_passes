#include "dbgIR.h"

#define endl "\n"

using namespace llvm;

char dbgIR::ID = 0;

static void saveModule(Module &M, Twine filename)
{
  int ll_fd;
  sys::fs::openFileForWrite(filename, ll_fd,
      sys::fs::F_RW | sys::fs::F_Text);
  raw_fd_ostream ll_file(ll_fd, true, true);
  M.print(ll_file, nullptr);
}

bool dbgIR::runOnModule(Module &M) {

  unsigned instID = 1;
  LLVMContext& ctx = M.getContext();
  std::string fileName = M.getName();
  fileName += ".ll";

  for (auto & F : M) {

    if (F.isIntrinsic()) continue;
    if (F.isDeclaration()) continue;

    SmallString<128> current_dir;
    llvm::sys::fs::current_path(current_dir);

    DIFile * defaultFile = DIFile::get(ctx, fileName, current_dir.str());

    for (auto & BB : F) {

      for (auto & I : BB) {
        MDNode * IDnode = MDNode::get(ctx, MDString::get(ctx, std::to_string(instID)));
        I.setMetadata("dbgID", IDnode);

        DILocation *DIL = NULL;
        DIL = DILocation::get(ctx, instID, 0, (DIScope *) defaultFile, 0);

        DebugLoc debugLoc(DIL);
        I.setDebugLoc(debugLoc);
        
        instID++;
      }
    }
  }

  saveModule(M, fileName);

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
