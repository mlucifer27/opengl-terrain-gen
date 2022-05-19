
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#include "terrain.hpp"

// macosx
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
// windows-specific
#ifdef _WIN32
#include <windows.h>
#endif
// both linux and windows
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#endif

/**
 * Initializes the OpenGL context.
 */
void initGL(GLuint &vertex_buffer)
{
  glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, 1.0, 1.0, 100.0);

  glShadeModel(GL_FLAT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Place the camera
  gluLookAt(-6, 5, -6, 0, 0, 2, 0, 1, 0);

  // Create vertex buffer
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
}

/**
 * Display callback.
 */
void render(Terrain *terrain)
{
  // clear the screen with blue
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();

  // Draw the terrain
  terrain->draw();
  terrain->drawReferenceSystem();

  glPopMatrix();
}

/**
 * Key input callback.
 */
void key_callback(GLFWwindow *window, int key, __attribute__((unused)) int scancode, __attribute__((unused)) int action, __attribute__((unused)) int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

/**
 * Error callback.
 */
void error_callback(__attribute__((unused)) int error, __attribute__((unused)) const char *description)
{
  fprintf(stderr, "GLFW Error: %s\n", description);
}

void resize_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (float)width / (float)height, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
  // Generate a random terrain
  Terrain *terrain = new Terrain(30, 30);
  terrain->randomize();

  // Initialize window
  GLFWwindow *window;
  // Initialize vertex buffer
  GLuint vertex_buffer;

  // Initialize GLFW
  if (!glfwInit())
    return -1;

  window = glfwCreateWindow(800, 800, "Terrain interpolation demo", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetErrorCallback(error_callback);
  glfwSetWindowSizeCallback(window, resize_callback);
  initGL(vertex_buffer);

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window))
  {

    // Render
    glClear(GL_COLOR_BUFFER_BIT);

    render(terrain);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();

  return EXIT_SUCCESS;
}