#pragma once

#include "Vec3.h"
#include "Mat4x4.h"

#include <cstddef>
#include <cmath>

namespace Math
{
    // ============================================================
    // DOT PRODUCT - VERSION DE REFERENCE
    // ============================================================

    inline void DotBatchReference(
        const Vec3* a,
        const Vec3* b,
        float* results,
        std::size_t count)
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            const float ax = a[i].x();
            const float ay = a[i].y();
            const float az = a[i].z();

            const float bx = b[i].x();
            const float by = b[i].y();
            const float bz = b[i].z();

            results[i] =
                ax * bx +
                ay * by +
                az * bz;
        }
    }


    // ============================================================
    // NORMALISATION - VERSION DE REFERENCE
    // ============================================================

    inline void NormalizeBatchReference(
        const Vec3* input,
        Vec3* results,
        std::size_t count)
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            const float x = input[i].x();
            const float y = input[i].y();
            const float z = input[i].z();

            const float lengthSquared =
                x * x +
                y * y +
                z * z;

            if (lengthSquared <= 0.0f)
            {
                results[i] = Vec3();
                continue;
            }

            const float length = std::sqrt(lengthSquared);

            results[i] = Vec3(
                x / length,
                y / length,
                z / length
            );
        }
    }


    // ============================================================
    // TRANSFORMATION DE POINTS - VERSION DE REFERENCE
    // ============================================================

    inline void TransformPointsBatchReference(
        const Vec3* input,
        Vec3* results,
        std::size_t count,
        const Mat4x4& matrix)
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            const float x = input[i].x();
            const float y = input[i].y();
            const float z = input[i].z();

            const float resultX =
                matrix.m[0][0] * x +
                matrix.m[0][1] * y +
                matrix.m[0][2] * z +
                matrix.m[0][3];

            const float resultY =
                matrix.m[1][0] * x +
                matrix.m[1][1] * y +
                matrix.m[1][2] * z +
                matrix.m[1][3];

            const float resultZ =
                matrix.m[2][0] * x +
                matrix.m[2][1] * y +
                matrix.m[2][2] * z +
                matrix.m[2][3];

            results[i] = Vec3(
                resultX,
                resultY,
                resultZ
            );
        }
    }
}