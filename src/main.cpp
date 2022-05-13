
#include <stdlib.h>
#include <stdio.h>

// macosx
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
// windows-specific
#ifdef _WIN32
#include <windows.h>
#endif
// both linux and windows
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include <math.h>

void display()
{
  // clear the screen with blue
  glClear(GL_COLOR_BUFFER_BIT);

  // draw stuff here

  glFlush();
}

void reshape(int width, int height)
{
  /* define the viewport transformation */
  glViewport(0, 0, width, height);
}

int main(int argc, char **argv)
{
  // initialize glut
  glutInit(&argc, argv);

  // set the display mode
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  // set the window size
  glutInitWindowSize(800, 800);

  // set the window position
  glutInitWindowPosition(100, 100);

  // create the window
  glutCreateWindow("Terrain interpolation demo");

  // set the display callback
  glutDisplayFunc(display);

  // set the reshape callback
  glutReshapeFunc(reshape);

  // enter the event loop
  glutMainLoop();
}