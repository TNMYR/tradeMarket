cmake_minimum_required(VERSION 3.10)

project(tradeMarket)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Определяем макрос для статической линковки GLEW
add_definitions(-DGLEW_STATIC)

find_package(Python REQUIRED COMPONENTS Interpreter Development Development.Module Development.Embed)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")


set(pybind11_DIR "$ENV{VCPKG_ROOT}/installed/x64-windows/share/pybind11")
find_package(pybind11 CONFIG REQUIRED)


pybind11_add_module(tradeMarketModule ${CMAKE_SOURCE_DIR}/main2.cpp)

target_include_directories(tradeMarketModule PRIVATE 
    ${Python_INCLUDE_DIRS}
)

target_link_libraries(tradeMarketModule PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/glfw3.lib
    ${CMAKE_SOURCE_DIR}/lib/glew32s.lib
    opengl32
    gdi32
    user32
    kernel32
    ${Python_LIBRARIES}
)