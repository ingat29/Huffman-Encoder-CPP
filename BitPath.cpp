#include "BitPath.h"

BitPath::BitPath() {
    this->top = 0;
    this->bits[32] = {0};
    this->length = 0;
}
BitPath::BitPath(const BitPath &bitPath) {
    this->top = bitPath.top;
    this->length = bitPath.length;
    for (int i = 0; i < this->length; i++) {
        this->bits[i] = bitPath.bits[i];
    }
}
bool BitPath::PushBit(bool bit) {
    if (this->length !=32) {
        this->top = static_cast<uint32_t>(bit);
        this->bits[this->length++] = bit;
        return true;
    }
    return false;
}

bool BitPath::PopBit() {
    if (length > 0) {
        this->top = this->bits[--this->length - 1];
    }
    return false;
}

// std::string BitPath::ToString() const {
//     return std::bitset<32>(bits).to_string().substr(32 - length); // Convert to binary string
// }

int BitPath::GetLength() const {
    return length;
}
std::ostream& operator<<(std::ostream& os, const BitPath& bitPath) {
    BitPath bitPathCopy = bitPath;
    for (int i = 0; i < bitPath.GetLength(); i++) {
        os<<bitPathCopy.top;
        bitPathCopy.PopBit();
    }
    return os;
}
