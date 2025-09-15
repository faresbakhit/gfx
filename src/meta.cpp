export module gfx.meta;

import std;

export namespace gfx {
template<class... T>
constexpr bool always_false = false;

template<class... T>
class undefined {
    static_assert(always_false<T...>, "undefined");
};
} // namespace gfx
