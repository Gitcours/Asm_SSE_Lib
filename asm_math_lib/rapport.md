# Bibliothèque mathématique C++ — Optimisation SIMD et assembleur

## 1. Présentation du projet

Ce projet consiste à développer une bibliothèque mathématique en C++20, puis à étudier différentes façons d'optimiser les calculs grâce aux instructions SIMD et à l'assembleur x64.

L'objectif est de comparer une version de référence en C++ avec des versions optimisées, en vérifiant leur exactitude et en mesurant leurs performances.

Le projet est développé sous Windows avec Visual Studio, en configuration Release x64.

Les trois traitements principaux étudiés sont :
- Le produit scalaire entre plusieurs paires de vecteurs.
- La normalisation de plusieurs vecteurs.
- La transformation de plusieurs points 3D par une matrice 4×4.

Une fonction de produit scalaire en assembleur x64 a également été développée et testée.

## 2. Organisation du projet

Le projet principal `asm_math_lib` contient les fichiers mathématiques, les fonctions SIMD, la fonction assembleur et le programme de benchmark. Trois projets supplémentaires permettent de séparer les tests unitaires des vecteurs et des matrices.

![Structure de la solution Visual Studio](Images/1.png)

L'organisation principale est la suivante :

- `ASM/` : fonction assembleur et déclaration C++.
- `Math/` : types mathématiques, traitements de référence et fonctions de validation.
- `SIMD/` : versions optimisées des traitements par lots.
- `Benchmark/` : contient `nanobench.cpp`, le programme de validation et de benchmark.
- `tests unitaires Vec3` : tests des vecteurs 3D.
- `tests unitaires Vec4` : tests des vecteurs 4D.
- `tests unitaires Mat4x4` : tests des matrices 4×4.
- `readme.md` : instructions de compilation et d'utilisation.
- `rapport.md` : analyse technique et résultats du projet.

Les fonctions de référence servent de base de comparaison pour les versions optimisées.

## 3. Base mathématique et conventions

La bibliothèque utilise des vecteurs 3D (`Vec3`), des vecteurs 4D (`Vec4`) et des matrices 4×4 (`Mat4x4`).

Le type `Vec3` est aligné sur 16 octets et utilise un registre `__m128` pour stocker ses trois coordonnées. La quatrième composante est inutilisée pour les calculs 3D.

Cette organisation permet d'utiliser les instructions SSE sur les données des vecteurs. Elle implique cependant que les conventions de stockage et les opérations doivent rester cohérentes entre les différentes implémentations.

Les calculs flottants ne garantissent pas toujours des résultats strictement identiques bit à bit. Les tests utilisent donc une tolérance numérique pour comparer les résultats.

Pour la transformation des points, la convention utilisée est celle d'une transformation affine avec une coordonnée homogène `w = 1`, sans division perspective.

## 4. Méthodologie

### 4.1 Versions comparées

Pour chaque traitement, plusieurs implémentations sont étudiées :

- **Référence C++** : version servant de base de comparaison.
- **SIMD SSE** : version utilisant explicitement des instructions SIMD.
- **SoA** : pour le produit scalaire, les coordonnées sont stockées dans trois tableaux séparés.
- **ASM x64** : fonction assembleur dédiée au produit scalaire de deux vecteurs.

La comparaison doit prendre en compte les performances, la précision des résultats, la taille des lots et les éventuels coûts de conversion des données.

### 4.2 Protocole de benchmark

Le programme de benchmark utilise la bibliothèque NanoBench. Les données sont générées de manière déterministe afin de rendre les essais reproductibles.

La configuration utilisée pour les mesures enregistrées est :

- Compilation : Release x64.
- Échauffement : 3 passages.
- Nombre minimal d'itérations NanoBench : 1 200 dans les mesures enregistrées. Une exécution a toutefois montré une variabilité plus élevée pour certaines variantes ; il faudra augmenter ce paramètre et relancer les mesures concernées pour confirmer leur stabilité.
- Tailles de lots prévues : 64, 256, 1 024, 4 096, 16 384 et 65 536 éléments.

Les données sont préparées avant les mesures des traitements. Les résultats sont écrits dans des tableaux de sortie afin que les calculs ne soient pas simplement ignorés par le compilateur.

