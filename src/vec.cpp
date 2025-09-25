module;
#include <cassert>
export module raytracer.vec;

import raytracer.types;
import std;

export namespace raytracer {
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

template<typename S>
union vec2_t {
private:
    std::array<S, 2> m_data;

public:
    using scalar_type = S;
    static constexpr usize size_tag = 2;

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

    [[nodiscard]] constexpr explicit vec2_t(vec3_t<S> const& xyz)
        : x(xyz.x)
        , y(xyz.y)
    {
    }

    [[nodiscard]] constexpr explicit vec2_t(vec4_t<S> const& xyzw)
        : x(xyzw.x)
        , y(xyzw.y)
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

    [[nodiscard]] constexpr vec2_t swap()
    {
        return {
            y,
            x,
        };
    }

    [[nodiscard]] constexpr S length() const { return std::sqrt(lengthSquared()); }
    [[nodiscard]] constexpr S lengthSquared() const { return x * x + y * y; }

    [[nodiscard]] constexpr auto data() { return m_data.data(); }
    [[nodiscard]] constexpr auto data() const { return m_data.data(); }

    [[nodiscard]] constexpr auto begin() const { return m_data.begin(); }
    [[nodiscard]] constexpr auto begin() { return m_data.begin(); }
    [[nodiscard]] constexpr auto cbegin() const { return m_data.cbegin(); }

    [[nodiscard]] constexpr auto end() const { return m_data.end(); }
    [[nodiscard]] constexpr auto end() { return m_data.end(); }
    [[nodiscard]] constexpr auto cend() const { return m_data.cend(); }

    [[nodiscard]] constexpr auto rbegin() const { return m_data.rbegin(); }
    [[nodiscard]] constexpr auto rbegin() { return m_data.rbegin(); }
    [[nodiscard]] constexpr auto crbegin() const { return m_data.crbegin(); }

    [[nodiscard]] constexpr auto rend() const { return m_data.rend(); }
    [[nodiscard]] constexpr auto rend() { return m_data.rend(); }
    [[nodiscard]] constexpr auto crend() const { return m_data.crend(); }
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
    std::array<S, 3> m_data;

public:
    using scalar_type = S;
    static constexpr usize size_tag = 3;

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
        , y(yz.x)
        , z(yz.y)
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

    [[nodiscard]] constexpr S length() const { return std::sqrt(lengthSquared()); }
    [[nodiscard]] constexpr S lengthSquared() const { return x * x + y * y + z * z; }

    [[nodiscard]] constexpr auto data() { return m_data.data(); }
    [[nodiscard]] constexpr auto data() const { return m_data.data(); }

    [[nodiscard]] constexpr auto begin() const { return m_data.begin(); }
    [[nodiscard]] constexpr auto begin() { return m_data.begin(); }
    [[nodiscard]] constexpr auto cbegin() const { return m_data.cbegin(); }

    [[nodiscard]] constexpr auto end() const { return m_data.end(); }
    [[nodiscard]] constexpr auto end() { return m_data.end(); }
    [[nodiscard]] constexpr auto cend() const { return m_data.cend(); }

    [[nodiscard]] constexpr auto rbegin() const { return m_data.rbegin(); }
    [[nodiscard]] constexpr auto rbegin() { return m_data.rbegin(); }
    [[nodiscard]] constexpr auto crbegin() const { return m_data.crbegin(); }

    [[nodiscard]] constexpr auto rend() const { return m_data.rend(); }
    [[nodiscard]] constexpr auto rend() { return m_data.rend(); }
    [[nodiscard]] constexpr auto crend() const { return m_data.crend(); }
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
    std::array<S, 4> m_data;

public:
    using scalar_type = S;
    static constexpr usize size_tag = 4;

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
        , y(yzw.x)
        , z(yzw.y)
        , w(yzw.z)
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
        , z(zw.x)
        , w(zw.y)
    {
    }

    [[nodiscard]] constexpr vec4_t(
        S const& x,
        vec2_t<S> const& yz,
        S const& w)
        : x(x)
        , y(yz.x)
        , z(yz.y)
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

