import std;
import raytracer;

using namespace raytracer;

int main()
{
    canvas c(100, 100);
    auto transform
        = mat4::scale(f32(c.width()) / 2.0f, f32(c.height()) / -2.0f, 0.0f)
        * mat4::translate(1.0f, -1.0f, 0.0f);
    vec4 p = vec4(0.0f, 0.9f, 0.0f, 1.0f);
    for (int i = 0; i < 12; i++) {
        c[(p * transform).xy] = one<vec3>;
        p = mat4::rotate_z(std::numbers::pi / -6.0f) * p;
    }
    write_ppm(c, "clock.ppm");
}
