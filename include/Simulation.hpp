//
// Created by Aaron Li on 6/9/23.
//

#ifndef PART1_SIMULATION_HPP
#define PART1_SIMULATION_HPP

#include <vector>
#include <glm/glm/glm.hpp>
#include "Particle.hpp"
#include "Render.hpp"
#include "Shader.hpp"

/**
 * The Simulation class is responsible for managing and updating a collection of particles.
 */
class Simulation {
private:
    const float particleRadius = 0.05f;
    std::vector<Particle> particles; // A list of particles in the simulation
    Render& renderer; // The renderer to use for drawing the particles
    Shader& shader; // The shader to use for the particles

    /**
     * Handles the collisions between the particles in the simulation.
     */
    void handleCollisions();

public:
    /**
     * Constructs a new simulation.
     * @param renderer The renderer to use for drawing the particles.
     * @param shader The shader to use for the particles.
     */
    Simulation(Render& renderer, Shader& shader);

    /**
     * Adds a particle to the simulation.
     * @param particle The particle to add.
     */
    void addParticle(const Particle& particle);

    /**
     * Updates the state of the simulation over the specified time interval.
     * @param dt The time interval to simulate, in seconds.
     */
    void simulate(float dt);

    /**
     * Renders the particles in the simulation.
     */
    void render();

    /**
     * Adds a specified number of randomly placed and colored particles to the simulation.
     * @param num The number of particles to add.
     */
    void addRandomParticles(int num);
};

#endif //PART1_SIMULATION_HPP
