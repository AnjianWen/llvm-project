#ifndef LLVM_LIB_TARGET_RISCW_RISCWTARGETMACHINE_H
#define LLVM_LIB_TARGET_RISCW_RISCWTARGETMACHINE_H

#include "MCTargetDesc/RISCWMCTargetDesc.h"
#include "RISCWSubtarget.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"
#include <optional>

namespace llvm {
  class RISCWTargetMachine : public LLVMTargetMachine {
    std::unique_ptr<TargetLoweringObjectFile> TLOF;
    mutable StringMap<std::unique_ptr<RISCWSubtarget>> SubtargetMap;

  public:
    RISCWTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                      StringRef FS, const TargetOptions &Options,
                      std::optional<Reloc::Model> RM,
                      std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                      bool JIT);

    const RISCWSubtarget *getSubtargetImpl() const = delete;

    const RISCWSubtarget *getSubtargetImpl(const Function &F) const override;

    TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

    TargetLoweringObjectFile *getObjFileLowering() const override {
      return TLOF.get();
    }
  };

} // End llvm namespace

#endif
