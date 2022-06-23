//
// Created by JerryGuo on 2022/6/21.
//

#ifndef RISC_V__INSTRUCTION_HPP_
#define RISC_V__INSTRUCTION_HPP_

#include <string>
#include "memory.hpp"
//#include <tuple>
#include <map>
#include <bitset>
#include <ostream>

namespace RISC_V {
enum opType {
  LUI, AUIPC, JAL, JALR, BEQ, BNE, BLT, BGE, BLTU, BGEU, LB, LH, LW,
  LBU, LHU, SB, SH, SW, ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI,
  SRAI, ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND
};

const std::string opName[37] = {
    "LUI", "AUIPC", "JAL", "JALR",
    "BEQ", "BNE", "BLT", "BGE", "BLTU", "BGEU",
    "LB", "LH", "LW", "LBU", "LHU", "SB", "SH", "SW",
    "ADDI", "SLTI", "SLTIU", "XORI", "ORI", "ANDI", "SLLI", "SRLI", "SRAI",
    "ADD", "SUB", "SLL", "SLT", "SLTU", "XOR", "SRL", "SRA", "OR", "AND"
};

enum instructionType {
  R_type, I_type, S_type, B_type, U_type, J_type
};

const std::string insTypeName[6] = {
    "[R]", "[I]", "[S]", "[B]", "[U]", "[J]"
};

instructionType ToInsType[37] = {
    U_type, U_type, J_type, I_type,
    B_type, B_type, B_type, B_type, B_type, B_type,
    I_type, I_type, I_type, I_type, I_type,
    S_type, S_type, S_type,
    I_type, I_type, I_type, I_type, I_type, I_type, I_type, I_type, I_type,
    R_type, R_type, R_type, R_type, R_type, R_type, R_type, R_type, R_type, R_type

};

class Instruction {
 public:
  opType op_type = LUI;
  uint32_t rs1 = 0, rs2 = 0, rd = 0, shamt = 0;
  uint32_t imm = 0;

  Instruction() = default;
  void Init() {
    op_type = LUI,  rs1 = 0, rs2 = 0,
    rd = 0, imm = 0, shamt = 0;
  }

//  void Print() {
//    std::string ca;
//    std::bitset<32> bits;
//    ca += "opName = " + opName[op_type] + "\n";
//    bits = opcode;
//    ca += "opCode = " + bits.to_string() + "\n";
//    bits = rs1;
//    ca += "rs1 = " + bits.to_string() + "\n";
//    bits = rs2;
//    ca += "rs2 = " + bits.to_string() + "\n";
//    bits = rd;
//    ca += "rd = " + bits.to_string() + "\n";
//    bits = funct3;
//    ca += "funct3 = " + bits.to_string() + "\n";
//    bits = funct7;
//    ca += "funct7 = " + bits.to_string() + "\n";
//    bits = imm;
//    ca += "imm = " + bits.to_string() + "\n";
//    bits = shamt;
//    ca += "shamt = " + bits.to_string() + "\n";
//
//  }
  friend std::ostream &operator<<(std::ostream &os, const Instruction &instruction) {
    os << "inst type: " << insTypeName[ToInsType[instruction.op_type]]
       << opName[instruction.op_type] << ", "
       << " rs1: " << instruction.rs1 << ", "
       << " rs2: " << instruction.rs2 << ", "
       << " imm: " << (int32_t) instruction.imm << ", "
       << " rd: " << instruction.rd;
//        << ", "
//       << " funct3: " << instruction.funct3 << ", "
//       << " funct7: " << instruction.funct7 << ", "
//
//       << " shamt: " << instruction.shamt;

    return os;
  }

};

class Decoder {
 public:
  inline static uint32_t getPart(uint32_t ins, int high, int low) {
    if (high == 31)return ins >> low;
    return (ins & (1 << (high + 1)) - 1) >> low;
  }

  inline static uint32_t Sext(uint32_t ins, int32_t top) {
    if (ins & (1 << top))return ins | -(1 << top);
    return ins;
  }

