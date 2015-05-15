#! /bin/bash

stringZ=''

stringZ=0

# toodles=$(echo "scale=2; 100/3" | bc)

# echo $toodles

echo 1 + 1

# for i in `seq 1 10`;
# do

# 		temp=$(echo "$i+1" | bc)
# 		#temp=$(bc <<< $(bc <<< "scale=1;$i")/2)
# 		#temp=$(bc <<<"scale=0;i%2;scale=1;$i/2")
# 		#temp=$("scale=10; $i" | bc)
#         stringZ="$stringZ, $temp"
# done    

# echo $stringZ

echo '

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
// Next Tut: https://www.youtube.com/watch?v=K-2bpL_06Vk&index=12&list=UUgmBi6eG4I1mykk-Qb1HuXQ
//

#define GLFW_INCLUDE_GLCOREARB
#include <iostream>
#include </opt/local/include/GLFW/glfw3.h>
//#include <IL/il.h>
#include </opt/local/include/glm/glm.hpp>
#include "ShaderUtils.h"
#include <cmath>

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
    
    glClearColor(.5, .5, .5, 1);
    
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
' + '         .05,.05,
        -.05,.05,
        -.05,-.05,
        .05,-.05
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), bufferData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    
    GLuint myEBO;
    glGenBuffers(1,&myEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO);
    
    GLushort indexData[] =
    {
        0,1,2,
        0,2,3,
    };
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indexData),indexData,GL_STATIC_DRAW);
    
    GLuint myVAO;
    glGenVertexArrays(1, &myVAO);
    glBindVertexArray(myVAO);
    
    GLint positionLoc = glGetAttribLocation(shaderProgram, "position");
    
    glEnableVertexAttribArray(positionLoc);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO);
    glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    glBindVertexArray(NULL);
    
    GLint colorLoc = glGetUniformLocation(shaderProgram, "color");
    
    while (!glfwWindowShouldClose(window))
    {
        GLint viewportWidth, viewportHeight;
        glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
        glViewport(0,0,viewportWidth,viewportHeight);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUniform4f(colorLoc, 1.0,sinf(glfwGetTime()),0.0,0.0);
        //glUniform4f(colorLoc, 1.0,0.0,0.0,1);
        
        glBindVertexArray(myVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,myEBO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,NULL);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,NULL);
        glBindVertexArray(NULL);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glDeleteBuffers(1,&myEBO);
    glDeleteBuffers(1,&myVBO);
    glDeleteVertexArrays(1, &myVAO);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}



' > main.cpp