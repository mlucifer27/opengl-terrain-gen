
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
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#endif

Terrain *terrain = new Terrain(256, 256, 256);

const char *GetGLErrorStr(GLenum err)
{
  switch (err)
  {
  case GL_NO_ERROR:
    return "No error";
  case GL_INVALID_ENUM:
    return "Invalid enum";
  case GL_INVALID_VALUE:
    return "Invalid value";
  case GL_INVALID_OPERATION:
    return "Invalid operation";
  case GL_STACK_OVERFLOW:
    return "Stack overflow";
  case GL_STACK_UNDERFLOW:
    return "Stack underflow";
  case GL_OUT_OF_MEMORY:
    return "Out of memory";
  default:
    return "Unknown error";
  }
}

void CheckGLError()
{
  while (true)
  {
    const GLenum err = glGetError();
    if (GL_NO_ERROR == err)
      break;

    std::cout << "GL Error: " << GetGLErrorStr(err) << std::endl;
  }
}

/**
 * Initializes the OpenGL context.
 */
void initGL(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // gluPerspective(65.0, 1.0, 1.0, 100.0);

  glShadeModel(GL_FLAT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Place the camera
  // gluLookAt(-6, 5, -6, 0, 0, 2, 0, 1, 0);
}

/**
 * Display callback.
 */
void render()
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
 * Reshape callback.
 */
void reshape(int width, int height)
{
  // define the viewport transformation;
  glViewport(0, 0, width, height);
  if (width < height)
    glViewport(0, (height - width) / 2, width, width);
  else
    glViewport((width - height) / 2, 0, height, height);
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

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
  // Generate a random terrain
  terrain->randomize(); // TODO: remove this

  // Initialize GLFW
  GLFWwindow *window;
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
  initGL();

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window))
  {

    // Render
    glClear(GL_COLOR_BUFFER_BIT);

    render();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();

  return EXIT_SUCCESS;
}