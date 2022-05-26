#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include "terrain.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

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
float camDistanceFactor = 1.0f;

int windowSize[2] = {800, 800};
float nearPlane = 0.1f;
float farPlane = 1000.0f;

float t = 0.0f;

Terrain *terrain;

/**
 * Place the camera in the scene
 */
void placeCamera()
{
  camDistance *= camDistanceFactor;
  camAngleX += camSpeedX;
  camAngleY += camSpeedY;
  glTranslatef(0.f, 0.f, -camDistance);
  glRotatef(camAngleX, 1.f, 0.f, 0.f);
  glRotatef(camAngleY, 0.f, 1.f, 0.f);
}

/**
 * Place the lighting in the scene.
 */
void placeLighting()
{
  GLfloat global_intensity = 0.4 * (exp(-1 / 2 * sin(t) * sin(t)) * sin(t) + 1.35);
  GLfloat red_intensity = global_intensity + 0.25 * exp(-10 * sin(t) * sin(t)) - 0.1;
  GLfloat light_ambient[] = {red_intensity, global_intensity, global_intensity, 1.0};
  GLfloat light_diffuse_specular[] = {0.1 * red_intensity, 0.1 * global_intensity, 0.1 * global_intensity, 1.0};

  // Light blue ambient light
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);

  // White directional light
  GLfloat directionalLight[] = {sin(t / (M_PI * 365)), sin(t), cos(t), 0.0};
  glLightfv(GL_LIGHT0, GL_POSITION, directionalLight);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse_specular);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_diffuse_specular);

  // Turn lights on
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // Set clear color to match the sky
  glClearColor(0.5 * light_ambient[0], 0.5 * light_ambient[1], 0.5 * light_ambient[2], light_ambient[3]);
}

/**
 * Display callback.
 */
void render()
{
  // clear the screen with blue
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // place the camera correctly
  placeCamera();

  // place the lights
  placeLighting();

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
      camDistanceFactor = 0.98f;
    if (key == GLFW_KEY_S)
      camDistanceFactor = 1.02f;
    if (key == GLFW_KEY_LEFT)
      camSpeedY = 1;
    if (key == GLFW_KEY_RIGHT)
      camSpeedY = -1;
    if (key == GLFW_KEY_UP)
      camSpeedX = 1;
    if (key == GLFW_KEY_DOWN)
      camSpeedX = -1;
    if (key == GLFW_KEY_R)
      terrain->randomize();
    if (key == GLFW_KEY_KP_ADD)
      terrain->setLod(terrain->getLod() + 1);
    if (key == GLFW_KEY_KP_SUBTRACT)
      terrain->setLod(terrain->getLod() - 1);
  }
  else if (action == GLFW_RELEASE)
  {
    if (key == GLFW_KEY_W || key == GLFW_KEY_S)
      camDistanceFactor = 1.0f;
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
  gluPerspective(65.0, (float)width / (float)height, nearPlane, farPlane);
  glMatrixMode(GL_MODELVIEW);
}

/**
 * Initializes the OpenGL context.
 */
void initGL()
{
  // Define the clear color
  glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
  glViewport(0, 0, windowSize[0], windowSize[1]);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (float)windowSize[0] / (float)windowSize[1], nearPlane, farPlane);
  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Gouraud shading
  glEnable(GL_NORMALIZE);
  // Enable color material blending
  glEnable(GL_COLOR_MATERIAL);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Place the camera
  gluLookAt(-6, 5, -6, 0, 0, 2, 0, 1, 0);
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{

  // Initialize window
  GLFWwindow *window;

  // Initialize GLFW
  if (!glfwInit())
    return -1;

  window = glfwCreateWindow(windowSize[0], windowSize[1], "Terrain interpolation demo", NULL, NULL);
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
  initGL();

  // Generate a random terrain (must be run after initGL)
  terrain = new Terrain(10, 10);
  terrain->randomize();

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window))
  {
    t += 0.005f;

    // Render
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    render();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();

  return EXIT_SUCCESS;
}