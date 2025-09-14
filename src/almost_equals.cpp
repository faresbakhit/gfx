// This code is adapted from Google Test
// https://github.com/google/googletest
// Licensed under the BSD 3-Clause License.
// Original copyright:
// Copyright 2005, Google Inc.
// All rights reserved.

export module gfx.almost_equals;

import gfx.mat;
import gfx.vec;
import gfx.types;
import std;

namespace gfx {
template<typename F>
using bits = std::conditional<std::is_same_v<F, f32>, u32, u64>::type;

template<typename F>
static constexpr usize bit_count = 8 * sizeof(F);

template<typename F>
static constexpr usize fraction_bit_count = std::numeric_limits<F>::digits - 1;

template<typename F>
static constexpr usize exponent_bit_count = bit_count<F> - 1 - fraction_bit_count<F>;

template<typename F>
static constexpr bits<F> sign_bit_mask = static_cast<bits<F>>(1) << (bit_count<F> - 1);

template<typename F>
static constexpr bits<F> fraction_bit_mask = ~static_cast<bits<F>>(0) >> (exponent_bit_count<F> + 1);

template<typename F>
static constexpr bits<F> exponent_bit_mask = ~(sign_bit_mask<F> | fraction_bit_mask<F>);

template<typename F>
constexpr bits<F> sign_and_magnitude_to_biased(bits<F> sam)
{
    if (sign_bit_mask<F> & sam) {
        return ~sam + 1;
    } else {
        return sign_bit_mask<F> | sam;
    }
}

template<typename F>
constexpr bits<F> distance_between_sign_and_magnitude_numbers(bits<F> sam1, bits<F> sam2)
{
    bits<F> const biased1 = sign_and_magnitude_to_biased<F>(sam1);
    bits<F> const biased2 = sign_and_magnitude_to_biased<F>(sam2);
    return (biased1 >= biased2) ? (biased1 - biased2) : (biased2 - biased1);
}

template<typename F>
constexpr bool is_nan(bits<F> fbits)
{
    bits<F> exponent_bits = exponent_bit_mask<F> & fbits;
    bits<F> fraction_bits = fraction_bit_mask<F> & fbits;
    return (exponent_bits == exponent_bit_mask<F>) && (fraction_bits != 0);
}

export template<typename F>
requires(std::is_same_v<F, f32> || std::is_same_v<F, f64>)
constexpr bool almost_equals(F a, F b, u32 max_ulps = 4)
{
    auto a_bits = std::bit_cast<bits<F>>(a);
    auto b_bits = std::bit_cast<bits<F>>(b);

    if (is_nan<F>(a_bits) || is_nan<F>(b_bits)) {
        return false;
    }

    return distance_between_sign_and_magnitude_numbers<F>(a_bits, b_bits) <= max_ulps;
}

export template<typename F>
constexpr bool almost_equals(vec2_t<F> const& v1, vec2_t<F> const& v2, u32 max_ulps = 4)
{
    return almost_equals(v1.x, v2.x, max_ulps)
        && almost_equals(v1.y, v2.y, max_ulps);
}

export template<typename F>
constexpr bool almost_equals(vec3_t<F> const& v1, vec3_t<F> const& v2, u32 max_ulps = 4)
{
    return almost_equals(v1.x, v2.x, max_ulps)
        && almost_equals(v1.y, v2.y, max_ulps)
        && almost_equals(v1.z, v2.z, max_ulps);
}

export template<typename F>
constexpr bool almost_equals(vec4_t<F> const& v1, vec4_t<F> const& v2, u32 max_ulps = 4)
{
    return almost_equals(v1.x, v2.x, max_ulps)
        && almost_equals(v1.y, v2.y, max_ulps)
        && almost_equals(v1.z, v2.z, max_ulps)
        && almost_equals(v1.w, v2.w, max_ulps);
}

export template<typename F>
constexpr bool almost_equals(mat4_t<F> const& m1, mat4_t<F> const& m2, u32 max_ulps = 4)
{
    return almost_equals(m1.x, m2.x, max_ulps)
        && almost_equals(m1.y, m2.y, max_ulps)
        && almost_equals(m1.z, m2.z, max_ulps)
        && almost_equals(m1.w, m2.w, max_ulps);
}
} // namespace gfx
