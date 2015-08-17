#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <file.h>
#include <refcounted.h>

class Shader : public Refcounted{
public:
    GLuint vshaderID;
    GLuint fshaderID;
    GLuint programID;
    
    std::map<std::string, GLuint> programUniformIDs;
    
    Shader(const std::string &vshaderFilename, const std::string &fshaderFilename);
    ~Shader();
    
    void mount();
    
    void compileShader(const GLuint &ID,const std::string &src,const std::string &name);
};