#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <cstddef>
#include <cmath>

#include "Vec3.h"
#include "Mat4x4.h"
#include "Batch.h"
#include "BatchSIMD.h"
#include "BatchSoA.h"
#include "BatchSoASIMD.h"
#include "DotVec3ASM.h"

using ankerl::nanobench::Bench;


// ============================================================
// TAILLES DE BATCH
// ============================================================

static constexpr std::size_t SIZES[] =
{
    64,
    256,
    1024,
    4096,
    16384,
    65536
};


// ============================================================
// DONNEES DE TEST
// ============================================================

struct BenchmarkData
{
    std::vector<Vec3> a;
    std::vector<Vec3> b;

    std::vector<Vec3> outputVec3;
    std::vector<float> outputFloat;

    Math::Vec3SoA soaA;
    Math::Vec3SoA soaB;
};


// ============================================================
// CREATION DES DONNEES
// ============================================================

BenchmarkData CreateData(std::size_t count)
{
    BenchmarkData data;

    // Allocation/préparation hors benchmark
    data.a.resize(count);
    data.b.resize(count);
    data.outputVec3.resize(count);
    data.outputFloat.resize(count);

    data.soaA.resize(count);
    data.soaB.resize(count);


    // Générateur déterministe
    std::mt19937 generator(12345);

    std::uniform_real_distribution<float> distribution(
        -100.0f,
        100.0f
    );


    // Création des vecteurs
    for (std::size_t i = 0; i < count; ++i)
    {
        data.a[i] = Vec3(
            distribution(generator),
            distribution(generator),
            distribution(generator)
        );

        data.b[i] = Vec3(
            distribution(generator),
            distribution(generator),
            distribution(generator)
        );
    }


    // --------------------------------------------------------
    // Préparation SoA hors benchmark
    // --------------------------------------------------------

    Math::ConvertAoSToSoA(
        data.a.data(),
        data.soaA,
        count
    );

    Math::ConvertAoSToSoA(
        data.b.data(),
        data.soaB,
        count
    );


    return data;
}


// ============================================================
// VALIDATION ASM
// ============================================================

bool NearlyEqualASM(
    float actual,
    float expected,
    float tolerance = 1e-5f)
{
    return std::fabs(actual - expected) <= tolerance;
}


// ============================================================
// TEST AUTOMATIQUE DE L'ASM
// ============================================================

bool ValidateDotVec3ASM()
{
    bool allTestsPassed = true;


    std::cout << "\n";
    std::cout << "============================================\n";
    std::cout << "VALIDATION DOT VEC3 ASM\n";
    std::cout << "============================================\n";


    // --------------------------------------------------------
    // TEST 1 : valeurs positives
    // --------------------------------------------------------

    {
        Vec3 a(
            1.0f,
            2.0f,
            3.0f
        );

        Vec3 b(
            4.0f,
            5.0f,
            6.0f
        );

        const float expected = 32.0f;
        const float actual = DotVec3ASM(a, b);

        const bool passed =
            NearlyEqualASM(
                actual,
                expected
            );

        std::cout
            << "["
            << (passed ? "PASS" : "FAIL")
            << "] ";

        std::cout
            << "Valeurs positives : "
            << actual
            << " (attendu "
            << expected
            << ")\n";


        if (!passed)
        {
            allTestsPassed = false;
        }
    }


    // --------------------------------------------------------
    // TEST 2 : valeurs négatives
    // --------------------------------------------------------

    {
        Vec3 a(
            -1.0f,
            2.0f,
            -3.0f
        );

        Vec3 b(
            4.0f,
            -5.0f,
            6.0f
        );

        const float expected = -32.0f;
        const float actual = DotVec3ASM(a, b);

        const bool passed =
            NearlyEqualASM(
                actual,
                expected
            );

        std::cout
            << "["
            << (passed ? "PASS" : "FAIL")
            << "] ";

        std::cout
            << "Valeurs negatives : "
            << actual
            << " (attendu "
            << expected
            << ")\n";


        if (!passed)
        {
            allTestsPassed = false;
        }
    }


    // --------------------------------------------------------
    // TEST 3 : vecteur nul
    // --------------------------------------------------------

    {
        Vec3 a(
            0.0f,
            0.0f,
            0.0f
        );

        Vec3 b(
            10.0f,
            20.0f,
            30.0f
        );

        const float expected = 0.0f;
        const float actual = DotVec3ASM(a, b);

        const bool passed =
            NearlyEqualASM(
                actual,
                expected
            );

        std::cout
            << "["
            << (passed ? "PASS" : "FAIL")
            << "] ";

        std::cout
            << "Vecteur nul : "
            << actual
            << " (attendu "
            << expected
            << ")\n";


        if (!passed)
        {
            allTestsPassed = false;
        }
    }


    // --------------------------------------------------------
    // TEST 4 : valeurs décimales
    // --------------------------------------------------------

    {
        Vec3 a(
            1.5f,
            -2.25f,
            3.5f
        );

        Vec3 b(
            -2.0f,
            4.0f,
            0.5f
        );

        const float expected = -10.25f;
        const float actual = DotVec3ASM(a, b);

        const bool passed =
            NearlyEqualASM(
                actual,
                expected
            );

        std::cout
            << "["
            << (passed ? "PASS" : "FAIL")
            << "] ";

        std::cout
            << "Valeurs decimales : "
            << actual
            << " (attendu "
            << expected
            << ")\n";


        if (!passed)
        {
            allTestsPassed = false;
        }
    }


    // --------------------------------------------------------
    // RESULTAT GLOBAL
    // --------------------------------------------------------

    std::cout << "\n";

    if (allTestsPassed)
    {
        std::cout
            << "RESULTAT GLOBAL : PASS\n";
    }
    else
    {
        std::cout
            << "RESULTAT GLOBAL : FAIL\n";
    }


    return allTestsPassed;
}


