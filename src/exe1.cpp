import std;
import gfx;

using namespace gfx;

int main()
{
    canvas c(200, 100);
    for (int j = 0; j < c.height(); j++) {
        for (int i = 0; i < c.width(); i++) {
            c[i, j] = vec3(
                float(i) / float(c.width()),
                float(c.height() - j - 1) / float(c.height()),
                0.2f);
        }
    }
    write_ppm(c, "hello.ppm");
}
