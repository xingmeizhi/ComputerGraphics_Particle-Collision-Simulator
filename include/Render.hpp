//
// Created by Aaron Li on 6/11/23.
//

#ifndef PART1_RENDER_HPP
#define PART1_RENDER_HPP

#include "Shader.hpp"
#include <vector>
#include <glm/glm/glm.hpp>
#include <SDL2/SDL.h>
#include <glm/glm/gtc/matrix_transform.hpp>


struct VertexData {
    glm::vec3 position;
    float velocity;
    float mass;
    glm::vec3 color;
};

class Render {
private:
    unsigned int VBO, VAO;
    SDL_Window *window;
    SDL_GLContext glContext;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

public:
    /**
     * Default constructor.
     */
    Render();

    /**
     * Destructor.
     */
    ~Render();


    /**
    * Draws a list of vertices using a given shader, binds the VAO, updates the VBO with vertex data,
    * and then draws the points.
    * @param shader The shader to use for rendering the vertices.
    * @param vertices The list of vertices to draw.
    */
    void draw(Shader &shader, const std::vector<VertexData> &vertices);

    /**
     * Returns the window in which rendering takes place.
     *
     * @return A pointer to the SDL_Window.
     */
    SDL_Window *getWindow() { return window; }

    /**
     * Returns the OpenGL rendering context.
     *
     * @return The SDL_GLContext.
     */
    SDL_GLContext getContext() { return glContext; }
};

#endif //PART1_RENDER_HPP
