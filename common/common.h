#pragma once
#include <GL/glew.h>
#include <stdbool.h>
#include <stdarg.h>
#include <GLFW/glfw3.h>

#define GL_LOG_FILE "gl.log"

#define STANDARD_WIDTH  640
#define STANDARD_HEIGHT 480

extern int window_width, window_height, fb_width, fb_height;

bool restart_gl_log();
bool gl_log(const char *message, ...);
bool gl_log_error(const char *message, ...);
void glfw_error_callback(int error, const char *description);
void glfw_window_resize_callback(GLFWwindow *window, int width, int height);
void glfw_framebuffer_resize_callback(GLFWwindow *window, int width, int height);

//Shader stuff
void print_shader_info(GLuint shader_index);
const char* GL_type_to_string (GLenum type);
void print_shader_program_info(GLuint program);
void print_all_shader_program_info(GLuint program);
bool is_shader_program_valid(GLuint program);
