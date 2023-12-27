class InstFormat<bits<5> val> {
  bits<5> Value = val;
}
def InstFormatPseudo : InstFormat<0>;
def InstFormatR      : InstFormat<1>;
def InstFormatR4     : InstFormat<2>;
def InstFormatI      : InstFormat<3>;
def InstFormatS      : InstFormat<4>;
def InstFormatB      : InstFormat<5>;
def InstFormatU      : InstFormat<6>;
def InstFormatJ      : InstFormat<7>;
def InstFormatCR     : InstFormat<8>;
def InstFormatCI     : InstFormat<9>;
def InstFormatCSS    : InstFormat<10>;
def InstFormatCIW    : InstFormat<11>;
def InstFormatCL     : InstFormat<12>;
def InstFormatCS     : InstFormat<13>;
def InstFormatCA     : InstFormat<14>;
def InstFormatCB     : InstFormat<15>;
def InstFormatCJ     : InstFormat<16>;
def InstFormatCU     : InstFormat<17>;
def InstFormatCLB    : InstFormat<18>;
def InstFormatCLH    : InstFormat<19>;
def InstFormatCSB    : InstFormat<20>;
def InstFormatCSH    : InstFormat<21>;
def InstFormatOther  : InstFormat<22>;

// The following opcode names match those given in Table 19.1 in the
// RISC-V User-level ISA specification ("RISC-V base opcode map").
class RISCWOpcode<string name, bits<7> val> {
  string Name = name;
  bits<7> Value = val;
}

def OPC_LOAD      : RISCWOpcode<"LOAD",      0b0000011>;
def OPC_LOAD_FP   : RISCWOpcode<"LOAD_FP",   0b0000111>;
def OPC_CUSTOM_0  : RISCWOpcode<"CUSTOM_0",  0b0001011>;
def OPC_MISC_MEM  : RISCWOpcode<"MISC_MEM",  0b0001111>;
def OPC_OP_IMM    : RISCWOpcode<"OP_IMM",    0b0010011>;
def OPC_AUIPC     : RISCWOpcode<"AUIPC",     0b0010111>;
def OPC_OP_IMM_32 : RISCWOpcode<"OP_IMM_32", 0b0011011>;
def OPC_STORE     : RISCWOpcode<"STORE",     0b0100011>;
def OPC_STORE_FP  : RISCWOpcode<"STORE_FP",  0b0100111>;
def OPC_CUSTOM_1  : RISCWOpcode<"CUSTOM_1",  0b0101011>;
def OPC_AMO       : RISCWOpcode<"AMO",       0b0101111>;
def OPC_OP        : RISCWOpcode<"OP",        0b0110011>;
def OPC_LUI       : RISCWOpcode<"LUI",       0b0110111>;
def OPC_OP_32     : RISCWOpcode<"OP_32",     0b0111011>;
def OPC_MADD      : RISCWOpcode<"MADD",      0b1000011>;
def OPC_MSUB      : RISCWOpcode<"MSUB",      0b1000111>;
def OPC_NMSUB     : RISCWOpcode<"NMSUB",     0b1001011>;
def OPC_NMADD     : RISCWOpcode<"NMADD",     0b1001111>;
def OPC_OP_FP     : RISCWOpcode<"OP_FP",     0b1010011>;
def OPC_OP_V      : RISCWOpcode<"OP_V",      0b1010111>;
def OPC_CUSTOM_2  : RISCWOpcode<"CUSTOM_2",  0b1011011>;
def OPC_BRANCH    : RISCWOpcode<"BRANCH",    0b1100011>;
def OPC_JALR      : RISCWOpcode<"JALR",      0b1100111>;
def OPC_JAL       : RISCWOpcode<"JAL",       0b1101111>;
def OPC_SYSTEM    : RISCWOpcode<"SYSTEM",    0b1110011>;
def OPC_OP_P      : RISCWOpcode<"OP_P",      0b1110111>;
def OPC_CUSTOM_3  : RISCWOpcode<"CUSTOM_3",  0b1111011>;


class RWInst<dag outs, dag ins, string opcodestr, string argstr,
             list<dag> pattern, InstFormat format>
    : Instruction {
  field bits<32> Inst;
  field bits<32> SoftFail = 0;
  let Size = 4;
  bits<7> Opcode = 0;
  let Inst{6-0} = Opcode;
  let Namespace = "RISCW";
  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString = opcodestr # "\t" # argstr;
  let Pattern = pattern;
  let TSFlags{4-0} = format.Value;
}

// Pseudo instructions
class Pseudo<dag outs, dag ins, list<dag> pattern, string opcodestr = "",
             string argstr = "">
    : RWInst<outs, ins, opcodestr, argstr, pattern, InstFormatPseudo>,
      Sched<[]> {
  let isPseudo = 1;
  let isCodeGenOnly = 1;
}

class RWInstR<bits<7> funct7, bits<3> funct3, RISCWOpcode opcode, dag outs,
              dag ins, string opcodestr, string argstr>
    : RWInst<outs, ins, opcodestr, argstr, [], InstFormatR> {
  bits<5> rs2;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31-25} = funct7;
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Opcode = opcode.Value;
}

class RWInstI<bits<3> funct3, RISCWOpcode opcode, dag outs, dag ins,
              string opcodestr, string argstr>
    : RWInst<outs, ins, opcodestr, argstr, [], InstFormatI> {
  bits<12> imm12;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31-20} = imm12;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Opcode = opcode.Value;
}

class RWInstU<RISCWOpcode opcode, dag outs, dag ins, string opcodestr,
              string argstr>
    : RWInst<outs, ins, opcodestr, argstr, [], InstFormatU> {
  bits<20> imm20;
  bits<5> rd;

  let Inst{31-12} = imm20;
  let Inst{11-7} = rd;
  let Inst{6-0} = opcode.Value;
}
