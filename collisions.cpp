#include <collisions.h>

Polygon::Polygon(){};
Polygon::~Polygon(){};

bool Polygon::isPointOnEdge(glm::vec2 point, glm::vec2 a, glm::vec2 b){
    //This only /really/ needs to work for points on the line... an optimization I could make in the future.    
    return ( a.x==b.x || (point.x-a.x) * (point.x-b.x) <= 0.0001)
            &&
           ( a.y==b.y || (point.y-a.y) * (point.y-b.y) <= 0.0001);
}

int Polygon::edgeDirection(glm::vec2 point, glm::vec2 a, glm::vec2 b){
    //-1 if behind a, +1 if in front of b, 0 if inbetween
    
    //selected components for comparison
    float pc;
    float ac;
    float bc;
    
    if (abs(a.x - b.x) <= 0.0001){ //vertical
        pc = point.y;
        ac = a.y;
        bc = b.y;
    }
    else{ //horizontal or diagonal
        pc = point.x;
        ac = a.x;
        bc = b.x;
    }
    
    if (ac>bc){ //If a>b, then p is a-wards if big, b-wards if small, inbetween if inbetween
        if      (pc>=ac) return -1;
        else if (pc<=bc) return 1;
        else return 0;
    }
    else{       //If a<=b, then p is a-wards if small, b-wards if big, inbetween if inbetween
        if      (pc<=ac) return -1;
        else if (pc>=bc) return 1;
        else return 0;
    }
}

glm::vec2 Polygon::nearestPointOnEdge(glm::vec2 point, glm::vec2 normal, float edgeProjected){
    float pointProjected = glm::dot(point,normal);
    float sinkDepth = pointProjected - edgeProjected;
    return glm::vec2(point - sinkDepth*normal);
}

bool Polygon::isInside(glm::vec2 point){
    for (unsigned int i=0;i<edgeNormals.size();i++){
        if (glm::dot(point,edgeNormals[i]) > edgesProjected[i]) return false;
    }
    return true;
}

float Polygon::getZ(glm::vec2 xy){
    return xy.x*xSlope + xy.y*ySlope + zIntercept;
}

glm::vec3 Polygon::getFootPos(glm::vec3 pos){
    return glm::vec3(pos.x,pos.y,pos.x*xSlope + pos.y*ySlope + zIntercept);
}

glm::vec3 Polygon::getCenter(){
    glm::vec2 sum = glm::vec2(0,0);
    for (unsigned int i=0; i<verts.size(); i++){
        sum += verts[i];
    }
    sum = sum/((float)verts.size());
    return glm::vec3(sum,getZ(sum));
}