// ============================================================
// DOT - AoS REFERENCE
// ============================================================

void BenchmarkDotReference(
    Bench& bench,
    BenchmarkData& data)
{
    bench.run(
        "Dot / AoS / Reference",
        [&]
        {
            Math::DotBatchReference(
                data.a.data(),
                data.b.data(),
                data.outputFloat.data(),
                data.a.size()
            );

            ankerl::nanobench::doNotOptimizeAway(
                data.outputFloat[0]
            );
        }
    );
}


// ============================================================
// DOT - AoS SIMD
// ============================================================

void BenchmarkDotSIMD(
    Bench& bench,
    BenchmarkData& data)
{
    bench.run(
        "Dot / AoS / SIMD",
        [&]
        {
            Math::DotBatchSIMD(
                data.a.data(),
                data.b.data(),
                data.outputFloat.data(),
                data.a.size()
            );

            ankerl::nanobench::doNotOptimizeAway(
                data.outputFloat[0]
            );
        }
    );
}


// ============================================================
// DOT - ASM
// ============================================================
//
// La fonction ASM calcule un seul produit scalaire.
//
// On l'appelle donc pour chaque paire de Vec3 du batch.
//
// Les allocations sont réalisées avant le benchmark.
// ============================================================

void BenchmarkDotASM(
    Bench& bench,
    BenchmarkData& data)
{
    bench.run(
        "Dot / ASM",
        [&]
        {
            for (std::size_t i = 0; i < data.a.size(); ++i)
            {
                data.outputFloat[i] =
                    DotVec3ASM(
                        data.a[i],
                        data.b[i]
                    );
            }

            ankerl::nanobench::doNotOptimizeAway(
                data.outputFloat[0]
            );
        }
    );
}


// ============================================================
// DOT - SoA REFERENCE
// ============================================================

void BenchmarkDotSoAReference(
    Bench& bench,
    BenchmarkData& data)
{
    bench.run(
        "Dot / SoA / Reference",
        [&]
        {
            Math::DotBatchSoAReference(
                data.soaA,
                data.soaB,
                data.outputFloat.data(),
                data.a.size()
            );

            ankerl::nanobench::doNotOptimizeAway(
                data.outputFloat[0]
            );
        }
    );
}


// ============================================================
// DOT - SoA SIMD
// ============================================================

