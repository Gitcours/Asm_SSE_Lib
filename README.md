# Bibliothèque mathématique C++ — SIMD et ASM

## 1. Présentation du projet

Ce projet consiste à développer une petite bibliothèque mathématique en C++20, avec pour objectif de comparer plusieurs façons d'effectuer des calculs sur des vecteurs et des points 3D.

Le but est de comprendre les différences de performances entre :
- une version de référence en C++ ;
- une version utilisant les instructions SIMD ;
- une fonction écrite en assembleur x64 ;
- deux organisations de données : AoS et SoA.

Le projet est réalisé avec Visual Studio et cible Windows x64.

## 2. Technologies utilisées

- C++20
- Visual Studio
- Assembleur x64 avec MASM
- Intrinsics SSE/SSE2
- NanoBench pour les benchmarks
- Projets de tests unitaires

## 3. Organisation du projet

```text
asm_math_lib/
├── ASM/
│   ├── DotVec3ASM.asm
│   └── DotVec3ASM.h
├── Benchmark/
├── Math/
│   ├── Batch.h
│   ├── BatchSOA.h
│   ├── BatchValidation.h
│   ├── Mat4x4.h
│   ├── Vec3.h
│   └── Vec4.h
├── SIMD/
│   ├── BatchSIMD.h
│   └── BatchSoASIMD.h
├── nanobench.cpp
├── rapport.md
└── readme.md

tests unitaires Mat4x4/
tests unitaires Vec3/
tests unitaires Vec4/
```

### Rôle des principaux fichiers

- **Vec3.h** : représente un vecteur 3D et contient ses opérations mathématiques.
- **Vec4.h** : représente un vecteur à quatre composantes.
- **Mat4x4.h** : contient les opérations sur les matrices 4×4.
- **Batch.h** : contient les traitements de référence en C++.
- **BatchSIMD.h** : contient les versions SIMD des traitements par lots.
- **BatchSOA.h** : contient la structure SoA, les conversions et le calcul de produit scalaire associé.
- **BatchSoASIMD.h** : contient la version SIMD du produit scalaire avec des données SoA.
- **BatchValidation.h** : contient les fonctions de validation des résultats.
- **DotVec3ASM.asm** : contient la fonction de produit scalaire en assembleur x64.
- **DotVec3ASM.h** : déclare la fonction assembleur pour pouvoir l'appeler depuis le C++.
- **nanobench.cpp** : lance les tests de validation et les benchmarks.

Les projets de tests unitaires sont séparés en trois parties : Vec3, Vec4 et Mat4x4.

## 4. Fonctionnalités

### Types mathématiques

La bibliothèque contient :
- des vecteurs 3D ;
- des vecteurs 4D ;
- des matrices 4×4 ;
- les opérations mathématiques associées, selon les fonctions implémentées.

### Traitements par lots

Trois traitements principaux sont étudiés :

1. **Produit scalaire** : calcule le produit scalaire entre deux tableaux de vecteurs.
2. **Normalisation** : normalise un tableau de vecteurs.
3. **Transformation de points** : applique une matrice affine 4×4 à un tableau de points 3D.

Chaque traitement possède une version de référence en C++ et une version SIMD.

Le produit scalaire dispose également :
- d'une version assembleur x64 ;
- d'une version de référence utilisant des données SoA ;
- d'une version SIMD utilisant des données SoA.

### Gestion des données

Deux organisations sont comparées :

- **AoS (Array of Structures)** : les composantes X, Y et Z sont regroupées dans chaque vecteur.
- **SoA (Structure of Arrays)** : les composantes X, Y et Z sont stockées dans des tableaux séparés.

Le projet contient également les fonctions de conversion entre ces deux organisations.

## 5. Compilation et exécution

### Prérequis

- Windows 64 bits
- Visual Studio avec les outils de développement C++
- Le support de MASM pour l'assembleur x64

### Étapes

1. Ouvrir la solution Visual Studio.
2. Sélectionner la configuration **Release**.
3. Sélectionner la plateforme **x64**.
4. Vérifier que `DotVec3ASM.asm` est bien configuré pour être assemblé avec MASM.
5. Compiler la solution.
6. Lancer le projet `asm_math_lib`.

Le programme principal se trouve dans `nanobench.cpp`.

## 6. Tests

Le projet contient des tests unitaires pour les vecteurs 3D, les vecteurs 4D et les matrices 4×4.

Le programme de benchmark vérifie également plusieurs cas pour la fonction assembleur, notamment :
- des valeurs positives ;
- des valeurs négatives ;
- un vecteur nul ;
- des valeurs décimales.

Les traitements par lots sont aussi comparés à leurs versions de référence afin de vérifier la cohérence des résultats.

Le nombre de tests validés doit être relevé après la dernière exécution complète des tests.

## 7. Benchmarks

Les mesures sont réalisées avec NanoBench.

Les tailles de lots utilisées sont :

- 64 éléments ;
- 256 éléments ;
- 1 024 éléments ;
- 4 096 éléments ;
- 16 384 éléments ;
- 65 536 éléments.

Les benchmarks couvrent :
- le produit scalaire ;
- la normalisation ;
- la transformation de points ;
- les conversions AoS vers SoA et SoA vers AoS.

Les temps mesurés sont affichés en nanosecondes par opération. Les résultats permettent de comparer les versions de référence, SIMD et assembleur lorsqu'elles sont disponibles.

Pour comparer correctement les performances, les mesures doivent être effectuées en Release x64, sans débogueur, dans des conditions similaires. Les résultats doivent être interprétés en tenant compte de leur stabilité et des éventuels coûts de conversion des données.

## 8. Résultats et limites

Les premières mesures montrent que les versions SIMD sont plus rapides que les versions de référence pour la normalisation et la transformation de points sur les tailles testées.

Pour le produit scalaire, la version SoA de référence obtient de meilleurs résultats que les versions AoS mesurées. Cela montre que l'organisation des données et les optimisations du compilateur peuvent avoir un effet important sur les performances.

La fonction assembleur de produit scalaire est plus lente dans le benchmark actuel. Elle est appelée une fois par vecteur, ce qui ajoute le coût des appels de fonction. Une fonction assembleur n'est donc pas automatiquement plus rapide qu'une boucle C++ ou SIMD traitant plusieurs éléments.

Les résultats dépendent notamment du processeur, du compilateur, des optimisations activées et des conditions de mesure.

Le profiling et l'analyse détaillée des instructions générées doivent compléter ces observations dans le rapport technique.

## 9. Rapport technique

Le fichier `rapport.md` présente l'analyse détaillée du projet, notamment :
- les choix d'implémentation ;
- l'organisation des données ;
- le protocole de benchmark ;
- les résultats et les comparaisons ;
- l'analyse du profiling ;
- les différences numériques et les limites observées.

Les captures du profiling et les extraits de désassemblage doivent être ajoutés au rapport lorsqu'ils auront été réalisés et analysés.

## 10. Sources et documentation

- Documentation Microsoft sur les intrinsics SSE/SSE2 : https://learn.microsoft.com/cpp/intrinsics/
- Documentation Microsoft sur MASM : https://learn.microsoft.com/cpp/assembler/masm/
- Dépôt NanoBench : https://github.com/martinus/nanobench

