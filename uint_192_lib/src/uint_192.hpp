//
// Created by jn98zk on 26.11.23.
//
#include <array>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <format>
#include <vector>

#ifndef MY_UINT192_UINT_192_HPP
#define MY_UINT192_UINT_192_HPP

namespace uint192_lib {
// Forward declaration required for linking to to_decimal_string
struct uint_192;
std::string to_base10_string(const uint_192 &number);
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

    [[nodiscard]] std::string to_bin_string() const {
        std::bitset<64> lower(this->parts[0]);
        std::bitset<64> mid(this->parts[1]);
        std::bitset<64> upper(this->parts[2]);

        return upper.to_string() + mid.to_string() + lower.to_string();
    }

    constexpr uint64_t operator[](size_t part_index) const {
        return parts[part_index];
    }
    constexpr uint64_t &operator[](size_t part_index) {
        return parts[part_index];
    }

    [[nodiscard]] std::string to_base10_string() const {

        return uint192_lib::to_base10_string(*this);
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

constexpr uint_192 operator-(const uint_192 &lhs, const uint_192 &rhs) noexcept {
    uint_192 result{};
    uint64_t carry_bit{0};
    uint64_t subtrahend{};
    for (uint64_t i = 0; i < lhs.parts.size(); ++i) {
        subtrahend = rhs.parts[i] + carry_bit;
        carry_bit = lhs.parts[i] < subtrahend;
        result.parts[i] = lhs.parts[i] - subtrahend;
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

    for (uint64_t lhs_iterator = 0; lhs_iterator < lhs.parts.size(); ++lhs_iterator) {
        const uint64_t lhs_lower_bits = lhs.parts[lhs_iterator] & LOWER_BITMASK;
        const uint64_t lhs_upper_bits = lhs.parts[lhs_iterator] >> UINT32_WIDTH;
        for (uint64_t rhs_iterator = 0; rhs_iterator < rhs.parts.size(); ++rhs_iterator) {
            const uint64_t rhs_lower_bits = rhs.parts[rhs_iterator] & LOWER_BITMASK;
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

template <typename T> struct uint192_div_rem {
    uint_192 quotient;
    T reminder;
};

using div_mod_uint64_remider = uint192_div_rem<uint64_t>;

[[nodiscard]] constexpr div_mod_uint64_remider div_mod(const uint_192 &dividend, const uint32_t divisor) {
    div_mod_uint64_remider result{};
    uint64_t intermediate_division_result{};
    for (uint64_t part_index = dividend.parts.size() - 1; part_index < static_cast<uint64_t>(-1); --part_index) {
        uint64_t upper_part = dividend.parts[part_index] >> UINT32_WIDTH;
        uint64_t lower_part = dividend.parts[part_index] & LOWER_BITMASK;
        // We add the reminder to the upper part of the upper_part
        upper_part = (result.reminder << UINT32_WIDTH) | upper_part;
        intermediate_division_result = upper_part / divisor;
        result.reminder = upper_part - (divisor * intermediate_division_result);
        result.quotient.parts[part_index] = intermediate_division_result << UINT32_WIDTH;

        // We add the reminder to the upper part of the lower_part
        lower_part = (result.reminder << UINT32_WIDTH) | lower_part;
        intermediate_division_result = lower_part / divisor;
        result.reminder = lower_part - (divisor * intermediate_division_result);
        // We add the division result to the lower bits
        result.quotient.parts[part_index] |= intermediate_division_result;
    }

    return result;
}

constexpr uint_192 operator/(const uint_192 &dividend, const uint32_t divisor) {
    return div_mod(dividend, divisor).quotient;
}

constexpr uint64_t operator%(const uint_192 &dividend, const uint32_t divisor) {
    return div_mod(dividend, divisor).reminder;
}

[[nodiscard]] std::string to_base10_string(const uint_192 &number) {
    constexpr uint192_lib::uint_192 ZERO{0};
    if (number == ZERO) {
        return "0";
    }
    std::string base_10_representation;

    // This is the maximum power of 10 that can be stored in an uint32_t
    constexpr uint32_t MAX_BASE_10 = 1000000000U;
    div_mod_uint64_remider by_10_divisor{number, 0};
    std::vector<uint64_t> base_10_parts;
    base_10_parts.reserve(by_10_divisor.quotient.parts.size());
    while (by_10_divisor.quotient != ZERO) {
        by_10_divisor = div_mod(by_10_divisor.quotient, MAX_BASE_10);
        base_10_parts.emplace_back(by_10_divisor.reminder);
    }
    std::string string_representation{};
    for (size_t i = 0; i < base_10_parts.size() - 1; ++i) {
        string_representation = std::format("{0:0>9}", base_10_parts[i]).append(string_representation);
    }

    return std::to_string(base_10_parts[base_10_parts.size() - 1]).append(string_representation);
}

std::ostream &operator<<(std::ostream &out, const uint_192 &number) {
    out << to_base10_string(number);
    return out;
}

} // namespace uint192_lib

#endif // MY_UINT192_UINT_192_HPP
