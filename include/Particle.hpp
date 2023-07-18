// Created by Aaron Li on 6/9/23.
//

#ifndef PART1_PARTICLE_HPP
#define PART1_PARTICLE_HPP

#include <glm/glm/glm.hpp>
#include <string>
#include "Render.hpp"

class Particle {
public:
    /**
     * Constructs a new Particle object with the given parameters.
     *
     * @param position The initial position of the particle.
     * @param velocity The initial velocity of the particle.
     * @param color The color of the particle.
     * @param mass The mass of the particle.
     */
    Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 color, float mass);

    /**
     * Updates the particle's position based on its velocity and the elapsed time.
     *
     * @param dt The time elapsed since the last update, in seconds.
     */
    void update(float dt);

    /**
     * Renders the particle using the given renderer and shader.
     *
     * @param renderer The renderer to use for drawing the particle.
     * @param shader The shader to use for coloring the particle.
     */
    void render(Render &renderer, Shader &shader) const;

    // Getter methods
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getVelocity() const { return velocity; }
    float getMass() const { return mass; }

    // Setter methods
    void setPosition(const glm::vec3 &pos) { position = pos; }
    void setVelocity(const glm::vec3 &vel) { velocity = vel; }

private:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 color;
    float mass;
};


#endif //PART1_PARTICLE_HPP
