export module raytracer.scalar;

import raytracer.types;
import std;

export namespace raytracer {
template<typename S>
struct scalar_traits;

template<typename S>
concept scalar = std::convertible_to<typename scalar_traits<S>::copy, S>
    && requires(S a, S b) {
           { a + b } -> std::same_as<S>;
           { a - b } -> std::same_as<S>;
           { a* b } -> std::same_as<S>;
           { a / b } -> std::same_as<S>;
           { scalar_traits<S>::epsilon() } -> std::same_as<S>;
           { scalar_traits<S>::one() } -> std::same_as<S>;
           { scalar_traits<S>::zero() } -> std::same_as<S>;
       };

template<>
struct scalar_traits<f32> {
    using copy = f32;
    using ref = f32&;

    static constexpr f32 epsilon() { return std::numeric_limits<f32>::epsilon(); }
    static constexpr f32 one() { return 1.0f; }
    static constexpr f32 zero() { return 0.0f; }
};

template<>
struct scalar_traits<f64> {
    using copy = f64;
    using ref = f64&;

    static constexpr f64 epsilon() { return std::numeric_limits<f64>::epsilon(); }
    static constexpr f64 one() { return 1.0; }
    static constexpr f64 zero() { return 0.0; }
};

template<>
struct scalar_traits<bool> {
    using copy = bool;
    using ref = bool&;

    static constexpr bool epsilon() { return false; }
    static constexpr bool one() { return true; }
    static constexpr bool zero() { return false; }
};

template<>
struct scalar_traits<u32> {
    using copy = u32;
    using ref = u32&;

    static constexpr u32 epsilon() { return 0; }
    static constexpr u32 one() { return 1; }
    static constexpr u32 zero() { return 0; }
};

template<>
struct scalar_traits<i32> {
    using copy = i32;
    using ref = i32&;

    static constexpr i32 epsilon() { return 0; }
    static constexpr i32 one() { return 1; }
    static constexpr i32 zero() { return 0; }
};
} // namespace raytracer
