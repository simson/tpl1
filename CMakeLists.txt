# Nom du projet
project(tpl1)

#Option
SET(CMAKE_C_FLAGS "-std=c99")
# Select flags.
SET(CMAKE_CXX_FLAGS "-Wall -Wextra")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
#SET(CMAKE_CXX_FLAGS_ASSEMBLY "-S")
SET(CMAKE_C_FLAGS_ASSEMBLY "-S")
# Déclaration de l'exécutable
add_executable(
    tpl1
    tp1.c
)
