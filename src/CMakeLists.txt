# Definir la librería del Lab (Header-only)
add_library(state_lab_lib INTERFACE)
target_include_directories(state_lab_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/state_lab)

# Ejecutable único para el Laboratorio de State
add_executable(state_app main.cpp)

# Enlazar la interfaz para que reconozca los headers en src/state_lab/
target_link_libraries(state_app PRIVATE state_lab_lib)