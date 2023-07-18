//
// Created by Aaron Li on 6/11/23.
//

#include "Render.hpp"
#include <SDL2/SDL.h>

/**
 * Constructor: Set up view and projection matrices, initialize SDL and OpenGL context,
 * load OpenGL function pointers, initialize and bind VAO and VBO, and set vertex attributes.
 */
Render::Render() {
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    viewMatrix = glm::lookAt(cameraPos, cameraTarget, upVector);

    float fieldOfView = glm::radians(45.0f);
    float aspectRatio = 1000.0f / 1000.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    projectionMatrix = glm::perspective(fieldOfView, aspectRatio, nearPlane, farPlane);

    // Initialize SDL and create an OpenGL context
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    window = SDL_CreateWindow("Particle Simulation",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              1000, 1000,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);


    glContext = SDL_GL_CreateContext(window);

    // Load OpenGL function pointers
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    // Initialize VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the VAO and VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, velocity));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, mass));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, color));
    glEnableVertexAttribArray(3);


    // Unbind the VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


/**
 * Draws a list of vertices using a given shader, binds the VAO, updates the VBO with vertex data,
 * and then draws the points.
 * @param shader The shader to use for rendering the vertices.
 * @param vertices The list of vertices to draw.
 */
void Render::draw(Shader& shader, const std::vector<VertexData>& vertices) {
    shader.use();
    shader.setMat4("view", viewMatrix);
    shader.setMat4("projection", projectionMatrix);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), &vertices[0], GL_STATIC_DRAW);

    glPointSize(100.0f);
    glDrawArrays(GL_POINTS, 0, vertices.size());

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/**
 * Destructor: Clean up by deleting the VAO and VBO.
 */
Render::~Render() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
