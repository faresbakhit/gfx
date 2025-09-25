export module raytracer.meta;

import std;

export namespace raytracer {
template<class... T>
constexpr bool always_false = false;

template<class... T>
struct undefined {
    static_assert(always_false<T...>, "undefined");
};
} // namespace raytracer
