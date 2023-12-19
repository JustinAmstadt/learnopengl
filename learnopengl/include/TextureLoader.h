#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <iostream>
#include <glad/glad.h>

class TextureLoader{
public:
    static unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

};
#endif