def RISCW_CCallingConv : CallingConv<[
  CCIfByVal<CCPassByVal<4, 4>>,

  CCIfType<[i1, i8, i16], CCPromoteToType<i32>>,

  CCIfType<[i32], CCAssignToReg<[X0, X1, X2, X3]>>,

  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;

def RISCW_CRetConv : CallingConv<[
  CCIfType<[i1, i8, i16], CCPromoteToType<i32>>,

  CCIfType<[i32], CCAssignToReg<[X0, X1, X2, X3]>>,

  CCIfType<[i32], CCAssignToStack<4, 4>>
]>;

def RISCW_CalleeSavedRegs : CalleeSavedRegs<(add X8, X9)>;
