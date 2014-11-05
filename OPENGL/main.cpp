//
//  main.cpp
//  OPENGL
//
//  Created by Bilbo Baggins on 11/5/14.
//  Copyright (c) 2014 Steven Thacker. All rights reserved.
//
// From Tutorial: https://www.youtube.com/watch?v=kCSZ0ycWR5g&list=UUgmBi6eG4I1mykk-Qb1HuXQ
//

#define GLFW_INCLUDE_GLCOREARB
#include <iostream>
#include </opt/local/include/GLFW/glfw3.h>
#include </opt/local/include/glm/glm.hpp>

int main(int argc, const char * argv[])
{
    GLint glfwStatus = glfwInit();
    if (glfwStatus != GL_TRUE)
    {
        std::cout << "GLFW Failed to Initialize!" << std::endl;
        glfwTerminate();
        return 1;
    }
    
    
    // NOT WORKING
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
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    while (!glfwWindowShouldClose(window))
    {
        GLint windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glViewport(0,0,windowWidth,windowHeight);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glDeleteBuffers(1,&myVBO);
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
