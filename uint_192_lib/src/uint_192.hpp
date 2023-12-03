//
// Created by jn98zk on 26.11.23.
//
#include <array>
#include <cstdint>

#ifndef MY_UINT192_UINT_192_HPP
#define MY_UINT192_UINT_192_HPP

namespace uint192_lib {
struct uint_192 {
    std::array<std::uint64_t, 3> parts;
};

constexpr uint_192 operator+(const uint_192 &lhs, const uint_192 &rhs) noexcept {
    uint_192 result{};
    uint64_t carry_bit{0};

    for (uint64_t i = 0; i < lhs.parts.size(); ++i) {
        result.parts[i] += carry_bit;
        result.parts[i] += lhs.parts[i] + rhs.parts[i];
        carry_bit = result.parts[i] < lhs.parts[i];
    }
    return result;
}

constexpr uint_192 operator<<(const uint_192 &number, const uint64_t shift) noexcept {
    uint_192 result{};
    uint64_t carry{};

    if (shift < UINT64_WIDTH) {
        for (uint64_t part_index = 0; part_index < number.parts.size(); ++part_index) {
            result.parts[part_index] += carry;
            carry = number.parts[part_index] >> (UINT64_WIDTH - shift);
            uint64_t shifted = number.parts[part_index] << shift;
            result.parts[part_index] += shifted;
        }

    } else {
        const uint64_t shift_adjust = shift % UINT64_WIDTH;
        const uint64_t shift_offset = shift / UINT64_WIDTH;
        for (uint64_t part_index = shift_offset; part_index < number.parts.size(); ++part_index) {
            const uint64_t shift_from_index = part_index - shift_offset;
            result.parts[part_index] = number.parts[shift_from_index] << shift_adjust;
        }
    }

    return result;
}

constexpr uint_192 operator>>(const uint_192 &number, const uint64_t shift) noexcept {
    uint_192 result{};
    uint64_t carry{};

    if (shift < UINT64_WIDTH) {
        for (uint64_t part_index = number.parts.size() - 1; part_index < static_cast<uint64_t>(-1);
             --part_index) {
            result.parts[part_index] += carry;
            carry = number.parts[part_index] << (UINT64_WIDTH - shift);
            uint64_t shifted = number.parts[part_index] >> shift;
            result.parts[part_index] += shifted;
        }

    } else {
        const uint64_t shift_adjust = shift % UINT64_WIDTH;
        const uint64_t shift_offset = shift / UINT64_WIDTH;
        for (uint64_t part_index = number.parts.size() - shift_offset - 1;
             part_index < static_cast<uint64_t>(-1); --part_index) {
            const uint64_t shift_from_index = part_index + shift_offset;
            result.parts[part_index] = number.parts[shift_from_index] >> shift_adjust;
        }
    }

    return result;
}

} // namespace uint192_lib

#endif // MY_UINT192_UINT_192_HPP
