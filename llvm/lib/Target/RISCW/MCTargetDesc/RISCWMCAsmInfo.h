#ifndef LLVM_LIB_TARGET_RISCW_MCTARGETDESC_RISCWMCASMINFO_H
#define LLVM_LIB_TARGET_RISCW_MCTARGETDESC_RISCWMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
  class Triple;

class RISCWMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit RISCWMCAsmInfo(const Triple &TheTriple);
};

} // namespace llvm

#endif // end LLVM_LIB_TARGET_RISCW_MCTARGETDESC_RISCWMCASMINFO_H
