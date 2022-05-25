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
  void drawReferenceSystem();
};

#endif // DRAWABLE_HPP