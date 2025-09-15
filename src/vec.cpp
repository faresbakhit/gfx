module;
#include <cassert>
export module gfx.vec;

import gfx.meta;
import gfx.types;
import std;

export namespace gfx {
template<typename S>
union vec2_t;

template<typename S>
union vec3_t;

template<typename S>
union vec4_t;

using vec2 = vec2_t<f32>;
using vec3 = vec3_t<f32>;
using vec4 = vec4_t<f32>;

using dvec2 = vec2_t<f64>;
using dvec3 = vec3_t<f64>;
using dvec4 = vec4_t<f64>;

using bvec2 = vec2_t<bool>;
using bvec3 = vec3_t<bool>;
using bvec4 = vec4_t<bool>;

using ivec2 = vec2_t<i32>;
using ivec3 = vec3_t<i32>;
using ivec4 = vec4_t<i32>;

using ivec2 = vec2_t<i32>;
using ivec3 = vec3_t<i32>;
using ivec4 = vec4_t<i32>;

using uvec2 = vec2_t<u32>;
using uvec3 = vec3_t<u32>;
using uvec4 = vec4_t<u32>;

template<typename>
struct is_vec : std::false_type { };

template<typename S>
struct is_vec<vec2_t<S>> : std::true_type { };

template<typename S>
struct is_vec<vec3_t<S>> : std::true_type { };

template<typename S>
struct is_vec<vec4_t<S>> : std::true_type { };

template<typename S>
concept vec = is_vec<S>::value;

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

template<typename S>
union vec2_t {
private:
    std::array<S, 2> data;

public:
    using scalar_type = S;
    static constexpr usize length_tag = 2;

    struct {
        S x, y;
    };

    struct {
        S w, h;
    };

    [[nodiscard]] constexpr vec2_t()
        : x(0)
        , y(0)
    {
    }

    [[nodiscard]] constexpr explicit vec2_t(S const& s)
        : x(s)
        , y(s)
    {
    }

    [[nodiscard]] constexpr vec2_t(
        S const& x,
        S const& y)
        : x(x)
        , y(y)
    {
    }