CollisionReport Polygon::collisionReport(glm::vec2 start, glm::vec2 end,int scanDirection){
    //for every edge
    
    int loop_start;
    int loop_end;
    
    if (scanDirection ==  1){
        loop_start=0;
        loop_end=verts.size();
    }
    if (scanDirection == -1){
        loop_start=verts.size()-1;
        loop_end=-1;
    }
    
    for (unsigned int i=loop_start; i != loop_end; i+=scanDirection){
        glm::vec2 edgeA = verts[i];
        glm::vec2 edgeB = verts[(i+1) % verts.size()];
        glm::vec2 normal = edgeNormals[i];
        float edgeProjected = edgesProjected[i];
        
        float startProjected = glm::dot(start,normal);
        float endProjected = glm::dot(end,normal);
        
        float sinkDepth = endProjected - edgeProjected;
        
        if (sinkDepth>0){ //if the end is over the line (not line segment yet, just line)
            float travelDistance = endProjected - startProjected; //note: this is distance paralell to normal line - not euclidean distance
            float ratio = sinkDepth/travelDistance;
            glm::vec2 delta = end-start;
            glm::vec2 sinkVector = delta*ratio;
            
            glm::vec2 intersectionLocation = end-sinkVector;
            //see if the point on the line is ALSO on the line segment
            if (isPointOnEdge(intersectionLocation,edgeA,edgeB)){
                //now we start the edgecrawl
                //the first step of the edgecrawl (looking at the line we intersect first)
                // can be done more efficiently using data we've already got, so we do it outside
                // of the loop.
                
                if (edgeLinks[i] != nullptr){
                    //our first opportunity to return early
                    //we found a collision and we won't be finishing on a different edge
                    //because we hit the edge link and just pass along to the other poly
                    
                    
                    
                    std::cout << "Link found " << this << ' ' << std::endl;
                    CollisionReport report;
                    report.complete = false; //the calling function needs to go check for collisions in finalPolygon
                    report.finalPoint = intersectionLocation;
                    report.finalPolygon = edgeLinks[i];
                    return report;
                }

                glm::vec2 snappedLocation = end-sinkDepth*normal;
                int direction = edgeDirection(snappedLocation,edgeA,edgeB);
                if (direction == 0){
                    //we might hit a wall and slide to somewhere on the same edge
                    CollisionReport report;
                    report.complete = true; //the only incomplete case is if we need to check another poly
                    report.finalPoint = snappedLocation;
                    report.finalPolygon = this;
                    return report;
                }
                
                //if we haven't returned already, it's because we hit a wall and are going to slide
                //to a new edge. Since we know we are sure to end up pressed against an edge, we can
                //find our final location with a cleverly efficient algorithm
                int currentEdge = (i+direction+edgeNormals.size()) % edgeNormals.size();
                while (true){
                    //we're going to go ahead and re-define these - we don't need any of the edge data for the thing we hit first anymore
                    edgeA = verts[currentEdge];
                    edgeB = verts[(currentEdge+1) % verts.size()];
                    
                    //the first possibility is that we've just slid onto a link
                    if (edgeLinks[currentEdge] != nullptr){
                        std::cout << "Link found inside edgecrawl " << this << ' ' << currentEdge << ' ' << direction << ' ' << edgeNormals.size() << std::endl;
                        
                        glm::vec2 finalPoint;
                        if (direction == 0)
                            finalPoint = snappedLocation;
                        else if (direction == 1)
                            finalPoint = edgeA;
                        else if (direction == -1)
                            finalPoint = edgeB;
                        
                        CollisionReport report;
                        report.complete = false; //the calling function needs to go check for collisions in finalPolygon
                        report.finalPoint = finalPoint;
                        report.finalPolygon = edgeLinks[currentEdge];
                        return report;
                    }
                    
                    //if we didn't slide into a link, now we've got to deal with sliding along an edge.
                    normal = edgeNormals[currentEdge];
                    edgeProjected = edgesProjected[currentEdge];
                    snappedLocation = nearestPointOnEdge(end,normal,edgeProjected);
                    int snappedLocationDirection = edgeDirection(snappedLocation,edgeA,edgeB);
                    
                    
                    
                    /*//a shot in the dark to compensate for suspected FP problems
                    if (abs(snappedLocation.x-edgeA.x) <= 0.0001 && abs(snappedLocation.y-edgeA.y) <= 0.0001){
                        std::cout << "Edge A same" << std::endl;
                        CollisionReport report;
                        report.complete = true;
                        report.finalPoint = edgeA;
                        report.finalPolygon = this;
                        return report;
                    }
                    if (abs(snappedLocation.x-edgeB.x) <= 0.0001 && abs(snappedLocation.y-edgeB.y) <= 0.0001){
                        std::cout << "Edge B same" << std::endl;
                        CollisionReport report;
                        report.complete = true;
                        report.finalPoint = edgeB;
                        report.finalPolygon = this;
                        return report;
                    }*/
                    
                    

                    /*std::cout << end.x << ',' << end.y << " " 
                              << snappedLocation.x << ',' << snappedLocation.y << " " 
                              << snappedLocationDirection << std::endl;*/
                    if (snappedLocationDirection != direction){
                        //if we go forwards and then back, that means we are stuck in a corner and should stay there.
                        glm::vec2 finalPoint;
                        
                        if (direction == 0)
                            finalPoint = snappedLocation;
                        else if (direction == 1)
                            finalPoint = edgeA;
                        else if (direction == -1)
                            finalPoint = edgeB;
                        
                        /*std::cout << "(snappedLocationDirection != direction) " << direction << ' ' 
                            << snappedLocation.x << ',' << snappedLocation.y << ' '
                            << edgeA.x << ',' << edgeA.y << ' '
                            << edgeB.x << ',' << edgeB.y << std::endl;*/
                            
                        CollisionReport report;
                        report.complete = true;
                        report.finalPoint = finalPoint;
                        report.finalPolygon = this;
                        return report;
                    }
                    
                    //if we've made it this far without returning, that means we slid to the end of an edge and need to slide again
                    //in the same direction
                    //so, just increment currentEdge and go around again
                    
                    //std::cout << currentEdge << ' ' << edgeNormals.size() << ' ' << direction << ' ' << edgeNormals.size() << std::endl;
                    
                    currentEdge = (currentEdge+direction+edgeNormals.size()) % edgeNormals.size();
                }
            }
        
        }
        
    }
    
    //all intersections found in the for loop will lead to an early return
    //if we get this far, we know we just need to return with no collision
    CollisionReport report;
    report.complete = true;
    report.finalPoint = end;
    report.finalPolygon = this;
    return report;
}








