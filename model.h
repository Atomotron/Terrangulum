#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <refcounted.h>

class Model : public Refcounted{
public:
    unsigned int numVerts;
    std::vector<GLfloat> vertPosData;
    std::vector<GLfloat> vertColorData;
    std::vector<GLfloat> vertNormalData;
    
    //Handles for the data on GPU RAM
    GLuint vertPosDataID;
    GLuint vertColorDataID;
    GLuint vertNormalDataID;
    
    //"Vertex Array" is a terrible name for what this is. I'm calling it a Buffer Array.
    GLuint bufferArrayID; //the handle for the one containing all of the above
    
    Model(const std::string &filename);
    
    void buildVAO();
    
    ~Model();
    
    void mount(); //binds vertex array
};