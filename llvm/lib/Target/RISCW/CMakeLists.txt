add_llvm_component_group(RISCW)

set(LLVM_TARGET_DEFINITIONS RISCW.td)

tablegen(LLVM RISCWGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM RISCWGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM RISCWGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM RISCWGenMCPseudoLowering.inc -gen-pseudo-lowering)

add_public_tablegen_target(RISCWCommonTableGen)

add_llvm_target(RISCWCodeGen
  RISCWTargetMachine.cpp

  LINK_COMPONENTS
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
