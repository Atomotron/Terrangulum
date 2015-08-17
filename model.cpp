#include <model.h>

Model::Model(const std::string &filename){
    std::ifstream file(filename, std::ios::binary);
    
    if (file.good()) {
        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        numVerts = size / sizeof(float) / 3 / 3; //4 chars per float, 3 floats per datapoint, 3 datapoints per vert (pos, color, normal)
        
        std::cout << "Loading from file " << size << " bytes long (Implying " << numVerts << " vertices)" << std::endl;
        
        std::vector<char> buffer(size);
        if (file.read(buffer.data(), size))
        {
            unsigned int block_size = numVerts*3*4; //number of floats per block
            
            for(int i=0;i<block_size;i+=sizeof(float))
            {
                float f=*((float*) &buffer[i]);
                vertPosData.push_back(f);
            }
            for(int i=block_size;i<2*block_size;i+=sizeof(float))
            {
                float f=*((float*) &buffer[i]);
                vertColorData.push_back(f);
            }
            for(int i=2*block_size;i<3*block_size;i+=sizeof(float))
            {
                float f=*((float*) &buffer[i]);
                vertNormalData.push_back(f);
            }
            
            buildVAO();
            
            std::cout << "File loaded. " << vertPosData.size() << ' ' << vertColorData.size() << ' ' << vertNormalData.size() << std::endl;
        }
        else {
            std::cout << "File not loaded. file.read(...)" << std::endl;
        }
    }
    else {
        std::cout << "File not loaded. - file.good()" << std::endl;
    }
}

void Model::buildVAO(){
    //first, create the VAO that will later be connected to all the buffers
    glGenVertexArrays(1, &bufferArrayID);
    glBindVertexArray(bufferArrayID);
    
    glGenBuffers(1, &vertPosDataID);
    glGenBuffers(1, &vertColorDataID);
    glGenBuffers(1, &vertNormalDataID);
    
    //binding a buffer tells the openGL state machine to shift focus to it.
    //in addition, we also must tell it what kind of buffer we are telling it to look at.
    glBindBuffer(GL_ARRAY_BUFFER, vertPosDataID);
    glBufferData(GL_ARRAY_BUFFER, vertPosData.size()*sizeof(GLfloat), &vertPosData[0], GL_STATIC_DRAW); //write the data
    glEnableVertexAttribArray(0); //the number here says where in the layout the VBO we are about to bind can be found
    glVertexAttribPointer(    0,  3,GL_FLOAT,GL_FALSE,0,(void*)0); //point layout(0) to the Pos VBO
    
    glBindBuffer(GL_ARRAY_BUFFER, vertColorDataID);
    glBufferData(GL_ARRAY_BUFFER, vertColorData.size()*sizeof(GLfloat), &vertColorData[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(    1,  3,GL_FLOAT,GL_FALSE,0,(void*)0); //point layout(1) to the Color VBO
    
    glBindBuffer(GL_ARRAY_BUFFER, vertNormalDataID);
    glBufferData(GL_ARRAY_BUFFER, vertNormalData.size()*sizeof(GLfloat), &vertNormalData[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(    2,  3,GL_FLOAT,GL_FALSE,0,(void*)0); //point layout(2) to the Normal VBO
}

Model::~Model(){ 
    //we only want to delete one thing with each call.
    //  so, we tell it the array length is 1 and give it 
    //  the address of the ID as if it were the base of an array.
    glDeleteBuffers(1, &vertPosDataID);
    glDeleteBuffers(1, &vertColorDataID);
    glDeleteBuffers(1, &vertNormalDataID);
    
    glDeleteVertexArrays(1, &bufferArrayID);
}

void Model::mount(){
    glBindVertexArray(bufferArrayID);
}