#include "pch.h"
#include "CppUnitTest.h"
#include "../asm_math_lib/Mat4x4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testunitaire
{
    TEST_CLASS(Mat4x4Test)
    {
    public:

        // Constructeur

        TEST_METHOD(DefaultConstructor)
        {
            Mat4x4 mat;

            for (int row = 0; row < 4; ++row)
            {
                for (int column = 0; column < 4; ++column)
                {
                    Assert::AreEqual(0.0f, mat.m[row][column]);
                }
            }
        }


        // Identité

        TEST_METHOD(Identity)
        {
            Mat4x4 mat = Mat4x4::Identity();

            for (int row = 0; row < 4; ++row)
            {
                for (int column = 0; column < 4; ++column)
                {
                    float expected =
                        (row == column) ? 1.0f : 0.0f;

                    Assert::AreEqual(
                        expected,
                        mat.m[row][column]
                    );
                }
            }
        }


        // Translation

        TEST_METHOD(Translation)
        {
            Mat4x4 mat =
                Mat4x4::Translation(10.0f, 20.0f, 30.0f);

            Assert::AreEqual(1.0f, mat.m[0][0]);
            Assert::AreEqual(1.0f, mat.m[1][1]);
            Assert::AreEqual(1.0f, mat.m[2][2]);
            Assert::AreEqual(1.0f, mat.m[3][3]);

            Assert::AreEqual(10.0f, mat.m[0][3]);
            Assert::AreEqual(20.0f, mat.m[1][3]);
            Assert::AreEqual(30.0f, mat.m[2][3]);

            Assert::AreEqual(0.0f, mat.m[0][1]);
            Assert::AreEqual(0.0f, mat.m[0][2]);
            Assert::AreEqual(0.0f, mat.m[1][0]);
            Assert::AreEqual(0.0f, mat.m[1][2]);
            Assert::AreEqual(0.0f, mat.m[2][0]);
            Assert::AreEqual(0.0f, mat.m[2][1]);
        }

        TEST_METHOD(TranslationTransformPoint)
        {
            Mat4x4 mat =
                Mat4x4::Translation(10.0f, 20.0f, 30.0f);

            Vec3 point(1.0f, 2.0f, 3.0f);

            Vec3 result = mat.TransformPoint(point);

            Assert::AreEqual(11.0f, result.x());
            Assert::AreEqual(22.0f, result.y());
            Assert::AreEqual(33.0f, result.z());
        }


        // Rotation X

        TEST_METHOD(RotationXZero)
        {
            Mat4x4 mat = Mat4x4::RotationX(0.0f);

            Mat4x4 identity = Mat4x4::Identity();

            for (int row = 0; row < 4; ++row)
            {
                for (int column = 0; column < 4; ++column)
                {
                    Assert::AreEqual(
                        identity.m[row][column],
                        mat.m[row][column],
                        0.0001f
                    );
                }
            }
        }

        TEST_METHOD(RotationX90Degrees)
        {
            const float pi = 3.14159265358979323846f;

            Mat4x4 mat =
                Mat4x4::RotationX(pi / 2.0f);

            Vec3 point(0.0f, 1.0f, 0.0f);

            Vec3 result = mat.TransformPoint(point);

            Assert::AreEqual(0.0f, result.x(), 0.0001f);
            Assert::AreEqual(0.0f, result.y(), 0.0001f);
            Assert::AreEqual(1.0f, result.z(), 0.0001f);
        }


        // Rotation Y

        TEST_METHOD(RotationYZero)
        {
            Mat4x4 mat = Mat4x4::RotationY(0.0f);

            Mat4x4 identity = Mat4x4::Identity();

            for (int row = 0; row < 4; ++row)
            {
                for (int column = 0; column < 4; ++column)
                {
                    Assert::AreEqual(
                        identity.m[row][column],
                        mat.m[row][column],
                        0.0001f
                    );
                }
            }
        }

        TEST_METHOD(RotationY90Degrees)
        {
            const float pi = 3.14159265358979323846f;

            Mat4x4 mat =
                Mat4x4::RotationY(pi / 2.0f);

            Vec3 point(1.0f, 0.0f, 0.0f);

            Vec3 result = mat.TransformPoint(point);

            Assert::AreEqual(0.0f, result.x(), 0.0001f);
            Assert::AreEqual(0.0f, result.y(), 0.0001f);
            Assert::AreEqual(-1.0f, result.z(), 0.0001f);
        }


        // Rotation Z

        TEST_METHOD(RotationZZero)
        {
            Mat4x4 mat = Mat4x4::RotationZ(0.0f);

            Mat4x4 identity = Mat4x4::Identity();

            for (int row = 0; row < 4; ++row)
            {
                for (int column = 0; column < 4; ++column)
                {
                    Assert::AreEqual(
                        identity.m[row][column],
                        mat.m[row][column],
                        0.0001f
                    );
                }
            }
        }

        TEST_METHOD(RotationZ90Degrees)
        {
            const float pi = 3.14159265358979323846f;

            Mat4x4 mat =
                Mat4x4::RotationZ(pi / 2.0f);

            Vec3 point(1.0f, 0.0f, 0.0f);

            Vec3 result = mat.TransformPoint(point);

            Assert::AreEqual(0.0f, result.x(), 0.0001f);
            Assert::AreEqual(1.0f, result.y(), 0.0001f);
            Assert::AreEqual(0.0f, result.z(), 0.0001f);
        }


        // Multiplication

        TEST_METHOD(MatrixMultiplication)
        {
            Mat4x4 a = Mat4x4::Identity();

            Mat4x4 b =
                Mat4x4::Translation(
                    10.0f,
                    20.0f,
                    30.0f
                );

            Mat4x4 result = a * b;

            for (int row = 0; row < 4; ++row)
            {
                for (int column = 0; column < 4; ++column)
                {
                    Assert::AreEqual(
                        b.m[row][column],
                        result.m[row][column],
                        0.0001f
                    );
                }
            }
        }

        TEST_METHOD(MatrixMultiplicationTranslation)
        {
            Mat4x4 a =
                Mat4x4::Translation(
                    10.0f,
                    20.0f,
                    30.0f
                );

            Mat4x4 b =
                Mat4x4::Translation(
                    1.0f,
                    2.0f,
                    3.0f
                );

            Mat4x4 result = a * b;

            Assert::AreEqual(
                11.0f,
                result.m[0][3],
                0.0001f
            );

            Assert::AreEqual(
                22.0f,
                result.m[1][3],
                0.0001f
            );

            Assert::AreEqual(
                33.0f,
                result.m[2][3],
                0.0001f
            );
        }

        TEST_METHOD(MatrixMultiplicationIdentity)
        {
            Mat4x4 a =
                Mat4x4::Translation(
                    10.0f,
                    20.0f,
                    30.0f
                );

            Mat4x4 identity = Mat4x4::Identity();

            Mat4x4 result = a * identity;

            for (int row = 0; row < 4; ++row)
            {
                for (int column = 0; column < 4; ++column)
                {
                    Assert::AreEqual(
                        a.m[row][column],
                        result.m[row][column],
                        0.0001f
                    );
                }
            }
        }


        // TransformPoint

        TEST_METHOD(TransformPointIdentity)
        {
            Mat4x4 mat = Mat4x4::Identity();

            Vec3 point(1.0f, 2.0f, 3.0f);

            Vec3 result = mat.TransformPoint(point);

            Assert::AreEqual(1.0f, result.x());
            Assert::AreEqual(2.0f, result.y());
            Assert::AreEqual(3.0f, result.z());
        }

        TEST_METHOD(TransformPoint)
        {
            Mat4x4 mat;

            mat.m[0][0] = 2.0f;
            mat.m[1][1] = 3.0f;
            mat.m[2][2] = 4.0f;
            mat.m[3][3] = 1.0f;

            mat.m[0][3] = 10.0f;
            mat.m[1][3] = 20.0f;
            mat.m[2][3] = 30.0f;

            Vec3 point(1.0f, 2.0f, 3.0f);

            Vec3 result = mat.TransformPoint(point);

            Assert::AreEqual(12.0f, result.x());
            Assert::AreEqual(26.0f, result.y());
            Assert::AreEqual(42.0f, result.z());
        }


        // Composition transformation

        TEST_METHOD(TranslationThenRotation)
        {
            const float pi = 3.14159265358979323846f;

            Mat4x4 translation =
                Mat4x4::Translation(
                    10.0f,
                    0.0f,
                    0.0f
                );

            Mat4x4 rotation =
                Mat4x4::RotationZ(
                    pi / 2.0f
                );

            Mat4x4 transform = rotation * translation;

            Vec3 point(0.0f, 0.0f, 0.0f);

            Vec3 result =
                transform.TransformPoint(point);

            Assert::AreEqual(0.0f, result.x(), 0.0001f);
            Assert::AreEqual(10.0f, result.y(), 0.0001f);
            Assert::AreEqual(0.0f, result.z(), 0.0001f);
        }


        // Taille et alignement

        TEST_METHOD(Size)
        {
            Assert::AreEqual<size_t>(
                64,
                sizeof(Mat4x4)
            );
        }

        TEST_METHOD(Alignment)
        {
            Mat4x4 mat;

            auto address =
                reinterpret_cast<std::uintptr_t>(&mat);

            Assert::AreEqual<std::uintptr_t>(
                0,
                address % 16
            );
        }
    };
}