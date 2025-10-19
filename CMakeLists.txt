cmake_minimum_required(VERSION 3.10)

project(tradeMarket)

# Принудительно устанавливаем x86 архитектуру
set(CMAKE_GENERATOR_PLATFORM Win32)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Определяем макрос для статической линковки GLEW
add_definitions(-DGLEW_STATIC)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

set(pybind11_DIR "$ENV{VCPKG_ROOT}/installed/x64-windows")

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(trade ${CMAKE_SOURCE_DIR}/main.cpp)

target_link_libraries(trade 
    glfw3
    glew32s  # статическая версия
    opengl32
    gdi32
    user32   # может потребоваться для GLFW
    kernel32 # может потребоваться для GLFW
)