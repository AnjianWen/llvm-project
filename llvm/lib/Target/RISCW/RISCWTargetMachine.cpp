#include "RISCWTargetMachine.h"
#include "RISCW.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "riscw"

extern "C" void LLVMInitializeRISCWTarget() {}
