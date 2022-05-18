
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

/**
 * Draws a basic RGB reference system.
 */
void DrawReferenceSystem()
{
  // set the line width to 3.0
  glLineWidth(3.0);

  // Draw three lines along the x, y, z axis to represent the reference system
  // Use red for the x-axis, green for the y-axis and blue for the z-axis
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(1.0, 0.0, 0.0);
  glEnd();

  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 1.0, 0.0);
  glEnd();

  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_LINES);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 1.0);
  glEnd();

  // reset the drawing color to white
  glColor3f(1.0, 1.0, 1.0);

  // reset the line width to 1.0
  glLineWidth(1.0);
}

/**
 * Initializes the OpenGL context.
 */
void initGL(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, 1.0, 1.0, 100.0);

  glShadeModel(GL_FLAT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Place the camera
  gluLookAt(-6, 5, -6, 0, 0, 2, 0, 1, 0);
}

/**
 * Display callback.
 */
void display()
{
  // clear the screen with blue
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();

  DrawReferenceSystem();

  glPopMatrix();

  glutSwapBuffers();
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

  // initialize the OpenGL graphics state
  initGL();

  // set the display callback
  glutDisplayFunc(display);

  // set the reshape callback
  glutReshapeFunc(reshape);

  // enter the event loop
  glutMainLoop();

  return EXIT_SUCCESS;
}