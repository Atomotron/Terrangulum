#include <shader.h>

Shader::Shader(const std::string &vshaderFilename, const std::string &fshaderFilename){
    std::string vshaderCode = readFile(vshaderFilename);
    std::string fshaderCode = readFile(fshaderFilename);
    
    if (vshaderCode == "ERR" || vshaderCode == "ERR"){
        std::cout << "One or both of the shader files didn't load." << std::endl;
        return;
    }
    
    std::cout << "Read code for " << vshaderFilename << " and " << fshaderFilename << "." << std::endl;
    
    vshaderID = glCreateShader(GL_VERTEX_SHADER);
    fshaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
    std::cout << "Read code for " << vshaderFilename << " and " << fshaderFilename << "." << std::endl;
    
    compileShader(vshaderID, vshaderCode, vshaderFilename);
    compileShader(fshaderID, fshaderCode, fshaderFilename);
    
    std::cout << "Linking program." << std::endl;
    
    programID = glCreateProgram();
    glAttachShader(programID, vshaderID);
    glAttachShader(programID, fshaderID);
    glLinkProgram(programID);
    
    
    //check for linking errors
    GLint compileStatus = GL_FALSE;
    GLint infoLogLength;
    
    glGetProgramiv(programID, GL_LINK_STATUS, &compileStatus);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> linkErrorMessage( std::max(infoLogLength, int(1)) );
    glGetProgramInfoLog(programID, infoLogLength, NULL, &linkErrorMessage[0]);
    std::cout << &linkErrorMessage[0] << std::endl;
    
    GLint numUniforms = 0;
    glGetProgramInterfaceiv(programID, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);
    
    std::vector<GLchar> nameData(256);
    for(GLint i=0; i<numUniforms; i++)
    {
        //Get name length.
        GLenum thingToGet = GL_NAME_LENGTH;
        GLint nameLength;
        glGetProgramResourceiv(programID, GL_UNIFORM, i, 1, &thingToGet, 1, NULL, &nameLength);
        
        //Read name into vector.
        nameData.resize(nameLength); //The length of the name.
        glGetProgramResourceName(programID, GL_UNIFORM, i, nameData.size(), NULL, &nameData[0]);
        
        //Put vector into string, add it to map.
        std::string name((char*)&nameData[0], nameData.size() - 1);
        GLint uniformID = glGetUniformLocation(programID, name.c_str());
        
        std::cout << "Found uniform named " << name << " at ID " << uniformID << "." << std::endl;
        programUniformIDs[name] = uniformID;
    }
    
    
    std::cout << "Done with " << vshaderFilename << " and " << fshaderFilename << "." << std::endl << std::endl;
}

void Shader::compileShader(const GLuint &ID,const std::string &src,const std::string &name){
    GLint compileStatus = GL_FALSE;
    GLint infoLogLength;
    
    //Compile shader.
    std::cout << "Compiling shader: " << name << std::endl;
    char const * sourcePointer = src.c_str();
    glShaderSource(ID, 1, &sourcePointer, NULL);
    glCompileShader(ID);
    
    //Get error status, if any.
    glGetShaderiv(ID, GL_COMPILE_STATUS, &compileStatus);
    glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> errorMessage(infoLogLength);
    glGetShaderInfoLog(ID, infoLogLength, NULL, &errorMessage[0]);
    
    void *errorExists;
    
    errorExists = &errorMessage[0];
    if (errorExists != nullptr)
    {
        std::string errString(errorMessage.begin(),errorMessage.end());
        std::cout << errString << std::endl;
    }
}

Shader::~Shader(){
    glDeleteShader(vshaderID);
    glDeleteShader(fshaderID);
    glDeleteProgram(programID);
}

void Shader::mount(){
    glUseProgram(programID);
}