#include "LineMesh.h"

LineMesh::LineMesh(const std::vector<glm::vec2> &linePositions) : numOfLines (linePositions.size() / 2)
{
    //vao care retine starea meshei
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    glGenBuffers(1, &vboHandle);

    //trimit GPU-ului vertecsii
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof (glm::vec2) * linePositions.size (),
                 &linePositions[0],
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof (glm::vec2), (void*) 0);

    glBindVertexArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, 0);
}

void LineMesh::draw () {
    glBindVertexArray (vaoHandle);
    glDrawArrays (GL_LINES, 0, numOfLines*2);
    glBindVertexArray (0);
}

LineMesh::~LineMesh()
{
    glDeleteBuffers(1, &vboHandle);
    glDeleteVertexArrays(1, &vaoHandle);
}
