#include <iostream>
#include "nanobench.h"

#include "Vec4.h"
#include "Vec3.h"
#include "Mat4x4.h"

int main() {
    Vec3 a(25, 48, 15);
    Vec3 b(84, 14, 96);

    ankerl::nanobench::Bench bench;

    bench.run("Vec3 addition", [&] {
        Vec3 c = a + b;
        ankerl::nanobench::doNotOptimizeAway(c);
        });
    bench.run("Vec3 soustraction", [&] {
        Vec3 c = a - b;
        ankerl::nanobench::doNotOptimizeAway(c);
        });
    bench.run("Vec3 multiplication", [&] {
        Vec3 c = a * 5;
        ankerl::nanobench::doNotOptimizeAway(c);
        });

    return 0;
}