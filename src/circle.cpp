import std;
import raytracer;

using namespace raytracer;

constexpr i32 canvas_size = 100;
constexpr f32 wall_size = 7.0f;
constexpr f32 wall_z = 10.0f;
constexpr f32 pixel_size = wall_size / canvas_size;
constexpr f32 half = wall_size / 2.0f;

int main()
{
    CanvasRGB canvas(canvas_size, canvas_size);
    Sphere s;
    auto ray_origin = vec3(0, 0, -5);
    for (i32 i = 0; i < canvas.width(); i++) {
        f32 world_x = -half + pixel_size * i;
        for (i32 j = 0; j < canvas.height(); j++) {
            f32 world_y = half - pixel_size * j;
            auto pos = vec3(world_x, world_y, wall_z);
            auto r = ray(ray_origin, normalize(pos - ray_origin));
            auto xs = s.intersect(r);
            if (hit(xs)) {
                canvas[i, j] = vec3(1, 0, 0);
            }
        }
    }
    writePAM(canvas, "circle.pam");
}
