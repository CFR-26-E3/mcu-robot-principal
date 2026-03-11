# Architecture du Code : Où placer son travail ?

Pour garder un code propre et maintenable, notre projet est séparé en trois couches distinctes. Chaque fichier doit être placé dans le bon dossier selon son rôle.

### 1. `App_Logic/` (Le Cerveau)
* **Rôle :** Contient toute l'intelligence et la logique métier du robot.
* **Quoi y mettre :** Les algorithmes, les calculs mathématiques (cinématique, odométrie), les machines à états et le traitement des données.
* **Règle d'or :** **Aucune dépendance matérielle ou système.** Il ne doit y avoir aucun appel aux fonctions de la carte (`HAL_...`) ni à FreeRTOS (`osDelay`, `xQueue...`). Ce code doit pouvoir être compilé et testé sur un simple PC.

### 2. `Drivers_Custom/` (Les Sens et les Muscles)
* **Rôle :** Faire le lien entre le microcontrôleur et les composants physiques (capteurs, moteurs, écrans).
* **Quoi y mettre :** Le code qui configure et interagit avec le matériel (I2C, SPI, UART, PWM).
* **Règle d'or :** Encapsuler la complexité. Le reste du projet ne doit pas savoir comment fonctionne un capteur, il doit juste appeler une fonction claire comme `CapteurDistance_Lire()` ou `Moteur_SetVitesse()`.

### 3. `Tasks/` (Le Chef d'Orchestre)
* **Rôle :** Gérer l'exécution en temps réel via FreeRTOS.
* **Quoi y mettre :** Les fonctions de tâches (les boucles `while(1)`), la gestion des délais (`osDelay`), des files d'attente (Queues) et des verrous (Mutex/Sémaphores).
Elles sont donc garantes de la protection des données partagées comme la `struct` de la pose du robot.
* **Règle d'or :** Les tâches lient le système. Elles lisent les données via `Drivers_Custom`, les envoient à `App_Logic` pour décider quoi faire, puis exécutent l'action de retour via `Drivers_Custom`. Elles ne doivent faire aucun calcul mathématique complexe.

---

**Flux de travail standard :**
`Tasks` lit une valeur via `Drivers_Custom` ➔ `Tasks` donne la valeur à `App_Logic` qui retourne une décision ➔ `Tasks` applique la décision via `Drivers_Custom`.