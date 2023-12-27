#include "RISCWTargetMachine.h"
#include "RISCW.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"
#include "TargetInfo/RISCWTargetInfo.h"
#include "RISCWTargetObjectFile.h"
#include "RISCWISelDAGToDAG.h"

using namespace llvm;

#define DEBUG_TYPE "riscw"

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISCWTarget() {
  RegisterTargetMachine<RISCWTargetMachine> X(getTheRISCWTarget());
}

static StringRef computeDataLayout(const Triple &TT) {
  return "e-m:e-p:32:32-i64:64-n32-S128";
}

static Reloc::Model getEffectiveRelocModel(const Triple &TT,
                                           std::optional<Reloc::Model> RM) {
  return RM.value_or(Reloc::Static);
}

RISCWTargetMachine::RISCWTargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       std::optional<Reloc::Model> RM,
                                       std::optional<CodeModel::Model> CM,
                                       CodeGenOptLevel OL, bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(TT), TT, CPU, FS, Options,
                        getEffectiveRelocModel(TT, RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<RISCWTargetObjectFile>()) {
  initAsmInfo();
}

const RISCWSubtarget *
RISCWTargetMachine::getSubtargetImpl(const Function &F) const {
  Attribute CPUAttr = F.getFnAttribute("target-cpu");
  Attribute FSAttr = F.getFnAttribute("target-features");

  std::string CPU =
      CPUAttr.isValid() ? CPUAttr.getValueAsString().str() : TargetCPU;
  std::string FS =
      FSAttr.isValid() ? FSAttr.getValueAsString().str() : TargetFS;

  auto &I = SubtargetMap[CPU + FS];
  if (!I) {
    resetTargetOptions(F);
    I = std::make_unique<RISCWSubtarget>(TargetTriple, CPU, CPU, FS, *this);
  }
  return I.get();
}

namespace {
class RISCWPassConfig : public TargetPassConfig {
public:
  RISCWPassConfig(RISCWTargetMachine &TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  RISCWTargetMachine &getRISCWTargetMachine() const {
    return getTM<RISCWTargetMachine>();
  }

  bool addInstSelector() override;
  void addPreEmitPass() override;
};
}

TargetPassConfig *RISCWTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new RISCWPassConfig(*this, PM);
}

bool RISCWPassConfig::addInstSelector() {
  addPass(new RISCWDAGToDAGISel(getRISCWTargetMachine(), getOptLevel()));
  return false;
}

void RISCWPassConfig::addPreEmitPass() {
}
