#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

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
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#endif

float camAngleX = 0.0f;
float camAngleY = 0.0f;
float camSpeedX = 0.0f;
float camSpeedY = 0.0f;
float camDistance = 10.0f;
float camDistanceSpeed = 0.0f;

/**
 * Initializes the OpenGL context.
 */
void initGL()
{
  glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, 1.0, 0.1, 1000.0);

  glShadeModel(GL_FLAT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Place the camera
  gluLookAt(-6, 5, -6, 0, 0, 2, 0, 1, 0);
}

void placeCamera()
{
  camDistance += camDistanceSpeed;
  camAngleX += camSpeedX;
  camAngleY += camSpeedY;
  glTranslatef(0.f, 0.f, -camDistance);
  glRotatef(camAngleX, 1.f, 0.f, 0.f);
  glRotatef(camAngleY, 0.f, 1.f, 0.f);
}

/**
 * Display callback.
 */
void render(Terrain *terrain)
{
  // clear the screen with blue
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // place the camera correctly
  placeCamera();

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
  if (action == GLFW_PRESS)
  {
    if (key == GLFW_KEY_ESCAPE)
      glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_W)
      camDistanceSpeed = -0.1;
    if (key == GLFW_KEY_S)
      camDistanceSpeed = 0.1;
    if (key == GLFW_KEY_LEFT)
      camSpeedY = 1;
    if (key == GLFW_KEY_RIGHT)
      camSpeedY = -1;
    if (key == GLFW_KEY_UP)
      camSpeedX = 1;
    if (key == GLFW_KEY_DOWN)
      camSpeedX = -1;
  }
  else if (action == GLFW_RELEASE)
  {
    if (key == GLFW_KEY_W || key == GLFW_KEY_S)
      camDistanceSpeed = 0;
    if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT)
      camSpeedY = 0;
    if (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN)
      camSpeedX = 0;
  }
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

  // Initialize window
  GLFWwindow *window;

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
  glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
  glfwSetErrorCallback(error_callback);
  glfwSetWindowSizeCallback(window, resize_callback);

  // Generate a random terrain (must be run after initGL)
  Terrain *terrain = new Terrain(4, 4);
  terrain->randomize();

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