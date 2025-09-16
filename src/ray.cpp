export module raytracer.ray;

import raytracer.types;
import raytracer.vec;
import raytracer.mat;
import std;

export namespace raytracer {
struct ray {
    vec3 o, d;

    [[nodiscard]] constexpr vec3 at(f32 const& t)
    {
        return o + d * t;
    }
};

[[nodiscard]] constexpr ray operator*(mat4 const& m, ray const& r)
{
    return {
        vec3(m * vec4::point(r.o)),
        vec3(m * vec4(r.d)),
    };
}

struct object;

constexpr u32 no_id = std::numeric_limits<u32>::max();

struct intersection {
    f32 t;
    u32 object_id;

    intersection() = delete;

    intersection(f32 t)
        : t(t)
        , object_id(no_id)
    {
    }

    intersection(f32 t, u32 object_id)
        : t(t)
        , object_id(object_id)
    {
    }

    intersection(f32 t, object const& o);

    bool operator==(intersection const&) const = default;
};

using intersections = std::unordered_set<intersection>;
} // namespace raytracer

template<>
struct ::std::hash<raytracer::intersection> {
    std::size_t operator()(raytracer::intersection const& i) const noexcept
    {
        return (static_cast<std::size_t>(i.t) << 32) | i.object_id;
    }
};

export namespace raytracer {
struct object {
    u32 id = no_id;
    virtual ~object() { }
    virtual std::unordered_set<intersection> intersect(ray const& r) const = 0;
};

intersection::intersection(f32 t, object const& o)
    : t(t)
    , object_id(o.id)
{
}

struct object_pool {
    std::vector<std::unique_ptr<object>> storage;

    template<typename T, typename... Args>
    T& add(Args&&... args)
    {
        auto obj = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *obj;
        obj->id = storage.size();
        storage.push_back(std::move(obj));
        return ref;
    }

    object& get(u32 id)
    {
        return *storage[id];
    }
};

struct sphere : public object {
    mat4 transform;

    virtual intersections intersect(ray const& r) const override
    {
        auto r2 = inverse(transform) * r;
        auto sphere_to_ray = r2.o - vec3(0.0f, 0.0f, 0.0f);
        auto a = dot(r2.d, r2.d);
        auto b = 2 * dot(r2.d, sphere_to_ray);
        auto c = dot(sphere_to_ray, sphere_to_ray) - 1;
        auto discriminant = b * b - 4.0f * a * c;
        if (discriminant < 0.0f) {
            return {};
        }
        auto t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
        auto t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);
        return { intersection(t1, id), intersection(t2, id) };
    }
};

[[nodiscard]] std::optional<intersection> hit(intersections const& xs)
{
    if (xs.empty()) {
        return {};
    }
    constexpr f32 inf = std::numeric_limits<f32>::infinity();
    intersection min_i = intersection(inf);
    for (auto const& i : xs) {
        if (i.t > 0.0f && i.t < min_i.t) {
            min_i = i;
        }
    }
    if (min_i.t == inf) {
        return {};
    }
    return min_i;
}
} // namespace raytracer

template<>
struct std::formatter<raytracer::intersection> {
    constexpr auto parse(auto& ctx)
    {
        return ctx.begin();
    }

    auto format(raytracer::intersection const& i, auto& ctx) const
    {
        if (i.object_id == raytracer::no_id) {
            return std::format_to(ctx.out(), "{}", i.t);
        } else {
            return std::format_to(ctx.out(), "{}{{{}}}", i.t, i.object_id);
        }
    }
};

template<>
struct std::formatter<raytracer::ray> {
    constexpr auto parse(auto& ctx)
    {
        return ctx.begin();
    }

    auto format(raytracer::ray const& r, auto& ctx) const
    {
        return std::format_to(ctx.out(), "({}, {})", r.o, r.d);
    }
};
