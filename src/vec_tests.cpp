import boost.ut;
import gfx.vec;

using namespace boost::ut::bdd;
using namespace boost::ut;
using namespace gfx;

int main()
{
    feature("Adding two vectors") = [] {
        auto u = vec4(3, -2, 5, 1);
        auto v = vec4(-2, 3, 1, 0);
        expect(u + v == vec4(1, 1, 6, 1));
    };

    feature("Subtracting two vectors") = [] {
        auto u = vec3(3, 2, 1);
        auto v = vec3(5, 6, 7);
        expect(u - v == vec3(-2, -4, -6));

        given("A zero vector") = [] {
            auto v = vec3(1, -2, 3);
            expect(v - zero<vec3> == v);
            expect(zero<vec3> - v == vec3(-1, 2, -3));
        };
    };

    feature("Negating a vector") = [] {
        auto a = vec4(1, -2, 3, -4);
        expect(-a == vec4(-1, 2, -3, 4));
    };

    feature("Multiplying a vector by a scalar") = [] {
        auto a = vec4(1, -2, 3, -4);
        expect(a * 3.5f == vec4(3.5, -7, 10.5, -14));
        expect(a * 0.5f == vec4(0.5, -1, 1.5, -2));
    };

    feature("Dividing a vector by a scalar") = [] {
        auto a = vec4(1, -2, 3, -4);
        expect(a / 2 == vec4(0.5, -1, 1.5, -2));
    };

    feature("Computing a vector's length") = [] {
        given("A unit vector") = [] {
            expect(unit_x<vec3>.length() == 1.0_f);
            expect(unit_y<vec3>.length() == 1.0_f);
            expect(unit_z<vec3>.length() == 1.0_f);
        };

        given("A vector and its negation") = [] {
            auto v = vec3(1, 2, 3);
            expect(v.length() == _f(std::sqrt(14)));
            v = -v;
            expect(v.length() == _f(std::sqrt(14)));
        };
    };

    feature("Normalizing a vector") = [] {
        expect(normalize(vec3(4, 0, 0)) == vec3(1, 0, 0));
        expect(normalize(vec3(1, 2, 3))
            == vec3(
                1.0f / std::sqrt(14.0f),
                2.0f / std::sqrt(14.0f),
                3.0f / std::sqrt(14.0f)));
    };

    feature("The dot product of two vectors") = [] {
        auto a = vec3(1, 2, 3);
        auto b = vec3(2, 3, 4);
        expect(dot(a, b) == 20.0_f);
    };

    feature("The cross product of two vectors") = [] {
        auto a = vec3(1, 2, 3);
        auto b = vec3(2, 3, 4);
        expect(cross(a, b) == vec3(-1, 2, -1));
        expect(cross(b, a) == vec3(1, -2, 1));
    };
}
