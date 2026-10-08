#pragma once

#include "Vec3.h"
#include "Mat4x4.h"

#include <xmmintrin.h>
#include <cstddef>

namespace Math
{
    // ============================================================
    // DOT PRODUCT PAR LOT - SIMD SSE
    // ============================================================

    inline void DotBatchSIMD(
        const Vec3* a,
        const Vec3* b,
        float* results,
        std::size_t count)
    {
        std::size_t i = 0;

        // Traitement de 4 Vec3 simultanément
        for (; i + 4 <= count; i += 4)
        {
            __m128 a0 = a[i].v;
            __m128 a1 = a[i + 1].v;
            __m128 a2 = a[i + 2].v;
            __m128 a3 = a[i + 3].v;

            __m128 b0 = b[i].v;
            __m128 b1 = b[i + 1].v;
            __m128 b2 = b[i + 2].v;
            __m128 b3 = b[i + 3].v;

            _MM_TRANSPOSE4_PS(a0, a1, a2, a3);
            _MM_TRANSPOSE4_PS(b0, b1, b2, b3);

            __m128 result = _mm_mul_ps(a0, b0);

            result = _mm_add_ps(
                result,
                _mm_mul_ps(a1, b1)
            );

            result = _mm_add_ps(
                result,
                _mm_mul_ps(a2, b2)
            );

            _mm_storeu_ps(
                &results[i],
                result
            );
        }

        // Gestion du reste
        for (; i < count; ++i)
        {
            const __m128 mul = _mm_mul_ps(
                a[i].v,
                b[i].v
            );

            __m128 shuf = _mm_shuffle_ps(
                mul,
                mul,
                _MM_SHUFFLE(2, 3, 2, 3)
            );

            __m128 sums = _mm_add_ps(
                mul,
                shuf
            );

            shuf = _mm_shuffle_ps(
                sums,
                sums,
                _MM_SHUFFLE(1, 1, 1, 1)
            );

            sums = _mm_add_ss(
                sums,
                shuf
            );

            results[i] = _mm_cvtss_f32(sums);
        }
    }


    // ============================================================
    // NORMALISATION PAR LOT - SIMD SSE
    // ============================================================

