#pragma once
#ifndef VEC3_SSE_H
#define VEC3_SSE_H

#include <xmmintrin.h>
//#include <smmintrin.h>

class alignas(16) Vec3
{
public:
    __m128 v;

    // Constructeurs

    Vec3() : v(_mm_setzero_ps()){}

    Vec3(float x, float y, float z) : v(_mm_set_ps(0.0f, z, y, x)){}

    explicit Vec3(__m128 valeur) : v(valeur){}

    // Accès

    float x() const
    {
        return _mm_cvtss_f32(v);
    }

    float y() const
    {
        return _mm_cvtss_f32(_mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1)));
    }

    float z() const
    {
        return _mm_cvtss_f32(_mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2)));
    }

    // Chargement / stockage

    static Vec3 load(const float* p)
    {
        return Vec3(_mm_set_ps(0.0f, p[2], p[1], p[0]));
    }

    void store(float* p) const
    {
        _mm_store_ss(&p[0], v);

        __m128 y = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 z = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));

        _mm_store_ss(&p[1], y);
        _mm_store_ss(&p[2], z);
    }

    // Opérateurs

    Vec3 operator+(const Vec3& rhs) const
    {
        return Vec3(_mm_add_ps(v, rhs.v));
    }

    Vec3 operator-(const Vec3& rhs) const
    {
        return Vec3(_mm_sub_ps(v, rhs.v));
    }

    Vec3 operator-() const
    {
        return Vec3(_mm_sub_ps(_mm_setzero_ps(), v));
    }

    Vec3 operator*(float s) const
    {
        return Vec3(_mm_mul_ps(v, _mm_set1_ps(s)));
    }

    Vec3 operator/(float s) const
    {
        return Vec3(_mm_div_ps(v, _mm_set1_ps(s)));
    }

    Vec3& operator+=(const Vec3& rhs)
    {
        v = _mm_add_ps(v, rhs.v);
        return *this;
    }

    Vec3& operator-=(const Vec3& rhs)
    {
        v = _mm_sub_ps(v, rhs.v);
        return *this;
    }

    Vec3& operator*=(float s)
    {
        v = _mm_mul_ps(v, _mm_set1_ps(s));
        return *this;
    }

    Vec3& operator/=(float s)
    {
        v = _mm_div_ps(v, _mm_set1_ps(s));
        return *this;
    }

    friend Vec3 operator*(float s, const Vec3& a)
    {
        return a * s;
    }

    // Produit scalaire

    float dot(const Vec3& rhs) const
    {
        __m128 mul = _mm_mul_ps(v, rhs.v);

        // x + y + z
        __m128 shuf = _mm_movehdup_ps(mul);
        __m128 sums = _mm_add_ps(mul, shuf);

        shuf = _mm_movehl_ps(shuf, sums);
        sums = _mm_add_ss(sums, shuf);

        return _mm_cvtss_f32(sums);
    }

    // Produit vectoriel

    Vec3 cross(const Vec3& rhs) const
    {
        __m128 a_yzx = _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 0, 2, 1));
        __m128 b_yzx = _mm_shuffle_ps(rhs.v, rhs.v, _MM_SHUFFLE(3, 0, 2, 1));

        __m128 c = _mm_sub_ps(
            _mm_mul_ps(v, b_yzx),
            _mm_mul_ps(a_yzx, rhs.v)
        );

        return Vec3(
            _mm_shuffle_ps(c, c, _MM_SHUFFLE(3, 0, 2, 1))
        );
    }

    // Longueur

    float lengthSquared() const
    {
        return dot(*this);
    }

    float length() const
    {
        return _mm_cvtss_f32(
            _mm_sqrt_ss(_mm_set_ss(lengthSquared()))
        );
    }

    // Normalisation

    Vec3 normalized() const
    {
        float lenSq = lengthSquared();

        if (lenSq <= 0.0f)
            return Vec3();

        __m128 lenSq4 = _mm_set1_ps(lenSq);
        __m128 invLen = _mm_rsqrt_ps(lenSq4);

        // Une itération de Newton-Raphson pour améliorer rsqrt
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
                        _mm_mul_ps(invLen, invLen)
                    )
                )
            )
        );

        return Vec3(_mm_mul_ps(v, invLen));
    }

    void normalize()
    {
        *this = normalized();
    }

    // Distance

    float distanceSquared(const Vec3& rhs) const
    {
        return (*this - rhs).lengthSquared();
    }

    float distance(const Vec3& rhs) const
    {
        return (*this - rhs).length();
    }

    // Min / Max

    static Vec3 min(const Vec3& a, const Vec3& b)
    {
        return Vec3(_mm_min_ps(a.v, b.v));
    }

    static Vec3 max(const Vec3& a, const Vec3& b)
    {
        return Vec3(_mm_max_ps(a.v, b.v));
    }

    // Abs

    Vec3 abs() const
    {
        const __m128 signMask =
            _mm_set1_ps(-0.0f);

        return Vec3(
            _mm_andnot_ps(signMask, v)
        );
    }

    // Lerp

    static Vec3 lerp(const Vec3& a, const Vec3& b, float t)
    {
        __m128 t4 = _mm_set1_ps(t);

        return Vec3(
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

#endif // VEC3_SSE_H
