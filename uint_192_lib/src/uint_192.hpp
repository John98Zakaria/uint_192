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

constexpr uint32_t LOWER_BITMASK = UINT32_MAX;

static_assert((UINT64_MAX & LOWER_BITMASK) == UINT32_MAX);

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

constexpr uint_192 operator*(const uint_192 &lhs, const uint_192 &rhs) {
    uint_192 result{};

    for (int lhs_iterator = 0; lhs_iterator < lhs.parts.size(); ++lhs_iterator) {
        const uint64_t lhs_lower_bits = lhs.parts[lhs_iterator] & UINT32_MAX;
        const uint64_t lhs_upper_bits = lhs.parts[lhs_iterator] >> UINT32_WIDTH;
        for (int rhs_iterator = 0; rhs_iterator < rhs.parts.size(); ++rhs_iterator) {
            const uint64_t rhs_lower_bits = rhs.parts[rhs_iterator] & UINT32_MAX;
            const uint64_t rhs_upper_bits = rhs.parts[rhs_iterator] >> UINT32_WIDTH;

            const uint_192 lower_lower = uint_192{lhs_lower_bits * rhs_lower_bits};
            const uint_192 lower_upper = uint_192{lhs_lower_bits * rhs_upper_bits};
            const uint_192 upper_lower = uint_192{lhs_upper_bits * rhs_lower_bits};
            const uint_192 upper_upper = uint_192{lhs_upper_bits * rhs_upper_bits};

            uint64_t iteration_shift = (lhs_iterator + rhs_iterator) * UINT64_WIDTH;
            uint64_t lower_upper_shift = iteration_shift + UINT32_WIDTH;
            uint64_t upper_upper_shift = iteration_shift + UINT64_WIDTH;

            result += (lower_lower << iteration_shift);
            result += (lower_upper << lower_upper_shift);
            result += (upper_lower << lower_upper_shift);
            result += (upper_upper << upper_upper_shift);
        }
    }

    return result;
}

} // namespace uint192_lib

#endif // MY_UINT192_UINT_192_HPP