Polygon* CollisionWorld::getPolygonContaining(glm::vec3 point){
    Polygon* bestMatch = polygons[0]; //always return at least something - maybe i'll change this later to nullptr
    float bestMatchHeightDelta = INFINITY;
    
    glm::vec2 point2d = glm::vec2(point.x,point.y);
    
    for (unsigned int i=0; i<polygons.size(); i++){
        Polygon* poly = polygons[i];
        if (poly->isInside(point2d)){
            float delta = point.z-poly->getZ(point2d);
            if (delta >= 0 && delta < bestMatchHeightDelta){
                bestMatch = poly;
                bestMatchHeightDelta = delta;
            }
        }
    }
    return bestMatch;
}

CollisionReport CollisionWorld::collisionReport(Polygon* startPolygon, glm::vec3 start, glm::vec3 end){
    Polygon* currentPolygon = startPolygon;
    glm::vec2 currentStart = glm::vec2(start.x,start.y);
    glm::vec2 end2 = glm::vec2(end.x,end.y);
    //std::cout <<  "Starting - - -"  << std::endl;
    int i = 0;
    int scanDirection = 1;
    while (true){
        CollisionReport report = currentPolygon->collisionReport(currentStart,end2,scanDirection);
        if (report.complete){
            if (report.finalPoint != end2) std::cout << "Report complete." <<std::endl;
            return report;
        }
        else{
            if (i>10) break;
            i++;
            
            currentPolygon = report.finalPolygon;
            currentStart = report.finalPoint;
        }
    }
    
    std::cout << "Running negative scan." <<std::endl;
    currentPolygon = startPolygon;
    currentStart = glm::vec2(start.x,start.y);
    end2 = glm::vec2(end.x,end.y);
    i = 0;
    scanDirection = -1;
    while (true){
        CollisionReport report = currentPolygon->collisionReport(currentStart,end2,scanDirection);
        if (report.complete){
            if (report.finalPoint != end2) std::cout << "Report complete." <<std::endl;
            return report;
        }
        else{
            if (i>10){
                report.complete = true;
                std::cout << "Stopped infininte loop at macro level." <<std::endl;
                return report;
            }
            i++;
            
            currentPolygon = report.finalPolygon;
            currentStart = report.finalPoint;
        }
    }
}