    [[nodiscard]] static constexpr vec4_t point()
    {
        return { 0, 0, 0, 1 };
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
        if (auto c = x <=> v.x; c != 0)
            return c;
        if (auto c = y <=> v.y; c != 0)
            return c;
        if (auto c = z <=> v.z; c != 0)
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

    [[nodiscard]] constexpr S length() const { return std::sqrt(lengthSquared()); }
    [[nodiscard]] constexpr S lengthSquared() const { return x * x + y * y + z * z + w * w; }

    [[nodiscard]] constexpr auto data() { return m_data.data(); }
    [[nodiscard]] constexpr auto data() const { return m_data.data(); }

    [[nodiscard]] constexpr auto begin() const { return m_data.begin(); }
    [[nodiscard]] constexpr auto begin() { return m_data.begin(); }
    [[nodiscard]] constexpr auto cbegin() const { return m_data.cbegin(); }

    [[nodiscard]] constexpr auto end() const { return m_data.end(); }
    [[nodiscard]] constexpr auto end() { return m_data.end(); }
    [[nodiscard]] constexpr auto cend() const { return m_data.cend(); }

    [[nodiscard]] constexpr auto rbegin() const { return m_data.rbegin(); }
    [[nodiscard]] constexpr auto rbegin() { return m_data.rbegin(); }
    [[nodiscard]] constexpr auto crbegin() const { return m_data.crbegin(); }

    [[nodiscard]] constexpr auto rend() const { return m_data.rend(); }
    [[nodiscard]] constexpr auto rend() { return m_data.rend(); }
    [[nodiscard]] constexpr auto crend() const { return m_data.crend(); }
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

// NOTE
// For some reason we need to explicitly initialize theese templates here so
// we can use them in a constant expression context outside of the module.
// Might be a bug in clang?

template union vec2_t<f32>;
template union vec2_t<f64>;
template union vec2_t<bool>;
template union vec2_t<i32>;
template union vec2_t<u32>;

template union vec3_t<f32>;
template union vec3_t<f64>;
template union vec3_t<bool>;
template union vec3_t<i32>;
template union vec3_t<u32>;

template union vec4_t<f32>;
template union vec4_t<f64>;
template union vec4_t<bool>;
template union vec4_t<i32>;
template union vec4_t<u32>;

template<vec V>
[[nodiscard]] constexpr auto map(V const& v, auto f)
{
    if constexpr (V::size_tag == 2)
        return vec2_t(f(v.x), f(v.y));
    else if constexpr (V::size_tag == 3)
        return vec3_t(f(v.x), f(v.y), f(v.z));
    else if constexpr (V::size_tag == 4)
        return vec4_t(f(v.x), f(v.y), f(v.z), f(v.w));
}

template<vec V>
[[nodiscard]] constexpr auto map2(V const& v1, V const& v2, auto f)
{
    if constexpr (V::size_tag == 2)
        return vec2_t(f(v1.x, v2.y), f(v1.y, v2.y));
    else if constexpr (V::size_tag == 3)
        return vec3_t(f(v1.x, v2.y), f(v1.y, v2.y), f(v1.z, v2.z));
    else if constexpr (V::size_tag == 4)
        return vec4_t(f(v1.x, v2.y), f(v1.y, v2.y), f(v1.z, v2.z), f(v1.w, v2.w));
}

template<vec V>
[[nodiscard]] constexpr auto reduce(V const& v, auto f)
{
    if constexpr (V::size_tag == 2)
        return f(v.x, v.y);
    else if constexpr (V::size_tag == 3)
        return f(f(v.x, v.y), v.z);
    else if constexpr (V::size_tag == 4)
        return f(f(f(v.x, v.y), v.z), v.w);
}

template<std::floating_point F>
[[nodiscard]] constexpr F abs(F const& f)
{
    return std::abs(f);
}

template<std::integral I>
[[nodiscard]] constexpr I abs(I const& i)
{
    return i < I(0) ? -i : i;
}

template<vec V>
[[nodiscard]] constexpr V abs(V const& v)
{
    return map(v, abs<typename V::scalar_type>);
}

template<vec V>
[[nodiscard]] constexpr V clamp(V const& v, typename V::scalar_type const& lo, typename V::scalar_type const& hi)
{
    using namespace std::placeholders;
    return map(v, std::bind(std::clamp<typename V::scalar_type>, _1, lo, hi));
}

template<vec V>
requires(V::size_tag == 3)
[[nodiscard]] constexpr V cross(V const& v1, V const& v2)
{
    return {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x,
    };
}

template<vec V>
[[nodiscard]] constexpr auto distance(V const& v1, V const& v2)
{
    return std::sqrt(distance_squared(v1, v2));
}

template<vec V>
[[nodiscard]] constexpr auto distanceSquared(V const& v1, V const& v2)
{
    auto diff = v1 - v2;
    return dot(diff, diff);
}

template<vec V>
[[nodiscard]] constexpr auto dot(V const& v1, V const& v2)
{
    return reduce(v1 * v2, std::plus {});
}

template<vec V>
[[nodiscard]] constexpr V normalize(V const& v)
{
    return v / v.length();
}

template<vec V>
[[nodiscard]] constexpr auto lessThan(V const& v1, V const& v2)
{
    return map2(v1, v2, std::less {});
}

template<vec V>
[[nodiscard]] constexpr auto lessThanEqual(V const& v1, V const& v2)
{
    return map2(v1, v2, std::less_equal {});
}

template<vec V>
[[nodiscard]] constexpr auto greaterThan(V const& v1, V const& v2)
{
    return map2(v1, v2, std::greater {});
}

template<vec V>
[[nodiscard]] constexpr auto greaterThanEqual(V const& v1, V const& v2)
{
    return map2(v1, v2, std::greater_equal {});
}

template<vec V>
[[nodiscard]] constexpr auto equal(V const& v1, V const& v2)
{
    return map2(v1, v2, std::equal_to {});
}

template<vec V>
[[nodiscard]] constexpr auto notEqual(V const& v1, V const& v2)
{
    return map2(v1, v2, std::not_equal_to {});
}

[[nodiscard]] constexpr bool any(bvec4 const& v)
{
    return reduce(v, std::logical_or {});
}

[[nodiscard]] constexpr bool all(bvec4 const& v)
{
    return reduce(v, std::logical_and {});
}

template<vec V>
[[nodiscard]] constexpr bool almostEqual(V const& v1, V const& v2)
requires(std::floating_point<typename V::scalar_type>)
{
    return all(lessThan(abs(v1 - v2), V(0.00001)));
}

template<vec V>
[[nodiscard]] constexpr V reflect(V const& v, V const& normal)
{
    using S = typename V::scalar_type;
    return v - normal * S(2) * dot(v, normal);
}
} // namespace raytracer

template<raytracer::vec V>
struct std::formatter<V, char> {
    constexpr auto parse(auto& ctx)
    {
        return ctx.begin();
    }

    auto format(V const& v, auto& ctx) const
    {
        if constexpr (V::size_tag == 2)
            return std::format_to(ctx.out(), "<{} {}>", v.x, v.y);
        else if constexpr (V::size_tag == 3)
            return std::format_to(ctx.out(), "<{} {} {}>", v.x, v.y, v.z);
        else if constexpr (V::size_tag == 4)
            return std::format_to(ctx.out(), "<{} {} {} {}>", v.x, v.y, v.z, v.w);
    }
};
