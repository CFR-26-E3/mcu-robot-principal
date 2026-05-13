# Crée la bibliothèque statique
add_library(Tasks STATIC
        Src/odometry_task.c
        Src/cmd_robot_vel_task.c
        Src/cmd_robot_pose_task.c
        Src/strategy_task.c
        Src/cursor_task.c
        Inc/Detection_task.h
        Src/Detection_task.c
)

# Rend le dossier Inc/ public pour que le projet puisse avoir accès aux fonctions, structures etc.
target_include_directories(Tasks PUBLIC Inc)

# Lie les bibliothèques dont cette bibliothèque a besoin pour fonctionner
target_link_libraries(Tasks PUBLIC stm32cubemx AppLogic DriversCustom)