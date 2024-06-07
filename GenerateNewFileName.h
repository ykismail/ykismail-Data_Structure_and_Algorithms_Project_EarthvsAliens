#pragma once
#include <string>
#include<iostream>
#include <fstream>
#include<sstream>
bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

std::string generateNewFilename(const std::string& filename) {
    if (!fileExists(filename)) {
        return filename;
    }

    size_t pos = filename.find_last_of('.');
    std::string name = filename.substr(0, pos);
    std::string extension = filename.substr(pos);

    int count = 1;
    std::string newFilename;
    do {
        std::ostringstream oss;
        oss << name << "(" << count << ")" << extension;
        newFilename = oss.str();
        if (!fileExists(newFilename)) {
            break;
        }
        ++count;
    } while (true);

    return newFilename;
}