CollisionWorld::CollisionWorld(const std::string &filename){
    std::ifstream file(filename, std::ios::binary);
    
    
    //first, we load all the raw data from the file into polygon objects
    if (file.good()) {
        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        std::vector<char> buffer(size);
        if (file.read(buffer.data(), size))
        {
            
            //first, we read in the polygon types
            int position = 0;
            unsigned int numPolyTypes = *((unsigned int*) &buffer[position]);
            position += sizeof(unsigned int);
            
            for (unsigned int i=0; i<numPolyTypes; i++){
                unsigned int strLen = *((unsigned int*) &buffer[position]);
                position += sizeof(unsigned int);
                
                std::string name = std::string(&buffer[position],strLen);
                
                PolyType* pt = new PolyType();
                pt->number = i;
                pt->name = name;
                polyTypes.push_back(pt);
                
                std::cout << "Found polygon type: " << name <<std::endl;
                
                position += sizeof(char)*strLen;
            }
            
            //now, we read in (and process) the polygons
            //the first go-round we will assign uint indices to the link pointers
            //then later on evaluate them into actual pointers
            unsigned int numPolygons = *((unsigned int*) &buffer[position]);
            position += sizeof(unsigned int);
            
            std::vector<std::vector<unsigned int>> edgeIndices = std::vector<std::vector<unsigned int>>();
            
            for (unsigned int i=0; i<numPolygons; i++){
                Polygon* p = new Polygon();
                
                unsigned int polyType = *((unsigned int*) &buffer[position]);
                position += sizeof(unsigned int);
                p->polyType = polyTypes[polyType];
                
                float normalX = *((float*) &buffer[position]);
                position += sizeof(float);
                float normalY = *((float*) &buffer[position]);
                position += sizeof(float);
                float normalZ = *((float*) &buffer[position]);
                position += sizeof(float);
                glm::vec3 normal = glm::vec3(normalX,normalY,normalZ);
                p->faceNormal = normal;
                
                unsigned int numVerts = *((unsigned int*) &buffer[position]);
                position += sizeof(unsigned int);
                
                glm::vec3 anyPoint = glm::vec3(0,0,0);
                for (unsigned int j=0; j<numVerts; j++){
                    float x = *((float*) &buffer[position]);
                    position += sizeof(float);
                    float y = *((float*) &buffer[position]);
                    position += sizeof(float);
                    float z = *((float*) &buffer[position]);
                    position += sizeof(float);
                    
                    p->verts.push_back(glm::vec2(x,y));
                    anyPoint = glm::vec3(x,y,z);
                }
                
                float d = glm::dot(anyPoint,normal);
                p->xSlope = -(normal.x/normal.z);
                p->ySlope = -(normal.y/normal.z);
                p->zIntercept = d/normal.z;
                
                std::vector<unsigned int>thisPolygonsEdgeIndices = std::vector<unsigned int>();
                for (unsigned int j=0; j<numVerts; j++){
                    unsigned int index = *((unsigned int*) &buffer[position]);
                    position += sizeof(unsigned int);
                    thisPolygonsEdgeIndices.push_back(index);
                }
                edgeIndices.push_back(thisPolygonsEdgeIndices);
                
                
                polygons.push_back(p);
            }
            
            //postprocessing polygons
            for (unsigned int i=0; i<polygons.size(); i++){
                Polygon* p = polygons[i];
                std::vector<unsigned int>thisPolygonsEdgeIndices = edgeIndices[i];
                for (unsigned int j=0; j<thisPolygonsEdgeIndices.size(); j++){
                    unsigned int eI = thisPolygonsEdgeIndices[j];
                    if (eI != 0xFFFFFFFF) p->edgeLinks.push_back(polygons[eI]);
                    else{
                        p->edgeLinks.push_back(nullptr);
                    }
                }
                for (unsigned int j=0; j<p->verts.size(); j++){
                    glm::vec2 a = p->verts[j];
                    glm::vec2 b = p->verts[(j+1)%p->verts.size()];
                    glm::vec2 delta = b-a;
                    float mag = glm::length(delta);
                    glm::vec2 normal = glm::vec2(delta.y/mag,-delta.x/mag);
                    
                    p->edgeNormals.push_back(normal);
                    p->edgesProjected.push_back(glm::dot(a,normal));
                }
            }
            
            
            
            std::cout << "Collision file loaded. " << std::endl;
        }
        else {
            std::cout << "Collision file not loaded. !file.read(...)" << std::endl;
        }
    }
    else {
        std::cout << "Collision file not loaded. !file.good()" << std::endl;
    }
}

CollisionWorld::~CollisionWorld(){
    for (unsigned int i=0; i<polygons.size(); i++){
        delete polygons[i];
    }
}