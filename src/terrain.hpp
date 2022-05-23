#include <iostream>
#include <cmath>
#include <vector>
#include "GL/gl.h"
#include "mesh.hpp"

#ifndef TERRAIN_HPP
#define TERRAIN_HPP

class Terrain
{
private:
  int rows;
  int columns;
  float maxHeight;
  float minHeight;
  GLuint vertex_buffer;
  std::vector<float> heightMap;
  std::vector<vertex> vertices;
  /**
   * Updates the entire vertex OpenGL buffer (pretty heavy).
   * @see updateGLBuffer(int, int)
   */
  void updateGLBuffer();
  /**
   * Updates a single vertex in the vertex OpenGL buffer (preferable when modifying few vertices).
   */
  void updateGLBuffer(int x, int y, float height);

public:
  Terrain(int rows, int columns);
  ~Terrain();
  /**
   * Randomize the terrain height.
   */
  void randomize();
  /**
   * Draw the terrain.
   */
  void draw();
  /**
   * Draws a basic RGB reference system.
   */
  void drawReferenceSystem();
  /**
   * Set the height of a specific point.
   */
  void setHeight(int x, int y, float height);
  /**
   * Get the height of a specific point.
   */
  float getHeight(int x, int y);
  /**
   * Set the heightmap.
   */
  void setHeightMap(std::vector<float> heightMap);
  /**
   * Get the heightmap.
   */
  std::vector<float> getHeightMap();
};

#endif