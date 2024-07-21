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

void glfw_window_resize_callback(GLFWwindow *window, int width, int height)
{
  window_width = width;
  window_height = height;
}

void glfw_framebuffer_resize_callback(GLFWwindow *window, int width, int height)
{
  fb_width = width;
  fb_height = height;
}

void print_shader_info(GLuint shader_index)
{
  int max_length = 2048;
  int actual_length = 0;
  char log[2048];
  glGetShaderInfoLog(shader_index, max_length, &actual_length, log);
  printf("shader info log for GL index %u:\n%s\n", shader_index, log);
}

void print_shader_program_info(GLuint program)
{
  int max_length = 2048;
  int actual_length = 0;
  char log[2048];
  glGetProgramInfoLog(program, max_length, &actual_length, log);
  printf("program info log for GL index %u:\n%s", program, log);
}

const char* GL_type_to_string (GLenum type)
{
  switch (type) 
  {
    case GL_BOOL: return "bool";
    case GL_INT: return "int";
    case GL_FLOAT: return "float";
    case GL_FLOAT_VEC2: return "vec2";
    case GL_FLOAT_VEC3: return "vec3";
    case GL_FLOAT_VEC4: return "vec4";
    case GL_FLOAT_MAT2: return "mat2";
    case GL_FLOAT_MAT3: return "mat3";
    case GL_FLOAT_MAT4: return "mat4";
    case GL_SAMPLER_2D: return "sampler2D";
    case GL_SAMPLER_3D: return "sampler3D";
    case GL_SAMPLER_CUBE: return "samplerCube";
    case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
    default: break;
  }

  return "other";
}

bool is_shader_program_valid(GLuint program)
{
  glValidateProgram(program);
  int params = -1;
  glGetProgramiv (program, GL_VALIDATE_STATUS, &params);
  printf ("program %i GL_VALIDATE_STATUS = %i\n", program, params);
  if (GL_TRUE != params) 
  {
    print_shader_program_info(program);
    return false;
  }
  return true;
}
