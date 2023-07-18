#version 410 core

// Variables received from the vertex shader
in float velocity;
in float mass;
in vec3 color;

// Output color
out vec4 FragColor;

void main()
{
    // Normalize the velocity and mass values to be between 0 and 1
    float velocityNormalized = clamp(length(velocity) / 0.01, 0.0, 1.0);
    float massNormalized = clamp(mass / 1.0, 0.0, 1.0);

    // Use the normalized velocity to mix between blue and red for the color
    vec3 colorVelocity = mix(vec3(0.0, 0.0, 1.0), vec3(1.0, 0.0, 0.0), velocityNormalized);

    // Use the normalized mass to determine the brightness of the color
    float brightness = massNormalized;

    // Output the final color
    FragColor = vec4(colorVelocity * brightness, 1.0);
}
