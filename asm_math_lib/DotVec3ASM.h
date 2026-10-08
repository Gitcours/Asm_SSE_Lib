#pragma once

class Vec3;

// ============================================================
// DOT PRODUCT - IMPLEMENTATION ASM x64
// ============================================================
//
// Calcule :
//
// A.x * B.x
// +
// A.y * B.y
// +
// A.z * B.z
//
// La fonction est implémentée en assembleur x64
// et appelée depuis le C++.
// ============================================================

extern "C" float DotVec3ASM(
    const Vec3& a,
    const Vec3& b
);