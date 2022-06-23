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

struct Tuple {
  uint32_t opcode = 0, func3 = 0, func7 = 0;
  Tuple() = default;
  Tuple(uint32_t func_1, uint32_t func_3, uint32_t func_7) : opcode(func_1), func3(func_3), func7(func_7) {};

  Tuple(const std::string &opcode_, const std::string &func3_, const std::string &func7_, int base = 2) {
    opcode = std::stoi(opcode_, nullptr, base);
    func3 = std::stoi(func3_, nullptr, base);
    func7 = std::stoi(func7_, nullptr, base);

    //std::cout << "##Test= " << opcode << "   " << func3 << "    " << func7 << std::endl;

  }

  Tuple &operator=(const Tuple &rhs) {
    if (this == &rhs)return *this;
    this->opcode = rhs.opcode;
    this->func3 = rhs.func3;
    this->func7 = rhs.func7;
    return *this;
  }

  bool operator==(const Tuple &rhs) const {
    return opcode == rhs.opcode &&
        func3 == rhs.func3 &&
        func7 == rhs.func7;
  }
  bool operator!=(const Tuple &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const Tuple &rhs) const {
    if (opcode < rhs.opcode)
      return true;
    if (rhs.opcode < opcode)
      return false;
    if (func3 < rhs.func3)
      return true;
    if (rhs.func3 < func3)
      return false;
    return func7 < rhs.func7;
  }
  bool operator>(const Tuple &rhs) const {
    return rhs < *this;
  }
  bool operator<=(const Tuple &rhs) const {
    return !(rhs < *this);
  }
  bool operator>=(const Tuple &rhs) const {
    return !(*this < rhs);
  }
};

std::map<Tuple, opType> ToOpType = {
    {Tuple("0110111", "0", "0"), LUI},
    {Tuple("0010111", "0", "0"), AUIPC},
    {Tuple("1101111", "0", "0"), JAL},
    {Tuple("1100111", "000", "0"), JALR},
    {Tuple("1100011", "000", "0"), BEQ},
    {Tuple("1100011", "001", "0"), BNE},
    {Tuple("1100011", "100", "0"), BLT},
    {Tuple("1100011", "101", "0"), BGE},
    {Tuple("1100011", "110", "0"), BLTU},
    {Tuple("1100011", "111", "0"), BGEU},
    {Tuple("0000011", "000", "0"), LB},
    {Tuple("0000011", "001", "0"), LH},
    {Tuple("0000011", "010", "0"), LW},
    {Tuple("0000011", "100", "0"), LBU},
    {Tuple("0000011", "101", "0"), LHU},
    {Tuple("0100011", "000", "0"), SB},
    {Tuple("0100011", "001", "0"), SH},
    {Tuple("0100011", "010", "0"), SW},
    {Tuple("0010011", "000", "0"), ADDI},
    {Tuple("0010011", "010", "0"), SLTI},
    {Tuple("0010011", "011", "0"), SLTIU},
    {Tuple("0010011", "100", "0"), XORI},
    {Tuple("0010011", "110", "0"), ORI},
    {Tuple("0010011", "111", "0"), ANDI},
    {Tuple("0010011", "001", "0000000"), SLLI},
    {Tuple("0010011", "101", "0000000"), SRLI},
    {Tuple("0010011", "101", "0100000"), SRAI},
    {Tuple("0110011", "000", "0000000"), ADD},
    {Tuple("0110011", "000", "0100000"), SUB},
    {Tuple("0110011", "001", "0000000"), SLL},
    {Tuple("0110011", "010", "0000000"), SLT},
    {Tuple("0110011", "011", "0000000"), SLTU},
    {Tuple("0110011", "100", "0000000"), XOR},
    {Tuple("0110011", "101", "0000000"), SRL},
    {Tuple("0110011", "101", "0100000"), SRA},
    {Tuple("0110011", "110", "0000000"), OR},
    {Tuple("0110011", "111", "0000000"), AND}
};

class Instruction {
 public:
  opType op_type = LUI;
  uint32_t opcode = 0, rs1 = 0, rs2 = 0, rd = 0, funct3 = 0, funct7 = 0, shamt = 0;
  uint32_t imm = 0;

  Instruction() = default;
  void Init() {
    op_type = LUI, opcode = 0, rs1 = 0, rs2 = 0,
    rd = 0, funct3 = 0, funct7 = 0, imm = 0, shamt = 0;
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
  static uint32_t getPart(uint32_t ins, int high, int low) {
    if (high == 31)return ins >> low;
    return (ins & (1 << (high + 1)) - 1) >> low;
  }

  static uint32_t Sext(uint32_t ins, int32_t top) {
    if (ins & (1 << top))return ins | -(1 << top);
    return ins;
  }

  static opType getOpType(uint32_t &opcode, uint32_t &func3, uint32_t &func7) {
    Tuple ca(opcode, func3, func7);
    auto res = ToOpType.find(ca);
    if (res != ToOpType.end())return res->second;
    func7 = 0;
    ca = Tuple(opcode, func3, 0);
    res = ToOpType.find(ca);
    if (res != ToOpType.end())return res->second;
    func3 = 0;
    ca = Tuple(opcode, 0, 0);
    res = ToOpType.find(ca);
    return res->second;
  }

  static void decode(uint32_t ins, Instruction &ins_ca) {
    ins_ca.Init();
    ins_ca.opcode = getPart(ins, 6, 0);
    ins_ca.funct3 = getPart(ins, 14, 12);
    ins_ca.funct7 = getPart(ins, 31, 25);
    ins_ca.op_type = getOpType(ins_ca.opcode, ins_ca.funct3, ins_ca.funct7);
    instructionType insType_ca = ToInsType[ins_ca.op_type];
    ins_ca.imm = getImm(insType_ca, ins);
    //if (insType_ca != U_type && insType_ca != J_type)
    ins_ca.rs1 = getPart(ins, 19, 15);
    //if (insType_ca == R_type || insType_ca == S_type || insType_ca == B_type)
    ins_ca.rs2 = getPart(ins, 24, 20);
    //if (insType_ca != S_type && insType_ca != B_type)
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
