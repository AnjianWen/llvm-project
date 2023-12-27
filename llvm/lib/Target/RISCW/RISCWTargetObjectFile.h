#ifndef LLVM_LIB_TARGET_RISCW_RISCWTARGETOBJECTFILE_H
#define LLVM_LIB_TARGET_RISCW_RISCWTARGETOBJECTFILE_H

#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"

namespace llvm {
class RISCWTargetObjectFile : public TargetLoweringObjectFileELF {
public:
  void Initialize(MCContext &Ctx, const TargetMachine &TM) override;

};
} // end namespace llvm

#endif
