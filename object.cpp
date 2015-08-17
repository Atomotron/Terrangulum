#include <object.h>
#include <glm/gtc/matrix_transform.hpp>

glm::vec3 Object::getPos(){
    return pos;
}

void Object::setPos(glm::vec3 pos){
    this->pos = pos;
    modelMatrix = glm::translate(glm::mat4(1.0f),pos);
}

Object::Object(Model* model,Shader* shader){
    this->model = model;
    this->model->reference();
    this->shader = shader;
    this->shader->reference();
    setPos(glm::vec3(0,0,0));
}

Object::Object(std::string modelFilename,std::string vshaderFilename,std::string fshaderFilename){
    this->model = new Model(modelFilename);
    this->model->reference();
    
    this->shader = new Shader(vshaderFilename,fshaderFilename);
    this->shader->reference();
    setPos(glm::vec3(0,0,0));
}

Object::~Object(){
    this->model->dereference();
    this->shader->dereference();
}