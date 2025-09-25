import raytracer;
import std;

using namespace raytracer;

int main()
{
    material m;
    vec3 pos = vec3();
    vec3 eyev = vec3(0, -std::sqrt(2.0f) / 2.0f, -std::sqrt(2.0f) / 2.0f);
    vec3 normalv = vec3(0, 0, -1);
    point_light light = point_light(vec3(0, 10, -10), vec3(1, 1, 1));
    std::println("{}", lighting(m, light, pos, eyev, normalv));
}
