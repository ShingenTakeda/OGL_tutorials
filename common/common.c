#include <stdio.h>
#include <time.h>
#include "common.h"

bool restart_gl_log()
{
  FILE *file = fopen(GL_LOG_FILE, "w");

  if(!file)
  {
    fprintf(stderr, "ERROR: could not open GL_LOG_FILE log file %s for writing\n", GL_LOG_FILE);
    return false;
  }

  time_t now = time(NULL);
  char *date = ctime(&now);
  fprintf(file, "GL_LOG_FILE log. local time %s\n", date);
  fclose(file);
  return true;
}

bool gl_log(const char *message, ...)
{
  va_list argptr;
  FILE *file = fopen(GL_LOG_FILE, "a");

  if(!file)
  {
    fprintf(stderr, "ERROR: could not open GL_LOG_FILE %s for appending\n", GL_LOG_FILE);
    return false;
  }

  va_start(argptr, message);
  vfprintf(file, message, argptr);
  va_end(argptr);
  fclose(file);

  return true;
}

bool gl_log_error(const char *message, ...)
{
  va_list argptr;
  FILE *file = fopen(GL_LOG_FILE, "a");
  if(!file)
  {
    fprintf(stderr, "ERROR: could not open GL_LOG_FILE %s file for appending\n", GL_LOG_FILE);
    return false;
  }

  va_start(argptr, message);
  vfprintf(file, message, argptr);
  va_end(argptr);
  va_start(argptr, message);
  vfprintf(file, message, argptr);
  va_end(argptr);
  fclose(file);
  return true;
}

void glfw_error_callback(int error, const char *description)
{
  gl_log_error("GLFW ERROR: code %i | MSG: %s\n", error, description);
}

void glfw_window_resize_callback(GLFWwindow *window, int *c_width, int *c_height, int width, int height)
{
  *c_width = width;
  *c_height = height;
}

void glfw_framebuffer_resize_callback(GLFWwindow *window, int *c_width, int *c_height, int width, int height)
{
  *c_width = width;
  *c_height = height;
}