void BenchmarkDotSoASIMD(
    Bench& bench,
    BenchmarkData& data)
{
    bench.run(
        "Dot / SoA / SIMD",
        [&]
        {
            Math::DotBatchSoASIMD(
                data.soaA,
                data.soaB,
                data.outputFloat.data(),
                data.a.size()
            );

            ankerl::nanobench::doNotOptimizeAway(
                data.outputFloat[0]
            );
        }
    );
}


// ============================================================
// NORMALIZE - REFERENCE
// ============================================================

void BenchmarkNormalizeReference(
    Bench& bench,
    BenchmarkData& data)
{
    bench.run(
        "Normalize / Reference",
        [&]
        {
            Math::NormalizeBatchReference(
                data.a.data(),
                data.outputVec3.data(),
                data.a.size()
            );

            ankerl::nanobench::doNotOptimizeAway(
                data.outputVec3[0]
            );
        }
    );
}


// ============================================================
// NORMALIZE - SIMD
// ============================================================

void BenchmarkNormalizeSIMD(
    Bench& bench,
    BenchmarkData& data)
{
    bench.run(
        "Normalize / SIMD",
        [&]
        {
            Math::NormalizeBatchSIMD(
                data.a.data(),
                data.outputVec3.data(),
                data.a.size()
            );

            ankerl::nanobench::doNotOptimizeAway(
                data.outputVec3[0]
            );
        }
    );
}


// ============================================================
// TRANSFORM - REFERENCE
// ============================================================

void BenchmarkTransformReference(
    Bench& bench,
    BenchmarkData& data,
    const Mat4x4& matrix)
{
    bench.run(
        "Transform / Reference",
        [&]
        {
            Math::TransformPointsBatchReference(
                data.a.data(),
                data.outputVec3.data(),
                data.a.size(),
                matrix
            );

            ankerl::nanobench::doNotOptimizeAway(
                data.outputVec3[0]
            );
        }
    );
}


// ============================================================
// TRANSFORM - SIMD
// ============================================================

void BenchmarkTransformSIMD(
    Bench& bench,
    BenchmarkData& data,
    const Mat4x4& matrix)
{
    bench.run(
        "Transform / SIMD",
        [&]
        {
            Math::TransformPointsBatchSIMD(
                data.a.data(),
                data.outputVec3.data(),
                data.a.size(),
                matrix
            );

            ankerl::nanobench::doNotOptimizeAway(
                data.outputVec3[0]
            );
        }
    );
}


// ============================================================
// CONVERSION AoS -> SoA
// ============================================================

void BenchmarkAoSToSoA(
    Bench& bench,
    BenchmarkData& data)
{
    bench.run(
        "Conversion / AoS -> SoA",
        [&]
        {
            Math::ConvertAoSToSoA_NoAlloc(
                data.a.data(),
                data.soaA,
                data.a.size()
            );

            ankerl::nanobench::doNotOptimizeAway(
                data.soaA.x[0]
            );
        }
    );
}


// ============================================================
// CONVERSION SoA -> AoS
// ============================================================

void BenchmarkSoAToAoS(
    Bench& bench,
    BenchmarkData& data)
{
    bench.run(
        "Conversion / SoA -> AoS",
        [&]
        {
            Math::ConvertSoAToAoS(
                data.soaA,
                data.outputVec3.data(),
                data.a.size()
            );

            ankerl::nanobench::doNotOptimizeAway(
                data.outputVec3[0]
            );
        }
    );
}


// ============================================================
// DOT
// ============================================================

void RunDotBenchmark(std::size_t count)
{
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "DOT - " << count << " elements\n";
    std::cout << "========================================\n\n";


    BenchmarkData data = CreateData(count);


    Bench bench;

    bench.title(
        "Dot - Batch size " + std::to_string(count)
    );

    bench.warmup(3);
    bench.minEpochIterations(1200);


    BenchmarkDotReference(
        bench,
        data
    );

    BenchmarkDotSIMD(
        bench,
        data
    );

    BenchmarkDotASM(
        bench,
        data
    );

    BenchmarkDotSoAReference(
        bench,
        data
    );

    BenchmarkDotSoASIMD(
        bench,
        data
    );


    std::cout << "\n--- Conversions ---\n\n";


    BenchmarkAoSToSoA(
        bench,
        data
    );

    BenchmarkSoAToAoS(
        bench,
        data
    );
}


