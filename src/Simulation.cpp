// Created by Aaron Li on 6/9/23.
//
#include "Simulation.hpp"
#include <random>

/**
 * Constructs a new simulation.
 * @param renderer The renderer to use for drawing the particles.
 * @param shader The shader to use for the particles.
 */
Simulation::Simulation(Render& renderer, Shader& shader)
        : renderer(renderer), shader(shader) {
}

/**
 * Handles the collisions between the particles in the simulation.
 */
void Simulation::handleCollisions() {
    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            glm::vec3 diff = particles[i].getPosition() - particles[j].getPosition();
            float distance = glm::length(diff);
            if (distance < 2.0f * particleRadius) {

                float overlap = 2.0f * particleRadius - distance;


                glm::vec3 normal = glm::normalize(diff);
                glm::vec3 relativeVelocity = particles[i].getVelocity() - particles[j].getVelocity();
                float impulse = glm::dot(relativeVelocity, normal);

                if (impulse < 0.0f) {

                    particles[i].setPosition(particles[i].getPosition() + overlap / 2.0f * normal);
                    particles[j].setPosition(particles[j].getPosition() - overlap / 2.0f * normal);


                    float totalMass = particles[i].getMass() + particles[j].getMass();
                    float impulseI = 2.0f * particles[j].getMass() / totalMass * impulse;
                    float impulseJ = 2.0f * particles[i].getMass() / totalMass * impulse;

                    particles[i].setVelocity(particles[i].getVelocity() - impulseI * normal);
                    particles[j].setVelocity(particles[j].getVelocity() + impulseJ * normal);
                }
            }
        }
    }
}



/**
 * Adds a particle to the simulation.
 * @param particle The particle to add.
 */
void Simulation::addParticle(const Particle& particle) {
    particles.push_back(particle);
}


/**
 * Updates the state of the simulation over the specified time interval.
 * @param dt The time interval to simulate, in seconds.
 */
void Simulation::simulate(float dt) {
    float boundary = 1.2f;
    int numIterations = 5;

    for (int iteration = 0; iteration < numIterations; ++iteration) {
        handleCollisions();
        for (Particle& particle : particles) {
            glm::vec3 pos = particle.getPosition();

            for (int i = 0; i < 3; ++i) {
                if (std::abs(pos[i]) > boundary) {
                    glm::vec3 velocity = particle.getVelocity();
                    velocity[i] = -velocity[i];
                    particle.setVelocity(velocity);
                }
            }

            particle.update(dt);
        }
    }
}


/**
  * Renders the particles in the simulation.
  */
void Simulation::render() {
    for (Particle& particle : particles) {
        particle.render(renderer, shader);
    }
}

/**
 * Adds a specified number of randomly placed and colored particles to the simulation.
 * @param num The number of particles to add.
 */
void Simulation::addRandomParticles(int numParticles) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<float> positionDistribution(-1.0f, 1.0f);
    std::uniform_real_distribution<float> velocityDistribution(-0.01f, 0.01f);
    std::uniform_real_distribution<float> massDistribution(0.1f, 1.0f);
    std::uniform_real_distribution<float> colorDistribution(0.0f, 1.0f);

    for(int i = 0; i < numParticles; ++i) {
        glm::vec3 position(positionDistribution(generator), positionDistribution(generator), 0.0f); // set z to 0
        glm::vec3 velocity(velocityDistribution(generator), velocityDistribution(generator), 0.0f); // set z to 0
        glm::vec3 color(0.0f, 0.0f, 0.0f);
        float mass = massDistribution(generator);
        addParticle(Particle(position, velocity, color, mass));
    }
}




