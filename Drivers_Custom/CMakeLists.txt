# Crée la bibliothèque statique
add_library(DriversCustom STATIC
        Src/dc_motor.c
        Src/encoder.c
        Src/servo.c
)

# Rend le dossier Inc/ public pour que le projet puisse avoir accès aux fonctions, structures etc.
target_include_directories(DriversCustom PUBLIC Inc)

# Lie les bibliothèques dont cette bibliothèque a besoin pour fonctionner
target_link_libraries(DriversCustom PUBLIC stm32cubemx)