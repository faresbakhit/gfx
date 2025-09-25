import std;
import raytracer;

using namespace raytracer;

constexpr i32 canvas_size = 512;
constexpr f32 wall_size = 7.0f;
constexpr f32 wall_z = 10.0f;
constexpr f32 pixel_size = wall_size / canvas_size;
constexpr f32 half = wall_size / 2.0f;

int main()
{
    CanvasRGBA canvas(canvas_size, canvas_size);
    auto s = Sphere();
    s.material.color = vec3(0.0, 0.5, 1.0);
    auto light = point_light(vec3(-10, 10, -10), vec3(1.0f, 1.0f, 1.0f));
    auto ray_origin = vec3(0, 0, -5);

    for (i32 i = 0; i < canvas.width(); i++) {
        f32 world_x = -half + pixel_size * i;
        for (i32 j = 0; j < canvas.height(); j++) {
            f32 world_y = half - pixel_size * j;
            auto pos = vec3(world_x, world_y, wall_z); // vec3, not vec4
            auto direction = normalize(pos - ray_origin);
            auto r = ray(ray_origin, direction);

            auto xs = s.intersect(r);
            auto h = hit(xs);
            if (h) {
                auto hit = h.value();
                auto point = r.at(hit.t);
                auto normal = s.normalAt(point); // must be normalized vec3
                auto eye = -r.d;
                auto color = lighting(s.material, light, point, eye, normal); // all vec3
                canvas[i, j] = vec4(color, 1.0f);
            }
        }
    }
    writePAM(canvas, "sphere.pam");
}
