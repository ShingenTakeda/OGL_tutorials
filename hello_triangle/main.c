#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <common.h>

GLfloat points[] = 
{
  0.0f, 0.5f, 0.0f,
  0.5f, -0.5f, 0.0f,
  -0.5, -0.5f, 0.0f
};

GLfloat color[] =
{
  1.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 1.0f
};

const char *svertex_shader = 
"#version 410\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main()"
"{"
	"color = vertex_color;"
	"gl_Position = vec4(vertex_position, 1.0);"
"}";

const char *sfragment_shader = 
"#version 410\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main()"
"{"
" frag_color = vec4(color, 1.0);"
"}";

GLuint vertex_shader, fragment_shader;
GLuint shader_program;

int window_width, window_height, fb_width, fb_height;

int main()
{
  GLFWwindow *window = NULL;
  const GLubyte *renderer;
  const GLubyte *version;

  GLuint vbo;
  GLuint vao;

  GLuint color_vbo = 0;

  if(!restart_gl_log())
  {
    return 1;
  }

  gl_log("starting GLFW\n%s\n", glfwGetVersionString());

  glfwSetErrorCallback(glfw_error_callback);

  if(!glfwInit())
  {
    fprintf(stderr, "ERROR: could not initialize start glfw\n");
    return 1;
  }

  window_width = STANDARD_WIDTH;
  window_height = STANDARD_HEIGHT;

  fb_width = window_width;
  fb_height = window_height;

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  window = glfwCreateWindow(window_width, window_height, "hello triangle", NULL, NULL);

  glfwSetWindowSizeCallback(window, glfw_window_resize_callback);
  glfwSetFramebufferSizeCallback(window, glfw_framebuffer_resize_callback);

  if(!window)
  {
    fprintf(stderr, "ERROR: could not initialize start glfw\n");
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  glewInit();

  renderer = glGetString(GL_RENDERER);
  version = glGetString(GL_VERSION);

  printf("RENDERER: %s\n", renderer);
  printf("VERSION: %s\n", version);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), points, GL_STATIC_DRAW);

  glGenBuffers(1, &color_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), color, GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &svertex_shader, NULL);
  glCompileShader(vertex_shader);

  int params = -1;
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &params);
  if(GL_TRUE != params)
  {
    fprintf(stderr, "ERROR: GL shader index %i did not compile\n", vertex_shader);
    print_shader_info(vertex_shader);
    return 1;
  }

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &sfragment_shader, NULL);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &params);
  if(GL_TRUE != params)
  {
    fprintf(stderr, "ERROR: GL shader index %i did not compile\n", fragment_shader);
    print_shader_info(fragment_shader);
    return 1;
  }

  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);

  glBindAttribLocation(shader_program, 0, "vertex_position");
  glBindAttribLocation(shader_program, 1, "vertex_color");

  glLinkProgram(shader_program);

  while(!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwPollEvents();
    glfwSwapBuffers(window);

    if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE))
    {
      glfwSetWindowShouldClose (window, 1);
    }
  }

  glfwTerminate();

  return 0;
}
