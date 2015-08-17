#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <model.h>
#include <shader.h>
#include <object.h>

class Scene{
private:
    //remembers OpenGL state machine state to avoid double-loading.
    GLint loadedShaderID;
    GLint loadedBufferArrayID;
    
public:
    //Camera data
    glm::mat4x4 viewMatrix;
    glm::mat4x4 projMatrix;
    glm::mat4x4 viewProjMatrix;
    
    glm::vec3 cameraPos;
    
    float cameraAngleAround;
    float cameraAngleUpdown;
    glm::vec3 cameraNormal;
    
    //Object data
    std::vector<Object*> objects;
    
    
    //---
    Scene();
    ~Scene();
    
    //Camera functions
    void updateCamera();
    void setAspectRatio(float ratio);
    
    //Object functions
    void addObject(Object* object);
    void draw(); 
};