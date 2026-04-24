cmake_minimum_required(VERSION 3.18)

project(CXX_PROJECT)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard required for build")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "is C++ standard a requirement")
set(CMAKE_CXX_EXTENSIONS OFF CACHE BOOL "enable/disable compiler specific extensions")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Flags de compilación estrictos para asegurar calidad en el SOC
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic")

# Herramientas de análisis estático
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "iwyu")

set(SRC_DIR src)
set(TEST_DIR test)

# Captura de todos los archivos .h y .cpp (incluyendo el nuevo state_lab)
file(GLOB_RECURSE ALL_SOURCE_FILES 
    ${CMAKE_SOURCE_DIR}/${SRC_DIR}/*.cpp 
    ${CMAKE_SOURCE_DIR}/${SRC_DIR}/*.h
    ${CMAKE_SOURCE_DIR}/${TEST_DIR}/*.cpp
    ${CMAKE_SOURCE_DIR}/${TEST_DIR}/*.h
)

# Target 'fix' para automatizar el formato con clang-format
add_custom_target(fix
    COMMAND clang-format -i ${ALL_SOURCE_FILES}
    COMMENT "Running clang-format to fix formatting in all modules..."
)

enable_testing()

# Organización de subdirectorios
add_subdirectory(src)
add_subdirectory(test)

# Asegura que los tests siempre corran sobre código formateado
add_dependencies(test_runner fix)