add_llvm_component_library(LLVMRISCWDesc
  RISCWMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  RISCWInfo
  Support
  TargetParser

  ADD_TO_COMPONENT
  RISCW
)
