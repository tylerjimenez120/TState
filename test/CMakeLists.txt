cmake_minimum_required(VERSION 3.18)

# 1. Configuración de GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Desactivar análisis estático para GoogleTest
foreach(target IN ITEMS gtest gtest_main gmock gmock_main)
    if(TARGET ${target})
        set_target_properties(${target} PROPERTIES 
        CXX_CLANG_TIDY ""
        CXX_INCLUDE_WHAT_YOU_USE "")
    endif()
endforeach()

# 2. Ejecutable de tests (Exclusivo para el Lab de State)
add_executable(test_runner main_test.cpp)

# 3. Vinculación de librerías
# Eliminamos observer_lib. Solo queda la librería de interfaz del State Lab.
target_link_libraries(test_runner 
    PRIVATE 
    state_lab_lib
    GTest::gtest
    GTest::gtest_main
)

# 4. Directorios de inclusión
target_include_directories(test_runner PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)

# Desactivar análisis en el runner para agilizar
set_target_properties(test_runner PROPERTIES
    CXX_CLANG_TIDY ""
    CXX_INCLUDE_WHAT_YOU_USE ""
)

# 5. Registro de tests en CTest
add_test(NAME State_Pattern_Lab_Tests COMMAND $<TARGET_FILE:test_runner>)