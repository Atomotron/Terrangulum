#include <stdlib.h>
#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <model.h>
#include <shader.h>
#include <object.h>
#include <scene.h>
#include <collisions.h>


double prevMouseX;
double prevMouseY;
Scene scene = Scene(); //global for now, a real game would put it in some kind of state object

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void onMouseMove(GLFWwindow* window, double xpos, double ypos)
{
    scene.cameraAngleAround += -(xpos-prevMouseX)/400;
    scene.cameraAngleUpdown += (ypos-prevMouseY)/500;
    prevMouseX = xpos;
    prevMouseY = ypos;
    scene.updateCamera();
}

int main(void)
{
    GLFWwindow* window; 
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
        
        
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 8);    
    window = glfwCreateWindow(1024, 768, "Simple example", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    GLenum glewErr = glewInit();
    std::cout << glewGetErrorString(glewErr) << std::endl;
    
    // get version info
    const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString (GL_VERSION); // version as a string
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported %s\n", version);
    
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CCW);
    glDepthFunc(GL_LESS);
    
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, onMouseMove);
    prevMouseX=0;
    prevMouseY=0;
    
    std::string resource_path = "J:/Program Files/CodeLite/3D1/3D1/resources/";
    
    Model* model = new Model(resource_path+"model.bin");
    Shader* shader = new Shader(resource_path+"VCN.vsh",resource_path+"VCN.fsh");
    Object* object = new Object(model,shader);
    
    scene.cameraPos = glm::vec3(0,0,1);
    scene.addObject(object);
    
    CollisionWorld world = CollisionWorld(resource_path+"collision.bin");
    Polygon* currentPolygon = world.getPolygonContaining(scene.cameraPos);
    
    glClearColor(0.74f,0.90f,1.0f,1.0f);
    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = width / (float) height;
        scene.setAspectRatio(ratio);
        
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader->programID);
        glBindVertexArray(model->bufferArrayID);
        
        glm::vec3 delta;
        
        int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (state == GLFW_PRESS) delta = scene.cameraNormal;
        state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
        if (state == GLFW_PRESS) delta = -scene.cameraNormal;
        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) delta = scene.cameraNormal;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) delta += -scene.cameraNormal;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) delta += glm::rotateZ(scene.cameraNormal,1.57079633f);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) delta += -glm::rotateZ(scene.cameraNormal,1.57079633f);
        
        
        if (glm::length(delta) > 1/200.0f) delta = glm::normalize(delta)/200.0f;
        
        glm::vec3 start = scene.cameraPos;
        glm::vec3 end = start+delta;
        
        CollisionReport report = world.collisionReport(currentPolygon,start,end);
        
        
        //std::cout << scene.cameraAngleAround << ' ' << scene.cameraPos.x << ',' << scene.cameraPos.y << scene.cameraPos.z << std::endl;
        if (report.finalPolygon->polyType->name == "gateA"){
            //0.685 8.17024,-6.08947
            scene.cameraAngleUpdown = 0;
            scene.cameraAngleAround = 0.685;
            end = glm::vec3(8.17024,-6.08947,1);
            currentPolygon = world.getPolygonContaining(end);
        }
        else if (report.finalPolygon->polyType->name == "gateB"){
            //6.32001 -46.4775,17.382
            scene.cameraAngleUpdown = 0;
            scene.cameraAngleAround = 6.32001;
            end = glm::vec3(-46.4775,17.382,1);
            currentPolygon = world.getPolygonContaining(end);
        }
        else{
            end = glm::vec3(report.finalPoint,1);
            currentPolygon = report.finalPolygon;
        }
        
        

        scene.cameraPos = currentPolygon->getFootPos(end) + glm::vec3(0,0,1);
        
        scene.updateCamera();
        
        scene.draw();

        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}