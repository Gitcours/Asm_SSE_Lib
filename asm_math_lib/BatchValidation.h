#pragma once

#include "Vec3.h"
#include "Mat4x4.h"
#include "Batch.h"
#include "BatchSIMD.h"

#include <cstddef>
#include <cmath>
#include <vector>

namespace Math
{
    // ============================================================
    // COMPARAISON FLOTTANTE
    // ============================================================

    inline bool NearlyEqual(
        float a,
        float b,
        float absoluteTolerance = 1e-4f,
        float relativeTolerance = 1e-4f)
    {
        const float difference = std::fabs(a - b);

        if (difference <= absoluteTolerance)
        {
            return true;
        }

        const float largest =
            (std::fabs(a) > std::fabs(b))
            ? std::fabs(a)
            : std::fabs(b);

        return difference <= largest * relativeTolerance;
    }


    // ============================================================
    // COMPARAISON DE DEUX VEC3
    // ============================================================

    inline bool Vec3NearlyEqual(
        const Vec3& a,
        const Vec3& b,
        float absoluteTolerance = 1e-4f,
        float relativeTolerance = 1e-4f)
    {
        return
            NearlyEqual(a.x(), b.x(), absoluteTolerance, relativeTolerance) &&
            NearlyEqual(a.y(), b.y(), absoluteTolerance, relativeTolerance) &&
            NearlyEqual(a.z(), b.z(), absoluteTolerance, relativeTolerance);
    }


    // ============================================================
    // VALIDATION DOT
    // ============================================================

    inline bool ValidateDotBatch(
        const Vec3* a,
        const Vec3* b,
        std::size_t count,
        float absoluteTolerance = 1e-4f,
        float relativeTolerance = 1e-4f)
    {
        if (count == 0)
        {
            DotBatchReference(
                nullptr,
                nullptr,
                nullptr,
                0
            );

            DotBatchSIMD(
                nullptr,
                nullptr,
                nullptr,
                0
            );

            return true;
        }

        std::vector<float> reference(count);
        std::vector<float> simd(count);

        DotBatchReference(
            a,
            b,
            reference.data(),
            count
        );

        DotBatchSIMD(
            a,
            b,
            simd.data(),
            count
        );

        for (std::size_t i = 0; i < count; ++i)
        {
            if (!NearlyEqual(
                reference[i],
                simd[i],
                absoluteTolerance,
                relativeTolerance))
            {
                return false;
            }
        }

        return true;
    }


    // ============================================================
    // VALIDATION NORMALISATION
    // ============================================================

    inline bool ValidateNormalizeBatch(
        const Vec3* input,
        std::size_t count,
        float absoluteTolerance = 1e-4f,
        float relativeTolerance = 1e-4f)
    {
        if (count == 0)
        {
            NormalizeBatchReference(
                nullptr,
                nullptr,
                0
            );

            NormalizeBatchSIMD(
                nullptr,
                nullptr,
                0
            );

            return true;
        }

        std::vector<Vec3> reference(count);
        std::vector<Vec3> simd(count);

        NormalizeBatchReference(
            input,
            reference.data(),
            count
        );

        NormalizeBatchSIMD(
            input,
            simd.data(),
            count
        );

        for (std::size_t i = 0; i < count; ++i)
        {
            if (!Vec3NearlyEqual(
                reference[i],
                simd[i],
                absoluteTolerance,
                relativeTolerance))
            {
                return false;
            }
        }

        return true;
    }


    // ============================================================
    // VALIDATION TRANSFORMATION
    // ============================================================

    inline bool ValidateTransformPointsBatch(
        const Vec3* input,
        std::size_t count,
        const Mat4x4& matrix,
        float absoluteTolerance = 1e-4f,
        float relativeTolerance = 1e-4f)
    {
        if (count == 0)
        {
            TransformPointsBatchReference(
                nullptr,
                nullptr,
                0,
                matrix
            );

            TransformPointsBatchSIMD(
                nullptr,
                nullptr,
                0,
                matrix
            );

            return true;
        }

        std::vector<Vec3> reference(count);
        std::vector<Vec3> simd(count);

        TransformPointsBatchReference(
            input,
            reference.data(),
            count,
            matrix
        );

        TransformPointsBatchSIMD(
            input,
            simd.data(),
            count,
            matrix
        );

        for (std::size_t i = 0; i < count; ++i)
        {
            if (!Vec3NearlyEqual(
                reference[i],
                simd[i],
                absoluteTolerance,
                relativeTolerance))
            {
                return false;
            }
        }

        return true;
    }
}