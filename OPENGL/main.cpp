//
//  main.cpp
//  OPENGL
//
//  Created by Bilbo Baggins on 11/5/14.
//  Copyright (c) 2014 Steven Thacker. All rights reserved.
//
// From Tutorial: https://www.youtube.com/watch?v=kCSZ0ycWR5g&list=UUgmBi6eG4I1mykk-Qb1HuXQ
//
// Macintosh HD ▸ Users ▸ BagginsHomeFolder ▸ Documents ▸ Abstract Desktop ▸ Xcode Pro Folder ▸ OPENGL
//

#define GLFW_INCLUDE_GLCOREARB
#include <iostream>
#include </opt/local/include/GLFW/glfw3.h>
#include </opt/local/include/glm/glm.hpp>
#include "ShaderUtils.h"

int main(int argc, const char * argv[])
{
    GLint glfwStatus = glfwInit();
    if (glfwStatus != GL_TRUE)
    {
        std::cout << "GLFW Failed to Initialize!" << std::endl;
        glfwTerminate();
        return 1;
    }
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    GLFWwindow* window = glfwCreateWindow(640, 360, "Modern OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Window failed to create" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    std::cout << glGetString(GL_VERSION) << std::endl;
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    GLuint vertexShader = ShaderUtils::createShaderFromFile("myShaderProgram.vs", GL_VERTEX_SHADER);
    GLuint fragmentShader = ShaderUtils::createShaderFromFile("myShaderProgram.fs", GL_FRAGMENT_SHADER);
    
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    glBindFragDataLocation(shaderProgram, 0, "fragData");
    
    glLinkProgram(shaderProgram);
    GLint linkStatus;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
    if(linkStatus != GL_TRUE)
    {
        std::cout << "Program Link Failed!" << std::endl;
        GLint infoLogLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* infoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, infoLog);
        std::cout << infoLog << std::endl;
        delete infoLog;
        
        return 0;
    }
    
    glUseProgram(shaderProgram);
    
    GLuint myVBO;
    glGenBuffers(1, &myVBO);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    
    GLfloat bufferData[] =
    {
        +0.0, +0.5,
        -0.5, -0.5,
        +0.5, -0.5,
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), bufferData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    
    GLuint myVAO;
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);
    
    GLint positionLoc = glGetAttribLocation(shaderProgram, "position");
    
    glEnableVertexAttribArray(positionLoc);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    glBindVertexArray(NULL);
    
    while (!glfwWindowShouldClose(window))
    {
        GLint windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0,0,windowWidth,windowHeight);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindVertexArray(myVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(NULL);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glDeleteBuffers(1,&myVBO);
    glDeleteVertexArrays(1, &myVAO);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
