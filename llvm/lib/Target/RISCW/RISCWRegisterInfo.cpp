#include "RISCWRegisterInfo.h"

#include "RISCW.h"
#include "RISCWSubtarget.h"
#include "RISCWMachineFunctionInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

#define GET_REGINFO_TARGET_DESC
#include "RISCWGenRegisterInfo.inc"

#define DEBUG_TYPE "riscw-reginfo"

using namespace llvm;

RISCWRegisterInfo::RISCWRegisterInfo(const RISCWSubtarget &ST)
  : RISCWGenRegisterInfo(RISCW::X1, /*DwarfFlavour*/0, /*EHFlavor*/0,
                         /*PC*/0), Subtarget(ST) {}

const MCPhysReg *
RISCWRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return RISCW_CalleeSavedRegs_SaveList;
}

const TargetRegisterClass *RISCWRegisterInfo::intRegClass(unsigned Size) const {
  return &RISCW::GPRRegClass;
}

const uint32_t *
RISCWRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                        CallingConv::ID) const {
  return RISCW_CalleeSavedRegs_RegMask;
}

BitVector RISCWRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  markSuperRegs(Reserved, RISCW::X0); // zero
  markSuperRegs(Reserved, RISCW::X2); // sp
  markSuperRegs(Reserved, RISCW::X3); // gp
  markSuperRegs(Reserved, RISCW::X4); // tp

  return Reserved;
}

bool RISCWRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                           int SPAdj,
                                           unsigned FIOperandNum,
                                           RegScavenger *RS) const {
  llvm_unreachable("Unsupported eliminateFrameIndex");
  return false;
}

bool
RISCWRegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const {
  return true;
}

bool
RISCWRegisterInfo::requiresFrameIndexScavenging(
                                            const MachineFunction &MF) const {
  return true;
}

bool
RISCWRegisterInfo::requiresFrameIndexReplacementScavenging(
                                            const MachineFunction &MF) const {
  return true;
}

bool
RISCWRegisterInfo::trackLivenessAfterRegAlloc(const MachineFunction &MF) const {
  return true;
}

Register RISCWRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  const TargetFrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? RISCW::X2 /*RISCW::X8, don't known what it is means */: RISCW::X2;
//  llvm_unreachable("Unsupported getFrameRegister");
}
