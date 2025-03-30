//
// Created by Max Wang on 2025/3/30.
//

#include "glutils.h"

void cleanup(unsigned int shader, GLFWwindow* window)
{
    glDeleteShader(shader);
    glfwDestroyWindow(window);
    glfwTerminate();
}

void compatibleForMac()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Compatible for mac
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

CreateWindowResult initWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return {-1, nullptr};
    }

    GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return {-1, nullptr};
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return {-1, nullptr};
    }
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    return {0, window};
}