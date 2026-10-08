#include <iostream>
#include "nanobench.h"

#include "Vec4.h"
#include "Vec3.h"
#include "Mat4x4.h"

ankerl::nanobench::Bench bench;

void BenchVec3()
{
    // Données de test

    Vec3 a(25.0f, 48.0f, 15.0f);
    Vec3 b(84.0f, 14.0f, 96.0f);

    float data[3] = { 25.0f, 48.0f, 15.0f };
    float output[3] = {};

    float scalar = 5.0f;
    float t = 0.35f;
    
    // Constructeurs

    bench.run("Constructeur Vec3()", [&] {
        Vec3 c;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("Constructeur Vec3(x, y, z)", [&] {
        Vec3 c(25.0f, 48.0f, 15.0f);
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("Constructeur Vec3(__m128)", [&] {
        __m128 value = _mm_set_ps(0.0f, 15.0f, 48.0f, 25.0f);
        Vec3 c(value);
        ankerl::nanobench::doNotOptimizeAway(c);
        });
    
    // Accès

    bench.run("x()", [&] {
        float x = a.x();
        ankerl::nanobench::doNotOptimizeAway(x);
        });

    bench.run("y()", [&] {
        float y = a.y();
        ankerl::nanobench::doNotOptimizeAway(y);
        });

    bench.run("z()", [&] {
        float z = a.z();
        ankerl::nanobench::doNotOptimizeAway(z);
        });
    
    // Chargement / stockage

    bench.run("load()", [&] {
        Vec3 c = Vec3::load(data);
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("store()", [&] {
        a.store(output);
        ankerl::nanobench::doNotOptimizeAway(output);
        });
    
    // Opérateurs

    bench.run("operator+", [&] {
        Vec3 c = a + b;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator-", [&] {
        Vec3 c = a - b;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator- unaire", [&] {
        Vec3 c = -a;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator* (Vec3 * float)", [&] {
        Vec3 c = a * scalar;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator/ (Vec3 / float)", [&] {
        Vec3 c = a / scalar;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator* (float * Vec3)", [&] {
        Vec3 c = scalar * a;
        ankerl::nanobench::doNotOptimizeAway(c);
        });
    
    // Opérateurs += -= *= /=

    bench.run("operator+=", [&] {
        Vec3 c = a;
        c += b;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator-=", [&] {
        Vec3 c = a;
        c -= b;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator*=", [&] {
        Vec3 c = a;
        c *= scalar;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator/=", [&] {
        Vec3 c = a;
        c /= scalar;
        ankerl::nanobench::doNotOptimizeAway(c);
        });
    
    // Produit scalaire

    bench.run("dot()", [&] {
        float result = a.dot(b);
        ankerl::nanobench::doNotOptimizeAway(result);
        });
    
    // Produit vectoriel

    bench.run("cross()", [&] {
        Vec3 c = a.cross(b);
        ankerl::nanobench::doNotOptimizeAway(c);
        });
    
    // Longueur

    bench.run("lengthSquared()", [&] {
        float result = a.lengthSquared();
        ankerl::nanobench::doNotOptimizeAway(result);
        });

    bench.run("length()", [&] {
        float result = a.length();
        ankerl::nanobench::doNotOptimizeAway(result);
        });
    
    // Normalisation

    bench.run("normalized()", [&] {
        Vec3 c = a.normalized();
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("normalize()", [&] {
        Vec3 c = a;
        c.normalize();
        ankerl::nanobench::doNotOptimizeAway(c);
        });
    
    // Distance

    bench.run("distanceSquared()", [&] {
        float result = a.distanceSquared(b);
        ankerl::nanobench::doNotOptimizeAway(result);
        });

    bench.run("distance()", [&] {
        float result = a.distance(b);
        ankerl::nanobench::doNotOptimizeAway(result);
        });
    
    // Min / Max

    bench.run("min()", [&] {
        Vec3 c = Vec3::min(a, b);
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("max()", [&] {
        Vec3 c = Vec3::max(a, b);
        ankerl::nanobench::doNotOptimizeAway(c);
        });
    
    // Abs

    bench.run("abs()", [&] {
        Vec3 c = (-a).abs();
        ankerl::nanobench::doNotOptimizeAway(c);
        });
    
    // Lerp

    bench.run("lerp()", [&] {
        Vec3 c = Vec3::lerp(a, b, t);
        ankerl::nanobench::doNotOptimizeAway(c);
        });
}

void BenchVec4()
{
    // Données de test

    Vec4 a(25.0f, 48.0f, 15.0f, 56.0f);
    Vec4 b(84.0f, 14.0f, 96.0f, 98.0f);

    alignas(16) float data[4] = {
        25.0f, 48.0f, 15.0f, 56.0f
    };

    alignas(16) float output[4] = {};

    float scalar = 5.0f;
    float t = 0.35f;

    // Constructeurs

    bench.run("Constructeur Vec4()", [&] {
        Vec4 c;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("Constructeur Vec4(x, y, z, w)", [&] {
        Vec4 c(25.0f, 48.0f, 15.0f, 56.0f);
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("Constructeur Vec4(__m128)", [&] {
        __m128 value = _mm_set_ps(56.0f, 15.0f, 48.0f, 25.0f);
        Vec4 c(value);
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    // Accès

    bench.run("x()", [&] {
        float x = a.x();
        ankerl::nanobench::doNotOptimizeAway(x);
        });

    bench.run("y()", [&] {
        float y = a.y();
        ankerl::nanobench::doNotOptimizeAway(y);
        });

    bench.run("z()", [&] {
        float z = a.z();
        ankerl::nanobench::doNotOptimizeAway(z);
        });

    bench.run("w()", [&] {
        float w = a.w();
        ankerl::nanobench::doNotOptimizeAway(w);
        });

    // Chargement / stockage

    bench.run("load()", [&] {
        Vec4 c = Vec4::load(data);
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("store()", [&] {
        a.store(output);
        ankerl::nanobench::doNotOptimizeAway(output);
        });

    // Opérateurs

    bench.run("operator+", [&] {
        Vec4 c = a + b;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator-", [&] {
        Vec4 c = a - b;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator- unaire", [&] {
        Vec4 c = -a;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator* (Vec4 * float)", [&] {
        Vec4 c = a * scalar;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator/ (Vec4 / float)", [&] {
        Vec4 c = a / scalar;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator* (float * Vec4)", [&] {
        Vec4 c = scalar * a;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    // Opérateurs += -= *= /=

    bench.run("operator+=", [&] {
        Vec4 c = a;
        c += b;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator-=", [&] {
        Vec4 c = a;
        c -= b;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator*=", [&] {
        Vec4 c = a;
        c *= scalar;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("operator/=", [&] {
        Vec4 c = a;
        c /= scalar;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    // Produit scalaire

    bench.run("dot()", [&] {
        float result = a.dot(b);
        ankerl::nanobench::doNotOptimizeAway(result);
        });

    // Longueur

    bench.run("lengthSquared()", [&] {
        float result = a.lengthSquared();
        ankerl::nanobench::doNotOptimizeAway(result);
        });

    bench.run("length()", [&] {
        float result = a.length();
        ankerl::nanobench::doNotOptimizeAway(result);
        });

    // Normalisation

    bench.run("normalized()", [&] {
        Vec4 c = a.normalized();
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("normalize()", [&] {
        Vec4 c = a;
        c.normalize();
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    // Distance

    bench.run("distanceSquared()", [&] {
        float result = a.distanceSquared(b);
        ankerl::nanobench::doNotOptimizeAway(result);
        });

    bench.run("distance()", [&] {
        float result = a.distance(b);
        ankerl::nanobench::doNotOptimizeAway(result);
        });

    // Min / Max

    bench.run("min()", [&] {
        Vec4 c = Vec4::min(a, b);
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    bench.run("max()", [&] {
        Vec4 c = Vec4::max(a, b);
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    // Abs

    bench.run("abs()", [&] {
        Vec4 c = (-a).abs();
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    // Lerp

    bench.run("lerp()", [&] {
        Vec4 c = Vec4::lerp(a, b, t);
        ankerl::nanobench::doNotOptimizeAway(c);
        });
}

void BenchMat4x4() {
    Mat4x4 a;
    Mat4x4 b;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            a.m[i][j] = (10 + j) * j;
            b.m[i][j] = (20 + i) * i;
        }
    }
    bench.run("Translation", [&] {
        Mat4x4 c = a.Translation(15, 12, 23);
        ankerl::nanobench::doNotOptimizeAway(c);
        });
    bench.run("RotationX", [&] {
        Mat4x4 c = a.RotationX(65.6);
        ankerl::nanobench::doNotOptimizeAway(c);
        });
    bench.run("RotationY", [&] {
        Mat4x4 c = a.RotationY(58.4);
        ankerl::nanobench::doNotOptimizeAway(c);
        });
    bench.run("RotationZ", [&] {
        Mat4x4 c = a.RotationZ(42);
        ankerl::nanobench::doNotOptimizeAway(c);
        });
    bench.run("Multiplication", [&] {
        Mat4x4 c = a * b;
        ankerl::nanobench::doNotOptimizeAway(c);
        });
    bench.run("TransformPoint", [&] {
        Vec3 d(54, 14, 19);
        Vec3 c = a.TransformPoint(d);
        ankerl::nanobench::doNotOptimizeAway(c);
        });
}

int main() {
    bench.minEpochIterations(10'000'000);
    BenchVec3();
    std::cout << "\nVec4 -------------------------------------------------------\n\n";
    BenchVec4();
    std::cout << "\nMat4x4  -------------------------------------------------------\n\n";
    BenchMat4x4();

    return 0;
}