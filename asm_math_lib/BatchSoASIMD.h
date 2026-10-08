#pragma once

#include "BatchSoA.h"

#include <xmmintrin.h>
#include <cstddef>

namespace Math
{
    // ============================================================
    // DOT PRODUCT SoA - VERSION SIMD SSE
    // ============================================================
    //
    // Avec SoA, les données sont déjà organisées comme :
    //
    // X = [x0,x1,x2,x3]
    // Y = [y0,y1,y2,y3]
    // Z = [z0,z1,z2,z3]
    //
    // On peut donc charger directement 4 valeurs avec SSE.
    // ============================================================

    inline void DotBatchSoASIMD(
        const Vec3SoA& a,
        const Vec3SoA& b,
        float* results,
        std::size_t count)
    {
        std::size_t i = 0;

        // --------------------------------------------------------
        // 4 éléments simultanément
        // --------------------------------------------------------

        for (; i + 4 <= count; i += 4)
        {
            __m128 ax = _mm_loadu_ps(&a.x[i]);
            __m128 ay = _mm_loadu_ps(&a.y[i]);
            __m128 az = _mm_loadu_ps(&a.z[i]);

            __m128 bx = _mm_loadu_ps(&b.x[i]);
            __m128 by = _mm_loadu_ps(&b.y[i]);
            __m128 bz = _mm_loadu_ps(&b.z[i]);

            __m128 result = _mm_mul_ps(ax, bx);

            result = _mm_add_ps(
                result,
                _mm_mul_ps(ay, by)
            );

            result = _mm_add_ps(
                result,
                _mm_mul_ps(az, bz)
            );

            _mm_storeu_ps(
                &results[i],
                result
            );
        }

        // --------------------------------------------------------
        // Reste
        // --------------------------------------------------------

        for (; i < count; ++i)
        {
            results[i] =
                a.x[i] * b.x[i] +
                a.y[i] * b.y[i] +
                a.z[i] * b.z[i];
        }
    }
}