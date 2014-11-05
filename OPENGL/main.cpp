//
//  main.cpp
//  OPENGL
//
//  Created by Bilbo Baggins on 11/5/14.
//  Copyright (c) 2014 Steven Thacker. All rights reserved.
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

    GLFWwindow* window = glfwCreateWindow(640, 360, "Modern OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Window failed to create" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}
