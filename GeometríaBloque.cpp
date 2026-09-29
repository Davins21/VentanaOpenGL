#include "BlockGenerator.h"

void BlockGenerator::AgregarCaja(
    std::vector<Vertex>& vertices,
    std::vector<GLuint>& indices,
    glm::vec3 min, glm::vec3 max,
    glm::vec3 color)
{
    GLuint baseIndex = (GLuint)vertices.size();

    Vertex v[8] = {
        { {min.x, min.y, max.z}, color, {0.0f, 0.0f} }, // 0: Frente-Inf-Izq
        { {max.x, min.y, max.z}, color, {1.0f, 0.0f} }, // 1: Frente-Inf-Der
        { {max.x, max.y, max.z}, color, {1.0f, 1.0f} }, // 2: Frente-Sup-Der
        { {min.x, max.y, max.z}, color, {0.0f, 1.0f} }, // 3: Frente-Sup-Izq

        { {min.x, min.y, min.z}, color, {1.0f, 0.0f} }, // 4: Atrás-Inf-Izq
        { {max.x, min.y, min.z}, color, {0.0f, 0.0f} }, // 5: Atrás-Inf-Der
        { {max.x, max.y, min.z}, color, {0.0f, 1.0f} }, // 6: Atrás-Sup-Der
        { {min.x, max.y, min.z}, color, {1.0f, 1.0f} }  // 7: Atrás-Sup-Izq
    };

    for (int i = 0; i < 8; ++i) {
        vertices.push_back(v[i]);
    }

    GLuint ind[] = {
        0, 1, 2,   2, 3, 0, // Frente
        5, 4, 7,   7, 6, 5, // Atrás
        4, 0, 3,   3, 7, 4, // Izquierda
        1, 5, 6,   6, 2, 1, // Derecha
        3, 2, 6,   6, 7, 3, // Arriba
        4, 5, 1,   1, 0, 4  // Abajo
    };

    for (int i = 0; i < 36; ++i) {
        indices.push_back(baseIndex + ind[i]);
    }
}

void BlockGenerator::GenerarHongoCaja(std::vector<Vertex>& vertices, std::vector<GLuint>& indices)
{
    // 1. TALLO (Prisma Piel/Beige)
    glm::vec3 minTallo(-0.25f, -0.6f, -0.25f);
    glm::vec3 maxTallo(0.25f, 0.0f, 0.25f);
    glm::vec3 colorTallo(1.0f, 0.85f, 0.7f);

    AgregarCaja(vertices, indices, minTallo, maxTallo, colorTallo);

    // 2. SOMBRERO (Caja Roja)
    glm::vec3 minSombrero(-0.5f, 0.0f, -0.5f);
    glm::vec3 maxSombrero(0.5f, 0.6f, 0.5f);
    glm::vec3 colorSombrero(0.9f, 0.1f, 0.1f);

    AgregarCaja(vertices, indices, minSombrero, maxSombrero, colorSombrero);
}