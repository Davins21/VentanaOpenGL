#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

// Definición de la estructura de Vértice
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec2 TexCoords;
};

class BlockGenerator {
public:
    // Firma de la función para agregar una caja 3D
    static void AgregarCaja(
        std::vector<Vertex>& vertices,
        std::vector<GLuint>& indices,
        glm::vec3 min, glm::vec3 max,
        glm::vec3 color
    );

    // Firma de la función para armar el hongo
    static void GenerarHongoCaja(
        std::vector<Vertex>& vertices,
        std::vector<GLuint>& indices
    );
}; 
