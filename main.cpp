// Created by Max Wang on 2025/3/30.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "glutils.h"
static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) //!result
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message =(char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length,message);
        std::cout << "Failed to compile " <<
        (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
        << " shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //attach
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    compatibleForMac();
    auto windowResult = initWindow(800, 600, "OpenGL window", nullptr, nullptr);
    GLFWwindow* window = nullptr;
    if (windowResult.result != 0) {
        return -1;
    } else {
        window = windowResult.window;
    }
    float vertices[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.0f,  0.5f,
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::string vertexShader =
            "#version 330 core\n"
            "\n"
            "layout (location = 0) in vec4 position;"
            "\n"
            "void main()\n"
            "{\n"
            "gl_Position = position;\n"
            "}\n";

    std::string fragmentShader =
            "#version 330 core\n"
            "\n"
            "layout (location = 0) out vec4 color;"
            "\n"
            "void main()\n"
            "{\n"
            "color = vec4(1.0,0.0,0.0,1.0);\n"
            "}\n";
    unsigned int shader = CreateShader(vertexShader,fragmentShader);
    glUseProgram(shader);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    cleanup(shader,window);
    return 0;
}
