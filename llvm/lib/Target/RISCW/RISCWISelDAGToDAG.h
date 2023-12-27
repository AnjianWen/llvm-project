#ifndef LLVM_LIB_TARGET_RISCW_RISCWISELDAGTODAG_H
#define LLVM_LIB_TARGET_RISCW_RISCWISELDAGTODAG_H

#include "RISCWSubtarget.h"
#include "RISCWTargetMachine.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

namespace llvm {
class RISCWDAGToDAGISel : public SelectionDAGISel {
public:
  static char ID;

  explicit RISCWDAGToDAGISel(RISCWTargetMachine &TM, CodeGenOptLevel OL)
      : SelectionDAGISel(ID, TM, OL) {}

  // Pass Name
  StringRef getPassName() const override {
    return "RISCW DAG->DAG Pattern Instruction Selection";
  }

  bool runOnMachineFunction(MachineFunction &MF) override;

  void Select(SDNode *Node) override;

#include "RISCWGenDAGISel.inc"

private:
  const RISCWSubtarget *Subtarget;
};
}

#endif // end LLVM_LIB_TARGET_RISCW_RISCWISELDAGTODAG_H
