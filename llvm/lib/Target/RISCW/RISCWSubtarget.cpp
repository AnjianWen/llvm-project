#include "RISCWSubtarget.h"

#include "RISCW.h"
#include "RISCWMachineFunctionInfo.h"
#include "RISCWRegisterInfo.h"
#include "RISCWTargetMachine.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "riscw-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "RISCWGenSubtargetInfo.inc"


RISCWSubtarget::RISCWSubtarget(const Triple &TT, StringRef CPU, StringRef TuneCPU, 
                               StringRef FS, const TargetMachine &TM)
    : RISCWGenSubtargetInfo(TT, CPU, TuneCPU, FS),
      FrameLowering(initializeSubtargetDependencies(TT, CPU, TuneCPU, FS, TM)), InstrInfo(*this), RegInfo(*this), TLInfo(TM, *this) { }

RISCWSubtarget&
RISCWSubtarget::initializeSubtargetDependencies(const Triple &TT, StringRef CPU,
                                                StringRef TuneCPU, StringRef FS,
                                                const TargetMachine &TM) {
  if (CPU.empty())
    CPU = "generic";

  if (TuneCPU.empty())
    TuneCPU = CPU;

  // Parse features string.
  ParseSubtargetFeatures(CPU, TuneCPU, FS);

  return *this;
}
