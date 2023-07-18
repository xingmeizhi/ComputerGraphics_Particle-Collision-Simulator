//
// Created by Aaron Li on 6/11/23.
//

#ifndef PART1_SHADER_HPP
#define PART1_SHADER_HPP

#include <string>
#include <glad/glad.h>
#include <glm/glm/glm.hpp>


/**
 * The Shader class is used to compile and use OpenGL shader programs.
 */
class Shader
{
public:
    unsigned int ID; // ID of the shader program

    /**
     * Constructor that reads and builds the shader from the provided vertex and fragment shader files.
     * @param vertexPath File path for the vertex shader.
     * @param fragmentPath File path for the fragment shader.
     */
    Shader(const char* vertexPath, const char* fragmentPath);

    /**
     * Function to activate the shader program.
     */
    void use();

    /**
     * Utility function to set a mat4 uniform in the shader.
     * @param name Name of the mat4 uniform in the shader.
     * @param mat Mat4 value to set.
     */
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    /**
     * Function to check and report shader compilation and linking errors.
     * @param shader Shader or program to check.
     * @param type Type of shader ("VERTEX", "FRAGMENT", or "PROGRAM").
     */
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif //PART1_SHADER_HPP
