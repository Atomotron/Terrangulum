#pragma once

class Refcounted{
private:
    unsigned int references;
public:
    Refcounted(){
        references = 0;
    }

    void reference(){
        references += 1;
    }
    
    void dereference(){
        references -= 1;
        if (references == 0){
            delete this;
        }
    }

};