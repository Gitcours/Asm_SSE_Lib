#include "pch.h"
#include "CppUnitTest.h"
#include "../asm_math_lib/Vec3.h"
#include "../asm_math_lib/Batch.h"
#include "../asm_math_lib/BatchSIMD.h"
#include "../asm_math_lib/BatchValidation.h"
#include "../asm_math_lib/BatchSOA.h"
#include "../asm_math_lib/BatchSoASIMD.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testunitaire
{
    TEST_CLASS(Testunitaire)
    {
    public:

        // ============================================================
        // Constructeurs
        // ============================================================

        TEST_METHOD(TestConstructeurParDefaut)
        {
            Vec3 v;

            Assert::AreEqual(0.0f, v.x());
            Assert::AreEqual(0.0f, v.y());
            Assert::AreEqual(0.0f, v.z());
        }

        TEST_METHOD(TestConstructeurXYZ)
        {
            Vec3 v(1.0f, 2.0f, 3.0f);

            Assert::AreEqual(1.0f, v.x());
            Assert::AreEqual(2.0f, v.y());
            Assert::AreEqual(3.0f, v.z());
        }


        // ============================================================
        // Load / Store
        // ============================================================

        TEST_METHOD(TestLoad)
        {
            float data[3] = { 1.0f, 2.0f, 3.0f };

            Vec3 v = Vec3::load(data);

            Assert::AreEqual(1.0f, v.x());
            Assert::AreEqual(2.0f, v.y());
            Assert::AreEqual(3.0f, v.z());
        }

        TEST_METHOD(TestStore)
        {
            Vec3 v(1.0f, 2.0f, 3.0f);

            float data[3] = {};

            v.store(data);

            Assert::AreEqual(1.0f, data[0]);
            Assert::AreEqual(2.0f, data[1]);
            Assert::AreEqual(3.0f, data[2]);
        }


        // ============================================================
        // Addition
        // ============================================================

        TEST_METHOD(TestAddition)
        {
            Vec3 a(1.0f, 2.0f, 3.0f);
            Vec3 b(4.0f, 5.0f, 6.0f);

            Vec3 result = a + b;

            Assert::AreEqual(5.0f, result.x());
            Assert::AreEqual(7.0f, result.y());
            Assert::AreEqual(9.0f, result.z());
        }

        TEST_METHOD(TestAdditionAssignment)
        {
            Vec3 a(1.0f, 2.0f, 3.0f);
            Vec3 b(4.0f, 5.0f, 6.0f);

            a += b;

            Assert::AreEqual(5.0f, a.x());
            Assert::AreEqual(7.0f, a.y());
            Assert::AreEqual(9.0f, a.z());
        }


        // ============================================================
        // Soustraction
        // ============================================================

        TEST_METHOD(TestSoustraction)
        {
            Vec3 a(5.0f, 7.0f, 9.0f);
            Vec3 b(1.0f, 2.0f, 3.0f);

            Vec3 result = a - b;

            Assert::AreEqual(4.0f, result.x());
            Assert::AreEqual(5.0f, result.y());
            Assert::AreEqual(6.0f, result.z());
        }

        TEST_METHOD(TestSoustractionAssignment)
        {
            Vec3 a(5.0f, 7.0f, 9.0f);
            Vec3 b(1.0f, 2.0f, 3.0f);

            a -= b;

            Assert::AreEqual(4.0f, a.x());
            Assert::AreEqual(5.0f, a.y());
            Assert::AreEqual(6.0f, a.z());
        }

        TEST_METHOD(TestOppose)
        {
            Vec3 v(1.0f, -2.0f, 3.0f);

            Vec3 result = -v;

            Assert::AreEqual(-1.0f, result.x());
            Assert::AreEqual(2.0f, result.y());
            Assert::AreEqual(-3.0f, result.z());
        }


        // ============================================================
        // Multiplication
        // ============================================================

        TEST_METHOD(TestMultiplicationScalaire)
        {
            Vec3 v(1.0f, 2.0f, 3.0f);

            Vec3 result = v * 2.0f;

            Assert::AreEqual(2.0f, result.x());
            Assert::AreEqual(4.0f, result.y());
            Assert::AreEqual(6.0f, result.z());
        }

        TEST_METHOD(TestMultiplicationScalaireInverse)
        {
            Vec3 v(1.0f, 2.0f, 3.0f);

            Vec3 result = 2.0f * v;

            Assert::AreEqual(2.0f, result.x());
            Assert::AreEqual(4.0f, result.y());
            Assert::AreEqual(6.0f, result.z());
        }

        TEST_METHOD(TestMultiplicationAssignment)
        {
            Vec3 v(1.0f, 2.0f, 3.0f);

            v *= 2.0f;

            Assert::AreEqual(2.0f, v.x());
            Assert::AreEqual(4.0f, v.y());
            Assert::AreEqual(6.0f, v.z());
        }


        // ============================================================
        // Division
        // ============================================================

        TEST_METHOD(TestDivisionScalaire)
        {
            Vec3 v(2.0f, 4.0f, 6.0f);

            Vec3 result = v / 2.0f;

            Assert::AreEqual(1.0f, result.x());
            Assert::AreEqual(2.0f, result.y());
            Assert::AreEqual(3.0f, result.z());
        }

        TEST_METHOD(TestDivisionAssignment)
        {
            Vec3 v(2.0f, 4.0f, 6.0f);

            v /= 2.0f;

            Assert::AreEqual(1.0f, v.x());
            Assert::AreEqual(2.0f, v.y());
            Assert::AreEqual(3.0f, v.z());
        }


        // ============================================================
        // Produit scalaire
        // ============================================================

        TEST_METHOD(TestProduitScalaire)
        {
            Vec3 a(1.0f, 2.0f, 3.0f);
            Vec3 b(4.0f, 5.0f, 6.0f);

            float result = a.dot(b);

            // 1*4 + 2*5 + 3*6 = 32
            Assert::AreEqual(32.0f, result);
        }

        TEST_METHOD(TestProduitScalaireOrthogonal)
        {
            Vec3 a(1.0f, 0.0f, 0.0f);
            Vec3 b(0.0f, 1.0f, 0.0f);

            float result = a.dot(b);

            Assert::AreEqual(0.0f, result);
        }


        // ============================================================
        // Produit vectoriel
        // ============================================================

        TEST_METHOD(TestProduitVectoriel)
        {
            Vec3 a(1.0f, 0.0f, 0.0f);
            Vec3 b(0.0f, 1.0f, 0.0f);

            Vec3 result = a.cross(b);

            Assert::AreEqual(0.0f, result.x());
            Assert::AreEqual(0.0f, result.y());
            Assert::AreEqual(1.0f, result.z());
        }

        TEST_METHOD(TestProduitVectorielInverse)
        {
            Vec3 a(1.0f, 0.0f, 0.0f);
            Vec3 b(0.0f, 1.0f, 0.0f);

            Vec3 result = b.cross(a);

            Assert::AreEqual(0.0f, result.x());
            Assert::AreEqual(0.0f, result.y());
            Assert::AreEqual(-1.0f, result.z());
        }

        TEST_METHOD(TestProduitVectorielVecteursParalleles)
        {
            Vec3 a(1.0f, 2.0f, 3.0f);
            Vec3 b(2.0f, 4.0f, 6.0f);

            Vec3 result = a.cross(b);

            Assert::AreEqual(0.0f, result.x());
            Assert::AreEqual(0.0f, result.y());
            Assert::AreEqual(0.0f, result.z());
        }


        // ============================================================
        // Longueur
        // ============================================================

        TEST_METHOD(TestLongueurAuCarre)
        {
            Vec3 v(1.0f, 2.0f, 3.0f);

            float result = v.lengthSquared();

            Assert::AreEqual(14.0f, result);
        }

        TEST_METHOD(TestLongueur)
        {
            Vec3 v(3.0f, 4.0f, 0.0f);

            float result = v.length();

            Assert::AreEqual(5.0f, result);
        }

        TEST_METHOD(TestLongueurVecteurZero)
        {
            Vec3 v;

            Assert::AreEqual(0.0f, v.length());
        }


        // ============================================================
        // Normalisation
        // ============================================================

        TEST_METHOD(TestNormalized)
        {
            Vec3 v(3.0f, 4.0f, 0.0f);

            Vec3 result = v.normalized();

            Assert::AreEqual(0.6f, result.x(), 0.001f);
            Assert::AreEqual(0.8f, result.y(), 0.001f);
            Assert::AreEqual(0.0f, result.z(), 0.001f);
        }

        TEST_METHOD(TestNormalizedLongueur)
        {
            Vec3 v(3.0f, 4.0f, 0.0f);

            Vec3 result = v.normalized();

            Assert::AreEqual(1.0f, result.length(), 0.001f);
        }

        TEST_METHOD(TestNormalize)
        {
            Vec3 v(3.0f, 4.0f, 0.0f);

            v.normalize();

            Assert::AreEqual(0.6f, v.x(), 0.001f);
            Assert::AreEqual(0.8f, v.y(), 0.001f);
            Assert::AreEqual(0.0f, v.z(), 0.001f);
        }

        TEST_METHOD(TestNormalizeVecteurZero)
        {
            Vec3 v;

            v.normalize();

            Assert::AreEqual(0.0f, v.x());
            Assert::AreEqual(0.0f, v.y());
            Assert::AreEqual(0.0f, v.z());
        }


        // ============================================================
        // Distance
        // ============================================================

        TEST_METHOD(TestDistanceAuCarre)
        {
            Vec3 a(1.0f, 2.0f, 3.0f);
            Vec3 b(4.0f, 6.0f, 3.0f);

            float result = a.distanceSquared(b);

            Assert::AreEqual(25.0f, result);
        }

        TEST_METHOD(TestDistance)
        {
            Vec3 a(1.0f, 2.0f, 3.0f);
            Vec3 b(4.0f, 6.0f, 3.0f);

            float result = a.distance(b);

            Assert::AreEqual(5.0f, result);
        }

        TEST_METHOD(TestDistanceVecteurIdentique)
        {
            Vec3 v(1.0f, 2.0f, 3.0f);

            Assert::AreEqual(0.0f, v.distance(v));
        }


        // ============================================================
        // Min / Max
        // ============================================================

        TEST_METHOD(TestMin)
        {
            Vec3 a(1.0f, 5.0f, 3.0f);
            Vec3 b(4.0f, 2.0f, 6.0f);

            Vec3 result = Vec3::min(a, b);

            Assert::AreEqual(1.0f, result.x());
            Assert::AreEqual(2.0f, result.y());
            Assert::AreEqual(3.0f, result.z());
        }

        TEST_METHOD(TestMax)
        {
            Vec3 a(1.0f, 5.0f, 3.0f);
            Vec3 b(4.0f, 2.0f, 6.0f);

            Vec3 result = Vec3::max(a, b);

            Assert::AreEqual(4.0f, result.x());
            Assert::AreEqual(5.0f, result.y());
            Assert::AreEqual(6.0f, result.z());
        }


        // ============================================================
        // Abs
        // ============================================================

        TEST_METHOD(TestAbs)
        {
            Vec3 v(-1.0f, 2.0f, -3.0f);

            Vec3 result = v.abs();

            Assert::AreEqual(1.0f, result.x());
            Assert::AreEqual(2.0f, result.y());
            Assert::AreEqual(3.0f, result.z());
        }


        // ============================================================
        // Lerp
        // ============================================================

        TEST_METHOD(TestLerpZero)
        {
            Vec3 a(1.0f, 2.0f, 3.0f);
            Vec3 b(10.0f, 20.0f, 30.0f);

            Vec3 result = Vec3::lerp(a, b, 0.0f);

            Assert::AreEqual(1.0f, result.x());
            Assert::AreEqual(2.0f, result.y());
            Assert::AreEqual(3.0f, result.z());
        }

        TEST_METHOD(TestLerpUn)
        {
            Vec3 a(1.0f, 2.0f, 3.0f);
            Vec3 b(10.0f, 20.0f, 30.0f);

            Vec3 result = Vec3::lerp(a, b, 1.0f);

            Assert::AreEqual(10.0f, result.x());
            Assert::AreEqual(20.0f, result.y());
            Assert::AreEqual(30.0f, result.z());
        }

        TEST_METHOD(TestLerpMilieu)
        {
            Vec3 a(0.0f, 0.0f, 0.0f);
            Vec3 b(10.0f, 20.0f, 30.0f);

            Vec3 result = Vec3::lerp(a, b, 0.5f);

            Assert::AreEqual(5.0f, result.x());
            Assert::AreEqual(10.0f, result.y());
            Assert::AreEqual(15.0f, result.z());
        }

        TEST_METHOD(TestLerpQuart)
        {
            Vec3 a(0.0f, 10.0f, 20.0f);
            Vec3 b(10.0f, 20.0f, 30.0f);

            Vec3 result = Vec3::lerp(a, b, 0.25f);

            Assert::AreEqual(2.5f, result.x());
            Assert::AreEqual(12.5f, result.y());
            Assert::AreEqual(22.5f, result.z());
        }


        // ============================================================
        // Alignement mémoire
        // ============================================================

        TEST_METHOD(TestTailleVec3)
        {
            Assert::AreEqual<size_t>(16, sizeof(Vec3));
        }

        TEST_METHOD(DotBatchReference)
        {
            Vec3 a[] =
            {
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(1.0f, 0.0f, 0.0f)
            };

            Vec3 b[] =
            {
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(0.0f, 1.0f, 0.0f)
            };

            float results[3] = {};

            Math::DotBatchReference(
                a,
                b,
                results,
                3
            );

            Assert::AreEqual(32.0f, results[0], 0.000001f);
            Assert::AreEqual(32.0f, results[1], 0.000001f);
            Assert::AreEqual(0.0f, results[2], 0.000001f);
        }

        TEST_METHOD(DotBatchReference_OneElement)
        {
            Vec3 a[] =
            {
                Vec3(1.0f, 2.0f, 3.0f)
            };

            Vec3 b[] =
            {
                Vec3(4.0f, 5.0f, 6.0f)
            };

            float result = 0.0f;

            Math::DotBatchReference(
                a,
                b,
                &result,
                1
            );

            Assert::AreEqual(32.0f, result, 0.000001f);
        }

        TEST_METHOD(DotBatchReference_NonMultipleOfFour)
        {
            Vec3 a[] =
            {
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(0.0f, 0.0f, 1.0f),
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(2.0f, 2.0f, 2.0f)
            };

            Vec3 b[] =
            {
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(0.0f, 0.0f, 1.0f),
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(1.0f, 2.0f, 3.0f)
            };

            float results[5] = {};

            Math::DotBatchReference(
                a,
                b,
                results,
                5
            );

            Assert::AreEqual(1.0f, results[0], 0.000001f);
            Assert::AreEqual(1.0f, results[1], 0.000001f);
            Assert::AreEqual(1.0f, results[2], 0.000001f);
            Assert::AreEqual(32.0f, results[3], 0.000001f);
            Assert::AreEqual(12.0f, results[4], 0.000001f);
        }
        TEST_METHOD(DotBatchReference_Empty)
        {
            Math::DotBatchReference(
                nullptr,
                nullptr,
                nullptr,
                0
            );

            Assert::IsTrue(true);
        }

        TEST_METHOD(NormalizeBatchReference)
        {
            Vec3 input[] =
            {
                Vec3(3.0f, 4.0f, 0.0f),
                Vec3(0.0f, 0.0f, 5.0f),
                Vec3(1.0f, 0.0f, 0.0f)
            };

            Vec3 results[3] = {};

            Math::NormalizeBatchReference(
                input,
                results,
                3
            );

            // (3,4,0) -> (0.6,0.8,0)
            Assert::AreEqual(0.6f, results[0].x(), 0.001f);
            Assert::AreEqual(0.8f, results[0].y(), 0.001f);
            Assert::AreEqual(0.0f, results[0].z(), 0.001f);

            // (0,0,5) -> (0,0,1)
            Assert::AreEqual(0.0f, results[1].x(), 0.001f);
            Assert::AreEqual(0.0f, results[1].y(), 0.001f);
            Assert::AreEqual(1.0f, results[1].z(), 0.001f);

            // (1,0,0) -> (1,0,0)
            Assert::AreEqual(1.0f, results[2].x(), 0.001f);
            Assert::AreEqual(0.0f, results[2].y(), 0.001f);
            Assert::AreEqual(0.0f, results[2].z(), 0.001f);
        }

        TEST_METHOD(NormalizeBatchReference_ZeroVector)
        {
            Vec3 input[] =
            {
                Vec3(0.0f, 0.0f, 0.0f)
            };

            Vec3 result;

            Math::NormalizeBatchReference(
                input,
                &result,
                1
            );

            Assert::AreEqual(0.0f, result.x());
            Assert::AreEqual(0.0f, result.y());
            Assert::AreEqual(0.0f, result.z());
        }

        TEST_METHOD(NormalizeBatchReference_OneElement)
        {
            Vec3 input[] =
            {
                Vec3(3.0f, 4.0f, 0.0f)
            };

            Vec3 result;

            Math::NormalizeBatchReference(
                input,
                &result,
                1
            );

            Assert::AreEqual(0.6f, result.x(), 0.001f);
            Assert::AreEqual(0.8f, result.y(), 0.001f);
            Assert::AreEqual(0.0f, result.z(), 0.001f);
        }

        TEST_METHOD(NormalizeBatchReference_NonMultipleOfFour)
        {
            Vec3 input[] =
            {
                Vec3(3.0f, 4.0f, 0.0f),
                Vec3(0.0f, 0.0f, 2.0f),
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 3.0f, 4.0f),
                Vec3(1.0f, 1.0f, 1.0f)
            };

            Vec3 results[5] = {};

            Math::NormalizeBatchReference(
                input,
                results,
                5
            );

            // (3,4,0) -> (0.6,0.8,0)
            Assert::AreEqual(0.6f, results[0].x(), 0.001f);
            Assert::AreEqual(0.8f, results[0].y(), 0.001f);
            Assert::AreEqual(0.0f, results[0].z(), 0.001f);

            // (0,0,2) -> (0,0,1)
            Assert::AreEqual(0.0f, results[1].x(), 0.001f);
            Assert::AreEqual(0.0f, results[1].y(), 0.001f);
            Assert::AreEqual(1.0f, results[1].z(), 0.001f);

            // (1,0,0) -> (1,0,0)
            Assert::AreEqual(1.0f, results[2].x(), 0.001f);
            Assert::AreEqual(0.0f, results[2].y(), 0.001f);
            Assert::AreEqual(0.0f, results[2].z(), 0.001f);

            // (0,3,4) -> (0,0.6,0.8)
            Assert::AreEqual(0.0f, results[3].x(), 0.001f);
            Assert::AreEqual(0.6f, results[3].y(), 0.001f);
            Assert::AreEqual(0.8f, results[3].z(), 0.001f);

            // (1,1,1) -> (1/sqrt(3),1/sqrt(3),1/sqrt(3))
            const float expected = 1.0f / std::sqrt(3.0f);

            Assert::AreEqual(expected, results[4].x(), 0.001f);
            Assert::AreEqual(expected, results[4].y(), 0.001f);
            Assert::AreEqual(expected, results[4].z(), 0.001f);
        }

        TEST_METHOD(NormalizeBatchReference_Empty)
        {
            Math::NormalizeBatchReference(
                nullptr,
                nullptr,
                0
            );

            Assert::IsTrue(true);
        }

        TEST_METHOD(TransformPointsBatchReference_Identity)
        {
            Vec3 input[] =
            {
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(-1.0f, 0.0f, 2.0f)
            };

            Vec3 results[3] = {};

            Mat4x4 matrix = Mat4x4::Identity();

            Math::TransformPointsBatchReference(
                input,
                results,
                3,
                matrix
            );

            Assert::AreEqual(1.0f, results[0].x(), 0.001f);
            Assert::AreEqual(2.0f, results[0].y(), 0.001f);
            Assert::AreEqual(3.0f, results[0].z(), 0.001f);

            Assert::AreEqual(4.0f, results[1].x(), 0.001f);
            Assert::AreEqual(5.0f, results[1].y(), 0.001f);
            Assert::AreEqual(6.0f, results[1].z(), 0.001f);

            Assert::AreEqual(-1.0f, results[2].x(), 0.001f);
            Assert::AreEqual(0.0f, results[2].y(), 0.001f);
            Assert::AreEqual(2.0f, results[2].z(), 0.001f);
        }

        TEST_METHOD(TransformPointsBatchReference_Translation)
        {
            Vec3 input[] =
            {
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(0.0f, 0.0f, 0.0f),
                Vec3(-1.0f, 5.0f, 2.0f)
            };

            Vec3 results[3] = {};

            Mat4x4 matrix = Mat4x4::Translation(
                10.0f,
                20.0f,
                30.0f
            );

            Math::TransformPointsBatchReference(
                input,
                results,
                3,
                matrix
            );

            Assert::AreEqual(11.0f, results[0].x(), 0.001f);
            Assert::AreEqual(22.0f, results[0].y(), 0.001f);
            Assert::AreEqual(33.0f, results[0].z(), 0.001f);

            Assert::AreEqual(10.0f, results[1].x(), 0.001f);
            Assert::AreEqual(20.0f, results[1].y(), 0.001f);
            Assert::AreEqual(30.0f, results[1].z(), 0.001f);

            Assert::AreEqual(9.0f, results[2].x(), 0.001f);
            Assert::AreEqual(25.0f, results[2].y(), 0.001f);
            Assert::AreEqual(32.0f, results[2].z(), 0.001f);
        }

        TEST_METHOD(TransformPointsBatchReference_RotationZ)
        {
            Vec3 input[] =
            {
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(1.0f, 1.0f, 0.0f)
            };

            Vec3 results[3] = {};

            Mat4x4 matrix = Mat4x4::RotationZ(
                3.14159265358979323846f / 2.0f
            );

            Math::TransformPointsBatchReference(
                input,
                results,
                3,
                matrix
            );

            // (1,0,0) -> (0,1,0)
            Assert::AreEqual(0.0f, results[0].x(), 0.001f);
            Assert::AreEqual(1.0f, results[0].y(), 0.001f);
            Assert::AreEqual(0.0f, results[0].z(), 0.001f);

            // (0,1,0) -> (-1,0,0)
            Assert::AreEqual(-1.0f, results[1].x(), 0.001f);
            Assert::AreEqual(0.0f, results[1].y(), 0.001f);
            Assert::AreEqual(0.0f, results[1].z(), 0.001f);

            // (1,1,0) -> (-1,1,0)
            Assert::AreEqual(-1.0f, results[2].x(), 0.001f);
            Assert::AreEqual(1.0f, results[2].y(), 0.001f);
            Assert::AreEqual(0.0f, results[2].z(), 0.001f);
        }

        TEST_METHOD(TransformPointsBatchReference_NonMultipleOfFour)
        {
            Vec3 input[] =
            {
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(0.0f, 0.0f, 0.0f),
                Vec3(-1.0f, 2.0f, 0.0f),
                Vec3(10.0f, 20.0f, 30.0f)
            };

            Vec3 results[5] = {};

            Mat4x4 matrix = Mat4x4::Translation(
                10.0f,
                20.0f,
                30.0f
            );

            Math::TransformPointsBatchReference(
                input,
                results,
                5,
                matrix
            );

            Assert::AreEqual(11.0f, results[0].x(), 0.001f);
            Assert::AreEqual(22.0f, results[0].y(), 0.001f);
            Assert::AreEqual(33.0f, results[0].z(), 0.001f);

            Assert::AreEqual(14.0f, results[1].x(), 0.001f);
            Assert::AreEqual(25.0f, results[1].y(), 0.001f);
            Assert::AreEqual(36.0f, results[1].z(), 0.001f);

            Assert::AreEqual(10.0f, results[2].x(), 0.001f);
            Assert::AreEqual(20.0f, results[2].y(), 0.001f);
            Assert::AreEqual(30.0f, results[2].z(), 0.001f);

            Assert::AreEqual(9.0f, results[3].x(), 0.001f);
            Assert::AreEqual(22.0f, results[3].y(), 0.001f);
            Assert::AreEqual(30.0f, results[3].z(), 0.001f);

            Assert::AreEqual(20.0f, results[4].x(), 0.001f);
            Assert::AreEqual(40.0f, results[4].y(), 0.001f);
            Assert::AreEqual(60.0f, results[4].z(), 0.001f);
        }

        TEST_METHOD(TransformPointsBatchReference_OneElement)
        {
            Vec3 input[] =
            {
                Vec3(1.0f, 2.0f, 3.0f)
            };

            Vec3 result;

            Mat4x4 matrix = Mat4x4::Translation(
                10.0f,
                20.0f,
                30.0f
            );

            Math::TransformPointsBatchReference(
                input,
                &result,
                1,
                matrix
            );

            Assert::AreEqual(11.0f, result.x(), 0.001f);
            Assert::AreEqual(22.0f, result.y(), 0.001f);
            Assert::AreEqual(33.0f, result.z(), 0.001f);
        }

        TEST_METHOD(TransformPointsBatchReference_Empty)
        {
            Mat4x4 matrix = Mat4x4::Identity();

            Math::TransformPointsBatchReference(
                nullptr,
                nullptr,
                0,
                matrix
            );

            Assert::IsTrue(true);
        }

        TEST_METHOD(DotBatchSIMD)
        {
            Vec3 a[] =
            {
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f)
            };

            Vec3 b[] =
            {
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(0.0f, 0.0f, 1.0f)
            };

            float results[4] = {};

            Math::DotBatchSIMD(
                a,
                b,
                results,
                4
            );

            Assert::AreEqual(32.0f, results[0], 0.001f);
            Assert::AreEqual(32.0f, results[1], 0.001f);
            Assert::AreEqual(0.0f, results[2], 0.001f);
            Assert::AreEqual(0.0f, results[3], 0.001f);
        }

        TEST_METHOD(DotBatchSIMD_NonMultipleOfFour)
        {
            Vec3 a[] =
            {
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(0.0f, 0.0f, 1.0f),
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(2.0f, 2.0f, 2.0f)
            };

            Vec3 b[] =
            {
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(0.0f, 0.0f, 1.0f),
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(1.0f, 2.0f, 3.0f)
            };

            float results[5] = {};

            Math::DotBatchSIMD(
                a,
                b,
                results,
                5
            );

            Assert::AreEqual(1.0f, results[0], 0.001f);
            Assert::AreEqual(1.0f, results[1], 0.001f);
            Assert::AreEqual(1.0f, results[2], 0.001f);
            Assert::AreEqual(32.0f, results[3], 0.001f);
            Assert::AreEqual(12.0f, results[4], 0.001f);
        }

        TEST_METHOD(DotBatchSIMD_OneElement)
        {
            Vec3 a[] =
            {
                Vec3(1.0f, 2.0f, 3.0f)
            };

            Vec3 b[] =
            {
                Vec3(4.0f, 5.0f, 6.0f)
            };

            float result = 0.0f;

            Math::DotBatchSIMD(
                a,
                b,
                &result,
                1
            );

            Assert::AreEqual(32.0f, result, 0.001f);
        }

        TEST_METHOD(DotBatchSIMD_Empty)
        {
            Math::DotBatchSIMD(
                nullptr,
                nullptr,
                nullptr,
                0
            );

            Assert::IsTrue(true);
        }

        TEST_METHOD(DotBatchSIMD_EightElements)
        {
            Vec3 a[] =
            {
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(0.0f, 0.0f, 1.0f),
                Vec3(1.0f, 2.0f, 3.0f),

                Vec3(2.0f, 0.0f, 0.0f),
                Vec3(0.0f, 2.0f, 0.0f),
                Vec3(0.0f, 0.0f, 2.0f),
                Vec3(2.0f, 2.0f, 2.0f)
            };

            Vec3 b[] =
            {
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(0.0f, 0.0f, 1.0f),
                Vec3(4.0f, 5.0f, 6.0f),

                Vec3(2.0f, 0.0f, 0.0f),
                Vec3(0.0f, 2.0f, 0.0f),
                Vec3(0.0f, 0.0f, 2.0f),
                Vec3(2.0f, 2.0f, 2.0f)
            };

            float results[8] = {};

            Math::DotBatchSIMD(
                a,
                b,
                results,
                8
            );

            Assert::AreEqual(1.0f, results[0], 0.001f);
            Assert::AreEqual(1.0f, results[1], 0.001f);
            Assert::AreEqual(1.0f, results[2], 0.001f);
            Assert::AreEqual(32.0f, results[3], 0.001f);

            Assert::AreEqual(4.0f, results[4], 0.001f);
            Assert::AreEqual(4.0f, results[5], 0.001f);
            Assert::AreEqual(4.0f, results[6], 0.001f);
            Assert::AreEqual(12.0f, results[7], 0.001f);
        }

        TEST_METHOD(NormalizeBatchSIMD)
        {
            Vec3 input[] =
            {
                Vec3(3.0f, 4.0f, 0.0f),
                Vec3(0.0f, 0.0f, 5.0f),
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(1.0f, 1.0f, 1.0f)
            };

            Vec3 results[4] = {};

            Math::NormalizeBatchSIMD(
                input,
                results,
                4
            );

            Assert::AreEqual(0.6f, results[0].x(), 0.001f);
            Assert::AreEqual(0.8f, results[0].y(), 0.001f);
            Assert::AreEqual(0.0f, results[0].z(), 0.001f);

            Assert::AreEqual(0.0f, results[1].x(), 0.001f);
            Assert::AreEqual(0.0f, results[1].y(), 0.001f);
            Assert::AreEqual(1.0f, results[1].z(), 0.001f);

            Assert::AreEqual(1.0f, results[2].x(), 0.001f);

            const float expected = 1.0f / std::sqrt(3.0f);

            Assert::AreEqual(expected, results[3].x(), 0.001f);
            Assert::AreEqual(expected, results[3].y(), 0.001f);
            Assert::AreEqual(expected, results[3].z(), 0.001f);
        }

        TEST_METHOD(NormalizeBatchSIMD_ZeroVector)
        {
            Vec3 input[] =
            {
                Vec3(0.0f, 0.0f, 0.0f),
                Vec3(3.0f, 4.0f, 0.0f),
                Vec3(0.0f, 0.0f, 0.0f),
                Vec3(1.0f, 0.0f, 0.0f)
            };

            Vec3 results[4] = {};

            Math::NormalizeBatchSIMD(
                input,
                results,
                4
            );

            Assert::AreEqual(0.0f, results[0].x());
            Assert::AreEqual(0.0f, results[0].y());
            Assert::AreEqual(0.0f, results[0].z());

            Assert::AreEqual(0.6f, results[1].x(), 0.001f);
            Assert::AreEqual(0.8f, results[1].y(), 0.001f);

            Assert::AreEqual(0.0f, results[2].x());
            Assert::AreEqual(0.0f, results[2].y());
            Assert::AreEqual(0.0f, results[2].z());

            Assert::AreEqual(1.0f, results[3].x(), 0.001f);
        }

        TEST_METHOD(NormalizeBatchSIMD_OneElement)
        {
            Vec3 input[] =
            {
                Vec3(3.0f, 4.0f, 0.0f)
            };

            Vec3 result;

            Math::NormalizeBatchSIMD(
                input,
                &result,
                1
            );

            Assert::AreEqual(0.6f, result.x(), 0.001f);
            Assert::AreEqual(0.8f, result.y(), 0.001f);
            Assert::AreEqual(0.0f, result.z(), 0.001f);
        }

        TEST_METHOD(NormalizeBatchSIMD_NonMultipleOfFour)
        {
            Vec3 input[] =
            {
                Vec3(3.0f, 4.0f, 0.0f),
                Vec3(0.0f, 0.0f, 2.0f),
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 3.0f, 4.0f),
                Vec3(1.0f, 1.0f, 1.0f)
            };

            Vec3 results[5] = {};

            Math::NormalizeBatchSIMD(
                input,
                results,
                5
            );

            Assert::AreEqual(0.6f, results[0].x(), 0.001f);
            Assert::AreEqual(0.8f, results[0].y(), 0.001f);

            Assert::AreEqual(1.0f, results[1].z(), 0.001f);

            Assert::AreEqual(1.0f, results[2].x(), 0.001f);

            Assert::AreEqual(0.6f, results[3].y(), 0.001f);
            Assert::AreEqual(0.8f, results[3].z(), 0.001f);

            const float expected = 1.0f / std::sqrt(3.0f);

            Assert::AreEqual(expected, results[4].x(), 0.001f);
            Assert::AreEqual(expected, results[4].y(), 0.001f);
            Assert::AreEqual(expected, results[4].z(), 0.001f);
        }

        TEST_METHOD(NormalizeBatchSIMD_Empty)
        {
            Math::NormalizeBatchSIMD(
                nullptr,
                nullptr,
                0
            );

            Assert::IsTrue(true);
        }

        // ============================================================
