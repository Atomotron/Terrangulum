#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_set>

#include <glm/glm.hpp>

struct PolyType{
    std::string name;
    unsigned int number;
};

struct CollisionReport;

class Polygon{
public:
    PolyType* polyType;

    std::vector<glm::vec2> verts;
    std::vector<glm::vec2> edgeNormals;
    std::vector<float> edgesProjected;
    std::vector<Polygon*> edgeLinks;
    
    glm::vec3 faceNormal;
    float xSlope;
    float ySlope;
    float zIntercept;
    
    Polygon();
    ~Polygon();
    
    bool isInside(glm::vec2 point);
    glm::vec3 getCenter();
    static bool isPointOnEdge(glm::vec2 point, glm::vec2 a, glm::vec2 b);
    static int edgeDirection(glm::vec2 point, glm::vec2 a, glm::vec2 b);
    static glm::vec2 nearestPointOnEdge(glm::vec2 point, glm::vec2 normal, float edgeProjected);
    
    float getZ(glm::vec2 xy);
    glm::vec3 getFootPos(glm::vec3 pos);
    
    CollisionReport collisionReport(glm::vec2 start, glm::vec2 end, int scanDirection);
};

class CollisionWorld{
public:
    std::vector<PolyType*> polyTypes;
    std::vector<Polygon*> polygons;
    
    CollisionWorld(const std::string &filename);
    ~CollisionWorld();
    
    Polygon* getPolygonContaining(glm::vec3 point);
    CollisionReport collisionReport(Polygon* startPolygon, glm::vec3 start, glm::vec3 end);
    
};

struct CollisionReport{
    Polygon* finalPolygon;
    glm::vec2 finalPoint;
    
    bool complete;
};