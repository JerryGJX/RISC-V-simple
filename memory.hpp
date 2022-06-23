//
// Created by JerryGuo on 2022/6/21.
//

#ifndef RISC_V__MYDEF_HPP_
#define RISC_V__MYDEF_HPP_

#include <cstdint>
#include <cstring>
#include <ostream>
namespace Memory {
class RAM {
  static constexpr uint32_t RAM_LIMIT = 500000;
  uint8_t Storage[RAM_LIMIT] = {};
 public:
  RAM() = default;
//  void Init(){
//    Storage
//  }
  void Write(uint32_t pos, std::string &Byte) {
    Storage[pos] = std::stoi(Byte, nullptr, 16);
  }

  void Write(uint32_t pos, uint8_t Byte) {
    Storage[pos] = Byte;
  }

  uint32_t ReadIns(uint32_t pos) {
    return ((uint32_t) Storage[pos + 3] << 24) + ((uint32_t) Storage[pos + 2] << 16)
        + ((uint32_t) Storage[pos + 1] << 8) + (uint32_t) Storage[pos];
  }

  uint32_t Read(uint32_t pos) {
    return Storage[pos];
  }
  uint8_t &operator[](uint32_t i) { return Storage[i]; }
};

class Register {
  static constexpr uint32_t REG_LIMIT = 32;
  uint32_t normalRegister[REG_LIMIT] = {};
  uint32_t PCRegister = 0;
 public:
  Register() = default;
  void WriteNormal(uint32_t pos, uint32_t info) {
    if (pos == 0)return;
    normalRegister[pos] = info;
  }

  uint32_t ReadNormal(uint32_t pos) {
    return normalRegister[pos];
  }

  int32_t ReadNormal_s(uint32_t pos) {
    return (int32_t) normalRegister[pos];
  }

  void WritePC(uint32_t info) {
    PCRegister = info;
  }

  uint32_t ReadPC() const {
    return PCRegister;
  }

  void PrintReg() {
    for (int i = 0; i < 32; i++)std::cout << (int32_t)normalRegister[i] << " ";
    std::cout << std::endl;
    std::cout << "pc: " << (int32_t)PCRegister << std::endl;
  }

};
}

#endif //RISC_V__MYDEF_HPP_