  static opType getOpType(uint32_t opcode, uint32_t func3, uint32_t func7) {
    switch (opcode) {
      case 0b0110111: return LUI;
      case 0b0010111: return AUIPC;
      case 0b1101111: return JAL;
      case 0b1100111: return JALR;
      case 0b1100011: {
        switch (func3) {
          case 0b000: return BEQ;
          case 0b001: return BNE;
          case 0b100: return BLT;
          case 0b101: return BGE;
          case 0b110: return BLTU;
          case 0b111: return BGEU;
        }

      }
      case 0b0000011: {
        switch (func3) {
          case 0b000: return LB;
          case 0b001: return LH;
          case 0b010: return LW;
          case 0b100: return LBU;
          case 0b101: return LHU;
        }

      }
      case 0b0100011: {
        switch (func3) {
          case 0b000: return SB;
          case 0b001: return SH;
          case 0b010: return SW;
        }

      }
      case 0b0010011: {
        switch (func3) {
          case 0b000: return ADDI;
          case 0b010: return SLTI;
          case 0b011: return SLTIU;
          case 0b100: return XORI;
          case 0b110: return ORI;
          case 0b111: return ANDI;
          case 0b001: return SLLI;
          case 0b101: return (func7 != 0) ? SRAI : SRLI;
        }

      }
      case 0b0110011: {
        switch (func3) {
          case 0b000: return (func7 != 0) ? SUB : ADD;
          case 0b001: return SLL;
          case 0b010: return SLT;
          case 0b011: return SLTU;
          case 0b100: return XOR;
          case 0b101: return (func7 != 0) ? SRA : SRL;
          case 0b110: return OR;
          case 0b111: return AND;
        }

      }
    }
  }

  static void decode(uint32_t ins, Instruction &ins_ca) {
    ins_ca.Init();
//    ins_ca.opcode = getPart(ins, 6, 0);
//    ins_ca.funct3 = getPart(ins, 14, 12);
//    ins_ca.funct7 = getPart(ins, 31, 25);
    ins_ca.op_type = getOpType(getPart(ins, 6, 0), getPart(ins, 14, 12), getPart(ins, 31, 25));
    instructionType insType_ca = ToInsType[ins_ca.op_type];
    ins_ca.imm = getImm(insType_ca, ins);
    if (insType_ca != U_type && insType_ca != J_type)
    ins_ca.rs1 = getPart(ins, 19, 15);
    if (insType_ca == R_type || insType_ca == S_type || insType_ca == B_type)
    ins_ca.rs2 = getPart(ins, 24, 20);
    if (insType_ca != S_type && insType_ca != B_type)
    ins_ca.rd = getPart(ins, 11, 7);
    ins_ca.shamt = ins >> 20 & 0b111111;
  }

  static uint32_t getImm(const instructionType &ins_type, uint32_t ins) {
    uint32_t ans = 0;
    switch (ins_type) {
      case R_type:return ans;
      case I_type:
        ans = (getPart(ins, 31, 31) << 11)
            + (getPart(ins, 30, 25) << 5)
            + (getPart(ins, 24, 21) << 1)
            + getPart(ins, 20, 20);
        ans = Sext(ans, 11);
        return ans;
      case S_type:
        ans = (getPart(ins, 31, 31) << 11)
            + (getPart(ins, 30, 25) << 5)
            + (getPart(ins, 11, 8) << 1)
            + getPart(ins, 7, 7);
        ans = Sext(ans, 11);
        return ans;
      case B_type:
        ans = (getPart(ins, 31, 31) << 12)
            + (getPart(ins, 7, 7) << 11)
            + (getPart(ins, 30, 25) << 5)
            + (getPart(ins, 11, 8) << 1);
        ans = Sext(ans, 12);
        return ans;
      case U_type:
        ans = (getPart(ins, 31, 31) << 31)
            + (getPart(ins, 30, 20) << 20)
            + (getPart(ins, 19, 12) << 12);
        return ans;
      case J_type:
        ans = (getPart(ins, 31, 31) << 20)
            + (getPart(ins, 19, 12) << 12)
            + (getPart(ins, 20, 20) << 11)
            + (getPart(ins, 30, 25) << 5)
            + (getPart(ins, 24, 21) << 1);
        ans = Sext(ans, 20);
        return ans;
    }
  }

};

}

#endif //RISC_V__INSTRUCTION_HPP_
