#include "RISCWInstrInfo.h"

#include "RISCWTargetMachine.h"
#include "RISCWMachineFunctionInfo.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "RISCWGenInstrInfo.inc"

RISCWInstrInfo::RISCWInstrInfo(const RISCWSubtarget &STI)
  : Subtarget(STI) { }
