#include <scene.h>

Scene::Scene(){
    loadedShaderID = -1;
    loadedBufferArrayID = -1;
    
    cameraPos = glm::vec3(0,0,0);
    cameraAngleAround = 0;
    cameraAngleUpdown = 0;
    
    setAspectRatio(1.333);
    
    updateCamera(); //this will fill out the other camera fields
}

Scene::~Scene(){
    for (unsigned int i=0;i<objects.size();i++){
        objects[i]->dereference();
    }
}

void Scene::setAspectRatio(float ratio){
    projMatrix = glm::perspective(
        70.0f, 
        ratio, 
        0.01f, 
        500.0f);
    viewProjMatrix = viewMatrix * projMatrix;
}

void Scene::updateCamera(){
    cameraNormal = glm::rotateZ(glm::rotateY(glm::vec3(1,0,0),cameraAngleUpdown),cameraAngleAround);
    glm::vec3 upDirection = glm::rotateZ(glm::rotateY(glm::vec3(0,0,1),cameraAngleUpdown),cameraAngleAround);
    viewMatrix = glm::lookAt(cameraPos,cameraPos+cameraNormal,upDirection);
    
    viewProjMatrix = projMatrix*viewMatrix;
}

void Scene::addObject(Object* object){
    objects.push_back(object);
    object->reference();
}

void Scene::draw(){
    for (unsigned int i=0;i<objects.size();i++){
        Object* object = objects[i];
        
        if (object->shader->programID != loadedShaderID){
            object->shader->mount();
            loadedShaderID = object->shader->programID;
            std::cout<<loadedShaderID;
        }
        if (object->model->bufferArrayID != loadedBufferArrayID){
            object->shader->mount();
            loadedBufferArrayID = object->model->bufferArrayID;
            std::cout<<loadedBufferArrayID;
        }
        
        //load model-view-projection matrix into shader
        glm::mat4x4 MVP = object->modelMatrix * viewProjMatrix;
        glUniformMatrix4fv(object->shader->programUniformIDs["MVP"], 1, GL_FALSE, &MVP[0][0]);
        
        glDrawArrays(GL_TRIANGLES, 0, object->model->numVerts);
        
        //std::cout << glGetError() <<' '<< GL_NO_ERROR <<std::endl;
    }
}