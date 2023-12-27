#ifndef LLVM_LIB_TARGET_RISCW_RISCWMACHINEFUNCTIONINFO_H
#define LLVM_LIB_TARGET_RISCW_RISCWMACHINEFUNCTIONINFO_H

#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {
  class RISCWMachineFunctionInfo : public MachineFunctionInfo {
  public:
    RISCWMachineFunctionInfo(MachineFunction &MF) : MF(MF) {}

    ~RISCWMachineFunctionInfo();

  private:
    MachineFunction &MF;
  };
} // End llvm namespace
#endif
