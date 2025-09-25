export module raytracer.object;

import raytracer.constants;
import raytracer.mat;
import raytracer.ray;
import raytracer.types;
import raytracer.vec;
import std;

export namespace raytracer {
constexpr u32 no_id = std::numeric_limits<u32>::max();

struct material {
    vec3 color = one<vec3>;
    f32 ambient = 0.1f,
        diffuse = 0.9f,
        specular = 0.9f,
        shininess = 200.0f;

    bool operator==(material const&) const = default;
};

struct point_light {
    vec3 position;
    vec3 intensity;

    bool operator==(point_light const&) const = default;
};

struct intersection;

using intersections = std::unordered_set<intersection>;

class Object {
public:
    u32 id = no_id;
    material material;

    virtual ~Object() { }
    virtual intersections intersect(ray const& r) const = 0;
    virtual vec3 normalAt(vec3 const& p) const = 0;

    mat4 const& transform() const
    {
        return m_transform;
    }

    mat4 const& inverseTransform() const
    {
        return m_inverse_transform;
    }

    void setTransform(mat4 const& t)
    {
        m_transform = t;
        m_inverse_transform = inverse(t);
    }

private:
    mat4 m_transform;
    mat4 m_inverse_transform;
};

class ObjectPool {
private:
    std::vector<std::unique_ptr<Object>> m_storage;

public:
    template<typename T, typename... Args>
    T& add(Args&&... args)
    {
        auto obj = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *obj;
        obj->id = m_storage.size();
        m_storage.push_back(std::move(obj));
        return ref;
    }

    Object& get(u32 id)
    {
        return *m_storage[id];
    }
};

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

    intersection(f32 t, Object const& o)
        : t(t)
        , object_id(o.id)
    {
    }

    bool operator==(intersection const&) const = default;
};

} // namespace raytracer

template<>
struct std::hash<raytracer::intersection> {
    std::size_t operator()(raytracer::intersection const& i) const noexcept
    {
        return (static_cast<std::size_t>(i.t) << 32) | i.object_id;
    }
};

export namespace raytracer {
class Sphere : public Object {
public:
    virtual intersections intersect(ray const& r) const override
    {
        auto r2 = inverseTransform() * r;
        auto sphere_to_ray = r2.o - zero<vec3>;
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

    virtual vec3 normalAt(vec3 const& p) const override
    {
        auto object_point = inverseTransform() * vec4::point(p);
        auto object_normal = object_point - vec4::point();
        auto world_normal = transpose(inverseTransform()) * object_normal;
        world_normal.w = 0;
        return vec3(normalize(world_normal));
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

[[nodiscard]] constexpr auto lighting(
    material const& m,
    point_light const& light,
    vec3 const& point,
    vec3 const& eyev,
    vec3 const& normalv)
{
    // colors are vec3
    vec3 effective_color = m.color * light.intensity; // both vec3
    vec3 lightv = normalize(light.position - point);

    vec3 ambient = effective_color * m.ambient;

    float light_dot_normal = dot(lightv, normalv);

    vec3 diffuse(0.0f);
    vec3 specular(0.0f);

    if (light_dot_normal >= 0.0f) {
        diffuse = effective_color * m.diffuse * light_dot_normal;

        vec3 reflectv = reflect(-lightv, normalv);
        float reflect_dot_eye = dot(reflectv, eyev);

        if (reflect_dot_eye > 0.0f) {
            float factor = std::pow(reflect_dot_eye, m.shininess);
            specular = light.intensity * m.specular * factor;
        }
    }

    return ambient + diffuse + specular; // vec3
}
} // namespace raytracer
