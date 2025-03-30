//
// Created by Max Wang on 2025/3/30.
//

#ifndef LEARNOPENGL_GLUTILS_H
#define LEARNOPENGL_GLUTILS_H
#include <GL/glew.h>
#include "iostream"
#include <GLFW/glfw3.h>
struct CreateWindowResult {
    int result;
    GLFWwindow* window;
};

void cleanup(unsigned int shader, GLFWwindow* window);
void compatibleForMac();
CreateWindowResult initWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
#endif //LEARNOPENGL_GLUTILS_H