// TRANSFORM POINTS SIMD
// ============================================================

        TEST_METHOD(TransformPointsBatchSIMD_Identity)
        {
            Vec3 input[] =
            {
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(-1.0f, 0.0f, 2.0f),
                Vec3(10.0f, 20.0f, 30.0f)
            };

            Vec3 results[4] = {};

            Mat4x4 matrix = Mat4x4::Identity();

            Math::TransformPointsBatchSIMD(
                input,
                results,
                4,
                matrix
            );

            Assert::AreEqual(1.0f, results[0].x(), 0.001f);
            Assert::AreEqual(2.0f, results[0].y(), 0.001f);
            Assert::AreEqual(3.0f, results[0].z(), 0.001f);

            Assert::AreEqual(4.0f, results[1].x(), 0.001f);
            Assert::AreEqual(5.0f, results[1].y(), 0.001f);
            Assert::AreEqual(6.0f, results[1].z(), 0.001f);

            Assert::AreEqual(-1.0f, results[2].x(), 0.001f);
            Assert::AreEqual(0.0f, results[2].y(), 0.001f);
            Assert::AreEqual(2.0f, results[2].z(), 0.001f);

            Assert::AreEqual(10.0f, results[3].x(), 0.001f);
            Assert::AreEqual(20.0f, results[3].y(), 0.001f);
            Assert::AreEqual(30.0f, results[3].z(), 0.001f);
        }


        TEST_METHOD(TransformPointsBatchSIMD_Translation)
        {
            Vec3 input[] =
            {
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(0.0f, 0.0f, 0.0f),
                Vec3(-1.0f, 5.0f, 2.0f),
                Vec3(10.0f, 20.0f, 30.0f)
            };

            Vec3 results[4] = {};

            Mat4x4 matrix = Mat4x4::Translation(
                10.0f,
                20.0f,
                30.0f
            );

            Math::TransformPointsBatchSIMD(
                input,
                results,
                4,
                matrix
            );

            Assert::AreEqual(11.0f, results[0].x(), 0.001f);
            Assert::AreEqual(22.0f, results[0].y(), 0.001f);
            Assert::AreEqual(33.0f, results[0].z(), 0.001f);

            Assert::AreEqual(10.0f, results[1].x(), 0.001f);
            Assert::AreEqual(20.0f, results[1].y(), 0.001f);
            Assert::AreEqual(30.0f, results[1].z(), 0.001f);

            Assert::AreEqual(9.0f, results[2].x(), 0.001f);
            Assert::AreEqual(25.0f, results[2].y(), 0.001f);
            Assert::AreEqual(32.0f, results[2].z(), 0.001f);

            Assert::AreEqual(20.0f, results[3].x(), 0.001f);
            Assert::AreEqual(40.0f, results[3].y(), 0.001f);
            Assert::AreEqual(60.0f, results[3].z(), 0.001f);
        }


        TEST_METHOD(TransformPointsBatchSIMD_RotationZ)
        {
            Vec3 input[] =
            {
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(1.0f, 1.0f, 0.0f),
                Vec3(2.0f, 0.0f, 0.0f)
            };

            Vec3 results[4] = {};

            Mat4x4 matrix = Mat4x4::RotationZ(
                3.14159265358979323846f / 2.0f
            );

            Math::TransformPointsBatchSIMD(
                input,
                results,
                4,
                matrix
            );

            // (1,0,0) -> (0,1,0)
            Assert::AreEqual(0.0f, results[0].x(), 0.001f);
            Assert::AreEqual(1.0f, results[0].y(), 0.001f);
            Assert::AreEqual(0.0f, results[0].z(), 0.001f);

            // (0,1,0) -> (-1,0,0)
            Assert::AreEqual(-1.0f, results[1].x(), 0.001f);
            Assert::AreEqual(0.0f, results[1].y(), 0.001f);
            Assert::AreEqual(0.0f, results[1].z(), 0.001f);

            // (1,1,0) -> (-1,1,0)
            Assert::AreEqual(-1.0f, results[2].x(), 0.001f);
            Assert::AreEqual(1.0f, results[2].y(), 0.001f);
            Assert::AreEqual(0.0f, results[2].z(), 0.001f);

            // (2,0,0) -> (0,2,0)
            Assert::AreEqual(0.0f, results[3].x(), 0.001f);
            Assert::AreEqual(2.0f, results[3].y(), 0.001f);
            Assert::AreEqual(0.0f, results[3].z(), 0.001f);
        }


        TEST_METHOD(TransformPointsBatchSIMD_NonMultipleOfFour)
        {
            Vec3 input[] =
            {
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(0.0f, 0.0f, 0.0f),
                Vec3(-1.0f, 2.0f, 0.0f),
                Vec3(10.0f, 20.0f, 30.0f)
            };

            Vec3 results[5] = {};

            Mat4x4 matrix = Mat4x4::Translation(
                10.0f,
                20.0f,
                30.0f
            );

            Math::TransformPointsBatchSIMD(
                input,
                results,
                5,
                matrix
            );

            Assert::AreEqual(11.0f, results[0].x(), 0.001f);
            Assert::AreEqual(22.0f, results[0].y(), 0.001f);
            Assert::AreEqual(33.0f, results[0].z(), 0.001f);

            Assert::AreEqual(14.0f, results[1].x(), 0.001f);
            Assert::AreEqual(25.0f, results[1].y(), 0.001f);
            Assert::AreEqual(36.0f, results[1].z(), 0.001f);

            Assert::AreEqual(10.0f, results[2].x(), 0.001f);
            Assert::AreEqual(20.0f, results[2].y(), 0.001f);
            Assert::AreEqual(30.0f, results[2].z(), 0.001f);

            Assert::AreEqual(9.0f, results[3].x(), 0.001f);
            Assert::AreEqual(22.0f, results[3].y(), 0.001f);
            Assert::AreEqual(30.0f, results[3].z(), 0.001f);

            Assert::AreEqual(20.0f, results[4].x(), 0.001f);
            Assert::AreEqual(40.0f, results[4].y(), 0.001f);
            Assert::AreEqual(60.0f, results[4].z(), 0.001f);
        }


        TEST_METHOD(TransformPointsBatchSIMD_OneElement)
        {
            Vec3 input[] =
            {
                Vec3(1.0f, 2.0f, 3.0f)
            };

            Vec3 result;

            Mat4x4 matrix = Mat4x4::Translation(
                10.0f,
                20.0f,
                30.0f
            );

            Math::TransformPointsBatchSIMD(
                input,
                &result,
                1,
                matrix
            );

            Assert::AreEqual(11.0f, result.x(), 0.001f);
            Assert::AreEqual(22.0f, result.y(), 0.001f);
            Assert::AreEqual(33.0f, result.z(), 0.001f);
        }


        TEST_METHOD(TransformPointsBatchSIMD_Empty)
        {
            Mat4x4 matrix = Mat4x4::Identity();

            Math::TransformPointsBatchSIMD(
                nullptr,
                nullptr,
                0,
                matrix
            );

            Assert::IsTrue(true);
        }

        // ============================================================
