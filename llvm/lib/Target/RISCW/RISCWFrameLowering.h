#ifndef LLVM_LIB_TARGET_RISCW_RISCWFRAMELOWERING_H
#define LLVM_LIB_TARGET_RISCW_RISCWFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/Support/TypeSize.h"

namespace llvm {
class RISCWSubtarget;

class RISCWFrameLowering : public TargetFrameLowering {
protected:
  const RISCWSubtarget &STI;

public:
  explicit RISCWFrameLowering(const RISCWSubtarget &sti)
    : TargetFrameLowering(StackGrowsDown, Align(16), 0, Align(16)),
      STI(sti) {}

  bool hasFP(const MachineFunction &MF) const override;

  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

  bool hasReservedCallFrame(const MachineFunction &MF) const override;
  MachineBasicBlock::iterator
  eliminateCallFramePseudoInstr(MachineFunction &MF, MachineBasicBlock &MBB,
                                MachineBasicBlock::iterator I) const override;

  void determineCalleeSaves(MachineFunction &MF, BitVector &SavedRegs,
                            RegScavenger *RS) const override;

};

} // End llvm namespace

#endif
