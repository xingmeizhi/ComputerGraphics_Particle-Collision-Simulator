//
// Created by Aaron Li on 6/9/23.
//

#include <SDL2/SDL.h>
#include "glad/glad.h"
#include "Shader.hpp"
#include "Particle.hpp"
#include "Render.hpp"
#include "Simulation.hpp"
#include "iostream"

void checkGLError(const std::string& checkpoint) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error at " << checkpoint << ": " << err << std::endl;
    }
}


int main(int argc, char** argv) {

    // Create the Render
    Render render;

    // Get the window and context from the Render
    SDL_Window* window = render.getWindow();
    SDL_GLContext context = render.getContext();

    // Check if window and context are created successfully
    if (window == nullptr) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    if (context == nullptr) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Load OpenGL using glad
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    checkGLError("After initializing OpenGL");

    // Print OpenGL version
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    // Create the shader
    Shader shader("./shaders/vert.glsl", "./shaders/frag.glsl");
    checkGLError("After creating the shader");
    // Create the simulation
    Simulation simulation(render,shader);


    // Add some particles to the simulation
    simulation.addParticle(Particle(glm::vec3(-0.5f, 1.0f, 0.0f), glm::vec3(0.009f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f));
    simulation.addParticle(Particle(glm::vec3(0.5f, 1.0f, 0.0f), glm::vec3(-0.001f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.2f));

    // Random particles
    simulation.addRandomParticles(15);


    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                        running = false;
                    }
                    break;
                default:
                    break;
            }
        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        checkGLError("After clearing the screen");

        // Simulate and render
        simulation.simulate(0.01f);
        simulation.render();
        checkGLError("After simulating and rendering");

        SDL_GL_SwapWindow(window);
        checkGLError("After swapping the window");
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


