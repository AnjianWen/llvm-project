include "llvm/Target/Target.td"

// Register Infomation
include "RISCWRegisterInfo.td"

// Calling Conversion
include "RISCWSchedule.td"

// Instruction Description
include "RISCWInstrInfo.td"

// Calling Convention
include "RISCWCallingConv.td"

//===----------------------------------------------------------------------===//
// RISCW processors supported
//===----------------------------------------------------------------------===//
def : ProcessorModel<"generic", NoSchedModel, []>;

def RISCWInstrInfo : InstrInfo;

def RISCW : Target {
  let InstructionSet = RISCWInstrInfo;
}
