# Simulation de Firmware IoT en C

Simulation d’un firmware IoT minimaliste modélisant une machine à états finis (FSM) et le comportement d’une LED système en fonction de l’état opérationnel.

## 1. Objectif

Ce projet illustre les bases d’un firmware embarqué :

- gestion d’états système (`STARTUP`, `NORMAL`, `WARNING`, `ERROR`) ;
- transitions d’état pilotées dans le temps ;
- rendu visuel d’un signal LED dans un terminal ;
- structuration d’une boucle principale temps-réel simplifiée.

## 2. Portée scientifique et pédagogique

Le programme met en œuvre une abstraction classique en systèmes embarqués :

- **Temps discret** : 1 tick = 100 ms ;
- **Automate fini** : transitions déterministes entre états ;
- **Signalisation d’état** : codage visuel par motifs de clignotement.

Ce modèle est utile pour l’enseignement de la logique firmware sans dépendance matérielle.

## 3. Architecture logicielle

Le cœur du projet est implémenté dans `main.c` :

- `SystemState` : énumération des états ;
- `currentState` : état courant global ;
- `globalTick` : compteur de ticks ;
- `getStateName()` : conversion état → chaîne affichable ;
- boucle principale :
  1. logique de transition d’état ;
  2. logique LED par état ;
  3. affichage console ;
  4. temporisation (`SLEEP_MS(100)`).

## 4. Comportement système

### États et intention de comportement LED

| État      | Rôle opérationnel                      | Motif LED |
|-----------|-----------------------------------------|-----------|
| STARTUP   | Initialisation système                  | 3 clignotements rapides puis passage à `NORMAL` |
| NORMAL    | Fonctionnement nominal                  | Clignotement lent régulier |
| WARNING   | Dégradation / alerte                    | Clignotement rapide continu |
| ERROR     | Défaut critique                         | 2 clignotements rapides puis pause |

### Dynamique temporelle

- Pas de temps : `Δt = 100 ms` ;
- Cycle de transition principal : `100 ticks` (10 s) ;
- Chaîne de transitions : `STARTUP → NORMAL → WARNING → ERROR → NORMAL → ...`

## 5. Compilation et exécution

### Prérequis

- GCC (ou compilateur C compatible C99)
- `make`

### Commandes principales

```bash
make          # Compile le binaire iot_simulation
make run      # Compile puis exécute
make clean    # Nettoie les artefacts
make debug    # Build debug (-g -DDEBUG)
make help     # Liste des cibles disponibles
```

## 6. Sortie attendue

Le programme affiche en continu :

- le temps discret (`globalTick`) ;
- l’état courant ;
- l’état LED (`(O)` allumée, `.` éteinte).

Exemple :

```text
[ Tps:   123 ] [ ETAT: WARNING ]  LED: (O)
```

## 7. Limites actuelles

- Simulation purement console (pas d’interface matérielle réelle) ;
- état global partagé (pas d’encapsulation avancée) ;
- pas de tests automatisés inclus dans le dépôt.

## 8. Perspectives d’évolution

- ajout de tests unitaires pour la logique de transition ;
- paramétrage des périodes de clignotement (fichier de configuration) ;
- journalisation structurée (CSV/JSON) ;
- portage vers microcontrôleur (HAL, timers matériels, GPIO).

## 9. Licence

Ce projet est distribué sous licence **MIT** (voir `LICENSE`).

## 10. Auteur

**YEVI Samuel**  
© 2025
