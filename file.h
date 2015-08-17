#pragma once

#include <fstream>
#include <iostream>

inline std::string readFile(const std::string &filename){
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (file.good()) {
        std::string out;
        file.seekg(0, std::ios::end);
        out.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&out[0], out.size());
        file.close();
        return out;
    }
    else {
        std::cout << "File '" << filename << "'not loaded. - !file.good()" << std::endl;
        return "ERR";
    }
}