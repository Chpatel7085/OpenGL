#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <glm/glm.hpp>
#include "shader.h"
#include "texture.h"

struct Vertex {
    /*
        vertex values
    */
    // position
    glm::vec3 pos;
    // normal vector
    // texture coordinate
    glm::vec2 texCoord;
    // tangent vector
    // generate list of vertices
    static std::vector<struct Vertex> genList(float* vertices, int noVertices);

    // calculate tangent vectors for each face
   // static void calcTanVectors(std::vector<Vertex>& list, std::vector<unsigned int>& indices);
};

typedef struct Vertex Vertex;

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO;

    std::vector<Texture> textures;

    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    void render(Shader shader);

    void cleanup();


private:
    unsigned int VBO, EBO;

    void setup();
};
#endif