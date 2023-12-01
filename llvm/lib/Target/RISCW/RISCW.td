include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Calling Conv, Instruction Descriptions, Register information, etc
//===----------------------------------------------------------------------===//

include "RISCWSchedule.td"
include "RISCWRegisterInfo.td"
include "RISCWInstrInfo.td"

def RISCWInstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// RISCW Target declaration
//===----------------------------------------------------------------------===//

def RISCW : Target {
  let InstructionSet = RISCWInstrInfo;
}
