import raytracer;

using namespace raytracer;

int main()
{
    CanvasRGB canvas(100, 100);
    auto transform
        = mat4::scale(f32(canvas.width()) / 2.0f, f32(canvas.height()) / -2.0f, 0.0f)
        * mat4::translate(1.0f, -1.0f, 0.0f);
    vec4 p = vec4(0.0f, 0.9f, 0.0f, 1.0f);
    for (int i = 0; i < 12; i++) {
        canvas[(p * transform).xy.swap()] = one<vec3>;
        p = mat4::rotateZ(pi<f32> / -6.0f) * p;
    }
    writePFM(canvas, "clock.pfm");
}
