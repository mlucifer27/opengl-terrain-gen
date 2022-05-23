#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

/**
 * @brief A drawable object.
 */
class Drawable
{
public:
  /* Draw the object. */
  virtual void draw() = 0;
  /* Draw a basic RGB reference system. */
  void drawReferenceSystem()
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
};

#endif // DRAWABLE_HPP