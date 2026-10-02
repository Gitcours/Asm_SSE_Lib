#pragma once
#ifndef VEC4_SSE_H
#define VEC4_SSE_H

#include <xmmintrin.h>

class alignas(16) Vec4
{
public:
    __m128 v;

    // Constructeurs

    Vec4() : v(_mm_setzero_ps()) {}

    Vec4(float x, float y, float z, float w)
        : v(_mm_set_ps(w, z, y, x)) {
    }

    explicit Vec4(__m128 valeur)
        : v(valeur) {
    }

    // Accès

    float x() const
    {
        return _mm_cvtss_f32(v);
    }

    float y() const
    {
        return _mm_cvtss_f32(
            _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1))
        );
    }

    float z() const
    {
        return _mm_cvtss_f32(
            _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2))
        );
    }

    float w() const
    {
        return _mm_cvtss_f32(
            _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3))
        );
    }

    // Chargement / stockage

    static Vec4 load(const float* p)
    {
        return Vec4(
            _mm_set_ps(
                p[3],
                p[2],
                p[1],
                p[0]
            )
        );
    }

    void store(float* p) const
    {
        _mm_store_ps(p, v);
    }

    // Opérateurs

    Vec4 operator+(const Vec4& rhs) const
    {
        return Vec4(_mm_add_ps(v, rhs.v));
    }

    Vec4 operator-(const Vec4& rhs) const
    {
        return Vec4(_mm_sub_ps(v, rhs.v));
    }

    Vec4 operator-() const
    {
        return Vec4(
            _mm_sub_ps(
                _mm_setzero_ps(),
                v
            )
        );
    }

    Vec4 operator*(float s) const
    {
        return Vec4(
            _mm_mul_ps(
                v,
                _mm_set1_ps(s)
            )
        );
    }

    Vec4 operator/(float s) const
    {
        return Vec4(
            _mm_div_ps(
                v,
                _mm_set1_ps(s)
            )
        );
    }

    Vec4& operator+=(const Vec4& rhs)
    {
        v = _mm_add_ps(v, rhs.v);
        return *this;
    }

    Vec4& operator-=(const Vec4& rhs)
    {
        v = _mm_sub_ps(v, rhs.v);
        return *this;
    }

    Vec4& operator*=(float s)
    {
        v = _mm_mul_ps(
            v,
            _mm_set1_ps(s)
        );

        return *this;
    }

    Vec4& operator/=(float s)
    {
        v = _mm_div_ps(
            v,
            _mm_set1_ps(s)
        );

        return *this;
    }

    friend Vec4 operator*(float s, const Vec4& a)
    {
        return a * s;
    }

    // Produit scalaire

    float dot(const Vec4& rhs) const
    {
        __m128 mul = _mm_mul_ps(v, rhs.v);

        // x + y + z + w
        __m128 shuf = _mm_movehdup_ps(mul);
        __m128 sums = _mm_add_ps(mul, shuf);

        shuf = _mm_movehl_ps(shuf, sums);
        sums = _mm_add_ss(sums, shuf);

        return _mm_cvtss_f32(sums);
    }

    // Longueur

    float lengthSquared() const
    {
        return dot(*this);
    }

    float length() const
    {
        return _mm_cvtss_f32(
            _mm_sqrt_ss(
                _mm_set_ss(lengthSquared())
            )
        );
    }

    // Normalisation

    Vec4 normalized() const
    {
        float lenSq = lengthSquared();

        if (lenSq <= 0.0f)
            return Vec4();

        __m128 lenSq4 = _mm_set1_ps(lenSq);
        __m128 invLen = _mm_rsqrt_ps(lenSq4);

        // Une itération de Newton-Raphson
        const __m128 half = _mm_set1_ps(0.5f);
        const __m128 three = _mm_set1_ps(3.0f);

        invLen = _mm_mul_ps(
            invLen,
            _mm_mul_ps(
                half,
                _mm_sub_ps(
                    three,
                    _mm_mul_ps(
                        lenSq4,
                        _mm_mul_ps(
                            invLen,
                            invLen
                        )
                    )
                )
            )
        );

        return Vec4(
            _mm_mul_ps(v, invLen)
        );
    }

    void normalize()
    {
        *this = normalized();
    }

    // Distance

    float distanceSquared(const Vec4& rhs) const
    {
        return (*this - rhs).lengthSquared();
    }

    float distance(const Vec4& rhs) const
    {
        return (*this - rhs).length();
    }

    // Min / Max

    static Vec4 min(const Vec4& a, const Vec4& b)
    {
        return Vec4(
            _mm_min_ps(a.v, b.v)
        );
    }

    static Vec4 max(const Vec4& a, const Vec4& b)
    {
        return Vec4(
            _mm_max_ps(a.v, b.v)
        );
    }

    // Abs

    Vec4 abs() const
    {
        const __m128 signMask =
            _mm_set1_ps(-0.0f);

        return Vec4(
            _mm_andnot_ps(signMask, v)
        );
    }

    // Lerp

    static Vec4 lerp(
        const Vec4& a,
        const Vec4& b,
        float t
    )
    {
        __m128 t4 = _mm_set1_ps(t);

        return Vec4(
            _mm_add_ps(
                a.v,
                _mm_mul_ps(
                    _mm_sub_ps(b.v, a.v),
                    t4
                )
            )
        );
    }
};

#endif // VEC4_SSE_H