// VALIDATION REFERENCE VS SIMD
// ============================================================

        TEST_METHOD(ValidateDotBatch_Empty)
        {
            Assert::IsTrue(
                Math::ValidateDotBatch(
                    nullptr,
                    nullptr,
                    0
                )
            );
        }


        TEST_METHOD(ValidateDotBatch_SmallSizes)
        {
            Vec3 a[] =
            {
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(2.0f, 3.0f, 4.0f),
                Vec3(-1.0f, 2.0f, -3.0f),
                Vec3(5.0f, 2.0f, 1.0f),
                Vec3(7.0f, 8.0f, 9.0f),
                Vec3(-4.0f, 3.0f, 2.0f)
            };

            Vec3 b[] =
            {
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(0.0f, 0.0f, 1.0f),
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(2.0f, -1.0f, 4.0f),
                Vec3(1.0f, 3.0f, 5.0f),
                Vec3(9.0f, 8.0f, 7.0f),
                Vec3(2.0f, -2.0f, 1.0f)
            };

            Assert::IsTrue(
                Math::ValidateDotBatch(a, b, 1)
            );

            Assert::IsTrue(
                Math::ValidateDotBatch(a, b, 2)
            );

            Assert::IsTrue(
                Math::ValidateDotBatch(a, b, 3)
            );

            Assert::IsTrue(
                Math::ValidateDotBatch(a, b, 4)
            );

            Assert::IsTrue(
                Math::ValidateDotBatch(a, b, 5)
            );

            Assert::IsTrue(
                Math::ValidateDotBatch(a, b, 7)
            );

            Assert::IsTrue(
                Math::ValidateDotBatch(a, b, 8)
            );

            Assert::IsTrue(
                Math::ValidateDotBatch(a, b, 9)
            );
        }


        TEST_METHOD(ValidateNormalizeBatch_Empty)
        {
            Assert::IsTrue(
                Math::ValidateNormalizeBatch(
                    nullptr,
                    0
                )
            );
        }


        TEST_METHOD(ValidateNormalizeBatch_SmallSizes)
        {
            Vec3 input[] =
            {
                Vec3(3.0f, 4.0f, 0.0f),
                Vec3(0.0f, 0.0f, 5.0f),
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(1.0f, 1.0f, 1.0f),
                Vec3(3.0f, 4.0f, 12.0f),
                Vec3(-2.0f, 5.0f, 1.0f),
                Vec3(7.0f, 2.0f, 9.0f),
                Vec3(-4.0f, -3.0f, 2.0f),
                Vec3(10.0f, 20.0f, 30.0f)
            };

            Assert::IsTrue(
                Math::ValidateNormalizeBatch(input, 1)
            );

            Assert::IsTrue(
                Math::ValidateNormalizeBatch(input, 2)
            );

            Assert::IsTrue(
                Math::ValidateNormalizeBatch(input, 3)
            );

            Assert::IsTrue(
                Math::ValidateNormalizeBatch(input, 4)
            );

            Assert::IsTrue(
                Math::ValidateNormalizeBatch(input, 5)
            );

            Assert::IsTrue(
                Math::ValidateNormalizeBatch(input, 7)
            );

            Assert::IsTrue(
                Math::ValidateNormalizeBatch(input, 8)
            );

            Assert::IsTrue(
                Math::ValidateNormalizeBatch(input, 9)
            );
        }


        TEST_METHOD(ValidateNormalizeBatch_WithZeroVectors)
        {
            Vec3 input[] =
            {
                Vec3(0.0f, 0.0f, 0.0f),
                Vec3(3.0f, 4.0f, 0.0f),
                Vec3(0.0f, 0.0f, 0.0f),
                Vec3(1.0f, 1.0f, 1.0f),
                Vec3(0.0f, 0.0f, 0.0f)
            };

            Assert::IsTrue(
                Math::ValidateNormalizeBatch(input, 5)
            );
        }


        TEST_METHOD(ValidateTransformBatch_Identity)
        {
            Vec3 input[] =
            {
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(-1.0f, 0.0f, 2.0f),
                Vec3(10.0f, 20.0f, 30.0f),
                Vec3(-5.0f, 4.0f, -2.0f)
            };

            Mat4x4 matrix = Mat4x4::Identity();

            Assert::IsTrue(
                Math::ValidateTransformPointsBatch(
                    input,
                    1,
                    matrix
                )
            );

            Assert::IsTrue(
                Math::ValidateTransformPointsBatch(
                    input,
                    2,
                    matrix
                )
            );

            Assert::IsTrue(
                Math::ValidateTransformPointsBatch(
                    input,
                    4,
                    matrix
                )
            );

            Assert::IsTrue(
                Math::ValidateTransformPointsBatch(
                    input,
                    5,
                    matrix
                )
            );
        }


        TEST_METHOD(ValidateTransformBatch_Translation)
        {
            Vec3 input[] =
            {
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(-1.0f, 0.0f, 2.0f),
                Vec3(10.0f, 20.0f, 30.0f),
                Vec3(-5.0f, 4.0f, -2.0f),
                Vec3(7.0f, -3.0f, 1.0f),
                Vec3(2.0f, 8.0f, 5.0f),
                Vec3(0.0f, 0.0f, 0.0f),
                Vec3(100.0f, -50.0f, 25.0f)
            };

            Mat4x4 matrix = Mat4x4::Translation(
                10.0f,
                20.0f,
                30.0f
            );

            Assert::IsTrue(
                Math::ValidateTransformPointsBatch(
                    input,
                    1,
                    matrix
                )
            );

            Assert::IsTrue(
                Math::ValidateTransformPointsBatch(
                    input,
                    4,
                    matrix
                )
            );

            Assert::IsTrue(
                Math::ValidateTransformPointsBatch(
                    input,
                    5,
                    matrix
                )
            );

            Assert::IsTrue(
                Math::ValidateTransformPointsBatch(
                    input,
                    8,
                    matrix
                )
            );

            Assert::IsTrue(
                Math::ValidateTransformPointsBatch(
                    input,
                    9,
                    matrix
                )
            );
        }


        TEST_METHOD(ValidateTransformBatch_Rotation)
        {
            Vec3 input[] =
            {
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(1.0f, 1.0f, 0.0f),
                Vec3(2.0f, 3.0f, 4.0f),
                Vec3(-1.0f, 5.0f, 2.0f)
            };

            Mat4x4 matrix = Mat4x4::RotationZ(
                3.14159265358979323846f / 2.0f
            );

            Assert::IsTrue(
                Math::ValidateTransformPointsBatch(
                    input,
                    1,
                    matrix
                )
            );

            Assert::IsTrue(
                Math::ValidateTransformPointsBatch(
                    input,
                    4,
                    matrix
                )
            );

            Assert::IsTrue(
                Math::ValidateTransformPointsBatch(
                    input,
                    5,
                    matrix
                )
            );
        }


        TEST_METHOD(ValidateTransformBatch_Empty)
        {
            Mat4x4 matrix = Mat4x4::Identity();

            Assert::IsTrue(
                Math::ValidateTransformPointsBatch(
                    nullptr,
                    0,
                    matrix
                )
            );
        }

        // ============================================================
