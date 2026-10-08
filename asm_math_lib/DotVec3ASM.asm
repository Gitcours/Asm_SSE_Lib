; ============================================================
; DotVec3ASM.asm
; ============================================================
;
; Fonction :
;
;     float DotVec3ASM(const Vec3& a, const Vec3& b)
;
; Calcule :
;
;     a.x * b.x
;   + a.y * b.y
;   + a.z * b.z
;
; Convention d'appel Windows x64 :
;
;     RCX = adresse de a
;     RDX = adresse de b
;
; Retour :
;
;     XMM0 = résultat float
;
; ============================================================

.code

PUBLIC DotVec3ASM

DotVec3ASM PROC

    ; --------------------------------------------------------
    ; Vec3 utilise un __m128.
    ;
    ; Dans Vec3 :
    ;
    ; v = [x, y, z, 0]
    ;
    ; Les 4 floats occupent donc 16 octets.
    ;
    ; a.v commence à [RCX]
    ; b.v commence à [RDX]
    ; --------------------------------------------------------

    ; Charger les 4 composantes de A
    movups xmm0, XMMWORD PTR [rcx]

    ; Charger les 4 composantes de B
    movups xmm1, XMMWORD PTR [rdx]

    ; Multiplier composante par composante
    ;
    ; xmm0 =
    ; [
    ;   ax * bx,
    ;   ay * by,
    ;   az * bz,
    ;   0
    ; ]
    mulps xmm0, xmm1

    ; Additionner x + y
    movaps xmm1, xmm0
    shufps xmm1, xmm1, 055h
    addss xmm0, xmm1

    ; Additionner z
    movaps xmm1, xmm0
    shufps xmm1, xmm1, 0AAh
    addss xmm0, xmm1

    ; Le résultat est dans XMM0
    ret

DotVec3ASM ENDP

END