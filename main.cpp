// main2.cpp
#include <pybind11/pybind11.h>
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

namespace py = pybind11;

// Глобальные переменные
GLFWwindow* g_window = nullptr;
bool g_initialized = false;

void initialize_opengl() {
    if (g_initialized) return;

    std::cout << "Initializing OpenGL context" << std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

    g_window = glfwCreateWindow(800, 600, "OpenGL Context", nullptr, nullptr);
    if (g_window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        return;
    }
    glfwMakeContextCurrent(g_window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return;
    }

    g_initialized = true;
}

void render_frame() {
    if (!g_initialized || !g_window) return;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(g_window);
    glfwPollEvents();
}

void cleanup() {
    if (g_window) {
        glfwDestroyWindow(g_window);
        g_window = nullptr;
    }
    glfwTerminate();
    g_initialized = false;
}

// Pybind11 модуль
PYBIND11_MODULE(tradeMarketModule, m) {
    m.doc() = "OpenGL trade market module";

    m.def("initialize", &initialize_opengl, "Initialize OpenGL context");
    m.def("render", &render_frame, "Render a frame");
    m.def("cleanup", &cleanup, "Cleanup resources");

    // Добавьте другие функции которые вам нужны
}