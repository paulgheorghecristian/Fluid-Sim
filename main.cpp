#include <iostream>
#include "display.h"
#include "shader.h"
#include "input.h"
#include "texture.h"
#include "framebuffer.h"
#include "SimulationGrid.h"
#include "mesh.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

#define N 100
#define WIDTH 600
#define HEIGHT 600
#define dt 16.6f

int main()
{
    Display display (WIDTH, HEIGHT, "Fluid Sim");
    Shader drawGridShader ("res/shaders/vertex", "res/shaders/fragment");
    Shader drawFluidParticles ("res/shaders/drawFluidParticles.vs", "res/shaders/drawFluidParticles.fs");
    Shader diffusionShader ("res/shaders/diffuse.vs", "res/shaders/diffuse.fs");
    Shader advectionShader ("res/shaders/advection.vs", "res/shaders/advection.fs");
    Framebuffer diffusionFramebuffer (N, N);
    Framebuffer advectionFramebuffer (N, N);
    diffusionFramebuffer.clear();
    advectionFramebuffer.clear();
    SimulationGrid simGrid (N, WIDTH, HEIGHT);
    Input input;
    long startTime, endTime;
    long unprocessedTime = 0, frameTime = 0;
    bool draw, startSim = false;
    int FPS = 0;
    float kineticViscosity = 0.3f;
    Mesh *particleMesh = Mesh::get_rectangle_mesh (0.0f, 0.0f, WIDTH, HEIGHT);

    display.set_viewport(0.0f, 0.0f, WIDTH, HEIGHT);

    drawGridShader.bind();
    drawGridShader.loadProjectionMatrix (glm::ortho (0.0f, (float) WIDTH, 0.0f, (float) HEIGHT, 1.0f, 1000.0f));

    drawFluidParticles.bind();
    drawFluidParticles.loadProjectionMatrix (glm::ortho (0.0f, (float) WIDTH, 0.0f, (float) HEIGHT, 1.0f, 1000.0f));
    drawFluidParticles.loadGeneralUniform ("N", N);
    drawFluidParticles.loadGeneralUniform ("densityAndVelocitySampler", 0);

    diffusionShader.bind();
    diffusionShader.loadProjectionMatrix (glm::ortho (0.0f, (float) WIDTH, 0.0f, (float) HEIGHT, 1.0f, 1000.0f));
    diffusionShader.loadGeneralUniform ("N", N);
    diffusionShader.loadGeneralUniform ("previousDensitySampler", 0);
    diffusionShader.loadGeneralUniform ("dt", dt/1000.0f);
    diffusionShader.loadGeneralUniform ("kineticViscosity", kineticViscosity);

    advectionShader.bind();
    advectionShader.loadProjectionMatrix (glm::ortho (0.0f, (float) WIDTH, 0.0f, (float) HEIGHT, 1.0f, 1000.0f));
    advectionShader.loadGeneralUniform ("N", N);
    advectionShader.loadGeneralUniform ("previousDensitySampler", 0);
    advectionShader.loadGeneralUniform ("dt", dt/1000.0f);

    startTime = SDL_GetTicks();

    while(!display.isClosed ()) {
        display.clear (1.0f, 1.0f, 1.0f, 1.0f);
        draw = false;

        if (frameTime >= 1000) {
            std::cout << "FPS=" << FPS << std::endl;
            FPS = 0;
            frameTime = 0;
        }

        while (unprocessedTime >= dt) {
            draw = true;
            input.update (display.getWindow());

            if (!startSim && input.GetMouse (1)) {
                glm::vec2 mousePosition = input.GetMousePos();
                simGrid.addDensity (mousePosition.x, mousePosition.y, 2.0f);
                simGrid.updateInitialTexture ();
            }

            if (input.GetKeyDown(SDLK_e)) {
                startSim = true;
            }
            if (input.GetKeyDown(SDLK_r)) {
                startSim = false;
            }

            if (startSim) {
                /*advectionFramebuffer.bind();

                simGrid.getInitialTexture()->use (0);
                particleMesh->draw();

                advectionFramebuffer.unbind();
                advectionFramebuffer.swapTextures (simGrid.getInitialTexture()->get_texture_id());*/

                diffusionFramebuffer.bind();

                for (int k = 0; k < 5; k++) {
                    diffusionShader.bind();

                    simGrid.getInitialTexture()->use (0);
                    particleMesh->draw();

                    diffusionFramebuffer.swapTextures (simGrid.getInitialTexture()->get_texture_id());
                }

                diffusionFramebuffer.unbind();
                //startSim = false;
                //diffusionFramebuffer.swapTextures (simGrid.getInitialTexture()->get_texture_id());
            }
            unprocessedTime -= dt;
        }

        if (draw) {
            FPS++;

            drawGridShader.bind();
            simGrid.drawGrid();

            drawFluidParticles.bind();
            simGrid.getInitialTexture()->use (0);
            particleMesh->draw();

            display.update();
        }

        endTime = SDL_GetTicks();
        unprocessedTime += endTime - startTime;
        frameTime += endTime - startTime;
        startTime = endTime;
    }

    return 0;
}

