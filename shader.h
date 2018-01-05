#ifndef SHADER_H
#define SHADER_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <string.h>
#include <glm/glm.hpp>

class Shader
{
    public:
        Shader(const std::string& vShaderPath, const std::string &fShaderPath);
        std::string load_shader(const std::string&);
        void bind();
        void getAllUniformLocations();
        void loadColor(glm::vec4);
        void loadVector(GLuint, glm::vec4);
        void loadMatrix(GLuint, glm::mat4);
        void loadProjectionMatrix(glm::mat4);
        void loadModelMatrix(glm::mat4);
        void loadViewMatrix(glm::mat4);
        void loadCoords(float, float, float, float);
        void loadMaxIter(int);
        void loadC(glm::vec2);
        void loadGeneralUniform (const std::string &name, int data);
        void loadGeneralUniform (const std::string &name, float data);
        virtual ~Shader();
    protected:
    private:
        GLuint vertex_handle, fragment_handle;
        GLuint program;
        GLuint projMat_location, modelMat_location, colorVector_location, min_coords_location, max_coords_location;
        GLuint max_iter_location;
        GLuint c_location;
        GLuint viewMat_location;
};

#endif // SHADER_H
