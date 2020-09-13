#pragma once

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

namespace Renderer
{
    class OBJLoader;
}
    class OBJLoader
    {
    public:
        OBJLoader() = default;
        ~OBJLoader() = default;
        std::vector<double>* FileLoader(const std::string& ObjFile);
        OBJLoader(const OBJLoader&) = delete;
        OBJLoader(const OBJLoader&&) = delete;
        OBJLoader& operator = (const OBJLoader&) = delete;
        OBJLoader& operator = (const OBJLoader&&) = delete;
 
    private:
        struct Face 
        {
            struct vertex
            {
            GLuint v_i;
            GLuint vt_i;
            GLuint vn_i;
			};
            vertex v[3];

            Face(vertex v1, vertex v2, vertex v3)
            {
                v[0] = v1;
                v[1] = v2;
                v[2] = v3;
            }
        };
        std::vector<std::string>file;
        std::vector<glm::vec3> vertex;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> textCord;
        std::vector<Face> faces;
        void creatArrayObj(const std::string& objFile);
    }; 