    inline void NormalizeBatchSIMD(
        const Vec3* input,
        Vec3* results,
        std::size_t count)
    {
        std::size_t i = 0;

        // Traitement de 4 Vec3 simultanément
        for (; i + 4 <= count; i += 4)
        {
            __m128 x0 = input[i].v;
            __m128 x1 = input[i + 1].v;
            __m128 x2 = input[i + 2].v;
            __m128 x3 = input[i + 3].v;

            _MM_TRANSPOSE4_PS(
                x0,
                x1,
                x2,
                x3
            );

            // lengthSquared = x² + y² + z²
            __m128 lengthSquared = _mm_mul_ps(
                x0,
                x0
            );

            lengthSquared = _mm_add_ps(
                lengthSquared,
                _mm_mul_ps(x1, x1)
            );

            lengthSquared = _mm_add_ps(
                lengthSquared,
                _mm_mul_ps(x2, x2)
            );

            // Détection des vecteurs nuls
            const __m128 zero = _mm_setzero_ps();

            const __m128 zeroMask = _mm_cmple_ps(
                lengthSquared,
                zero
            );

            // Approximation de 1 / sqrt(lengthSquared)
            __m128 invLength = _mm_rsqrt_ps(
                lengthSquared
            );

            const __m128 half = _mm_set1_ps(0.5f);
            const __m128 threeHalves = _mm_set1_ps(1.5f);

            // Newton-Raphson #1
            __m128 invSquared = _mm_mul_ps(
                invLength,
                invLength
            );

            __m128 correction = _mm_mul_ps(
                lengthSquared,
                invSquared
            );

            correction = _mm_mul_ps(
                correction,
                half
            );

            correction = _mm_sub_ps(
                threeHalves,
                correction
            );

            invLength = _mm_mul_ps(
                invLength,
                correction
            );

            // Newton-Raphson #2
            invSquared = _mm_mul_ps(
                invLength,
                invLength
            );

            correction = _mm_mul_ps(
                lengthSquared,
                invSquared
            );

            correction = _mm_mul_ps(
                correction,
                half
            );

            correction = _mm_sub_ps(
                threeHalves,
                correction
            );

            invLength = _mm_mul_ps(
                invLength,
                correction
            );

            // Normalisation
            __m128 resultX = _mm_mul_ps(
                x0,
                invLength
            );

            __m128 resultY = _mm_mul_ps(
                x1,
                invLength
            );

            __m128 resultZ = _mm_mul_ps(
                x2,
                invLength
            );

            // Vecteurs nuls -> (0,0,0)
            resultX = _mm_andnot_ps(
                zeroMask,
                resultX
            );

            resultY = _mm_andnot_ps(
                zeroMask,
                resultY
            );

            resultZ = _mm_andnot_ps(
                zeroMask,
                resultZ
            );

            __m128 resultW = zero;

            // Transposition inverse
            _MM_TRANSPOSE4_PS(
                resultX,
                resultY,
                resultZ,
                resultW
            );

            results[i].v = resultX;
            results[i + 1].v = resultY;
            results[i + 2].v = resultZ;
            results[i + 3].v = resultW;
        }

        // Gestion du reste
        for (; i < count; ++i)
        {
            __m128 value = input[i].v;

            __m128 squared = _mm_mul_ps(
                value,
                value
            );

            __m128 shuf = _mm_shuffle_ps(
                squared,
                squared,
                _MM_SHUFFLE(2, 3, 2, 3)
            );

            __m128 sum = _mm_add_ps(
                squared,
                shuf
            );

            shuf = _mm_shuffle_ps(
                sum,
                sum,
                _MM_SHUFFLE(1, 1, 1, 1)
            );

            sum = _mm_add_ss(
                sum,
                shuf
            );

            const float lengthSquared =
                _mm_cvtss_f32(sum);

            if (lengthSquared <= 0.0f)
            {
                results[i] = Vec3();
                continue;
            }

            __m128 invLength = _mm_rsqrt_ss(
                sum
            );

            const __m128 half = _mm_set_ss(0.5f);
            const __m128 threeHalves = _mm_set_ss(1.5f);

            // Newton-Raphson #1
            __m128 invSquared = _mm_mul_ss(
                invLength,
                invLength
            );

            __m128 correction = _mm_mul_ss(
                sum,
                invSquared
            );

            correction = _mm_mul_ss(
                correction,
                half
            );

            correction = _mm_sub_ss(
                threeHalves,
                correction
            );

            invLength = _mm_mul_ss(
                invLength,
                correction
            );

            // Newton-Raphson #2
            invSquared = _mm_mul_ss(
                invLength,
                invLength
            );

            correction = _mm_mul_ss(
                sum,
                invSquared
            );

            correction = _mm_mul_ss(
                correction,
                half
            );

            correction = _mm_sub_ss(
                threeHalves,
                correction
            );

            invLength = _mm_mul_ss(
                invLength,
                correction
            );

            const __m128 invLength4 = _mm_shuffle_ps(
                invLength,
                invLength,
                _MM_SHUFFLE(0, 0, 0, 0)
            );

            results[i].v = _mm_mul_ps(
                value,
                invLength4
            );
        }
    }


    // ============================================================
    // TRANSFORMATION DE POINTS PAR LOT - SIMD SSE
    // ============================================================
    //
    // Transforme 4 points simultanément.
    //
    // Pour chaque point :
    //
    // x' = m00*x + m01*y + m02*z + m03
    // y' = m10*x + m11*y + m12*z + m13
    // z' = m20*x + m21*y + m22*z + m23
    //
    // w = 1
    //
    // Pas de perspective divide.
    // ============================================================