Les conversions AoS vers SoA et SoA vers AoS sont mesurées séparément. La conversion AoS vers SoA utilisée dans le benchmark ne réalise pas de nouvelle allocation pendant la mesure.

Les tableaux ci-dessous regroupent les mesures disponibles pour les six tailles de lots. Pour le produit scalaire, plusieurs exécutions à 65 536 éléments ont donné des résultats différents, notamment pour les variantes AoS ; les chiffres sont donc à lire comme des mesures observées et non comme des valeurs absolues. Les performances dépendent du processeur, du compilateur, de la charge système et des optimisations activées.

## 5. Résultats des benchmarks

Les durées sont exprimées en nanosecondes par exécution du traitement complet sur le lot indiqué. Les mesures ont été réalisées en Release x64. Elles correspondent à cette machine et à ces conditions de test : elles ne sont pas universelles.

### 5.1 Produit scalaire

| Taille du lot | AoS référence (ns) | AoS SIMD (ns) | ASM (ns) | SoA référence (ns) | SoA SIMD (ns) |
|---:|---:|---:|---:|---:|---:|
| 64 | 44,50 | 27,18 | 85,00 | 14,82 | 21,46 |
| 256 | 179,20 | 110,07 | 346,27 | 46,42 | 84,95 |
| 1 024 | 711,74 | 422,99 | 1 347,40 | 180,14 | 311,37 |
| 4 096 | 2 804,05 | 1 747,90 | 5 533,25 | 822,02 | 1 385,29 |
| 16 384 | 11 324,96 | 6 767,05 | 21 881,43 | 3 404,95 | 5 605,59 |
| 65 536 | 37 367,39 | 22 793,33 | 77 418,21 | 15 070,25 | 19 392,95 |

Pour le dernier relevé à 65 536 éléments, la version AoS SIMD est environ **1,64 fois plus rapide** que la référence AoS, soit une réduction du temps mesuré d'environ 39 %. La référence SoA est environ **2,48 fois plus rapide** que la référence AoS et obtient le meilleur temps parmi les variantes du produit scalaire présentées ici. La version SoA SIMD est environ 1,93 fois plus rapide que la référence AoS, mais reste plus lente que la référence SoA.

La fonction ASM est plus lente que la référence AoS dans ces mesures : son temps est environ 2,07 fois supérieur à celui de la référence AoS pour 65 536 éléments. Elle est appelée individuellement pour chaque paire de vecteurs ; le coût des appels répétés peut annuler le bénéfice des instructions SSE utilisées à l'intérieur de la fonction.

Une autre exécution à 65 536 éléments a produit des valeurs différentes, notamment pour les variantes AoS. L'erreur relative affichée par NanoBench atteignait environ 3,7 à 4,4 % pour ces deux mesures dans le dernier relevé. Il est donc préférable de relancer les mesures AoS avec davantage d'itérations minimales et une charge système aussi stable que possible avant de considérer les différences faibles comme définitives.

Ces résultats illustrent aussi que l'organisation des données peut avoir un effet majeur. La référence SoA peut être très efficace, notamment parce que les données sont organisées par composante et que le compilateur peut optimiser la boucle. L'utilisation explicite des intrinsics SIMD ne garantit pas automatiquement le meilleur temps : le C++ de référence peut lui aussi bénéficier de la vectorisation automatique du compilateur.

### 5.2 Normalisation

| Taille du lot | Référence (ns) | SIMD (ns) | Accélération approximative |
|---:|---:|---:|---:|
| 64 | 210,03 | 82,04 | 2,56× |
| 256 | 843,85 | 328,33 | 2,57× |
| 1 024 | 3 402,65 | 1 312,03 | 2,59× |
| 4 096 | 13 593,51 | 5 256,91 | 2,59× |
| 16 384 | 54 463,00 | 21 502,77 | 2,53× |
| 65 536 | 218 541,59 | 86 137,58 | 2,54× |

Sur les mesures disponibles, la version SIMD est environ **2,5 à 2,6 fois plus rapide** que la référence selon la taille du lot. À 65 536 éléments, le temps passe d'environ 218 542 ns à 86 138 ns.

