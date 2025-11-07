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
  
## **Branche Mattys** par Mathis (celle utilisé pendant la présentation)
*...sera compléter plus tard par Mathis*

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
