#ifndef LUMINATE_UTILITY_H
#define LUMINATE_UTILITY_H

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

/**
 * Load GLSL shaders and compile a shader program.
 */
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

/**
 * Get the GLSL shader program with the given handle.
 */
GLuint GetShaderProgram(int index);

/**
 * Get an unused texture ID from OpenGL.
 */
GLuint GetGLTexID();

/**
 * Bind a blank texture to OpenGL.
 */
void BindBlankTexture();

/**
 * Get an array of N random floats.
 */
float* GetRandomFloats(int num);

/**
 * Get an array of N integer points within the specified bounds.
 */
glm::ivec2* GetRandomIntPoints(int num_points, int min_x, int max_x, int min_y, int max_y);

/**
 * Get an array of random RGB colours.
 */
glm::vec3* GetRandomColours(int num_colours);

/**
 * Get an array of HSV colours with random hues and a specified saturation and value.
 */
glm::vec3* GetRandomHues(int num_colours, float saturation, float value);

/**
 * Convert an HSV colour to and RGB colour.
 */
glm::vec3 ConvertHSVtoRGB(glm::vec3 hsv_colour);

#endif