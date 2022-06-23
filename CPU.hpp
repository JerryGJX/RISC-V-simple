//
// Created by JerryGuo on 2022/6/22.
//

#ifndef INSTRUCTION_HPP__CPU_HPP_
#define INSTRUCTION_HPP__CPU_HPP_
#include "memory.hpp"
#include "instruction.hpp"
#include "iostream"
namespace RISC_V {
class ALU {
//  static uint32_t Cal(const Instruction &ins, const Decoder &decoder, Memory::Register &reg) {
//    switch (ins.op_type) {
//      case LUI:return ins.imm << 12;
//      case AUIPC:return reg.ReadPC() + (ins.imm << 12);
//      case JALR:return (reg.ReadNormal(ins.rs1) + ins.imm) & ~1;
//      case LB:return RISC_V::Decoder::Sext(reg.ReadNormal(ins.rs1) + ins.imm, 7);
//      case LH:return RISC_V::Decoder::Sext(reg.ReadNormal(ins.rs1) + ins.imm, 15);
//      case LW:return RISC_V::Decoder::Sext(reg.ReadNormal(ins.rs1) + ins.imm, 31);
//      case LBU:return RISC_V::Decoder::getPart(reg.ReadNormal(ins.rs1) + ins.imm, 7, 0);
//      case LHU:return RISC_V::Decoder::getPart(reg.ReadNormal(ins.rs1) + ins.imm, 15, 0);
//      case SB:return RISC_V::Decoder::getPart(reg.ReadNormal(ins.rs2), 7, 0);
//      case SH:return RISC_V::Decoder::getPart(reg.ReadNormal(ins.rs2), 15, 0);
//      case SW:return RISC_V::Decoder::getPart(reg.ReadNormal(ins.rs2), 31, 0);
//      case ADDI:return reg.ReadNormal(ins.rs2) + ins.imm;
//      case SLTI:return reg.ReadNormal(ins.rs2) < ins.imm;
//      case SLTIU:return (int32_t) reg.ReadNormal(ins.rs2) < (int32_t) ins.imm;
//      case XORI:return reg.ReadNormal(ins.rs1) ^ ins.imm;
//      case ORI:return reg.ReadNormal(ins.rs1) | ins.imm;
//      case ANDI:return reg.ReadNormal(ins.rs1) & ins.imm;
//      case SLLI:
//        if (ins.shamt & 1 << 5)
//          case SRLI:return;
//      case SRAI:return;
//      case ADD:return;
//      case SUB:return;
//      case SLL:return;
//      case SLT:return;
//      case SLTU:return;
//      case XOR:return;
//      case SRL:return;
//      case SRA:return;
//      case OR:return;
//      case AND:return;
//    }
//  }

};

class CPU {
  Memory::Register reg{};
  Memory::RAM ram{};
  Decoder decoder{};
  ALU alu{};
 public:
  CPU() = default;

  void Init() {
    std::string str_ca;
    uint32_t start_pos = 0;
    while (std::getline(std::cin, str_ca)) {

//      std::cout<<str_ca<<std::endl;
//      continue;


      if (str_ca[0] == '@') {
        start_pos = std::stoi(str_ca.substr(1), nullptr, 16);
        continue;
      }
      for (int i = 0; i < str_ca.size(); i += 3) {
        std::string Byte = str_ca.substr(i, 2);
        ram.Write(start_pos, Byte);

        //std::cout << "startPos = " << start_pos << " ## " << std::hex << ram.Read(start_pos) << std::endl;
//        printf("pos: %d, mem: %02X\n", start_pos, ram[start_pos]);
        start_pos++;
      }
    }
    Process();
  }

