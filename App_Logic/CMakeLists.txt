# Crée la bibliothèque statique
add_library(AppLogic STATIC
        Src/pid_controller.c
)

# Rend le dossier Inc/ public pour que le projet puisse avoir accès aux fonctions, structures etc.
target_include_directories(AppLogic PUBLIC Inc)

# Lie les bibliothèques dont cette bibliothèque a besoin pour fonctionner
target_link_libraries(AppLogic PUBLIC stm32cubemx)