// ============================================================
// NORMALIZE
// ============================================================

void RunNormalizeBenchmark(std::size_t count)
{
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "NORMALIZE - " << count << " elements\n";
    std::cout << "========================================\n\n";


    BenchmarkData data = CreateData(count);


    Bench bench;

    bench.title(
        "Normalize - Batch size " + std::to_string(count)
    );

    bench.warmup(3);
    bench.minEpochIterations(1200);


    BenchmarkNormalizeReference(
        bench,
        data
    );

    BenchmarkNormalizeSIMD(
        bench,
        data
    );
}


// ============================================================
// TRANSFORM
// ============================================================

void RunTransformBenchmark(std::size_t count)
{
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "TRANSFORM - " << count << " elements\n";
    std::cout << "========================================\n\n";


    BenchmarkData data = CreateData(count);


    Mat4x4 matrix =
        Mat4x4::Translation(
            10.0f,
            20.0f,
            30.0f
        );


    Bench bench;

    bench.title(
        "Transform - Batch size " + std::to_string(count)
    );

    bench.warmup(3);
    bench.minEpochIterations(1200);


    BenchmarkTransformReference(
        bench,
        data,
        matrix
    );

    BenchmarkTransformSIMD(
        bench,
        data,
        matrix
    );
}


// ============================================================
// SELECTION DE LA TAILLE
// ============================================================

std::size_t SelectBatchSize()
{
    std::cout << "\n";
    std::cout << "Choisissez la taille du batch :\n\n";


    for (
        std::size_t i = 0;
        i < sizeof(SIZES) / sizeof(SIZES[0]);
        ++i
        )
    {
        std::cout
            << (i + 1)
            << ". "
            << SIZES[i]
            << " elements\n";
    }


    std::cout << "\nChoix : ";


    int choice;
    std::cin >> choice;


    if (
        choice < 1 ||
        choice > static_cast<int>(
            sizeof(SIZES) / sizeof(SIZES[0])
            )
        )
    {
        return 1024;
    }


    return SIZES[choice - 1];
}


// ============================================================
// MAIN
// ============================================================

int main()
{
    std::cout
        << "============================================\n";

    std::cout
        << "      SIMD / ASM MATH LIBRARY BENCHMARK\n";

    std::cout
        << "============================================\n";


    std::cout
        << "\nConfiguration : Release x64 recommandee\n";

    std::cout
        << "Donnees : deterministes\n";

    std::cout
        << "Warm-up : 3\n";

    std::cout
        << "Iterations minimales : 1200\n";


    // ========================================================
    // VALIDATION ASM
    // ========================================================

    const bool asmTestsPassed =
        ValidateDotVec3ASM();


    if (!asmTestsPassed)
    {
        std::cout
            << "\n";

        std::cout
            << "ERREUR : les tests ASM ont echoue.\n";

        std::cout
            << "Les benchmarks ne seront pas lances.\n";

        return 1;
    }


    std::cout
        << "\nTous les tests ASM sont valides.\n";


    // ========================================================
    // MENU PRINCIPAL
    // ========================================================

    while (true)
    {
        std::cout
            << "\n";

        std::cout
            << "============================================\n";

        std::cout
            << "MENU\n";

        std::cout
            << "============================================\n";

        std::cout
            << "1. Dot\n";

        std::cout
            << "2. Normalize\n";

        std::cout
            << "3. Transform\n";

        std::cout
            << "4. Tout lancer pour une taille\n";

        std::cout
            << "0. Quitter\n";

        std::cout
            << "\nChoix : ";


        int choice;
        std::cin >> choice;


        if (choice == 0)
        {
            break;
        }


        std::size_t count =
            SelectBatchSize();


        switch (choice)
        {
        case 1:

            RunDotBenchmark(
                count
            );

            break;


        case 2:

            RunNormalizeBenchmark(
                count
            );

            break;


        case 3:

            RunTransformBenchmark(
                count
            );

            break;


        case 4:

            RunDotBenchmark(
                count
            );

            RunNormalizeBenchmark(
                count
            );

            RunTransformBenchmark(
                count
            );

            break;


        default:

            std::cout
                << "\nChoix invalide.\n";

            break;
        }
    }


    return 0;
}