  void Process() {
    std::string flag = "0ff00513";

    while (true) {
      uint32_t pos = reg.ReadPC();
      uint32_t ins = ram.ReadIns(pos);
      Instruction ins_ca;
      RISC_V::Decoder::decode(ins, ins_ca);

      //reg.PrintReg();


      //std::cout << "###Ins =" << ins << std::endl;
      //std::cout << ins_ca << std::endl;

      if (ins == std::stoi(flag, nullptr, 16)) {
        printf("%d",reg.ReadNormal(10) & 255u);
        return;
      }

      switch (ins_ca.op_type) {
        case LUI:Pro_LUI(ins_ca);
          continue;
        case AUIPC:Pro_AUIPC(ins_ca);
          continue;
        case JAL:Pro_JAL(ins_ca);
          continue;
        case JALR:Pro_JALR(ins_ca);
          continue;
        case BEQ:Pro_BEQ(ins_ca);
          continue;
        case BNE:Pro_BNE(ins_ca);
          continue;
        case BLT:Pro_BLT(ins_ca);
          continue;
        case BGE:Pro_BGE(ins_ca);
          continue;
        case BLTU:Pro_BLTU(ins_ca);
          continue;
        case BGEU:Pro_BGEU(ins_ca);
          continue;
        case LB:Pro_LB(ins_ca);
          continue;
        case LH:Pro_LH(ins_ca);
          continue;
        case LW:Pro_LW(ins_ca);
          continue;
        case LBU:Pro_LBU(ins_ca);
          continue;
        case LHU:Pro_LHU(ins_ca);
          continue;
        case SB:Pro_SB(ins_ca);
          continue;
        case SH:Pro_SH(ins_ca);
          continue;
        case SW:Pro_SW(ins_ca);
          continue;
        case ADDI:Pro_ADDI(ins_ca);
          continue;
        case SLTI:Pro_SLTI(ins_ca);
          continue;
        case SLTIU:Pro_SLTIU(ins_ca);
          continue;
        case XORI:Pro_XORI(ins_ca);
          continue;
        case ORI:Pro_ORI(ins_ca);
          continue;
        case ANDI:Pro_ANDI(ins_ca);
          continue;
        case SLLI:Pro_SLLI(ins_ca);
          continue;
        case SRLI:Pro_SRLI(ins_ca);
          continue;
        case SRAI:Pro_SRAI(ins_ca);
          continue;
        case ADD:Pro_ADD(ins_ca);
          continue;
        case SUB:Pro_SUB(ins_ca);
          continue;
        case SLL:Pro_SLL(ins_ca);
          continue;
        case SLT:Pro_SLT(ins_ca);
          continue;
        case SLTU:Pro_SLTU(ins_ca);
          continue;
        case XOR:Pro_XOR(ins_ca);
          continue;
        case SRL:Pro_SRL(ins_ca);
          continue;
        case SRA:Pro_SRA(ins_ca);
          continue;
        case OR:Pro_OR(ins_ca);
          continue;
        case AND:Pro_AND(ins_ca);
          continue;
      }
    }
  }

