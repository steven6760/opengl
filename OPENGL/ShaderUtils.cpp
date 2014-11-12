//
//  ShaderUtils.cpp
//  OPENGL
//
//  Created by Bilbo Baggins on 11/12/14.
//  Copyright (c) 2014 Steven Thacker. All rights reserved.
//

#include "ShaderUtils.h"

GLuint ShaderUtils::createShaderFromFile(const GLchar *path, GLenum shaderType)
{
    GLuint shaderID = glCreateShader(shaderType);
    
    std::ifstream fin;
    fin.open(path);
    if(!fin.is_open())
    {
        fin.close();
        std::cout << "File Not Found: '" <<path << "'!" << std::endl;
        return 0;
    }
    std::string source((std::istreambuf_iterator<GLchar>(fin)), std::istreambuf_iterator<GLchar>());
    
    const GLchar* shaderSource = source.c_str();
    glShaderSource (shaderID, 1, &shaderSource, NULL);
    
    glCompileShader(shaderID);
    
    GLint compileStatus;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
    if(compileStatus != GL_TRUE)
    {
        std::cout << "Shader Failed To Compile: " << path << "'!" << std::endl;
        GLint infoLogLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* infoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, infoLog);
        std::cout << infoLog << std::endl;
        delete infoLog;
        
        return 0;
    }
    
    return shaderID;
}