Cette amélioration s'explique par l'utilisation d'opérations vectorielles pour effectuer plusieurs étapes du calcul dans des registres SIMD. La normalisation SIMD utilise une approximation de l'inverse de la racine carrée suivie d'une étape de raffinement. Cette approche peut être plus rapide qu'un calcul scalaire classique, mais elle peut produire de légères différences numériques. Il est donc important de conserver les tests de précision et de vérifier le comportement des vecteurs nuls.

### 5.3 Transformation des points

| Taille du lot | Référence (ns) | SIMD (ns) | Accélération approximative |
|---:|---:|---:|---:|
| 64 | 109,57 | 48,94 | 2,24× |
| 256 | 453,99 | 188,75 | 2,41× |
| 1 024 | 1 813,61 | 745,03 | 2,43× |
| 4 096 | 7 066,64 | 2 882,92 | 2,45× |
| 16 384 | 28 068,45 | 11 620,66 | 2,42× |
| 65 536 | 114 668,57 | 47 337,00 | 2,42× |

La version SIMD est environ **2,2 à 2,5 fois plus rapide** que la référence sur les tailles mesurées. À 65 536 éléments, le temps mesuré est réduit d'environ 114 669 ns à 47 337 ns.

Ce traitement implique plusieurs multiplications et additions pour chaque point. Les instructions SIMD permettent de regrouper certaines opérations et de réduire le coût du calcul. La transformation doit néanmoins respecter exactement les mêmes conventions mathématiques dans les deux versions, notamment pour la matrice utilisée et la coordonnée homogène `w = 1`.

### 5.4 Conversion entre AoS et SoA

Pour un lot de 65 536 éléments, le dernier relevé donne :

| Opération | Temps mesuré |
|---|---:|
| AoS vers SoA | 39 288,00 ns |
| SoA vers AoS | 37 063,84 ns |
| **Total aller-retour** | **76 351,84 ns** |

Ces mesures montrent que les conversions ont elles-mêmes un coût important. Le temps de conversion AoS vers SoA seul est environ 2,61 fois supérieur au temps de calcul du produit scalaire SoA de référence mesuré sur le même lot (15 070,25 ns). Une conversion aller-retour complète coûte donc davantage que le calcul du produit scalaire SoA seul.

Il ne suffit pas de constater qu'une opération est rapide en SoA. Il faut aussi prendre en compte le temps nécessaire pour convertir les données si le reste du programme utilise un stockage AoS. Pour une utilisation ponctuelle, le coût de conversion peut réduire ou annuler le bénéfice obtenu. En revanche, si plusieurs traitements exploitent les mêmes données en SoA, ce coût peut être amorti.

### 5.5 Fonction assembleur

Une fonction `DotVec3ASM` a été développée en assembleur x64. Elle reçoit les adresses de deux vecteurs et retourne leur produit scalaire dans le registre de retour flottant `XMM0`. La fonction a été intégrée au projet Visual Studio à l'aide de MASM. Son intégration a été vérifiée lors de la compilation et de l'édition des liens.

Pour un lot de 65 536 éléments, le dernier benchmark a mesuré **77 418,21 ns** pour la variante ASM. Cette valeur est nettement supérieure aux 22 793,33 ns de la variante AoS SIMD et aux 37 367,39 ns de la référence AoS lors de cette même campagne. Cette comparaison porte sur la fonction ASM appelée de manière répétée pour chaque paire de vecteurs, et non sur une fonction assembleur qui traiterait tout le lot en un seul appel.

La validation comprend quatre cas :
- Valeurs positives : résultat attendu de 32.
- Valeurs négatives : résultat attendu de -32.
- Vecteur nul : résultat attendu de 0.
- Valeurs décimales : résultat attendu de -10,25.

Les quatre cas ont réussi. L'assembleur permet de contrôler précisément les instructions utilisées, mais il ne garantit pas à lui seul une meilleure performance. Le coût des appels répétés et les optimisations déjà appliquées au C++ doivent être pris en compte.

## 6. Analyse du profiling CPU

Le profiling a été effectué dans Visual Studio sur les trois traitements. Il permet d'observer quelles fonctions consomment le plus de temps processeur pendant l'exécution.