    template<typename From>
    [[nodiscard]] constexpr vec2_t(vec2_t<From> const& other)
        : x(other.x)
        , y(other.y)
    {
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator+(vec2_t<S2> const& v) const -> vec2_t<decltype(S {} + S2 {})>
    {
        return {
            x + v.x,
            y + v.y,
        };
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator-(vec2_t<S2> const& v) const -> vec2_t<decltype(S {} - S2 {})>
    {
        return {
            x - v.x,
            y - v.y,
        };
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator*(vec2_t<S2> const& v) const -> vec2_t<decltype(S {} * S2 {})>
    {
        return {
            x * v.x,
            y * v.y,
        };
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator/(vec2_t<S2> const& v) const -> vec2_t<decltype(S {} / S2 {})>
    {
        return {
            x / v.x,
            y / v.y,
        };
    }

    template<typename S2>
    constexpr vec2_t& operator+=(vec2_t<S2> const& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    template<typename S2>
    constexpr vec2_t& operator-=(vec2_t<S2> const& v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    template<typename S2>
    constexpr vec2_t& operator*=(vec2_t<S2> const& v)
    {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    template<typename S2>
    constexpr vec2_t& operator/=(vec2_t<S2> const& v)
    {
        x /= v.x;
        y /= v.y;
        return *this;
    }

    template<typename S2>
    constexpr bool operator==(vec2_t<S2> const& v) const
    {
        return (x == v.x)
            && (y == v.y);
    }

    template<typename S2>
    constexpr bool operator!=(vec2_t<S2> const& v) const
    {
        return (x != v.x)
            || (y != v.y);
    }

    template<typename S2>
    constexpr auto operator<=>(vec2_t<S2> const& v) const
    {
        if (auto c = x <=> v.x; c != 0)
            return c;
        return y <=> v.y;
    }

    [[nodiscard]] constexpr auto operator+(S const& s) const -> vec2_t<decltype(S {} + S {})>
    {
        return {
            x + s,
            y + s,
        };
    }

    [[nodiscard]] constexpr auto operator-(S const& s) const -> vec2_t<decltype(S {} - S {})>
    {
        return {
            x - s,
            y - s,
        };
    }

    [[nodiscard]] constexpr auto operator*(S const& s) const -> vec2_t<decltype(S {} * S {})>
    {
        return {
            x * s,
            y * s,
        };
    }

    [[nodiscard]] constexpr auto operator/(S const& s) const -> vec2_t<decltype(S {} / S {})>
    {
        return {
            x / s,
            y / s,
        };
    }

    constexpr vec2_t& operator+=(S const& s)
    {
        x += s;
        y += s;
        return *this;
    }

    constexpr vec2_t& operator-=(S const& s)
    {
        x -= s;
        y -= s;
        return *this;
    }

    constexpr vec2_t& operator*=(S const& s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    constexpr vec2_t& operator/=(S const& s)
    {
        x /= s;
        y /= s;
        return *this;
    }

    [[nodiscard]] constexpr auto operator+() const -> vec2_t<decltype(+S {})>
    {
        return {
            +x,
            +y,
        };
    }

    [[nodiscard]] constexpr auto operator-() const -> vec2_t<decltype(-S {})>
    {
        return {
            -x,
            -y,
        };
    }

    [[nodiscard]] constexpr S const& operator[](usize i) const
    {
        assert(i < 2);
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            std::unreachable();
        }
    }

    [[nodiscard]] constexpr S& operator[](usize i)
    {
        assert(i < 2);
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        default:
            std::unreachable();
        }
    }

    [[nodiscard]] constexpr S length() const { return std::sqrt(length_squared()); }
    [[nodiscard]] constexpr S length_squared() const { return x * x + y * y; }

    [[nodiscard]] constexpr auto begin() const { return data.begin(); }
    [[nodiscard]] constexpr auto begin() { return data.begin(); }
    [[nodiscard]] constexpr auto cbegin() const { return data.cbegin(); }

    [[nodiscard]] constexpr auto end() const { return data.end(); }
    [[nodiscard]] constexpr auto end() { return data.end(); }
    [[nodiscard]] constexpr auto cend() const { return data.cend(); }

    [[nodiscard]] constexpr auto rbegin() const { return data.rbegin(); }
    [[nodiscard]] constexpr auto rbegin() { return data.rbegin(); }
    [[nodiscard]] constexpr auto crbegin() const { return data.crbegin(); }

    [[nodiscard]] constexpr auto rend() const { return data.rend(); }
    [[nodiscard]] constexpr auto rend() { return data.rend(); }
    [[nodiscard]] constexpr auto crend() const { return data.crend(); }
};

template<typename S>
[[nodiscard]] constexpr auto operator+(S const& s, vec2_t<S> const& v)
{
    return v + s;
}

template<typename S>
[[nodiscard]] constexpr auto operator-(S const& s, vec2_t<S> const& v) -> vec2_t<decltype(S {} - S {})>
{
    return {
        s - v.x,
        s - v.y,
    };
}

template<typename S>
[[nodiscard]] constexpr auto operator*(S const& s, vec2_t<S> const& v)
{
    return v * s;
}

template<typename S>
[[nodiscard]] constexpr auto operator/(S const& s, vec2_t<S> const& v) -> vec2_t<decltype(S {} / S {})>
{
    return {
        s / v.x,
        s / v.y,
    };
}

template<typename S>
std::ostream& operator<<(std::ostream& os, vec2_t<S> const& v)
{
    return os << '<' << v.x << ' ' << v.y << '>';
}

template<typename S>
union vec3_t {
private:
    std::array<S, 3> data;

public:
    using scalar_type = S;
    static constexpr usize length_tag = 3;

    struct {
        S x, y, z;
    };

    struct {
        S r, g, b;
    };

    vec2_t<S> xy;

    [[nodiscard]] constexpr vec3_t()
        : x(0)
        , y(0)
        , z(0)
    {
    }

    [[nodiscard]] constexpr explicit vec3_t(S const& s)
        : x(s)
        , y(s)
        , z(s)
    {
    }

    [[nodiscard]] constexpr vec3_t(
        S x,
        S y,
        S z)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    [[nodiscard]] constexpr vec3_t(vec2_t<S> const& xy, S const& z)
        : x(xy.x)
        , y(xy.y)
        , z(z)
    {
    }

    [[nodiscard]] constexpr vec3_t(S const& x, vec2_t<S> const& yz)
        : x(x)
        , y(yz.y)
        , z(yz.z)
    {
    }

    [[nodiscard]] constexpr explicit vec3_t(vec4_t<S> const& xyzw)
        : x(xyzw.x)
        , y(xyzw.y)
        , z(xyzw.z)
    {
    }

    template<typename From>
    [[nodiscard]] constexpr vec3_t(vec3_t<From> const& other)
        : x(other.x)
        , y(other.y)
        , z(other.z)
    {
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator+(vec3_t<S2> const& v) const -> vec3_t<decltype(S {} + S2 {})>
    {
        return {
            x + v.x,
            y + v.y,
            z + v.z,
        };
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator-(vec3_t<S2> const& v) const -> vec3_t<decltype(S {} - S2 {})>
    {
        return {
            x - v.x,
            y - v.y,
            z - v.z,
        };
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator*(vec3_t<S2> const& v) const -> vec3_t<decltype(S {} * S2 {})>
    {
        return {
            x * v.x,
            y * v.y,
            z * v.z,
        };
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator/(vec3_t<S2> const& v) const -> vec3_t<decltype(S {} / S2 {})>
    {
        return {
            x / v.x,
            y / v.y,
            z / v.z,
        };
    }

    template<typename S2>
    constexpr vec3_t& operator+=(vec3_t<S2> const& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    template<typename S2>
    constexpr vec3_t& operator-=(vec3_t<S2> const& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    template<typename S2>
    constexpr vec3_t& operator*=(vec3_t<S2> const& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    template<typename S2>
    constexpr vec3_t& operator/=(vec3_t<S2> const& v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    template<typename S2>
    constexpr bool operator==(vec3_t<S2> const& v) const
    {
        return (x == v.x)
            && (y == v.y)
            && (z == v.z);
    }

    template<typename S2>
    constexpr bool operator!=(vec3_t<S2> const& v) const
    {
        return (x != v.x)
            || (y != v.y)
            || (z != v.z);
    }

    template<typename S2>
    constexpr auto operator<=>(vec3_t<S2> const& v) const
    {
        if (auto c = x <=> v.x; c != 0)
            return c;
        if (auto c = y <=> v.y; c != 0)
            return c;
        return z <=> v.z;
    }

    [[nodiscard]] constexpr auto operator+(S const& s) const -> vec3_t<decltype(S {} + S {})>
    {
        return {
            x + s,
            y + s,
            z + s,
        };
    }

    [[nodiscard]] constexpr auto operator-(S const& s) const -> vec3_t<decltype(S {} - S {})>
    {
        return {
            x - s,
            y - s,
            z - s,
        };
    }

    [[nodiscard]] constexpr auto operator*(S const& s) const -> vec3_t<decltype(S {} * S {})>
    {
        return {
            x * s,
            y * s,
            z * s,
        };
    }

    [[nodiscard]] constexpr auto operator/(S const& s) const -> vec3_t<decltype(S {} / S {})>
    {
        return {
            x / s,
            y / s,
            z / s,
        };
    }

    constexpr vec3_t& operator+=(S const& s)
    {
        x += s;
        y += s;
        z += s;
        return *this;
    }

    constexpr vec3_t& operator-=(S const& s)
    {
        x -= s;
        y -= s;
        z -= s;
        return *this;
    }

    constexpr vec3_t& operator*=(S const& s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    constexpr vec3_t& operator/=(S const& s)
    {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    [[nodiscard]] constexpr auto operator+() const -> vec3_t<decltype(+S {})>
    {
        return {
            -x,
            -y,
            -z,
        };
    }

    [[nodiscard]] constexpr auto operator-() const -> vec3_t<decltype(-S {})>
    {
        return {
            -x,
            -y,
            -z,
        };
    }

    [[nodiscard]] constexpr S const& operator[](usize i) const
    {
        assert(i < 3);
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            std::unreachable();
        }
    }

    [[nodiscard]] constexpr S& operator[](usize i)
    {
        assert(i < 3);
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            std::unreachable();
        }
    }
    [[nodiscard]] constexpr S length() const { return std::sqrt(length_squared()); }
    [[nodiscard]] constexpr S length_squared() const { return x * x + y * y + z * z; }

    [[nodiscard]] constexpr auto begin() const { return data.begin(); }
    [[nodiscard]] constexpr auto begin() { return data.begin(); }
    [[nodiscard]] constexpr auto cbegin() const { return data.cbegin(); }

    [[nodiscard]] constexpr auto end() const { return data.end(); }
    [[nodiscard]] constexpr auto end() { return data.end(); }
    [[nodiscard]] constexpr auto cend() const { return data.cend(); }

    [[nodiscard]] constexpr auto rbegin() const { return data.rbegin(); }
    [[nodiscard]] constexpr auto rbegin() { return data.rbegin(); }
    [[nodiscard]] constexpr auto crbegin() const { return data.crbegin(); }

    [[nodiscard]] constexpr auto rend() const { return data.rend(); }
    [[nodiscard]] constexpr auto rend() { return data.rend(); }
    [[nodiscard]] constexpr auto crend() const { return data.crend(); }
};

template<typename S>
[[nodiscard]] constexpr auto operator+(S const& s, vec3_t<S> const& v)
{
    return v + s;
}

template<typename S>
[[nodiscard]] constexpr auto operator-(S const& s, vec3_t<S> const& v) -> vec3_t<decltype(S {} - S {})>
{
    return {
        s - v.x,
        s - v.y,
        s - v.z,
    };
}

template<typename S>
[[nodiscard]] constexpr auto operator*(S const& s, vec3_t<S> const& v)
{
    return v * s;
}

template<typename S>
[[nodiscard]] constexpr auto operator/(S const& s, vec3_t<S> const& v) -> vec3_t<decltype(S {} / S {})>
{
    return {
        s / v.x,
        s / v.y,
        s / v.z,
    };
}

template<typename S>
std::ostream& operator<<(std::ostream& os, vec3_t<S> const& v)
{
    return os << '<' << v.x << ' ' << v.y << ' ' << v.z << '>';
}

template<typename S>
union vec4_t {
private:
    std::array<S, 4> data;

public:
    using scalar_type = S;
    static constexpr usize length_tag = 4;

    struct {
        S x, y, z, w;
    };

    struct {
        S r, g, b, a;
    };

    vec3_t<S> rgb;

    vec3_t<S> xyz;

    struct {
        vec2_t<S> xy;
        vec2_t<S> zw;
    };

    [[nodiscard]] constexpr vec4_t()
        : x(0)
        , y(0)
        , z(0)
        , w(0)
    {
    }

    [[nodiscard]] constexpr explicit vec4_t(S const& s)
        : x(s)
        , y(s)
        , z(s)
        , w(s)
    {
    }

    [[nodiscard]] constexpr vec4_t(
        S const& x,
        S const& y,
        S const& z,
        S const& w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    [[nodiscard]] constexpr vec4_t(
        S const& x,
        S const& y,
        S const& z)
        : x(x)
        , y(y)
        , z(z)
        , w(0)
    {
    }

    [[nodiscard]] constexpr vec4_t(
        vec3_t<S> const& xyz,
        S const& w)
        : x(xyz.x)
        , y(xyz.y)
        , z(xyz.z)
        , w(w)
    {
    }

    [[nodiscard]] constexpr vec4_t(vec3_t<S> const& xyz)
        : x(xyz.x)
        , y(xyz.y)
        , z(xyz.z)
        , w(0)
    {
    }

    [[nodiscard]] constexpr vec4_t(
        S const& x,
        vec3_t<S> const& yzw)
        : x(x)
        , y(yzw.y)
        , z(yzw.z)
        , w(yzw.w)
    {
    }

    [[nodiscard]] constexpr vec4_t(
        vec2_t<S> const& xy,
        vec2_t<S> const& zw)
        : x(xy.x)
        , y(xy.y)
        , z(zw.w)
        , w(zw.w)
    {
    }

    [[nodiscard]] constexpr vec4_t(
        vec2_t<S> const& xy,
        S const& z,
        S const& w)
        : x(xy.x)
        , y(xy.y)
        , z(z)
        , w(w)
    {
    }

    [[nodiscard]] constexpr vec4_t(
        S const& x,
        S const& y,
        vec2_t<S> const& zw)
        : x(x)
        , y(y)
        , z(zw.z)
        , w(zw.w)
    {
    }

    [[nodiscard]] constexpr vec4_t(
        S const& x,
        vec2_t<S> const& yz,
        S const& w)
        : x(x)
        , y(yz.y)
        , z(yz.z)
        , w(w)
    {
    }

    template<typename From>
    [[nodiscard]] constexpr vec4_t(vec4_t<From> const& other)
        : x(other.x)
        , y(other.y)
        , z(other.z)
        , w(other.w)
    {
    }

    [[nodiscard]] static constexpr vec4_t point(S const& x, S const& y, S const& z)
    {
        return { x, y, z, 1 };
    }

    [[nodiscard]] static constexpr vec4_t point(vec3_t<S> const& xyz)
    {
        return { xyz.x, xyz.y, xyz.z, 1 };
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator+(vec4_t<S2> const& v) const -> vec4_t<decltype(S {} + S2 {})>
    {
        return {
            x + v.x,
            y + v.y,
            z + v.z,
            w + v.w,
        };
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator-(vec4_t<S2> const& v) const -> vec4_t<decltype(S {} - S2 {})>
    {
        return {
            x - v.x,
            y - v.y,
            z - v.z,
            w - v.w,
        };
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator*(vec4_t<S2> const& v) const -> vec4_t<decltype(S {} * S2 {})>
    {
        return {
            x * v.x,
            y * v.y,
            z * v.z,
            w * v.w,
        };
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator/(vec4_t<S2> const& v) const -> vec4_t<decltype(S {} / S2 {})>
    {
        return {
            x / v.x,
            y / v.y,
            z / v.z,
            w / v.w,
        };
    }

    template<typename S2>
    constexpr vec4_t& operator+=(vec4_t<S2> const& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return *this;
    }

    template<typename S2>
    constexpr vec4_t& operator-=(vec4_t<S2> const& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return *this;
    }

    template<typename S2>
    constexpr vec4_t& operator*=(vec4_t<S2> const& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
        return *this;
    }

    template<typename S2>
    constexpr vec4_t& operator/=(vec4_t<S2> const& v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;
        return *this;
    }

    template<typename S2>
    constexpr bool operator==(vec4_t<S2> const& v) const
    {
        return (x == v.x)
            && (y == v.y)
            && (z == v.z)
            && (w == v.w);
    }

    template<typename S2>
    constexpr bool operator!=(vec4_t<S2> const& v) const
    {
        return (x != v.x)
            || (y != v.y)
            || (z != v.z)
            || (w != v.w);
    }

    template<typename S2>
    constexpr auto operator<=>(vec4_t<S2> const& v) const
    {
        auto a = x <=> v.x;
        if (a != 0)
            return a;
        auto b = y <=> v.y;
        if (b != 0)
            return b;
        auto c = z <=> v.z;
        if (c != 0)
            return c;
        return w <=> v.w;
    }

    [[nodiscard]] constexpr auto operator+(S const& s) const -> vec4_t<decltype(S {} + S {})>
    {
        return {
            x + s,
            y + s,
            z + s,
            w + s,
        };
    }

    [[nodiscard]] constexpr auto operator-(S const& s) const -> vec4_t<decltype(S {} - S {})>
    {
        return {
            x - s,
            y - s,
            z - s,
            w - s,
        };
    }

    [[nodiscard]] constexpr auto operator*(S const& s) const -> vec4_t<decltype(S {} * S {})>
    {
        return {
            x * s,
            y * s,
            z * s,
            w * s,
        };
    }

    [[nodiscard]] constexpr auto operator/(S const& s) const -> vec4_t<decltype(S {} / S {})>
    {
        return {
            x / s,
            y / s,
            z / s,
            w / s,
        };
    }

    constexpr vec4_t& operator+=(S const& s)
    {
        x += s;
        y += s;
        z += s;
        w += s;
        return *this;
    }

    constexpr vec4_t& operator-=(S const& s)
    {
        x -= s;
        y -= s;
        z -= s;
        w -= s;
        return *this;
    }

    constexpr vec4_t& operator*=(S const& s)
    {
        x *= s;
        y *= s;
        z *= s;
        w *= s;
        return *this;
    }

    constexpr vec4_t& operator/=(S const& s)
    {
        x /= s;
        y /= s;
        z /= s;
        w /= s;
        return *this;
    }

    [[nodiscard]] constexpr auto operator+() const -> vec4_t<decltype(+S {})>
    {
        return {
            -x,
            -y,
            -z,
            -w,
        };
    }

    [[nodiscard]] constexpr auto operator-() const -> vec4_t<decltype(-S {})>
    {
        return {
            -x,
            -y,
            -z,
            -w,
        };
    }

    [[nodiscard]] constexpr S const& operator[](usize i) const
    {
        assert(i < 4);
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            std::unreachable();
        }
    }

    [[nodiscard]] constexpr S& operator[](usize i)
    {
        assert(i < 4);
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            std::unreachable();
        }
    }

    [[nodiscard]] constexpr S length() const { return std::sqrt(length_squared()); }
    [[nodiscard]] constexpr S length_squared() const { return x * x + y * y + z * z + w * w; }

    [[nodiscard]] constexpr auto begin() const { return data.begin(); }
    [[nodiscard]] constexpr auto begin() { return data.begin(); }
    [[nodiscard]] constexpr auto cbegin() const { return data.cbegin(); }

    [[nodiscard]] constexpr auto end() const { return data.end(); }
    [[nodiscard]] constexpr auto end() { return data.end(); }
    [[nodiscard]] constexpr auto cend() const { return data.cend(); }

    [[nodiscard]] constexpr auto rbegin() const { return data.rbegin(); }
    [[nodiscard]] constexpr auto rbegin() { return data.rbegin(); }
    [[nodiscard]] constexpr auto crbegin() const { return data.crbegin(); }

    [[nodiscard]] constexpr auto rend() const { return data.rend(); }
    [[nodiscard]] constexpr auto rend() { return data.rend(); }
    [[nodiscard]] constexpr auto crend() const { return data.crend(); }
};

template<typename S>
[[nodiscard]] constexpr auto operator+(S const& s, vec4_t<S> const& v)
{
    return v + s;
}

template<typename S>
[[nodiscard]] constexpr auto operator-(S const& s, vec4_t<S> const& v) -> vec4_t<decltype(S {} - S {})>
{
    return {
        s - v.x,
        s - v.y,
        s - v.z,
        s - v.w,
    };
}

template<typename S>
[[nodiscard]] constexpr auto operator*(S const& s, vec4_t<S> const& v)
{
    return v * s;
}

template<typename S>
[[nodiscard]] constexpr auto operator/(S const& s, vec4_t<S> const& v) -> vec4_t<decltype(S {} / S {})>
{
    return {
        s / v.x,
        s / v.y,
        s / v.z,
        s / v.w,
    };
}

template<typename S>
std::ostream& operator<<(std::ostream& os, vec4_t<S> const& v)
{
    return os << '<' << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << '>';
}

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

template<typename S>
[[nodiscard]] constexpr vec2_t<S> abs(vec2_t<S> const& v)
{
    return vec2_t<S>(std::abs(v.x), std::abs(v.y));
}
template<typename S>
[[nodiscard]] constexpr vec3_t<S> abs(vec3_t<S> const& v)
{
    return vec3_t<S>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}
template<typename S>
[[nodiscard]] constexpr vec4_t<S> abs(vec4_t<S> const& v)
{
    return vec4_t<S>(std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w));
}

template<typename S>
[[nodiscard]] constexpr vec2_t<S> clamp(vec2_t<S> const& v, S const& lo, S const& hi)
{
    return vec2_t<S>(std::clamp(v.x, lo, hi), std::clamp(v.y, lo, hi));
}
template<typename S>
[[nodiscard]] constexpr vec3_t<S> clamp(vec3_t<S> const& v, S const& lo, S const& hi)
{
    return vec3_t<S>(std::clamp(v.x, lo, hi), std::clamp(v.y, lo, hi), std::clamp(v.z, lo, hi));
}
template<typename S>
[[nodiscard]] constexpr vec4_t<S> clamp(vec4_t<S> const& v, S const& lo, S const& hi)
{
    return vec4_t<S>(std::clamp(v.x, lo, hi), std::clamp(v.y, lo, hi), std::clamp(v.z, lo, hi), std::clamp(v.w, lo, hi));
}

template<typename S>
[[nodiscard]] constexpr vec3_t<S> cross(vec3_t<S> const& v1, vec3_t<S> const& v2)
{
    return vec3_t(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x);
}

template<vec V1, vec V2>
requires(V1::length_tag == V2::length_tag)
[[nodiscard]] constexpr auto distance(V1 const& v1, V2 const& v2)
{
    return std::sqrt(distance_squared(v1, v2));
}

template<vec V1, vec V2>
requires(V1::length_tag == V2::length_tag)
[[nodiscard]] constexpr auto distance_squared(V1 const& v1, V2 const& v2)
{
    auto diff = v1 - v2;
    return dot(diff, diff);
}

template<typename S1, typename S2>
[[nodiscard]] constexpr auto dot(vec2_t<S1> const& v1, vec2_t<S2> const& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}
template<typename S1, typename S2>
[[nodiscard]] constexpr auto dot(vec3_t<S1> const& v1, vec3_t<S2> const& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
template<typename S1, typename S2>
[[nodiscard]] constexpr auto dot(vec4_t<S1> const& v1, vec4_t<S2> const& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

template<vec V>
[[nodiscard]] constexpr V normalize(V const& v)
{
    return v / v.length();
}

template<typename S1, typename S2>
[[nodiscard]] constexpr bvec2 less_than(vec2_t<S1> const& v1, vec2_t<S2> const& v2)
{
    return {
        v1.x < v2.x,
        v1.y < v2.y,
    };
}
template<typename S1, typename S2>
[[nodiscard]] constexpr bvec3 less_than(vec3_t<S1> const& v1, vec3_t<S2> const& v2)
{
    return {
        v1.x < v2.x,
        v1.y < v2.y,
        v1.z < v2.z,
    };
}
template<typename S1, typename S2>
[[nodiscard]] constexpr bvec4 less_than(vec4_t<S1> const& v1, vec4_t<S2> const& v2)
{
    return {
        v1.x < v2.x,
        v1.y < v2.y,
        v1.z < v2.z,
        v1.w < v2.w,
    };
}

template<typename S1, typename S2>
[[nodiscard]] constexpr bvec2 less_than_equal(vec2_t<S1> const& v1, vec2_t<S2> const& v2)
{
    return {
        v1.x <= v2.x,
        v1.y <= v2.y,
    };
}
template<typename S1, typename S2>
[[nodiscard]] constexpr bvec3 less_than_equal(vec3_t<S1> const& v1, vec3_t<S2> const& v2)
{
    return {
        v1.x <= v2.x,
        v1.y <= v2.y,
        v1.z <= v2.z,
    };
}
template<typename S1, typename S2>
[[nodiscard]] constexpr bvec4 less_than_equal(vec4_t<S1> const& v1, vec4_t<S2> const& v2)
{
    return {
        v1.x <= v2.x,
        v1.y <= v2.y,
        v1.z <= v2.z,
        v1.w <= v2.w,
    };
}

template<typename S1, typename S2>
[[nodiscard]] constexpr bvec2 greater_than(vec2_t<S1> const& v1, vec2_t<S2> const& v2)
{
    return {
        v1.x > v2.x,
        v1.y > v2.y,
    };
}
template<typename S1, typename S2>
[[nodiscard]] constexpr bvec3 greater_than(vec3_t<S1> const& v1, vec3_t<S2> const& v2)
{
    return {
        v1.x > v2.x,
        v1.y > v2.y,
        v1.z > v2.z,
    };
}
template<typename S1, typename S2>
[[nodiscard]] constexpr bvec4 greater_than(vec4_t<S1> const& v1, vec4_t<S2> const& v2)
{
    return {
        v1.x > v2.x,
        v1.y > v2.y,
        v1.z > v2.z,
        v1.w > v2.w,
    };
}

template<typename S1, typename S2>
[[nodiscard]] constexpr bvec2 greater_than_equal(vec2_t<S1> const& v1, vec2_t<S2> const& v2)
{
    return {
        v1.x >= v2.x,
        v1.y >= v2.y,
    };
}
template<typename S1, typename S2>
[[nodiscard]] constexpr bvec3 greater_than_equal(vec3_t<S1> const& v1, vec3_t<S2> const& v2)
{
    return {
        v1.x >= v2.x,
        v1.y >= v2.y,
        v1.z >= v2.z,
    };
}
template<typename S1, typename S2>
[[nodiscard]] constexpr bvec4 greater_than_equal(vec4_t<S1> const& v1, vec4_t<S2> const& v2)
{
    return {
        v1.x >= v2.x,
        v1.y >= v2.y,
        v1.z >= v2.z,
        v1.w >= v2.w,
    };
}

template<typename S1, typename S2>
[[nodiscard]] constexpr bvec2 equal(vec2_t<S1> const& v1, vec2_t<S2> const& v2)
{
    return {
        v1.x == v2.x,
        v1.y == v2.y,
    };
}
template<typename S1, typename S2>
[[nodiscard]] constexpr bvec3 equal(vec3_t<S1> const& v1, vec3_t<S2> const& v2)
{
    return {
        v1.x == v2.x,
        v1.y == v2.y,
        v1.z == v2.z,
    };
}
template<typename S1, typename S2>
[[nodiscard]] constexpr bvec4 equal(vec4_t<S1> const& v1, vec4_t<S2> const& v2)
{
    return {
        v1.x == v2.x,
        v1.y == v2.y,
        v1.z == v2.z,
        v1.w == v2.w,
    };
}

template<typename S1, typename S2>
[[nodiscard]] constexpr bvec2 not_equal(vec2_t<S1> const& v1, vec2_t<S2> const& v2)
{
    return {
        v1.x != v2.x,
        v1.y != v2.y,
    };
}
template<typename S1, typename S2>
[[nodiscard]] constexpr bvec3 not_equal(vec3_t<S1> const& v1, vec3_t<S2> const& v2)
{
    return {
        v1.x != v2.x,
        v1.y != v2.y,
        v1.z != v2.z,
    };
}
template<typename S1, typename S2>
[[nodiscard]] constexpr bvec4 not_equal(vec4_t<S1> const& v1, vec4_t<S2> const& v2)
{
    return {
        v1.x != v2.x,
        v1.y != v2.y,
        v1.z != v2.z,
        v1.w != v2.w,
    };
}

[[nodiscard]] constexpr bool any(bvec2 const& v)
{
    return v.x
        || v.y;
}
[[nodiscard]] constexpr bool any(bvec3 const& v)
{
    return v.x
        || v.y
        || v.z;
}
[[nodiscard]] constexpr bool any(bvec4 const& v)
{
    return v.x
        || v.y
        || v.z
        || v.w;
}

[[nodiscard]] constexpr bool all(bvec2 const& v)
{
    return v.x
        && v.y;
}
[[nodiscard]] constexpr bool all(bvec3 const& v)
{
    return v.x
        && v.y
        && v.z;
}
[[nodiscard]] constexpr bool all(bvec4 const& v)
{
    return v.x
        && v.y
        && v.z
        && v.w;
}

template<vec V>
[[nodiscard]] constexpr bool almost_equals(V const& v1, V const& v2)
{
    return v1 == v2;
}

template<vec V>
[[nodiscard]] constexpr bool almost_equals(V const& v1, V const& v2)
requires(std::floating_point<typename V::scalar_type>)
{
    return all(less_than(abs(v1 - v2), V(0.00001)));
}

template<typename S>
[[nodiscard]] constexpr auto map(vec2_t<S> const& v, auto f)
{
    return vec2_t(f(v.x), f(v.y));
}
template<typename S>
[[nodiscard]] constexpr auto map(vec3_t<S> const& v, auto f)
{
    return vec3_t(f(v.x), f(v.y), f(v.z));
}
template<typename S>
[[nodiscard]] constexpr auto map(vec4_t<S> const& v, auto f)
{
    return vec4_t(f(v.x), f(v.y), f(v.z), f(v.w));
}
} // namespace gfx

template<typename S>
struct std::formatter<gfx::vec2_t<S>, char> {
    constexpr auto parse(auto& ctx)
    {
        return ctx.begin();
    }

    auto format(gfx::vec2_t<S> const& v, auto& ctx) const
    {
        return std::format_to(ctx.out(), "<{} {}>", v.x, v.y);
    }
};

template<typename S>
struct std::formatter<gfx::vec3_t<S>, char> {
    constexpr auto parse(auto& ctx)
    {
        return ctx.begin();
    }

    auto format(gfx::vec3_t<S> const& v, auto& ctx) const
    {
        return std::format_to(ctx.out(), "<{} {} {}>", v.x, v.y, v.z);
    }
};

template<typename S>
struct std::formatter<gfx::vec4_t<S>, char> {
    constexpr auto parse(auto& ctx)
    {
        return ctx.begin();
    }

    auto format(gfx::vec4_t<S> const& v, auto& ctx) const
    {
        return std::format_to(ctx.out(), "<{} {} {} {}>", v.x, v.y, v.z, v.w);
    }
};
