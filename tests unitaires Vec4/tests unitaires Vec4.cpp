#include "pch.h"
#include "CppUnitTest.h"
#include "../asm_math_lib/Vec4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testunitaire
{
    TEST_CLASS(Vec4Test)
    {
    public:

        // Constructeurs

        TEST_METHOD(DefaultConstructor)
        {
            Vec4 v;

            Assert::AreEqual(0.0f, v.x());
            Assert::AreEqual(0.0f, v.y());
            Assert::AreEqual(0.0f, v.z());
            Assert::AreEqual(0.0f, v.w());
        }

        TEST_METHOD(FloatConstructor)
        {
            Vec4 v(1.0f, 2.0f, 3.0f, 4.0f);

            Assert::AreEqual(1.0f, v.x());
            Assert::AreEqual(2.0f, v.y());
            Assert::AreEqual(3.0f, v.z());
            Assert::AreEqual(4.0f, v.w());
        }

        TEST_METHOD(M128Constructor)
        {
            __m128 value = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);

            Vec4 v(value);

            Assert::AreEqual(1.0f, v.x());
            Assert::AreEqual(2.0f, v.y());
            Assert::AreEqual(3.0f, v.z());
            Assert::AreEqual(4.0f, v.w());
        }


        // Accès

        TEST_METHOD(XAccessor)
        {
            Vec4 v(10.0f, 20.0f, 30.0f, 40.0f);

            Assert::AreEqual(10.0f, v.x());
        }

        TEST_METHOD(YAccessor)
        {
            Vec4 v(10.0f, 20.0f, 30.0f, 40.0f);

            Assert::AreEqual(20.0f, v.y());
        }

        TEST_METHOD(ZAccessor)
        {
            Vec4 v(10.0f, 20.0f, 30.0f, 40.0f);

            Assert::AreEqual(30.0f, v.z());
        }

        TEST_METHOD(WAccessor)
        {
            Vec4 v(10.0f, 20.0f, 30.0f, 40.0f);

            Assert::AreEqual(40.0f, v.w());
        }


        // Chargement / stockage

        TEST_METHOD(Load)
        {
            alignas(16) float data[4] =
            {
                1.0f,
                2.0f,
                3.0f,
                4.0f
            };

            Vec4 v = Vec4::load(data);

            Assert::AreEqual(1.0f, v.x());
            Assert::AreEqual(2.0f, v.y());
            Assert::AreEqual(3.0f, v.z());
            Assert::AreEqual(4.0f, v.w());
        }

        TEST_METHOD(Store)
        {
            Vec4 v(1.0f, 2.0f, 3.0f, 4.0f);

            alignas(16) float data[4] = {};

            v.store(data);

            Assert::AreEqual(1.0f, data[0]);
            Assert::AreEqual(2.0f, data[1]);
            Assert::AreEqual(3.0f, data[2]);
            Assert::AreEqual(4.0f, data[3]);
        }

        TEST_METHOD(LoadAndStore)
        {
            alignas(16) float input[4] =
            {
                5.0f,
                6.0f,
                7.0f,
                8.0f
            };

            alignas(16) float output[4] = {};

            Vec4 v = Vec4::load(input);
            v.store(output);

            Assert::AreEqual(input[0], output[0]);
            Assert::AreEqual(input[1], output[1]);
            Assert::AreEqual(input[2], output[2]);
            Assert::AreEqual(input[3], output[3]);
        }


        // Addition

        TEST_METHOD(Addition)
        {
            Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
            Vec4 b(5.0f, 6.0f, 7.0f, 8.0f);

            Vec4 result = a + b;

            Assert::AreEqual(6.0f, result.x());
            Assert::AreEqual(8.0f, result.y());
            Assert::AreEqual(10.0f, result.z());
            Assert::AreEqual(12.0f, result.w());
        }

        TEST_METHOD(AdditionAssignment)
        {
            Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
            Vec4 b(5.0f, 6.0f, 7.0f, 8.0f);

            a += b;

            Assert::AreEqual(6.0f, a.x());
            Assert::AreEqual(8.0f, a.y());
            Assert::AreEqual(10.0f, a.z());
            Assert::AreEqual(12.0f, a.w());
        }


        // Soustraction

        TEST_METHOD(Subtraction)
        {
            Vec4 a(10.0f, 20.0f, 30.0f, 40.0f);
            Vec4 b(1.0f, 2.0f, 3.0f, 4.0f);

            Vec4 result = a - b;

            Assert::AreEqual(9.0f, result.x());
            Assert::AreEqual(18.0f, result.y());
            Assert::AreEqual(27.0f, result.z());
            Assert::AreEqual(36.0f, result.w());
        }

        TEST_METHOD(SubtractionAssignment)
        {
            Vec4 a(10.0f, 20.0f, 30.0f, 40.0f);
            Vec4 b(1.0f, 2.0f, 3.0f, 4.0f);

            a -= b;

            Assert::AreEqual(9.0f, a.x());
            Assert::AreEqual(18.0f, a.y());
            Assert::AreEqual(27.0f, a.z());
            Assert::AreEqual(36.0f, a.w());
        }


        // Opposé

        TEST_METHOD(UnaryMinus)
        {
            Vec4 v(1.0f, -2.0f, 3.0f, -4.0f);

            Vec4 result = -v;

            Assert::AreEqual(-1.0f, result.x());
            Assert::AreEqual(2.0f, result.y());
            Assert::AreEqual(-3.0f, result.z());
            Assert::AreEqual(4.0f, result.w());
        }


        // Multiplication scalaire

        TEST_METHOD(ScalarMultiplication)
        {
            Vec4 v(1.0f, 2.0f, 3.0f, 4.0f);

            Vec4 result = v * 2.0f;

            Assert::AreEqual(2.0f, result.x());
            Assert::AreEqual(4.0f, result.y());
            Assert::AreEqual(6.0f, result.z());
            Assert::AreEqual(8.0f, result.w());
        }

        TEST_METHOD(ScalarMultiplicationReversed)
        {
            Vec4 v(1.0f, 2.0f, 3.0f, 4.0f);

            Vec4 result = 2.0f * v;

            Assert::AreEqual(2.0f, result.x());
            Assert::AreEqual(4.0f, result.y());
            Assert::AreEqual(6.0f, result.z());
            Assert::AreEqual(8.0f, result.w());
        }

        TEST_METHOD(ScalarMultiplicationAssignment)
        {
            Vec4 v(1.0f, 2.0f, 3.0f, 4.0f);

            v *= 2.0f;

            Assert::AreEqual(2.0f, v.x());
            Assert::AreEqual(4.0f, v.y());
            Assert::AreEqual(6.0f, v.z());
            Assert::AreEqual(8.0f, v.w());
        }


        // Division scalaire

        TEST_METHOD(ScalarDivision)
        {
            Vec4 v(2.0f, 4.0f, 6.0f, 8.0f);

            Vec4 result = v / 2.0f;

            Assert::AreEqual(1.0f, result.x());
            Assert::AreEqual(2.0f, result.y());
            Assert::AreEqual(3.0f, result.z());
            Assert::AreEqual(4.0f, result.w());
        }

        TEST_METHOD(ScalarDivisionAssignment)
        {
            Vec4 v(2.0f, 4.0f, 6.0f, 8.0f);

            v /= 2.0f;

            Assert::AreEqual(1.0f, v.x());
            Assert::AreEqual(2.0f, v.y());
            Assert::AreEqual(3.0f, v.z());
            Assert::AreEqual(4.0f, v.w());
        }


        // Produit scalaire

        TEST_METHOD(Dot)
        {
            Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
            Vec4 b(5.0f, 6.0f, 7.0f, 8.0f);

            float result = a.dot(b);

            Assert::AreEqual(70.0f, result);
        }

        TEST_METHOD(DotOrthogonal)
        {
            Vec4 a(1.0f, 0.0f, 0.0f, 0.0f);
            Vec4 b(0.0f, 1.0f, 0.0f, 0.0f);

            Assert::AreEqual(0.0f, a.dot(b));
        }

        TEST_METHOD(DotWithSelf)
        {
            Vec4 v(1.0f, 2.0f, 3.0f, 4.0f);

            Assert::AreEqual(30.0f, v.dot(v));
        }


        // Longueur

        TEST_METHOD(LengthSquared)
        {
            Vec4 v(1.0f, 2.0f, 3.0f, 4.0f);

            Assert::AreEqual(30.0f, v.lengthSquared());
        }

        TEST_METHOD(Length)
        {
            Vec4 v(3.0f, 4.0f, 0.0f, 0.0f);

            Assert::AreEqual(5.0f, v.length(), 0.0001f);
        }

        TEST_METHOD(ZeroLength)
        {
            Vec4 v;

            Assert::AreEqual(0.0f, v.length());
        }


        // Normalisation

        TEST_METHOD(Normalized)
        {
            Vec4 v(3.0f, 0.0f, 0.0f, 0.0f);

            Vec4 result = v.normalized();

            Assert::AreEqual(1.0f, result.x(), 0.001f);
            Assert::AreEqual(0.0f, result.y(), 0.001f);
            Assert::AreEqual(0.0f, result.z(), 0.001f);
            Assert::AreEqual(0.0f, result.w(), 0.001f);
        }

        TEST_METHOD(NormalizedLength)
        {
            Vec4 v(3.0f, 4.0f, 0.0f, 0.0f);

            Vec4 result = v.normalized();

            Assert::AreEqual(1.0f, result.length(), 0.001f);
        }

        TEST_METHOD(Normalize)
        {
            Vec4 v(3.0f, 4.0f, 0.0f, 0.0f);

            v.normalize();

            Assert::AreEqual(0.6f, v.x(), 0.001f);
            Assert::AreEqual(0.8f, v.y(), 0.001f);
            Assert::AreEqual(0.0f, v.z(), 0.001f);
            Assert::AreEqual(0.0f, v.w(), 0.001f);
        }

        TEST_METHOD(NormalizeZero)
        {
            Vec4 v;

            v.normalize();

            Assert::AreEqual(0.0f, v.x());
            Assert::AreEqual(0.0f, v.y());
            Assert::AreEqual(0.0f, v.z());
            Assert::AreEqual(0.0f, v.w());
        }

        TEST_METHOD(NormalizedZero)
        {
            Vec4 v;

            Vec4 result = v.normalized();

            Assert::AreEqual(0.0f, result.x());
            Assert::AreEqual(0.0f, result.y());
            Assert::AreEqual(0.0f, result.z());
            Assert::AreEqual(0.0f, result.w());
        }


        // Distance

        TEST_METHOD(DistanceSquared)
        {
            Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
            Vec4 b(2.0f, 4.0f, 6.0f, 8.0f);

            Assert::AreEqual(30.0f, a.distanceSquared(b));
        }

        TEST_METHOD(Distance)
        {
            Vec4 a(0.0f, 0.0f, 0.0f, 0.0f);
            Vec4 b(3.0f, 4.0f, 0.0f, 0.0f);

            Assert::AreEqual(5.0f, a.distance(b), 0.001f);
        }

        TEST_METHOD(DistanceToSelf)
        {
            Vec4 v(1.0f, 2.0f, 3.0f, 4.0f);

            Assert::AreEqual(0.0f, v.distance(v));
        }


        // Min / Max

        TEST_METHOD(Min)
        {
            Vec4 a(1.0f, 5.0f, 3.0f, 8.0f);
            Vec4 b(4.0f, 2.0f, 6.0f, 7.0f);

            Vec4 result = Vec4::min(a, b);

            Assert::AreEqual(1.0f, result.x());
            Assert::AreEqual(2.0f, result.y());
            Assert::AreEqual(3.0f, result.z());
            Assert::AreEqual(7.0f, result.w());
        }

        TEST_METHOD(Max)
        {
            Vec4 a(1.0f, 5.0f, 3.0f, 8.0f);
            Vec4 b(4.0f, 2.0f, 6.0f, 7.0f);

            Vec4 result = Vec4::max(a, b);

            Assert::AreEqual(4.0f, result.x());
            Assert::AreEqual(5.0f, result.y());
            Assert::AreEqual(6.0f, result.z());
            Assert::AreEqual(8.0f, result.w());
        }


        // Abs

        TEST_METHOD(Abs)
        {
            Vec4 v(-1.0f, 2.0f, -3.0f, 4.0f);

            Vec4 result = v.abs();

            Assert::AreEqual(1.0f, result.x());
            Assert::AreEqual(2.0f, result.y());
            Assert::AreEqual(3.0f, result.z());
            Assert::AreEqual(4.0f, result.w());
        }


        // Lerp

        TEST_METHOD(LerpZero)
        {
            Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
            Vec4 b(5.0f, 6.0f, 7.0f, 8.0f);

            Vec4 result = Vec4::lerp(a, b, 0.0f);

            Assert::AreEqual(1.0f, result.x());
            Assert::AreEqual(2.0f, result.y());
            Assert::AreEqual(3.0f, result.z());
            Assert::AreEqual(4.0f, result.w());
        }

        TEST_METHOD(LerpOne)
        {
            Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
            Vec4 b(5.0f, 6.0f, 7.0f, 8.0f);

            Vec4 result = Vec4::lerp(a, b, 1.0f);

            Assert::AreEqual(5.0f, result.x());
            Assert::AreEqual(6.0f, result.y());
            Assert::AreEqual(7.0f, result.z());
            Assert::AreEqual(8.0f, result.w());
        }

        TEST_METHOD(LerpHalf)
        {
            Vec4 a(0.0f, 0.0f, 0.0f, 0.0f);
            Vec4 b(10.0f, 20.0f, 30.0f, 40.0f);

            Vec4 result = Vec4::lerp(a, b, 0.5f);

            Assert::AreEqual(5.0f, result.x());
            Assert::AreEqual(10.0f, result.y());
            Assert::AreEqual(15.0f, result.z());
            Assert::AreEqual(20.0f, result.w());
        }

        TEST_METHOD(LerpQuarter)
        {
            Vec4 a(0.0f, 0.0f, 0.0f, 0.0f);
            Vec4 b(4.0f, 8.0f, 12.0f, 16.0f);

            Vec4 result = Vec4::lerp(a, b, 0.25f);

            Assert::AreEqual(1.0f, result.x());
            Assert::AreEqual(2.0f, result.y());
            Assert::AreEqual(3.0f, result.z());
            Assert::AreEqual(4.0f, result.w());
        }


        // Taille et alignement

        TEST_METHOD(Size)
        {
            Assert::AreEqual<size_t>(16, sizeof(Vec4));
        }

        TEST_METHOD(Alignment)
        {
            Vec4 v;

            auto address =
                reinterpret_cast<std::uintptr_t>(&v);

            Assert::AreEqual<std::uintptr_t>(
                0,
                address % 16
            );
        }
    };
}