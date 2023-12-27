#ifndef LLVM_LIB_TARGET_RISCW_RISCWSUBTARGET_H
#define LLVM_LIB_TARGET_RISCW_RISCWSUBTARGET_H

#include "RISCWFrameLowering.h"
#include "RISCWISelLowering.h"
#include "RISCWInstrInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/MC/MCInstrItineraries.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include <string>

#define GET_SUBTARGETINFO_HEADER
#include "RISCWGenSubtargetInfo.inc"

namespace llvm {
class RISCWSubtarget : public RISCWGenSubtargetInfo {
protected:
#include "RISCWGenSubtargetInfo.inc"
  SelectionDAGTargetInfo TSInfo;
  RISCWInstrInfo InstrInfo;
  RISCWFrameLowering FrameLowering;
  RISCWTargetLowering TLInfo;
  RISCWRegisterInfo RegInfo;

public:
  RISCWSubtarget(const Triple &TT, StringRef CPU, StringRef TuneCPU, StringRef FS,
                 const TargetMachine &TM);


  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);

  RISCWSubtarget &initializeSubtargetDependencies(const Triple &TT,
                                                  StringRef CPU, 
                                                  StringRef TuneCPU, 
                                                  StringRef FS,
                                                  const TargetMachine &TM);

  const SelectionDAGTargetInfo *getSelectionDAGInfo() const override {
    return &TSInfo;
  }

  const RISCWInstrInfo *getInstrInfo() const override {
    return &InstrInfo;
  }

  const TargetFrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }

  const RISCWRegisterInfo *getRegisterInfo() const override {
    return &RegInfo;
  }

  const RISCWTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }

  /// getMaxInlineSizeThreshold - Returns the maximum memset / memcpy size
  /// that still makes it profitable to inline the call.
  unsigned getMaxInlineSizeThreshold() const {
    return 64;
  }
};
}

#endif
