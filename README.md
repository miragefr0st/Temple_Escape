# Temple_Escape
## Behavior Tree

### **Branche BehaviorTreeTest** par Marcus
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
  
### **Branche Mattys** par Mathis (celle utilisé pendant la présentation)
*...sera compléter plus tard par Mathis*
