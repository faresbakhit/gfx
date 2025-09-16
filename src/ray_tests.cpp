import boost.ut;
import raytracer.ray;
import raytracer.vec;
import raytracer.mat;

using namespace boost::ut::bdd;
using namespace boost::ut;
using namespace raytracer;

int main()
{
    scenario("Creating and querying a ray") = []() {
        auto origin = vec3(1.0f, 2, 3);
        auto direction = vec3(4, 5, 6);
        auto r = ray(origin, direction);
        expect(r.o == origin);
        expect(r.d == direction);
    };

    scenario("Computing a point from a distance") = []() {
        auto origin = vec3(2, 3, 4);
        auto direction = vec3(1, 0, 0);
        auto r = ray(origin, direction);
        expect(r.at(0) == vec3(2, 3, 4));
        expect(r.at(1) == vec3(3, 3, 4));
        expect(r.at(-1) == vec3(1, 3, 4));
        expect(r.at(2.5) == vec3(4.5f, 3, 4));
    };

    object_pool pool;

    scenario("A ray intersects a sphere at two points") = [&pool]() {
        auto r = ray(vec3(0, 0, -5), vec3(0, 0, 1));
        auto& s = pool.add<sphere>();
        auto xs = s.intersect(r);
        expect(xs == std::unordered_set { intersection(4, 0), intersection(6, 0) });
    };

    scenario("A ray intersects a sphere at a tangent") = [&pool]() {
        auto r = ray(vec3(0, 1, -5), vec3(0, 0, 1));
        auto& s = pool.add<sphere>();
        auto xs = s.intersect(r);
        expect(xs == std::unordered_set { intersection(5, 1) });
    };

    scenario("A ray misses a sphere") = [&pool]() {
        auto r = ray(vec3(0, 2, -5), vec3(0, 0, 1));
        auto& s = pool.add<sphere>();
        auto xs = s.intersect(r);
        expect(s.id == 2);
        expect(xs.size() == 0);
    };

    scenario("A ray originates inside a sphere") = [&pool]() {
        auto r = ray(vec3(0, 0, 0), vec3(0, 0, 1));
        auto& s = pool.add<sphere>();
        auto xs = s.intersect(r);
        expect(xs == std::unordered_set { intersection(-1, 3), intersection(1.0f, 3) });
    };

    scenario("A sphere is behind a ray") = [&pool]() {
        auto r = ray(vec3(0, 0, 5), vec3(0, 0, 1));
        auto& s = pool.add<sphere>();
        auto xs = s.intersect(r);
        expect(xs == std::unordered_set { intersection(-6, 4), intersection(-4, 4) });
    };

    scenario("The hit, when all intersections have positive t") = []() {
        auto s = sphere();
        auto i1 = intersection(1, s);
        auto i2 = intersection(2, s);
        auto i = hit(intersections { i1, i2 });
        expect(i == i1);
    };

    scenario("The hit, when some intersections have negative t") = []() {
        auto s = sphere();
        auto i1 = intersection(-1, s);
        auto i2 = intersection(1, s);
        auto i = hit(intersections { i1, i2 });
        expect(i == i2);
    };

    scenario("The hit, when all intersections have negative t") = []() {
        auto s = sphere();
        auto i1 = intersection(-2, s);
        auto i2 = intersection(-1, s);
        auto i = hit(intersections { i1, i2 });
        expect(!i.has_value());
    };

    scenario("The hit is always the lowest nonnegative intersection") = []() {
        auto s = sphere();
        auto i1 = intersection(5, s);
        auto i2 = intersection(7, s);
        auto i3 = intersection(-3, s);
        auto i4 = intersection(2, s);
        auto i = hit(intersections { i1, i2, i3, i4 });
        expect(i == i4);
    };

    scenario("Translating a ray") = []() {
        auto r = ray(vec3(1, 2, 3), vec3(0, 1, 0));
        auto t = mat4::translate(3, 4, 5);
        auto r2 = r * t;
        expect(r2.o == vec3(4, 6, 8));
        expect(r2.d == vec3(0, 1, 0));
    };

    scenario("Intersecting a scaled sphere with a ray") = []() {
        auto s = sphere();
        auto r = ray(vec3(0, 0, -5), vec3(0, 0, 1));
        s.transform = mat4::scale(2, 2, 2);
        auto xs = s.intersect(r);
        expect(xs == std::unordered_set { intersection(3), intersection(7) });
    };

    scenario("Intersecting a translated sphere with a ray") = []() {
        auto s = sphere();
        auto r = ray(vec3(0, 0, -5), vec3(0, 0, 1));
        s.transform = mat4::translate(5, 0, 0);
        auto xs = s.intersect(r);
        expect(xs.empty());
    };
}