    inline void TransformPointsBatchSIMD(
        const Vec3* input,
        Vec3* results,
        std::size_t count,
        const Mat4x4& matrix)
    {
        std::size_t i = 0;

        // --------------------------------------------------------
        // Constantes de la matrice
        // --------------------------------------------------------

        const __m128 m00 = _mm_set1_ps(matrix.m[0][0]);
        const __m128 m01 = _mm_set1_ps(matrix.m[0][1]);
        const __m128 m02 = _mm_set1_ps(matrix.m[0][2]);
        const __m128 m03 = _mm_set1_ps(matrix.m[0][3]);

        const __m128 m10 = _mm_set1_ps(matrix.m[1][0]);
        const __m128 m11 = _mm_set1_ps(matrix.m[1][1]);
        const __m128 m12 = _mm_set1_ps(matrix.m[1][2]);
        const __m128 m13 = _mm_set1_ps(matrix.m[1][3]);

        const __m128 m20 = _mm_set1_ps(matrix.m[2][0]);
        const __m128 m21 = _mm_set1_ps(matrix.m[2][1]);
        const __m128 m22 = _mm_set1_ps(matrix.m[2][2]);
        const __m128 m23 = _mm_set1_ps(matrix.m[2][3]);

        // --------------------------------------------------------
        // Traitement de 4 points simultanément
        // --------------------------------------------------------

        for (; i + 4 <= count; i += 4)
        {
            __m128 p0 = input[i].v;
            __m128 p1 = input[i + 1].v;
            __m128 p2 = input[i + 2].v;
            __m128 p3 = input[i + 3].v;

            // Transposition :
            //
            // p0 = [x0, x1, x2, x3]
            // p1 = [y0, y1, y2, y3]
            // p2 = [z0, z1, z2, z3]

            _MM_TRANSPOSE4_PS(
                p0,
                p1,
                p2,
                p3
            );

            // ----------------------------------------------------
            // X'
            // ----------------------------------------------------

            __m128 resultX = _mm_mul_ps(
                p0,
                m00
            );

            resultX = _mm_add_ps(
                resultX,
                _mm_mul_ps(p1, m01)
            );

            resultX = _mm_add_ps(
                resultX,
                _mm_mul_ps(p2, m02)
            );

            resultX = _mm_add_ps(
                resultX,
                m03
            );

            // ----------------------------------------------------
            // Y'
            // ----------------------------------------------------

            __m128 resultY = _mm_mul_ps(
                p0,
                m10
            );

            resultY = _mm_add_ps(
                resultY,
                _mm_mul_ps(p1, m11)
            );

            resultY = _mm_add_ps(
                resultY,
                _mm_mul_ps(p2, m12)
            );

            resultY = _mm_add_ps(
                resultY,
                m13
            );

            // ----------------------------------------------------
            // Z'
            // ----------------------------------------------------

            __m128 resultZ = _mm_mul_ps(
                p0,
                m20
            );

            resultZ = _mm_add_ps(
                resultZ,
                _mm_mul_ps(p1, m21)
            );

            resultZ = _mm_add_ps(
                resultZ,
                _mm_mul_ps(p2, m22)
            );

            resultZ = _mm_add_ps(
                resultZ,
                m23
            );

            // W = 0 dans Vec3
            __m128 resultW = _mm_setzero_ps();

            // ----------------------------------------------------
            // Retour au format :
            //
            // [x,y,z,0]
            // ----------------------------------------------------

            _MM_TRANSPOSE4_PS(
                resultX,
                resultY,
                resultZ,
                resultW
            );

            results[i].v = resultX;
            results[i + 1].v = resultY;
            results[i + 2].v = resultZ;
            results[i + 3].v = resultW;
        }

        // --------------------------------------------------------
        // Gestion du reste
        // --------------------------------------------------------

        for (; i < count; ++i)
        {
            const __m128 value = input[i].v;

            // Extraction des composantes
            const __m128 x = _mm_shuffle_ps(
                value,
                value,
                _MM_SHUFFLE(0, 0, 0, 0)
            );

            const __m128 y = _mm_shuffle_ps(
                value,
                value,
                _MM_SHUFFLE(1, 1, 1, 1)
            );

            const __m128 z = _mm_shuffle_ps(
                value,
                value,
                _MM_SHUFFLE(2, 2, 2, 2)
            );

            // X'
            __m128 resultX = _mm_mul_ps(
                x,
                m00
            );

            resultX = _mm_add_ps(
                resultX,
                _mm_mul_ps(y, m01)
            );

            resultX = _mm_add_ps(
                resultX,
                _mm_mul_ps(z, m02)
            );

            resultX = _mm_add_ps(
                resultX,
                m03
            );

            // Y'
            __m128 resultY = _mm_mul_ps(
                x,
                m10
            );

            resultY = _mm_add_ps(
                resultY,
                _mm_mul_ps(y, m11)
            );

            resultY = _mm_add_ps(
                resultY,
                _mm_mul_ps(z, m12)
            );

            resultY = _mm_add_ps(
                resultY,
                m13
            );

            // Z'
            __m128 resultZ = _mm_mul_ps(
                x,
                m20
            );

            resultZ = _mm_add_ps(
                resultZ,
                _mm_mul_ps(y, m21)
            );

            resultZ = _mm_add_ps(
                resultZ,
                _mm_mul_ps(z, m22)
            );

            resultZ = _mm_add_ps(
                resultZ,
                m23
            );

            // Reconstruction du Vec3
            const float rx = _mm_cvtss_f32(resultX);
            const float ry = _mm_cvtss_f32(resultY);
            const float rz = _mm_cvtss_f32(resultZ);

            results[i] = Vec3(
                rx,
                ry,
                rz
            );
        }
    }
}