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


} // namespace uint192_lib

#endif // MY_UINT192_UINT_192_HPP
