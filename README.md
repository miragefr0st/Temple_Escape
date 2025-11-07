# Temple_Escape
## Behavior Tree

## **Branche BehaviorTreeTest** par Marcus
Dans cette branche les exercices relatifs à l'IA se trouve dans le dossier **Maps > BlazingGear**, il contient :
- **BehaviorTreeLvl** : level pour tester l'IA
- **BP_EnemyIA** : le character ennemi
- **AIC_EnemyBase** : l'IA Controller de l'ennemi muni d'un Perception IA Component
- **BP_PatrolRoute** : une spline que devra suivre l'IA
- **BPI_EnemyIA** : un interface qui m'évite de caster directement vers BP_EnemyIA car on aprévu different types d'ennemi.
- **E_EnumSpeed** : une énumération pour les différentes vitesse de déplacement de l'IA
- **E_Sense** : une énumération pour les différentes type de sense pour la perception de l'IA (hearing, sight, dammage)
- **BehaviorTree** : un dossier contenant
    - **BT_EnemyBase** : le behavior tree de l'ennemi
    - **BB_EnemyBase** : le blackboard associé au behavior tree
    - **Decorator** : un dossier contenant les decorateur du behavior tree (juste un pour le moment qui verifie si l'IA possede un spline)
    - **Task** : dossier contenant les tâches du behavior tree, un pour suivre la spline et un pour changer la vitesse de l'IA

*Remarque : j'ai pas pu detaillé le contenu des blueprint car je n'ai plus d'espace pour installer UE 5.6*
  
## **Branche Mattys** par Mattys (celle utilisé pendant la présentation)

Sur cette branche, j’ai implémenté une IA de type Mecha utilisant un Behavior Tree avec un système de states géré par un Blackboard et un Enum.
L’IA possède deux états principaux :

**1. Patrol / Idle State**
L’IA attend ou patrouille en choisissant un point aléatoire dans la zone.
Avant chaque déplacement, elle clear son focus pour éviter les conflits.
Le point de destination est obtenu via le Blueprint BP_FlyingZone, qui fournit une position aléatoire dans la map.
Ce comportement est géré par la task Patrol.

**2. Chase Player State**
Lorsqu’un joueur entre dans la sphère de détection (vision), l’IA change d’état vers Chase.
Elle clear son focus, puis set le focus sur le joueur et se met à le poursuivre.
Une fois la distance d’attaque atteinte, elle exécute la task Attack.


*Le changement d’état entre Patrol et Chase est contrôlé par la détection du joueur dans la sphère de vision.*

Les tasks principales du Behavior Tree sont :
- ClearFocus
- SetFocus
- Patrol
- Attack

Les Blueprints utilisés sont :
- **BP_Mecha** : gère l’apparence du robot et ses composants d’IA.
- **IAC_Mecha** : le AI Controller contenant la logique du Behavior Tree et la gestion du Blackboard.
- **BP_FlyingZone** : détermine un point aléatoire dans la zone de patrouille.


## **Branche EventDispatcher_Caleb** par Caleb
J'ai réutiliser la branche où j'ai réalisé les exercices sur les events dispatcher.
Vous pouvez retrouver les blueprints relatifs à l'IA que j'ai réalisé dans content/blueprint/IA.
J'ai également modifier le bp_thirdpersoncharacter d'unreal pour ajouter le crouch et le component AIPerception StimulusSource.


## **Branche Mamitiana**
### Objectif 
Mettre en place une IA de base dans *Unreal Engine 5* à l’aide d’un Behavior Tree et d’un Blackboard, pour lui permettre de patrouiller, détecter le joueur et réagir dynamiquement à son environnement.

## Fonctionnalités principales

### Structure AI
- Création d’un Behavior Tree (`BT_Enemy`)
- Création d’un Blackboard (`BB_Enemy`) avec les clés :
  - `TargetActor` → le joueur à poursuivre  
  - `TargetLocation` → position actuelle de la cible  
  - `PatrolIndex` → point de patrouille actif  

### AI Controller
- Lancement du Behavior Tree au `BeginPlay`  
- Mise à jour automatique du Blackboard  
- Gestion de la perception du joueur (via Pawn Sensing)  

### Logique du Behavior Tree
```plaintext
Root
└── Selector
    ├── Sequence (Chase)
    │   ├── Condition: Has TargetActor
    │   ├── Task: Set State (Chasing)
    │   └── Task: Move To (TargetActor)
    ├── Sequence (Patrol)
    │   ├── Condition: No TargetActor
    │   ├── Task: Move To (Next Patrol Point)
    │   └── Task: Wait (Random Delay)
    └── Task: Idle
```

### Blueprint Tasks personnalisées
- Move To Location → déplace l’IA vers un point défini  
- Set State → met à jour l’état interne (chasse, patrouille, idle)  
- Wait → ajoute un délai aléatoire entre les mouvements  

---

## Résultat
L’IA est désormais capable de :
- Patrouiller entre plusieurs points définis  
- Détecter et poursuivre le joueur lorsqu’il entre dans le champ de vision  
- Revenir en patrouille si le joueur s’échappe  

---

## Améliorations possibles
- Ajouter des comportements avancés : embuscade.  
- Intégrer un système de perception visuelle et auditive plus réaliste.  
- Optimiser la structure du Behavior Tree pour gérer plusieurs types d’ennemis.  

---
