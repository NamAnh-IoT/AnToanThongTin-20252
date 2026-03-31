#include <iostream>
#include <cstdint>
#include <iomanip>

// Hàm xoay bit trái (Left Rotation)
uint32_t rotl(uint32_t value, int shift) {
    return (value << shift) | (value >> (32 - shift));
}

// Một bước biến đổi Quarter-round trên 4 số 32-bit
void quarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d) {
    b ^= rotl(a + d, 7);
    c ^= rotl(b + a, 9);
    d ^= rotl(c + b, 13);
    a ^= rotl(d + c, 18);
}

void s20_hash(uint32_t seq[16]) {
    uint32_t x[16];
    for (int i = 0; i < 16; ++i) x[i] = seq[i];

    // Thực hiện 20 vòng (10 vòng đôi: cột rồi đến hàng)
    for (int i = 20; i > 0; i -= 2) {
        // Vòng cột (Column-round)
        quarterRound(x[0], x[4], x[8], x[12]);
        quarterRound(x[5], x[9], x[13], x[1]);
        quarterRound(x[10], x[14], x[2], x[6]);
        quarterRound(x[15], x[3], x[7], x[11]);

        // Vòng hàng (Row-round)
        quarterRound(x[0], x[1], x[2], x[3]);
        quarterRound(x[5], x[6], x[7], x[4]);
        quarterRound(x[10], x[11], x[8], x[9]);
        quarterRound(x[15], x[12], x[13], x[14]);
    }

    // Cộng kết quả sau 20 vòng với ma trận ban đầu
    for (int i = 0; i < 16; ++i) seq[i] += x[i];
}

int main() {
    // Ma trận 512-bit (16 số uint32)
    uint32_t matrix[16] = {
        0x61707865, 0x01020304, 0x05060708, 0x090a0b0c, // Constant, Key...
        0x0d0e0f10, 0x3320646e, 0x01020304, 0x05060708, // Key, Constant, Nonce...
        0x00000000, 0x00000000, 0x79622d32, 0x01020304, // Index, Constant...
        0x05060708, 0x090a0b0c, 0x0d0e0f10, 0x6b206574  // Key, Constant
    };

    std::cout << "Ma tran Keystream dau ra (64 bytes):" << std::endl;
    s20_hash(matrix);

    for (int i = 0; i < 16; ++i) {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << matrix[i] << " ";
        if ((i + 1) % 4 == 0) std::cout << std::endl;
    }

    return 0;
}