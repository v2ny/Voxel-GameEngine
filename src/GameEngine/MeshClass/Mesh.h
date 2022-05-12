#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>
#include <Organizing/VAO/VAO.h>
#include <Organizing/VBO/VBO.h>
#include <Organizing/EBO/EBO.h>
#include <Camera.h>
#include <Texture.h>

class Mesh
{
    public:
        std::vector <Vertex> vertices;
        std::vector <GLuint> indices;
        std::vector <Texture> textures;

        VAO VAO;

        Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

        void Draw(Shader& shader, Camera& camera);
};

#endif //MESH_CLASS_H