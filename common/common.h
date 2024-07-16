#pragma once
#include <stdbool.h>
#include <stdarg.h>
#include <GLFW/glfw3.h>


#define GL_LOG_FILE "gl.log"

#define STANDARD_WIDTH  640
#define STANDARD_HEIGHT 480

bool restart_gl_log();
bool gl_log(const char *message, ...);
bool gl_log_error(const char *message, ...);
void glfw_error_callback(int error, const char *description);
void glfw_window_resize_callback(GLFWwindow *window, int *c_width, int *c_height, int width, int height);
void glfw_framebuffer_resize_callback(GLFWwindow *window, int *c_width, int *c_height, int width, int height);
