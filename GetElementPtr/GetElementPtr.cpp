#include "GetElementPtr.h"

#define endl "\n"

using namespace llvm;

char GetElementPtr::ID = 0;

bool GetElementPtr::runOnModule(Module &M) {

  const DataLayout & DL = M.getDataLayout();

  for (auto & F : M) {

    errs() << F.getName() << endl;

    for (auto & BB : F) 
      for (auto & I : BB) {

        if (GetElementPtrInst * GEPI = dyn_cast<GetElementPtrInst>(&I)) {
          errs() << I << "\n";

          unsigned int ASL = GEPI->getPointerAddressSpace();
          unsigned BitWidth = DL.getPointerSizeInBits(ASL);

          APInt asize(BitWidth, 0);
          if (GEPI->accumulateConstantOffset(DL, asize)){
            errs() << "Get the offset: " << asize.getZExtValue() << "\n";
          } else {
            errs() << "Cannot get the offset\n";
          }
        }
      }
  }

  return true;
}

static RegisterPass<GetElementPtr> X("GetElementPtr", "encoding IR debug info to file");

static void registerGetElementPtrPass(const PassManagerBuilder &,
    legacy::PassManagerBase &PM) {
  PM.add(new GetElementPtr());
}

static RegisterStandardPasses RegisterGetElementPtrPass(
    PassManagerBuilder::EP_OptimizerLast, registerGetElementPtrPass);
static RegisterStandardPasses RegisterGetElementPtrPass0(
    PassManagerBuilder::EP_EnabledOnOptLevel0, registerGetElementPtrPass);
