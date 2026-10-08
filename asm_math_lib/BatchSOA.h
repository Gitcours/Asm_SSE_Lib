#pragma once

#include "Vec3.h"

#include <cstddef>
#include <vector>

namespace Math
{
    // ============================================================
    // STRUCTURE SOA
    // ============================================================
    //
    // AoS :
    //
    // Vec3 = [x,y,z]
    // Vec3 = [x,y,z]
    // Vec3 = [x,y,z]
    //
    // SoA :
    //
    // X = [x0,x1,x2,x3,...]
    // Y = [y0,y1,y2,y3,...]
    // Z = [z0,z1,z2,z3,...]
    //
    // Cela permet de charger directement plusieurs valeurs
    // d'une même composante dans un registre SIMD.
    // ============================================================

    struct Vec3SoA
    {
        std::vector<float> x;
        std::vector<float> y;
        std::vector<float> z;

        void resize(std::size_t count)
        {
            x.resize(count);
            y.resize(count);
            z.resize(count);
        }

        std::size_t size() const
        {
            return x.size();
        }
    };


    // ============================================================
    // CONVERSION AoS -> SoA
    // ============================================================
    //
    // Version normale :
    // - redimensionne les tableaux
    // - copie les données
    //
    // Cette fonction est utilisée pour préparer les données
    // avant les benchmarks.
    // ============================================================

    inline void ConvertAoSToSoA(
        const Vec3* input,
        Vec3SoA& output,
        std::size_t count)
    {
        output.resize(count);

        for (std::size_t i = 0; i < count; ++i)
        {
            output.x[i] = input[i].x();
            output.y[i] = input[i].y();
            output.z[i] = input[i].z();
        }
    }


    // ============================================================
    // CONVERSION AoS -> SoA SANS ALLOCATION
    // ============================================================
    //
    // IMPORTANT POUR LES BENCHMARKS :
    //
    // Les tableaux de sortie doivent déjà avoir la bonne taille.
    //
    // Cette fonction mesure uniquement le coût de la conversion
    // des données et pas celui d'une éventuelle allocation mémoire.
    // ============================================================

    inline void ConvertAoSToSoA_NoAlloc(
        const Vec3* input,
        Vec3SoA& output,
        std::size_t count)
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            output.x[i] = input[i].x();
            output.y[i] = input[i].y();
            output.z[i] = input[i].z();
        }
    }


    // ============================================================
    // CONVERSION SoA -> AoS
    // ============================================================

    inline void ConvertSoAToAoS(
        const Vec3SoA& input,
        Vec3* output,
        std::size_t count)
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            output[i] = Vec3(
                input.x[i],
                input.y[i],
                input.z[i]
            );
        }
    }


    // ============================================================
    // DOT PRODUCT SoA - VERSION DE REFERENCE
    // ============================================================

    inline void DotBatchSoAReference(
        const Vec3SoA& a,
        const Vec3SoA& b,
        float* results,
        std::size_t count)
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            results[i] =
                a.x[i] * b.x[i] +
                a.y[i] * b.y[i] +
                a.z[i] * b.z[i];
        }
    }
}