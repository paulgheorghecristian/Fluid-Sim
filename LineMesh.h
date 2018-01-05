#ifndef LINEMESH_H
#define LINEMESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class LineMesh
{
    public:
        LineMesh(const std::vector<glm::vec2> &linePositions);
        void draw ();
        virtual ~LineMesh();
    protected:
    private:
        GLuint vaoHandle, vboHandle;
        unsigned int numOfLines;
};

#endif // LINEMESH_H
