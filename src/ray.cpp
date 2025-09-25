export module raytracer.ray;

import raytracer.types;
import raytracer.vec;
import raytracer.mat;
import std;

export namespace raytracer {
struct ray {
    vec3 o, d;

    [[nodiscard]] constexpr vec3 at(vec3::scalar_type const& t)
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
} // namespace raytracer
