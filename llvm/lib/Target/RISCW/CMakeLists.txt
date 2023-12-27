add_llvm_component_group(RISCW)

set(LLVM_TARGET_DEFINITIONS RISCW.td)

tablegen(LLVM RISCWGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM RISCWGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM RISCWGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM RISCWGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM RISCWGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM RISCWGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM RISCWGenCallingConv.inc -gen-callingconv)

add_public_tablegen_target(RISCWCommonTableGen)

add_llvm_target(RISCWCodeGen
  RISCWAsmPrinter.cpp
  RISCWFrameLowering.cpp
  RISCWInstrInfo.cpp
  RISCWISelLowering.cpp
  RISCWRegisterInfo.cpp
  RISCWSubtarget.cpp
  RISCWTargetObjectFile.cpp
  RISCWISelDAGToDAG.cpp
  RISCWTargetMachine.cpp
  RISCWMachineFunctionInfo.cpp  

  LINK_COMPONENTS
  AsmPrinter
  CodeGen
  Core
  MC
  SelectionDAG
  RISCWDesc
  RISCWInfo
  Support
  Target

  ADD_TO_COMPONENT
  RISCW
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
