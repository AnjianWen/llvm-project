#include "RISCWMCTargetDesc.h"
#include "TargetInfo/RISCWTargetInfo.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/ADT/STLExtras.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "RISCWGenInstrInfo.inc"

//#define GET_SUBTARGETINFO_MC_DESC
//#include "RISCWGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "RISCWGenRegisterInfo.inc"

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRISCWTargetMC() {
}
