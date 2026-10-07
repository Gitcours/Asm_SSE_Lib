#include "pch.h"
#include "CppUnitTest.h"
#include "../asm_math_lib/Vec3.h"

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
    };
}