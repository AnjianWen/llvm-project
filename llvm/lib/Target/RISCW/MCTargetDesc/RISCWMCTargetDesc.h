#ifndef LLVM_LIB_TARGET_RISCW_MCTARGETDESC_RISCWMCTARGETDESC_H
#define LLVM_LIB_TARGET_RISCW_MCTARGETDESC_RISCWMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm {
  class Target;
  class Triple;

  Target &getTheRISCWTarget();
}

// Defines symbolic names for RISCW registers. This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "RISCWGenRegisterInfo.inc"

// Defines symbolic names for the RISCW instructions.
#define GET_INSTRINFO_ENUM
#include "RISCWGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "RISCWGenSubtargetInfo.inc"

#endif // end LLVM_LIB_TARGET_RISCW_MCTARGETDESC_RISCWMCTARGETDESC_H
