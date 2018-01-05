#include "SimulationGrid.h"

#include <iostream>
#include "texture.h"
#include <limits.h>

SimulationGrid::SimulationGrid (unsigned int N,
                                unsigned int screenWidth,
                                unsigned int screenHeight) : N (N),
                                                             screenWidth (screenWidth),
                                                             screenHeight (screenHeight),
                                                             totalSize ((N+2) * (N+2)),
                                                             rectangleWidth ((float) screenWidth / N),
                                                             rectangleHeight ((float) screenHeight / N)
{
    density = (float *) calloc (totalSize, sizeof (float));
    u[0] = (float *) calloc (totalSize, sizeof (float));
    u[1] = (float *) calloc (totalSize, sizeof (float));

    for (unsigned int i = 0; i < totalSize; i++) {
        u[0][i] = 1;
        u[1][i] = 1;
    }

    std::vector <glm::vec2> positions;

    for (unsigned int i = 0; i < N; i++) {
        positions.push_back (glm::vec2 (rectangleWidth*i, 0));
        positions.push_back (glm::vec2 (rectangleWidth*i, screenHeight));

        positions.push_back (glm::vec2 (0, rectangleHeight*i));
        positions.push_back (glm::vec2 (screenWidth, rectangleHeight*i));
    }

    lineMesh = new LineMesh (positions);
    initialDensityAndVelocity = new Texture (GL_RGB32F, N, N, GL_RGB, GL_FLOAT, NULL);

    data = (float *) malloc (sizeof (float ) * N * N * 3);
}

void SimulationGrid::addDensity (float x, float y, float amount) {
    int i, j;

    coordsToIndices (x, y, j, i);
    density[SimIndex(i, j)] += amount;
    /*for (int q = i; q < i+10; q++) {
        for (int w = j; w < j+10; w++) {
            density[SimIndex(q, w)] += amount;
        }
    }*/

}

void SimulationGrid::drawGrid() {
    lineMesh->draw();
}

void SimulationGrid::coordsToIndices (const float &x, const float &y, int &i, int &j) {
    i = x / rectangleWidth;
    j = y / rectangleHeight;

    i++;j++;
}

void SimulationGrid::updateInitialTexture () {
    #define Ind(i,j) ((i)*3*N + j)
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= 3*N; j += 3) {
            data[Ind(i-1, j-1)] = density[SimIndex(i, (j-1)/3 + 1)];
            data[Ind(i-1, j)] = u[0][SimIndex(i, (j-1)/3 + 1)];
            data[Ind(i-1, j+1)] = u[1][SimIndex(i, (j-1)/3 + 1)];
        }
    }
    #undef Ind

    initialDensityAndVelocity->bind();
    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    0,
                    0,
                    N,
                    N,
                    GL_RGB,
                    GL_FLOAT,
                    (void *) &data[0]);
    initialDensityAndVelocity->unbind();
}

Texture *SimulationGrid::getInitialTexture () {
    return initialDensityAndVelocity;
}

SimulationGrid::~SimulationGrid ()
{
    free (density);
    free (u[0]);
    free (u[1]);
    delete lineMesh;
    delete initialDensityAndVelocity;
    free (data);
}
