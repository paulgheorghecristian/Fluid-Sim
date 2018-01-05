#ifndef SIMULATIONGRID_H
#define SIMULATIONGRID_H

#include "LineMesh.h"

class Texture;

#define SimIndex(i, j) (i*(N+2) + j)

class SimulationGrid
{
    public:
        SimulationGrid (unsigned int N, unsigned int screenWidth, unsigned int screenHeight);
        void addDensity (float x, float y, float amount); /*x = width y = height */
        void drawGrid ();
        void updateInitialTexture ();
        Texture *getInitialTexture ();
        virtual ~SimulationGrid ();
    protected:
    private:
        const unsigned int N, screenWidth, screenHeight, totalSize;
        float rectangleWidth, rectangleHeight;
        float *density, *prev_density, *u[2], *data;
        LineMesh *lineMesh;
        Texture *initialDensityAndVelocity;

        void coordsToIndices (const float &x, const float &y, int &i, int &j);
};

#endif // SIMULATIONGRID_H
