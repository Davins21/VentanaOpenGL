#pragma once

#include <glad/glad.h>
#include <string>

class Texture
{
public:
    GLuint ID;
    std::string type; // Útil si en el futuro usas mapas de especular o normales

    // Constructor que carga la imagen y configura OpenGL
    Texture(const char* imagePath);

    // Métodos para usar y limpiar la textura
    void Bind(GLenum textureUnit = GL_TEXTURE0);
    void Unbind();
    void Delete();
};