#pragma once

#include <string>

#include <glm/glm.hpp>

#include <refcounted.h>
#include <model.h>
#include <shader.h>

class Object : public Refcounted{
private:
    glm::vec3 pos;
public:
    glm::mat4x4 modelMatrix;
    Shader* shader;
    Model* model;
    
    Object(Model* model,Shader* shader);
    Object(std::string modelFilename,std::string vshaderFilename,std::string fshaderFilename);
    //Object(std::string objectFilename); //TODO: Implement this.
    ~Object();
    
    glm::vec3 getPos();
    void setPos(glm::vec3 pos);
};