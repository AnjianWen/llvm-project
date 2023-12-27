#include "TargetInfo/RISCWTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheRISCWTarget() {
  static Target TheRISCWTarget;
  return TheRISCWTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISCWTargetInfo() {
  RegisterTarget<Triple::riscw, /*HasJIT=*/true> X(getTheRISCWTarget(), "riscw", "32-bit RISC-W", "RISCW");
}
