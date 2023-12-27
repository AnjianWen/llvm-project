#ifndef LLVM_LIB_TARGET_RISCW_RISCWINSTRINFO_H
#define LLVM_LIB_TARGET_RISCW_RISCWINSTRINFO_H

#include "RISCW.h"
#include "RISCWRegisterInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "RISCWGenInstrInfo.inc"

namespace llvm {
  class RISCWInstrInfo : public RISCWGenInstrInfo {
  protected:
    const RISCWSubtarget &Subtarget;
  public:
    explicit RISCWInstrInfo(const RISCWSubtarget &STI);
  };
}

#endif
