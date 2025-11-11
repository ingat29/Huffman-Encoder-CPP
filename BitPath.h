#pragma once
#ifndef BITPATH_H
#define BITPATH_H
#include <string>
#include <bitset>
#include <cstdint>
#include <iostream>

class BitPath {
private:
    uint8_t bits[32/* 256/8 */];
    uint32_t top;
    uint8_t length;
public:
    BitPath();
    BitPath(const BitPath& bitPath);
    bool PushBit(bool bit);
    bool PopBit();
    // std::string ToString()const;
    int GetLength()const;
    friend class Utils;
    friend std::ostream& operator<<(std::ostream& os, const BitPath& bitPath);
};



#endif //BITPATH_H
