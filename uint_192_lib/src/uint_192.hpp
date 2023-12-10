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

    constexpr uint_192 &operator+=(const uint_192 &rhs) noexcept {
        uint64_t carry_bit{0};

        for (uint64_t i = 0; i < this->parts.size(); ++i) {
            this->parts[i] += carry_bit;
            this->parts[i] += rhs.parts[i];
            carry_bit = this->parts[i] < rhs.parts[i];
        }

        return *this;
    }
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

    // Prevent UB when shifting by (UINT64_WIDTH - 0) => 64
    if (shift == 0) {
        result = number;
    } else {
        const uint64_t shift_adjust = shift % UINT64_WIDTH;
        const uint64_t shift_offset = shift / UINT64_WIDTH;
        const uint64_t carry_shifting = UINT64_WIDTH - shift_adjust;
        for (uint64_t current_position = shift_offset; current_position < number.parts.size(); ++current_position) {
            result.parts[current_position] += carry;
            const uint64_t shift_from_index = current_position - shift_offset;
            result.parts[current_position] += number.parts[shift_from_index] << shift_adjust;
            carry = carry_shifting == 64 ? 0 : number.parts[shift_from_index] >> carry_shifting;
        }
    }

    return result;
}

constexpr bool operator==(const uint_192 &lhs, const uint_192 &rhs) {
    return lhs.parts == rhs.parts;
}

constexpr bool operator!=(const uint_192 &lhs, const uint_192 &rhs) {
    return lhs.parts != rhs.parts;
}

constexpr bool operator<(const uint_192 &lhs, const uint_192 &rhs) {
    for (uint64_t part_index = lhs.parts.size() - 1; part_index < static_cast<uint64_t>(-1); --part_index) {
        if (lhs.parts[part_index] < rhs.parts[part_index])
            return true;
        if (lhs.parts[part_index] > rhs.parts[part_index])
            return false;
    }
    return false;
}

constexpr bool operator<=(const uint_192 &lhs, const uint_192 &rhs) {
    return lhs == rhs || lhs < rhs;
}

constexpr bool operator>(const uint_192 &lhs, const uint_192 &rhs) {
    return !(lhs <= rhs);
}

constexpr bool operator>=(const uint_192 &lhs, const uint_192 &rhs) {
    return !(lhs < rhs);
}

} // namespace uint192_lib

#endif // MY_UINT192_UINT_192_HPP
