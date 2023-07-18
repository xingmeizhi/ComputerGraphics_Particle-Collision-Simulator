#version 410 core

// Vertex input: position, velocity, mass, color
layout (location = 0) in vec3 aPos;
layout (location = 1) in float aVelocity;
layout (location = 2) in float aMass;
layout (location = 3) in vec3 aColor;

// Uniforms for the view and projection matrices
uniform mat4 view;
uniform mat4 projection;

// Variables to be passed to the fragment shader
out float velocity;
out float mass;
out vec3 color;

void main()
{
    // Transform the vertex position by the view and projection matrices
    gl_Position = projection * view * vec4(aPos, 1.0);

    // Pass through the velocity, mass and color to the fragment shader
    velocity = aVelocity;
    mass = aMass;
    color = aColor;
}