  void Pro_LUI(const Instruction &ins) {
    reg.WriteNormal(ins.rd, ins.imm);

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_AUIPC(const Instruction &ins) {
    reg.WritePC(reg.ReadPC() + ins.imm);
    reg.WriteNormal(ins.rd, reg.ReadPC());

  };

  void Pro_JAL(const Instruction &ins) {
    reg.WriteNormal(ins.rd, reg.ReadPC() + 4);
    reg.WritePC(reg.ReadPC() + ins.imm);
  };

  void Pro_JALR(const Instruction &ins) {
    reg.WriteNormal(ins.rd, reg.ReadPC() + 4);
    reg.WritePC((reg.ReadNormal(ins.rs1) + ins.imm) & ~(uint32_t) 1);
  };

  void Pro_BEQ(const Instruction &ins) {
    if (reg.ReadNormal(ins.rs1) == reg.ReadNormal(ins.rs2))
      reg.WritePC(reg.ReadPC() + ins.imm);
    else reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_BNE(const Instruction &ins) {
    if (reg.ReadNormal(ins.rs1) != reg.ReadNormal(ins.rs2))
      reg.WritePC(reg.ReadPC() + ins.imm);
    else reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_BLT(const Instruction &ins) {
    if ((int32_t) reg.ReadNormal(ins.rs1) < (int32_t) reg.ReadNormal(ins.rs2))
      reg.WritePC(reg.ReadPC() + ins.imm);
    else reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_BGE(const Instruction &ins) {
    if ((int32_t) reg.ReadNormal(ins.rs1) >= (int32_t) reg.ReadNormal(ins.rs2))
      reg.WritePC(reg.ReadPC() + ins.imm);
    else reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_BLTU(const Instruction &ins) {
    if (reg.ReadNormal(ins.rs1) < reg.ReadNormal(ins.rs2))
      reg.WritePC(reg.ReadPC() + ins.imm);
    else reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_BGEU(const Instruction &ins) {
    if (reg.ReadNormal(ins.rs1) >= reg.ReadNormal(ins.rs2))
      reg.WritePC(reg.ReadPC() + ins.imm);
    else reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_LB(const Instruction &ins) {
    uint32_t ca = ram.Read(reg.ReadNormal(ins.rs1) + (int32_t) ins.imm);
    ca = RISC_V::Decoder::Sext(ca, 7);
    reg.WriteNormal(ins.rd, ca);

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_LH(const Instruction &ins) {
    uint32_t ca1 = ram.Read(reg.ReadNormal(ins.rs1) + (int32_t) ins.imm);
    uint32_t ca2 = ram.Read(reg.ReadNormal(ins.rs1) + (int32_t) ins.imm + 1);
    uint32_t ca = (ca2 << 8) + ca1;
    ca = RISC_V::Decoder::Sext(ca, 15);
    reg.WriteNormal(ins.rd, ca);

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_LW(const Instruction &ins) {
    uint32_t ca1 = ram.Read(reg.ReadNormal(ins.rs1) + (int32_t) ins.imm);
    uint32_t ca2 = ram.Read(reg.ReadNormal(ins.rs1) + (int32_t) ins.imm + 1);
    uint32_t ca3 = ram.Read(reg.ReadNormal(ins.rs1) + (int32_t) ins.imm + 2);
    uint32_t ca4 = ram.Read(reg.ReadNormal(ins.rs1) + (int32_t) ins.imm + 3);

    uint32_t ca = (ca4 << 24) + (ca3 << 16) + (ca2 << 8) + ca1;
    //ca = RISC_V::Decoder::Sext(ca, 15);
    reg.WriteNormal(ins.rd, ca);

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_LBU(const Instruction &ins) {
    uint32_t ca = ram.Read(reg.ReadNormal(ins.rs1) + ins.imm);
    reg.WriteNormal(ins.rd, ca);

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_LHU(const Instruction &ins) {
    uint32_t ca1 = ram.Read(reg.ReadNormal(ins.rs1) + ins.imm);
    uint32_t ca2 = ram.Read(reg.ReadNormal(ins.rs1) + ins.imm + 1);
    uint32_t ca = (ca2 << 8) + ca1;

    reg.WriteNormal(ins.rd, ca);

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_SB(const Instruction &ins) {
    ram.Write(reg.ReadNormal(ins.rs1) + ins.imm, (uint8_t) reg.ReadNormal(ins.rs2));

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_SH(const Instruction &ins) {
    ram.Write(reg.ReadNormal(ins.rs1) + ins.imm, (uint8_t) reg.ReadNormal(ins.rs2));
    ram.Write(reg.ReadNormal(ins.rs1) + ins.imm + 1, (uint8_t) (reg.ReadNormal(ins.rs2) >> 8));

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_SW(const Instruction &ins) {
    ram.Write(reg.ReadNormal(ins.rs1) + ins.imm, (uint8_t) reg.ReadNormal(ins.rs2));
    ram.Write(reg.ReadNormal(ins.rs1) + ins.imm + 1, (uint8_t) (reg.ReadNormal(ins.rs2) >> 8));
    ram.Write(reg.ReadNormal(ins.rs1) + ins.imm + 2, (uint8_t) (reg.ReadNormal(ins.rs2) >> 16));
    ram.Write(reg.ReadNormal(ins.rs1) + ins.imm + 3, (uint8_t) (reg.ReadNormal(ins.rs2) >> 24));

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_ADDI(const Instruction &ins) {
    reg.WriteNormal(ins.rd, reg.ReadNormal(ins.rs1) + ins.imm);

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_SLTI(const Instruction &ins) {
    reg.WriteNormal(ins.rd, (int32_t) reg.ReadNormal(ins.rs1) < (int32_t) ins.imm);

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_SLTIU(const Instruction &ins) {
    reg.WriteNormal(ins.rd, reg.ReadNormal(ins.rs1) < ins.imm);

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_XORI(const Instruction &ins) {
    reg.WriteNormal(ins.rd, reg.ReadNormal(ins.rs1) ^ ins.imm);

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_ORI(const Instruction &ins) {
    reg.WriteNormal(ins.rd, reg.ReadNormal(ins.rs1) | ins.imm);

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_ANDI(const Instruction &ins) {
    reg.WriteNormal(ins.rd, reg.ReadNormal(ins.rs1) & ins.imm);

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_SLLI(const Instruction &ins) {
//    std::cout << ins << std::endl;
    reg.WriteNormal(ins.rd, reg.ReadNormal(ins.rs1) << ins.imm);

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_SRLI(const Instruction &ins) {
//    if (ins.shamt & 1 << 5)
      reg.WriteNormal(ins.rd, reg.ReadNormal(ins.rs1) >> ins.shamt);

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_SRAI(const Instruction &ins) {
    //if (!(ins.shamt & 1 << 5))return;
    uint32_t move = ins.shamt;
    uint32_t ca = reg.ReadNormal(ins.rs1) >> move;
    reg.WriteNormal(ins.rd, RISC_V::Decoder::Sext(ca, 31 - move));
    reg.WritePC(reg.ReadPC() + 4);

  };

  void Pro_ADD(const Instruction &ins) {
    reg.WriteNormal(ins.rd, reg.ReadNormal(ins.rs1) + reg.ReadNormal(ins.rs2));

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_SUB(const Instruction &ins) {
    reg.WriteNormal(ins.rd, reg.ReadNormal(ins.rs1) - reg.ReadNormal(ins.rs2));

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_SLL(const Instruction &ins) {
    reg.WriteNormal(ins.rd, reg.ReadNormal(ins.rs1) << RISC_V::Decoder::getPart(reg.ReadNormal(ins.rs2), 4, 0));

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_SLT(const Instruction &ins) {
    reg.WriteNormal(ins.rd, (int32_t) reg.ReadNormal(ins.rs1) < (int32_t) reg.ReadNormal(ins.rs2));

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_SLTU(const Instruction &ins) {
    reg.WriteNormal(ins.rd, reg.ReadNormal(ins.rs1) < reg.ReadNormal(ins.rs2));

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_XOR(const Instruction &ins) {
    reg.WriteNormal(ins.rd, reg.ReadNormal(ins.rs1) ^ reg.ReadNormal(ins.rs2));

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_SRL(const Instruction &ins) {
    reg.WriteNormal(ins.rd, reg.ReadNormal(ins.rs1) >> RISC_V::Decoder::getPart(reg.ReadNormal(ins.rs2), 4, 0));

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_SRA(const Instruction &ins) {
    uint32_t move = RISC_V::Decoder::getPart(reg.ReadNormal(ins.rs2), 4, 0);
    uint32_t ca = reg.ReadNormal(ins.rs1) >> move;
    reg.WriteNormal(ins.rd, RISC_V::Decoder::Sext(ca, 31 - move));

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_OR(const Instruction &ins) {
    reg.WriteNormal(ins.rd, reg.ReadNormal(ins.rs1) | reg.ReadNormal(ins.rs2));

    reg.WritePC(reg.ReadPC() + 4);
  };

  void Pro_AND(const Instruction &ins) {
    reg.WriteNormal(ins.rd, reg.ReadNormal(ins.rs1) & reg.ReadNormal(ins.rs2));

    reg.WritePC(reg.ReadPC() + 4);
  };

};
}

#endif //INSTRUCTION_HPP__CPU_HPP_
