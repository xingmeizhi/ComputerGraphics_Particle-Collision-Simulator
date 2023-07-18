//
// Created by Aaron Li on 6/9/23.
//
#include "Particle.hpp"
#include "Render.hpp"

/**
 * Constructs a new Particle object with the given parameters.
 *
 * @param position The initial position of the particle.
 * @param velocity The initial velocity of the particle.
 * @param color The color of the particle.
 * @param mass The mass of the particle.
 */
Particle::Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 color, float mass)
        : position(position), velocity(velocity), color(color), mass(mass) {}


/**
* Updates the particle's position based on its velocity and the elapsed time.
*
* @param dt The time elapsed since the last update, in seconds.
*/
void Particle::update(float dt) {
    position += velocity * dt;
}


/**
 * Renders the particle using the given renderer and shader.
 *
 * @param renderer The renderer to use for drawing the particle.
 * @param shader The shader to use for coloring the particle.
 */
void Particle::render(Render& renderer, Shader& shader) const {
    VertexData data;
    data.position = position;
    data.velocity = glm::length(velocity);
    data.mass = mass;
    data.color = color;
    renderer.draw(shader, {data});
}



