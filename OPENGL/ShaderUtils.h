//
//  ShaderUtils.h
//  OPENGL
//
//  Created by Bilbo Baggins on 11/12/14.
//  Copyright (c) 2014 Steven Thacker. All rights reserved.
//

#ifndef __OPENGL__ShaderUtils__
#define __OPENGL__ShaderUtils__

#include <stdio.h>

#define GLFW_INCLUDE_GLCOREARB

#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include </opt/local/include/GLFW/glfw3.h>

class ShaderUtils
{
public:
    static GLuint createShaderFromFile(const GLchar* path, GLenum shaderType);
};

#endif /* defined(__OPENGL__ShaderUtils__) */




