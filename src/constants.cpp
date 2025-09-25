export module raytracer.constants;

import raytracer.mat;
import raytracer.meta;
import raytracer.vec;
import std;

export namespace raytracer {
template<typename T>
inline constexpr T pi = undefined<T> {};
template<typename T>
inline constexpr T epsilon = undefined<T> {};
template<typename T>
inline constexpr T one = undefined<T> {};
template<typename T>
inline constexpr T unit_x = undefined<T> {};
template<typename T>
inline constexpr T unit_y = undefined<T> {};
template<typename T>
inline constexpr T unit_z = undefined<T> {};
template<typename T>
inline constexpr T unit_w = undefined<T> {};
template<typename T>
inline constexpr T zero = undefined<T> {};
template<typename T>
inline constexpr T identity = undefined<T> {};

// scalar constants
template<std::floating_point T>
inline constexpr T pi<T> = std::numbers::pi_v<T>;
// vec2_t constants
template<typename S>
inline constexpr vec2_t<S> epsilon<vec2_t<S>> = vec2_t<S>(std::numeric_limits<S>::epsilon());
template<typename S>
inline constexpr vec2_t<S> one<vec2_t<S>> = vec2_t<S>(1);
template<typename S>
inline constexpr vec2_t<S> unit_x<vec2_t<S>> = vec2_t<S>(1, 0);
template<typename S>
inline constexpr vec2_t<S> unit_y<vec2_t<S>> = vec2_t<S>(0, 1);
template<typename S>
inline constexpr vec2_t<S> zero<vec2_t<S>> = vec2_t<S>();
// vec3_t constants
template<typename S>
inline constexpr vec3_t<S> epsilon<vec3_t<S>> = vec3_t<S>(std::numeric_limits<S>::epsilon());
template<typename S>
inline constexpr vec3_t<S> one<vec3_t<S>> = vec3_t<S>(1);
template<typename S>
inline constexpr vec3_t<S> unit_x<vec3_t<S>> = vec3_t<S>(1, 0, 0);
template<typename S>
inline constexpr vec3_t<S> unit_y<vec3_t<S>> = vec3_t<S>(0, 1, 0);
template<typename S>
inline constexpr vec3_t<S> unit_z<vec3_t<S>> = vec3_t<S>(0, 0, 1);
template<typename S>
inline constexpr vec3_t<S> zero<vec3_t<S>> = vec3_t<S>();
// vec4_t constants
template<typename S>
inline constexpr vec4_t<S> epsilon<vec4_t<S>> = vec4_t<S>(std::numeric_limits<S>::epsilon());
template<typename S>
inline constexpr vec4_t<S> one<vec4_t<S>> = vec4_t<S>(1);
template<typename S>
inline constexpr vec4_t<S> unit_x<vec4_t<S>> = vec4_t<S>(1, 0, 0, 0);
template<typename S>
inline constexpr vec4_t<S> unit_y<vec4_t<S>> = vec4_t<S>(0, 1, 0, 0);
template<typename S>
inline constexpr vec4_t<S> unit_z<vec4_t<S>> = vec4_t<S>(0, 0, 1, 0);
template<typename S>
inline constexpr vec4_t<S> unit_w<vec4_t<S>> = vec4_t<S>(0, 0, 0, 1);
template<typename S>
inline constexpr vec4_t<S> zero<vec4_t<S>> = vec4_t<S>();
// mat4_t constants
template<typename S>
inline constexpr mat4_t<S> identity<mat4_t<S>> = mat4_t<S>();
template<typename S>
inline constexpr mat4_t<S> one<mat4_t<S>> = mat4_t<S>(
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1);
template<typename S>
inline constexpr mat4_t<S> zero<mat4_t<S>> = mat4_t<S>(0);
}; // namespace raytracer
