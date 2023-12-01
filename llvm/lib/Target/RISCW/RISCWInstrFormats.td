// Format specifies the encoding used by the instruction. This is used by
// RISCVMCCodeEmitter to determine which form of fixup to use. These
// definitions must be kept in-sync with RISCVBaseInfo.h.
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
class RISCWOpcode<bits<7> val> {
  bits<7> Value = val;
}
def OPC_LOAD      : RISCWOpcode<0b0000011>;
def OPC_LOAD_FP   : RISCWOpcode<0b0000111>;
def OPC_MISC_MEM  : RISCWOpcode<0b0001111>;
def OPC_OP_IMM    : RISCWOpcode<0b0010011>;
def OPC_AUIPC     : RISCWOpcode<0b0010111>;
def OPC_OP_IMM_32 : RISCWOpcode<0b0011011>;
def OPC_STORE     : RISCWOpcode<0b0100011>;
def OPC_STORE_FP  : RISCWOpcode<0b0100111>;
def OPC_AMO       : RISCWOpcode<0b0101111>;
def OPC_OP        : RISCWOpcode<0b0110011>;
def OPC_LUI       : RISCWOpcode<0b0110111>;
def OPC_OP_32     : RISCWOpcode<0b0111011>;
def OPC_MADD      : RISCWOpcode<0b1000011>;
def OPC_MSUB      : RISCWOpcode<0b1000111>;
def OPC_NMSUB     : RISCWOpcode<0b1001011>;
def OPC_NMADD     : RISCWOpcode<0b1001111>;
def OPC_OP_FP     : RISCWOpcode<0b1010011>;
def OPC_BRANCH    : RISCWOpcode<0b1100011>;
def OPC_JALR      : RISCWOpcode<0b1100111>;
def OPC_JAL       : RISCWOpcode<0b1101111>;
def OPC_SYSTEM    : RISCWOpcode<0b1110011>;

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
