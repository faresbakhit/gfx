module;
#include <cassert>
export module gfx.mat;

import gfx.types;
import gfx.vec;
import std;

template<class T>
struct undefined_constant {
    static_assert(std::false_type(), "undefined constant");
};

export namespace gfx {
template<typename S>
union mat4_t;

using mat4 = mat4_t<f32>;
using dmat4 = mat4_t<f64>;

template<typename T>
inline constexpr T identity = undefined_constant<T> {};

template<typename S>
union mat4_t {
private:
    std::array<vec4_t<S>, 4> data;

public:
    struct {
        vec4_t<S> x;
        vec4_t<S> y;
        vec4_t<S> z;
        vec4_t<S> w;
    };

    [[nodiscard]] constexpr mat4_t()
        : x(1, 0, 0, 0)
        , y(0, 1, 0, 0)
        , z(0, 0, 1, 0)
        , w(0, 0, 0, 1)
    {
    }

    [[nodiscard]] constexpr explicit mat4_t(S s)
        : x(s, 0, 0, 0)
        , y(0, s, 0, 0)
        , z(0, 0, s, 0)
        , w(0, 0, 0, s)
    {
    }

    [[nodiscard]] constexpr mat4_t(
        vec4_t<S> x,
        vec4_t<S> y,
        vec4_t<S> z,
        vec4_t<S> w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    [[nodiscard]] constexpr mat4_t(
        S x0, S x1, S x2, S x3,
        S y0, S y1, S y2, S y3,
        S z0, S z1, S z2, S z3,
        S w0, S w1, S w2, S w3)
        : x(x0, x1, x2, x3)
        , y(y0, y1, y2, y3)
        , z(z0, z1, z2, z3)
        , w(w0, w1, w2, w3)
    {
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator+(mat4_t<S2> const& m) const -> mat4_t<decltype(S {} + S2 {})>
    {
        return {
            x + m.x,
            y + m.y,
            z + m.z,
            w + m.w,
        };
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator-(mat4_t<S2> const& m) const -> mat4_t<decltype(S {} - S2 {})>
    {
        return {
            x - m.x,
            y - m.y,
            z - m.z,
            w - m.w,
        };
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator*(mat4_t<S2> const& m) const
    {
        return mat4_t {
            x.x * m.x.x + y.x * m.x.y + z.x * m.x.z + w.x * m.x.w,
            x.y * m.x.x + y.y * m.x.y + z.y * m.x.z + w.y * m.x.w,
            x.z * m.x.x + y.z * m.x.y + z.z * m.x.z + w.z * m.x.w,
            x.w * m.x.x + y.w * m.x.y + z.w * m.x.z + w.w * m.x.w,

            x.x * m.y.x + y.x * m.y.y + z.x * m.y.z + w.x * m.y.w,
            x.y * m.y.x + y.y * m.y.y + z.y * m.y.z + w.y * m.y.w,
            x.z * m.y.x + y.z * m.y.y + z.z * m.y.z + w.z * m.y.w,
            x.w * m.y.x + y.w * m.y.y + z.w * m.y.z + w.w * m.y.w,

            x.x * m.z.x + y.x * m.z.y + z.x * m.z.z + w.x * m.z.w,
            x.y * m.z.x + y.y * m.z.y + z.y * m.z.z + w.y * m.z.w,
            x.z * m.z.x + y.z * m.z.y + z.z * m.z.z + w.z * m.z.w,
            x.w * m.z.x + y.w * m.z.y + z.w * m.z.z + w.w * m.z.w,

            x.x * m.w.x + y.x * m.w.y + z.x * m.w.z + w.x * m.w.w,
            x.y * m.w.x + y.y * m.w.y + z.y * m.w.z + w.y * m.w.w,
            x.z * m.w.x + y.z * m.w.y + z.z * m.w.z + w.z * m.w.w,
            x.w * m.w.x + y.w * m.w.y + z.w * m.w.z + w.w * m.w.w,
        };
    }

    template<typename S2>
    [[nodiscard]] constexpr auto operator/(mat4_t<S2> const& m) const
    {
        return operator*(inverse(m));
    }

    template<typename S2>
    [[nodiscard]] constexpr mat4_t<S>& operator+=(mat4_t<S2> const& m)
    {
        x += m.x;
        y += m.y;
        z += m.z;
        w += m.w;
        return *this;
    }

    template<typename S2>
    [[nodiscard]] constexpr mat4_t<S>& operator-=(mat4_t<S2> const& m)
    {
        x -= m.x;
        y -= m.y;
        z -= m.z;
        w -= m.w;
        return *this;
    }

    template<typename S2>
    [[nodiscard]] constexpr mat4_t<S>& operator*=(mat4_t<S2> const& m)
    {
        return (*this = *this * m);
    }

    template<typename S2>
    [[nodiscard]] constexpr mat4_t<S>& operator/=(mat4_t<S2> const& m)
    {
        return (*this = *this / m);
    }

    template<typename S2>
    constexpr bool operator==(mat4_t<S2> const& m) const
    {
        return (x == m.x)
            && (y == m.y)
            && (z == m.z)
            && (w == m.w);
    }

    template<typename S2>
    constexpr bool operator!=(mat4_t<S2> const& m) const
    {
        return (x != m.x)
            || (y != m.y)
            || (z != m.z)
            || (w != m.w);
    }

    [[nodiscard]] constexpr mat4_t operator+(S s) const
    {
        return {
            x + s,
            y + s,
            z + s,
            w + s,
        };
    }

    [[nodiscard]] constexpr mat4_t operator-(S s) const
    {
        return {
            x - s,
            y - s,
            z - s,
            w - s,
        };
    }

    [[nodiscard]] constexpr mat4_t operator*(S s) const
    {
        return {
            x * s,
            y * s,
            z * s,
            w * s,
        };
    }

    [[nodiscard]] constexpr mat4_t operator/(S s) const
    {
        return {
            x / s,
            y / s,
            z / s,
            w / s,
        };
    }

    [[nodiscard]] constexpr mat4_t<S>& operator+=(S s)
    {
        x += s;
        y += s;
        z += s;
        w += s;
        return *this;
    }

    [[nodiscard]] constexpr mat4_t<S>& operator-=(S s)
    {
        x -= s;
        y -= s;
        z -= s;
        w -= s;
        return *this;
    }

    [[nodiscard]] constexpr mat4_t<S>& operator*=(S s)
    {
        x *= s;
        y *= s;
        z *= s;
        w *= s;
        return *this;
    }

    [[nodiscard]] constexpr mat4_t<S>& operator/=(S s)
    {
        x /= s;
        y /= s;
        z /= s;
        w /= s;
        return *this;
    }

    [[nodiscard]] constexpr vec4_t<S> const& operator[](usize i) const
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

    [[nodiscard]] constexpr vec4_t<S>& operator[](usize i)
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

    [[nodiscard]] constexpr S det() const
    {

        auto d0 = z.z * w.w - w.z * z.w;
        auto d1 = y.z * w.w - w.z * y.w;
        auto d2 = y.z * z.w - z.z * y.w;
        auto d3 = x.z * w.w - w.z * x.w;
        auto d4 = x.z * z.w - z.z * x.w;
        auto d5 = x.z * y.w - y.z * x.w;
        return (
            x.x * (y.y * d0 - z.y * d1 + w.y * d2)
            - y.x * (x.y * d0 - z.y * d3 + w.y * d4)
            + z.x * (x.y * d1 - y.y * d3 + w.y * d5)
            - w.x * (x.y * d2 - y.y * d4 + z.y * d5));
    }

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

template<typename S1, typename S2>
[[nodiscard]] constexpr auto operator+(S1 s, mat4_t<S2> const& m)
{
    return m + s;
}

template<typename S1, typename S2>
[[nodiscard]] constexpr auto operator-(S1 s, mat4_t<S2> const& m)
{
    return mat4_t {
        s - m.x,
        s - m.y,
        s - m.z,
        s - m.w,
    };
}

template<typename S1, typename S2>
[[nodiscard]] constexpr auto operator*(S1 s, mat4_t<S2> const& m)
{
    return m * s;
}

template<typename S1, typename S2>
[[nodiscard]] constexpr auto operator/(S1 s, mat4_t<S2> const& m)
{
    return inverse(m) * s;
}

template<typename S>
[[nodiscard]] constexpr vec4_t<S> operator*(vec4_t<S> const& v, mat4_t<S> const& m)
{
    return {
        v.x * m.x.x + v.y * m.x.y + v.z * m.x.z + v.w * m.x.w,
        v.x * m.y.x + v.y * m.y.y + v.z * m.y.z + v.w * m.y.w,
        v.x * m.z.x + v.y * m.z.y + v.z * m.z.z + v.w * m.z.w,
        v.x * m.w.x + v.y * m.w.y + v.z * m.w.z + v.w * m.w.w,
    };
}

template<typename S>
[[nodiscard]] constexpr vec4_t<S> operator*(mat4_t<S> const& m, vec4_t<S> const& v)
{
    return {
        m.x.x * v.x + m.y.x * v.y + m.z.x * v.z + m.w.x * v.w,
        m.x.y * v.x + m.y.y * v.y + m.z.y * v.z + m.w.y * v.w,
        m.x.z * v.x + m.y.z * v.y + m.z.z * v.z + m.w.z * v.w,
        m.x.w * v.x + m.y.w * v.y + m.z.w * v.z + m.w.w * v.w,
    };
}

template<typename S>
std::ostream& operator<<(std::ostream& os, mat4_t<S> const& m)
{
    return os << std::format("{}", m);
}

template<typename S>
inline constexpr mat4_t<S> identity<mat4_t<S>> = mat4_t<S>();
template<typename S>
inline constexpr mat4_t<S> one<mat4_t<S>> = mat4_t<S>(
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1);
template<typename S>
inline constexpr mat4_t<S> zero<mat4_t<S>> = mat4_t<S>(0);

template<typename S>
[[nodiscard]] constexpr mat4_t<S> inverse(mat4_t<S> const& m)
{
    auto d00 = m.z.z * m.w.w - m.w.z * m.z.w;
    auto d01 = m.y.z * m.w.w - m.w.z * m.y.w;
    auto d02 = m.y.z * m.z.w - m.z.z * m.y.w;
    auto d03 = m.x.z * m.w.w - m.w.z * m.x.w;
    auto d04 = m.x.z * m.z.w - m.z.z * m.x.w;
    auto d05 = m.x.z * m.y.w - m.y.z * m.x.w;

    auto d06 = m.z.x * m.w.y - m.w.x * m.z.y;
    auto d07 = m.y.x * m.w.y - m.w.x * m.y.y;
    auto d08 = m.y.x * m.z.y - m.z.x * m.y.y;
    auto d09 = m.x.x * m.w.y - m.w.x * m.x.y;
    auto d10 = m.x.x * m.z.y - m.z.x * m.x.y;
    auto d11 = m.x.x * m.y.y - m.y.x * m.x.y;

    auto xx = m.y.y * d00 - m.z.y * d01 + m.w.y * d02;
    auto xy = m.z.y * d03 - m.x.y * d00 - m.w.y * d04;
    auto xz = m.x.y * d01 - m.y.y * d03 + m.w.y * d05;
    auto xw = m.y.y * d04 - m.x.y * d02 - m.z.y * d05;
    auto yx = m.z.x * d01 - m.y.x * d00 - m.w.x * d02;
    auto yy = m.x.x * d00 - m.z.x * d03 + m.w.x * d04;
    auto yz = m.y.x * d03 - m.x.x * d01 - m.w.x * d05;
    auto yw = m.x.x * d02 - m.y.x * d04 + m.z.x * d05;
    auto zx = m.y.w * d06 - m.z.w * d07 + m.w.w * d08;
    auto zy = m.z.w * d09 - m.x.w * d06 - m.w.w * d10;
    auto zz = m.x.w * d07 - m.y.w * d09 + m.w.w * d11;
    auto zw = m.y.w * d10 - m.x.w * d08 - m.z.w * d11;
    auto wx = m.z.z * d07 - m.y.z * d06 - m.w.z * d08;
    auto wy = m.x.z * d06 - m.z.z * d09 + m.w.z * d10;
    auto wz = m.y.z * d09 - m.x.z * d07 - m.w.z * d11;
    auto ww = m.x.z * d08 - m.y.z * d10 + m.z.z * d11;

    auto d = m.det();

    return mat4_t {
        xx / d, xy / d, xz / d, xw / d,
        yx / d, yy / d, yz / d, yw / d,
        zx / d, zy / d, zz / d, zw / d,
        wx / d, wy / d, wz / d, ww / d
    };
}

template<typename S>
[[nodiscard]] constexpr mat4_t<S> transpose(mat4_t<S> const& m)
{
    return {
        m.x.x, m.y.x, m.z.x, m.w.x,
        m.x.y, m.y.y, m.z.y, m.w.y,
        m.x.z, m.y.z, m.z.z, m.w.z,
        m.x.w, m.y.w, m.z.w, m.w.w
    };
}
}; // namespace gfx

template<typename S>
struct std::formatter<gfx::mat4_t<S>, char> {
    constexpr auto parse(auto& ctx)
    {
        return ctx.begin();
    }

    auto format(gfx::mat4_t<S> const& m, auto& ctx) const
    {
        gfx::ivec4 p;
        for (std::tuple<gfx::vec4_t<S> const&, gfx::i32&> e : std::ranges::views::zip(m, p)) {
            auto [col, padding] = e;
            for (auto c : col)
                padding = std::max(
                    padding,
                    gfx::i32(std::format("{}", c).length()));
        }
        return std::format_to(ctx.out(),
            "<<{:{}} {:{}} {:{}} {:{}}>\n <{:{}} {:{}} {:{}} {:{}}>\n <{:{}} {:{}} {:{}} {:{}}>\n <{:{}} {:{}} {:{}} {:{}}>>",
            m.x.x, p.x, m.y.x, p.y, m.z.x, p.z, m.w.x, p.w,
            m.x.y, p.x, m.y.y, p.y, m.z.y, p.z, m.w.y, p.w,
            m.x.z, p.x, m.y.z, p.y, m.z.z, p.z, m.w.z, p.w,
            m.x.w, p.x, m.y.w, p.y, m.z.w, p.z, m.w.w, p.w);
    }
};