// TESTS AoS -> SoA
// ============================================================

        TEST_METHOD(AoSToSoA)
        {
            Vec3 input[] =
            {
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(7.0f, 8.0f, 9.0f)
            };

            Math::Vec3SoA soa;

            Math::ConvertAoSToSoA(
                input,
                soa,
                3
            );

            Assert::AreEqual(3u, static_cast<unsigned int>(soa.size()));

            Assert::AreEqual(1.0f, soa.x[0]);
            Assert::AreEqual(4.0f, soa.x[1]);
            Assert::AreEqual(7.0f, soa.x[2]);

            Assert::AreEqual(2.0f, soa.y[0]);
            Assert::AreEqual(5.0f, soa.y[1]);
            Assert::AreEqual(8.0f, soa.y[2]);

            Assert::AreEqual(3.0f, soa.z[0]);
            Assert::AreEqual(6.0f, soa.z[1]);
            Assert::AreEqual(9.0f, soa.z[2]);
        }


        // ============================================================
        // TESTS SoA -> AoS
        // ============================================================

        TEST_METHOD(SoAToAoS)
        {
            Math::Vec3SoA soa;

            soa.resize(3);

            soa.x[0] = 1.0f;
            soa.y[0] = 2.0f;
            soa.z[0] = 3.0f;

            soa.x[1] = 4.0f;
            soa.y[1] = 5.0f;
            soa.z[1] = 6.0f;

            soa.x[2] = 7.0f;
            soa.y[2] = 8.0f;
            soa.z[2] = 9.0f;

            Vec3 output[3];

            Math::ConvertSoAToAoS(
                soa,
                output,
                3
            );

            Assert::AreEqual(1.0f, output[0].x());
            Assert::AreEqual(2.0f, output[0].y());
            Assert::AreEqual(3.0f, output[0].z());

            Assert::AreEqual(4.0f, output[1].x());
            Assert::AreEqual(5.0f, output[1].y());
            Assert::AreEqual(6.0f, output[1].z());

            Assert::AreEqual(7.0f, output[2].x());
            Assert::AreEqual(8.0f, output[2].y());
            Assert::AreEqual(9.0f, output[2].z());
        }


        // ============================================================
        // TEST DOT SoA REFERENCE
        // ============================================================

        TEST_METHOD(DotBatchSoAReference)
        {
            Vec3 a[] =
            {
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(2.0f, 2.0f, 2.0f)
            };

            Vec3 b[] =
            {
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(0.0f, 0.0f, 1.0f),
                Vec3(1.0f, 2.0f, 3.0f)
            };

            Math::Vec3SoA soaA;
            Math::Vec3SoA soaB;

            Math::ConvertAoSToSoA(
                a,
                soaA,
                5
            );

            Math::ConvertAoSToSoA(
                b,
                soaB,
                5
            );

            float results[5] = {};

            Math::DotBatchSoAReference(
                soaA,
                soaB,
                results,
                5
            );

            Assert::AreEqual(32.0f, results[0], 0.001f);
            Assert::AreEqual(32.0f, results[1], 0.001f);
            Assert::AreEqual(0.0f, results[2], 0.001f);
            Assert::AreEqual(0.0f, results[3], 0.001f);
            Assert::AreEqual(12.0f, results[4], 0.001f);
        }


        // ============================================================
        // TEST DOT SoA SIMD
        // ============================================================

        TEST_METHOD(DotBatchSoASIMD)
        {
            Vec3 a[] =
            {
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(2.0f, 2.0f, 2.0f)
            };

            Vec3 b[] =
            {
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(0.0f, 0.0f, 1.0f),
                Vec3(1.0f, 2.0f, 3.0f)
            };

            Math::Vec3SoA soaA;
            Math::Vec3SoA soaB;

            Math::ConvertAoSToSoA(
                a,
                soaA,
                5
            );

            Math::ConvertAoSToSoA(
                b,
                soaB,
                5
            );

            float results[5] = {};

            Math::DotBatchSoASIMD(
                soaA,
                soaB,
                results,
                5
            );

            Assert::AreEqual(32.0f, results[0], 0.001f);
            Assert::AreEqual(32.0f, results[1], 0.001f);
            Assert::AreEqual(0.0f, results[2], 0.001f);
            Assert::AreEqual(0.0f, results[3], 0.001f);
            Assert::AreEqual(12.0f, results[4], 0.001f);
        }


        // ============================================================
        // TEST SOA - 8 ELEMENTS
        // ============================================================

        TEST_METHOD(DotBatchSoASIMD_EightElements)
        {
            Vec3 a[] =
            {
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(0.0f, 0.0f, 1.0f),
                Vec3(1.0f, 2.0f, 3.0f),
                Vec3(2.0f, 0.0f, 0.0f),
                Vec3(0.0f, 2.0f, 0.0f),
                Vec3(0.0f, 0.0f, 2.0f),
                Vec3(2.0f, 2.0f, 2.0f)
            };

            Vec3 b[] =
            {
                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(0.0f, 0.0f, 1.0f),
                Vec3(4.0f, 5.0f, 6.0f),
                Vec3(2.0f, 0.0f, 0.0f),
                Vec3(0.0f, 2.0f, 0.0f),
                Vec3(0.0f, 0.0f, 2.0f),
                Vec3(2.0f, 2.0f, 2.0f)
            };

            Math::Vec3SoA soaA;
            Math::Vec3SoA soaB;

            Math::ConvertAoSToSoA(a, soaA, 8);
            Math::ConvertAoSToSoA(b, soaB, 8);

            float results[8] = {};

            Math::DotBatchSoASIMD(
                soaA,
                soaB,
                results,
                8
            );

            Assert::AreEqual(1.0f, results[0], 0.001f);
            Assert::AreEqual(1.0f, results[1], 0.001f);
            Assert::AreEqual(1.0f, results[2], 0.001f);
            Assert::AreEqual(32.0f, results[3], 0.001f);

            Assert::AreEqual(4.0f, results[4], 0.001f);
            Assert::AreEqual(4.0f, results[5], 0.001f);
            Assert::AreEqual(4.0f, results[6], 0.001f);
            Assert::AreEqual(12.0f, results[7], 0.001f);
        }


        // ============================================================
        // TEST SOA - VIDE
        // ============================================================

        TEST_METHOD(DotBatchSoASIMD_Empty)
        {
            Math::Vec3SoA a;
            Math::Vec3SoA b;

            float* results = nullptr;

            Math::DotBatchSoASIMD(
                a,
                b,
                results,
                0
            );

            Assert::IsTrue(true);
        }
    };
}