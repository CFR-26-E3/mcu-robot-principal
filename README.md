# Architecture du Code : Où placer son travail ?

Pour garder un code propre et maintenable, notre projet est séparé en trois couches distinctes. Chaque fichier doit être
placé dans le bon dossier selon son rôle.

### 1. `App_Logic/` (Le Cerveau)

* **Rôle :** Contient toute l'intelligence et la logique métier du robot.
* **Quoi y mettre :** Les algorithmes, les calculs mathématiques (cinématique, odométrie), les machines à états et le
  traitement des données.
* **Règle d'or :** **Aucune dépendance matérielle ou système.** Il ne doit y avoir aucun appel aux fonctions de la
  carte (`HAL_...`) ni à FreeRTOS (`osDelay`, `xQueue...`). Ce code doit pouvoir être compilé et testé sur un simple PC.

### 2. `Drivers_Custom/` (Les Sens et les Muscles)

* **Rôle :** Faire le lien entre le microcontrôleur et les composants physiques (capteurs, moteurs, écrans).
* **Quoi y mettre :** Le code qui configure et interagit avec le matériel (I2C, SPI, UART, PWM).
* **Règle d'or :** Encapsuler la complexité. Le reste du projet ne doit pas savoir comment fonctionne un capteur, il
  doit juste appeler une fonction claire comme `CapteurDistance_Lire()` ou `Moteur_SetVitesse()`.

### 3. `Tasks/` (Le Chef d'Orchestre)

* **Rôle :** Gérer l'exécution en temps réel via FreeRTOS.
* **Quoi y mettre :** Les fonctions de tâches (les boucles `while(1)`), la gestion des délais (`osDelay`), des files
  d'attente (Queues) et des verrous (Mutex/Sémaphores).
  Elles sont donc garantes de la protection des données partagées comme la `struct` de la pose du robot.
* **Règle d'or :** Les tâches lient le système. Elles lisent les données via `Drivers_Custom`, les envoient à
  `App_Logic` pour décider quoi faire, puis exécutent l'action de retour via `Drivers_Custom`. Elles ne doivent faire
  aucun calcul mathématique complexe.

---

**Flux de travail standard :**
`Tasks` lit une valeur via `Drivers_Custom` ➔ `Tasks` donne la valeur à `App_Logic` qui retourne une décision ➔ `Tasks`
applique la décision via `Drivers_Custom`.

# Configuration des pins (PINOUT)

### Configuration du Mapping des Pins

| Pin      | Nom du Signal    |
|:---------|:-----------------|
| **PB14** | PWMA_PAP_RAIL    |
| **PB15** | PWMB_PAP_RAIL    |
| **PC08** | PWM_LEVAGE1      |
| **PC09** | PWM_ROUE_GAUCHE  |
| **PC07** | PWM_ROUE_DROITE  |
| **PA08** | PWM_SERRAGE1     |
| **PA09** | PWM_SERRAGE2     |
| **PA10** | PWM_RETOURNE1    |
| **PA11** | PWM_RETOURNE2    |
| **PB07** | ENCA_ROUE_GAUCHE |
| **PB06** | ENCB_ROUE_GAUCHE |
| **PA07** | ENCA_ROUE_DROITE |
| **PA06** | ENCB_ROUE_DROITE |
| **PA00** | ENCA_LEVAGE1     |
| **PA01** | ENCB_LEVAGE1     |
| **PC05** | DIRB_ROUE_DROITE |
| **PC04** | DIRA_ROUE_DROITE |
| **PB00** | DIRA_ROUE_GAUCHE |
| **PB01** | DIRB_ROUE_GAUCHE |
| **PB02** | DIRA_LEVAGE1     |
| **PC13** | DIRB_LEVAGE1     |
| **PA05** | FDC_RAIL_AR      |
| **PA12** | FDC_RAIL_AV      |
| **PC00** | DIRA_PAP_RAIL    |
| **PC01** | DIRB_PAP_RAIL    |
| **PC02** | DIRC_PAP_RAIL    |
| **PC03** | DIRD_PAP_RAIL    |
| **PC10** | TRIG_GAUCHE_AV   |
| **PC11** | TRIG_GAUCHE_AR   |
| **PC12** | TRIG_DROITE_AV   |
| **PD02** | TRIG_DROITE_AR   |
| **PA15** | ECHO_GAUCHE_AV   |
| **PB05** | ECHO_GAUCHE_AR   |
| **PB08** | ECHO_DROITE_AV   |
| **PB09** | ECHO_DROITE_AR   |
| **PB11** | CC_SDA_PINCE1    |
| **PB10** | CC_SCL_PINCE1    |