Les pourcentages ci-dessous correspondent aux profils enregistrés. Ils décrivent la répartition du temps CPU observé dans chaque session et ne constituent pas, à eux seuls, une comparaison absolue des performances entre deux versions.

### 6.1 Profiling de la normalisation

![Profiling CPU de la normalisation](Images/2.png)

Dans cette session, les résultats indiquent :

| Fonction | Part du temps processeur |
|---|---:|
| `Math::NormalizeBatchReference` | 71,59 % |
| `Math::NormalizeBatchSIMD` | 28,19 % |

La version de référence représente la plus grande part du temps processeur mesuré. La version SIMD consomme une part plus faible.

Cette observation est cohérente avec les benchmarks, dans lesquels la version SIMD est plus rapide. Le profiling permet de confirmer que la normalisation de référence représente une part importante du travail effectué pendant cette session.

Les pourcentages dépendent toutefois des données, du nombre d'itérations et de la session de profiling. Ils ne doivent pas être interprétés directement comme un facteur d'accélération.

### 6.2 Profiling du produit scalaire

![Profiling CPU du produit scalaire](Images/3.png)

Dans la session enregistrée, les principales fonctions identifiées comprennent :

| Fonction | Part du temps processeur |
|---|---:|
| `DotVec3ASM` | 21,38 % |
| `Math::ConvertAoSToSoA_NoAlloc` | 16,07 % |
| `Math::DotBatchReference` | 14,45 % |
| `Math::DotBatchSIMD` | 9,19 % |
| `Math::DotBatchSoASIMD` | 7,68 % |
| `Math::DotBatchSoAReference` | 6,16 % |

La fonction assembleur et la conversion AoS vers SoA apparaissent parmi les fonctions qui consomment le plus de temps dans cette session.

Le coût de conversion est donc un élément important à prendre en compte. Il peut représenter une part significative du travail effectué, même si les calculs en SoA sont efficaces.

La fonction ASM est appelée dans une boucle qui traite les vecteurs individuellement. Son coût inclut donc les appels répétés. Le fait qu'elle utilise des instructions SSE ne signifie pas nécessairement qu'elle sera plus rapide qu'une implémentation par lots.

Les résultats du profiling ne suffisent pas à classer les fonctions par efficacité intrinsèque : il faut aussi considérer le nombre d'appels, le volume de données et les mesures NanoBench.

### 6.3 Profiling de la transformation

![Profiling CPU de la transformation des points](Images/4.png)

Dans cette session, les résultats sont les suivants :

| Fonction | Part du temps processeur |
|---|---:|
| `Math::TransformPointsBatchReference` | 69,29 % |
| `Math::TransformPointsBatchSIMD` | 30,21 % |

La version de référence représente la majorité du temps CPU mesuré. La version SIMD représente une part plus faible.

Cette observation correspond aux mesures de benchmark, où la version SIMD est environ 2,43 fois plus rapide sur un lot de 65 536 éléments.

Le profiling confirme que les deux implémentations constituent l'essentiel du calcul observé dans cette session.

### 6.4 Conclusion du profiling

Le profiling a permis d'identifier les principales fonctions impliquées dans les traitements et de mieux comprendre où le temps processeur est consommé.

Les trois profils montrent que les versions de référence occupent une part importante du temps mesuré. Le profil du produit scalaire met également en évidence le coût de la fonction ASM et des conversions de données.

Le profiling et le benchmark sont complémentaires : le premier aide à localiser le travail effectué, tandis que le second permet de comparer les durées d'exécution dans des conditions contrôlées.

## 7. Analyse du désassemblage

Le désassemblage permet d'observer les instructions machine réellement générées ou exécutées.

### 7.1 Produit scalaire de référence

![Désassemblage du produit scalaire de référence](Images/5.png)

La version de référence est écrite en C++, mais le compilateur génère des instructions machine adaptées à la cible x64.

Le code désassemblé montre notamment des chargements de données et des instructions SSE. Cela illustre le fait que du code C++ classique peut déjà bénéficier d'optimisations du compilateur.

La comparaison ne doit donc pas opposer simplement du C++ à du SIMD : elle doit comparer le C++ optimisé avec la version utilisant explicitement les intrinsics SIMD.

