import boost.ut;
import raytracer.constants;
import raytracer.mat;
import raytracer.types;
import raytracer.vec;

using namespace boost::ut::bdd;
using namespace boost::ut;
using namespace raytracer;

int main()
{
    feature("Multiplying two matrices") = []() {
        auto a = mat4(
            1, 5, 9, 5,
            2, 6, 8, 4,
            3, 7, 7, 3,
            4, 8, 6, 2);
        auto b = mat4(
            -2, 3, 4, 1,
            1, 2, 3, 2,
            2, 1, 6, 7,
            3, -1, 5, 8);

        expect(a * b
            == mat4(
                20, 44, 40, 16,
                22, 54, 58, 26,
                50, 114, 110, 46,
                48, 108, 102, 42));

        given("An identity matrix") = [&]() {
            expect(a * identity<mat4> == a);
            expect(identity<mat4> * a == a);
        };
    };

    feature("A matrix multiplied by a vector") = []() {
        auto a = mat4(
            1, 2, 8, 0,
            2, 4, 6, 0,
            3, 4, 4, 0,
            4, 2, 1, 1);
        auto b = vec4(1, 2, 3, 1);
        expect(a * b == vec4(18, 24, 33, 1));
    };

    feature("Transposing a matrix") = []() {
        auto a = mat4(
            0, 9, 1, 0,
            9, 8, 8, 0,
            3, 0, 5, 5,
            0, 8, 3, 8);
        expect(transpose(a)
            == mat4(
                0, 9, 3, 0,
                9, 8, 0, 8,
                1, 8, 5, 3,
                0, 0, 5, 8));

        given("An identity matrix") = []() {
            expect(transpose(identity<mat4>) == identity<mat4>);
        };
    };

    feature("Calculating the determinant") = []() {
        auto a = mat4(
            -2, -3, 1, -6,
            -8, 1, 2, 7,
            3, 7, -9, 7,
            5, 3, 6, -9);
        expect(a.det() == -4071.0_f);
    };

    feature("Calculating the inverse of a matrix") = []() {
        scenario("The following 4x4 matrix") = []() {
            mat4 a(
                -5, 1, 7, 1,
                2, -5, 7, -3,
                6, 1, -6, 7,
                -8, 8, -7, 4);
            expect((almostEqual(inverse(a),
                mat4(
                    0.21805, -0.80827, -0.07895, -0.52256,
                    0.45113, -1.45677, -0.22368, -0.81391,
                    0.24060, -0.44361, -0.05263, -0.30075,
                    -0.04511, 0.52068, 0.19737, 0.30639))));
        };
        scenario("Another 4x4 matrix") = []() {
            mat4 a(
                8, 7, -6, -3,
                -5, 5, 0, 0,
                9, 6, 9, -9,
                2, 1, 6, -4);
            expect((almostEqual(inverse(a),
                mat4(
                    -0.15385, -0.07692, 0.35897, -0.69231,
                    -0.15385, 0.12308, 0.35897, -0.69231,
                    -0.28205, 0.02564, 0.43590, -0.76923,
                    -0.53846, 0.03077, 0.92308, -1.92308))));
        };
        scenario("A third 4x4 matrix") = []() {
            mat4 a(
                9, -5, -4, -7,
                3, -2, 9, 6,
                0, -6, 6, 6,
                9, -3, 4, 2);
            expect((almostEqual(inverse(a),
                mat4(
                    -0.04074, -0.07778, -0.02901, 0.17778,
                    -0.07778, 0.03333, -0.14630, 0.06667,
                    0.14444, 0.36667, -0.10926, -0.26667,
                    -0.22222, -0.33333, 0.12963, 0.33333))));
        };
        scenario("Multiplying a product by its inverse") = []() {
            mat4 a(
                3, 3, -4, -6,
                -9, -8, 4, 5,
                7, 2, 4, -1,
                3, -9, 1, 1);
            mat4 b(
                8, 3, 7, 6,
                2, -1, 0, -2,
                2, 7, 5, 0,
                2, 0, 4, 5);
            mat4 c = a * b;
            expect(almostEqual(c * inverse(b), a));
        };
    };

    feature("Translation matrix") = []() {
        auto transform = mat4::translate(5, -3, 2);
        auto p = vec4(-3, 4, 5, 1);
        scenario("Multiplying by a translation matrix") = [&]() {
            expect(transform * p == vec4(2, 1, 7, 1));
        };
        scenario("Multiplying by the inverse of a translation matrix") = [&]() {
            expect(inverse(transform) * p == vec4(-8, 7, 3, 1));
        };
        scenario("Translation does not affect vectors") = [&]() {
            auto v = vec4(-3, 4, 5, 0);
            expect(transform * v == v);
        };
    };

    feature("Scaling matrix") = []() {
        auto transform = mat4::scale(2, 3, 4);
        auto p = vec4(-4, 6, 8, 1);
        scenario("Multiplying by a translation matrix") = [&]() {
            expect(transform * p == vec4(-8, 18, 32, 1));
        };
        scenario("Multiplying by the inverse of a translation matrix") = [&]() {
            expect(inverse(transform) * p == vec4(-2, 2, 2, 1));
        };
        scenario("Translation affects vectors") = [&]() {
            auto v = vec4(-4, 6, 8, 0);
            expect(transform * v == vec4(-8, 18, 32, 0));
        };
        scenario("Refletion is scaling by a negative value") = []() {
            expect(mat4::scale(-1, 1, 1) * vec4(2, 3, 4, 1) == vec4(-2, 3, 4, 1));
        };
    };

    feature("Rotation matrix") = []() {
        scenario("Rotating a point around the x axis") = []() {
            auto half_quarter = dmat4::rotateX(std::numbers::pi / 4.0);
            auto full_quarter = dmat4::rotateX(std::numbers::pi / 2.0);
            auto p = dvec4(0.0, 1.0, 0.0, 1.0);
            expect(almostEqual(half_quarter * p, dvec4(0.0, std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0, 1.0)));
            expect(almostEqual(full_quarter * p, dvec4(0.0, 0.0, 1.0, 1.0)));
            expect(almostEqual(inverse(half_quarter) * p, dvec4(0.0, std::sqrt(2.0) / 2.0, -std::sqrt(2.0) / 2.0, 1.0)));
        };
        scenario("Rotating a point around the y axis") = []() {
            auto half_quarter = dmat4::rotateY(std::numbers::pi / 4.0);
            auto full_quarter = dmat4::rotateY(std::numbers::pi / 2.0);
            auto p = dvec4(0.0, 0.0, 1.0, 1.0);
            expect(almostEqual(half_quarter * p, dvec4(std::sqrt(2.0) / 2.0, 0.0, std::sqrt(2.0) / 2.0, 1.0)));
            expect(almostEqual(full_quarter * p, dvec4(1.0, 0.0, 0.0, 1.0)));
        };
        scenario("Rotating a point around the z axis") = []() {
            auto half_quarter = dmat4::rotateZ(std::numbers::pi / 4.0);
            auto full_quarter = dmat4::rotateZ(std::numbers::pi / 2.0);
            auto p = dvec4(0.0, 1.0, 0.0, 1.0);
            expect(almostEqual(half_quarter * p, dvec4(-std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0, 0.0, 1.0)));
            expect(almostEqual(full_quarter * p, dvec4(-1.0, 0.0, 0.0, 1.0)));
        };
    };

    feature("Individual transformations are applied in sequence") = [] {
        auto p1 = dvec4(1, 0, 1, 1);
        auto p2 = dvec4(15, 0, 7, 1);
        auto a = dmat4::rotateX(std::numbers::pi / 2.0f);
        auto b = dmat4::scale(5, 5, 5);
        auto c = dmat4::translate(10, 5, 7);
        auto p11 = a * p1;
        expect(almostEqual(p11, dvec4(1, -1, 0, 1)));
        auto p12 = b * p11;
        expect(almostEqual(p12, dvec4(5, -5, 0, 1)));
        auto p13 = c * p12;
        expect(almostEqual(p13, p2));
        auto t = c * b * a;
        expect(almostEqual(t * p1, p2));
    };
}