### 7.2 Produit scalaire SIMD

![Désassemblage du produit scalaire SIMD](Images/6.png)

La version SIMD utilise des registres vectoriels pour effectuer des opérations sur plusieurs composantes.

Le code désassemblé montre des instructions de déplacement de données vectorielles et des instructions de mélange (`shufps`) qui servent à réorganiser les composantes.

Le compilateur peut également générer des instructions supplémentaires pour organiser les données ou traiter les derniers éléments d'un lot.

Le désassemblage permet ainsi de mieux comprendre le fonctionnement de l'implémentation et de vérifier que les instructions vectorielles attendues sont bien présentes.

## 8. Tests et validation

Les tests ont été utilisés pour vérifier les résultats mathématiques et comparer les versions de référence et les versions SIMD.

La validation des traitements par lots a atteint **144 tests réussis sur 144** lors de la dernière exécution enregistrée.

Les tests couvrent notamment :
- Les valeurs positives et négatives.
- Les vecteurs nuls.
- Les valeurs décimales.
- Les lots vides et les petites tailles.
- Les cas où la taille du lot n'est pas un multiple de la largeur SIMD.
- La comparaison entre les résultats de référence et les résultats optimisés.
- Les transformations de points avec les conventions prévues.

La fonction assembleur a également passé ses quatre cas de validation.

Les tests sont importants car deux versions peuvent donner des performances différentes tout en devant respecter les mêmes conventions mathématiques. Une différence flottante limitée peut être acceptable, mais une erreur de calcul ou un accès mémoire invalide ne l'est pas.

## 9. Limites du projet

Plusieurs limites doivent être prises en compte dans l'interprétation des résultats.

Premièrement, les mesures ont été effectuées sur une configuration matérielle et logicielle particulière. Les performances peuvent varier selon le processeur, le compilateur et les paramètres de compilation.

Deuxièmement, les mesures présentées pour le lot de 65 536 éléments ne suffisent pas à déterminer quelle implémentation est la meilleure pour toutes les tailles. Les petits lots peuvent notamment être davantage affectés par le coût d'appel des fonctions et par la préparation des données.

Troisièmement, l'organisation SoA implique des conversions lorsqu'elle est utilisée avec des données initialement stockées en AoS. Ces conversions doivent être incluses dans une comparaison de bout en bout.

Enfin, les instructions SIMD et les approximations numériques peuvent introduire de petites différences dans les résultats flottants. Les tolérances doivent être justifiées et les cas limites doivent rester testés.

## 10. Conclusion

Ce projet m'a permis de comparer plusieurs approches d'optimisation de calculs mathématiques en C++.

Les mesures réalisées sur six tailles de lots montrent des gains réguliers pour les versions SIMD de la normalisation et de la transformation des points. Pour le produit scalaire, la variante AoS SIMD est plus rapide que la référence AoS, mais la référence SoA obtient le meilleur temps parmi les variantes présentées. La variante ASM appelée une fois par paire de vecteurs est plus lente dans cette configuration, ce qui souligne l'importance du coût d'appel et du traitement par lots.

Le profiling a permis d'identifier les fonctions les plus sollicitées pendant les tests, tandis que le désassemblage a aidé à comprendre les instructions générées par le compilateur et celles utilisées dans l'implémentation SIMD.

La fonction assembleur a été intégrée et validée sur plusieurs cas de test. Les résultats rappellent cependant qu'une optimisation doit être évaluée dans son contexte : les appels de fonctions, les conversions mémoire et la taille des lots peuvent influencer les performances.

La principale conclusion est qu'il ne suffit pas d'utiliser des instructions SIMD ou de l'assembleur pour obtenir automatiquement un meilleur résultat. Il faut mesurer, vérifier la précision, comprendre le code généré et choisir une organisation des données adaptée au traitement.

## 11. Sources et outils

- C++20 et Visual Studio.
- Instructions SIMD SSE et intrinsics Microsoft.
- Assembleur x64 avec MASM.
- NanoBench pour les benchmarks.
- Outils de diagnostic et de profiling CPU de Visual Studio.
- Documentation Microsoft Learn sur les intrinsics et l'assembleur x64.
