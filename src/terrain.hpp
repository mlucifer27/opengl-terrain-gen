#include "mesh.hpp"
#include "drawable.hpp"
#include "GL/gl.h"

#include <iostream>
#include <cmath>
#include <vector>

#ifndef TERRAIN_HPP
#define TERRAIN_HPP

class Terrain : public Drawable
{
private:
  /* Level of detail of the terrain (defaults to zero, ie. lowest). */
  int subdivisions = 0;
  /* The number of rows in the terrain. */
  int rows;
  /* The number of columns in the heightmap. */
  int columns;
  /* maximum height of the terrain. */
  float maxHeight;
  /* minimum height of the terrain. */
  float minHeight;
  /* The heightmap (backlog states it can be exported). */
  std::vector<float> heightMap;
  /* The mesh associated with the terrain. */
  Mesh mesh;
  /**
   * Updates the vertices and primitives of the mesh.
   */
  void updateMesh();

public:
  /**
   * Creates a terrain with the given number of rows and columns.
   */
  Terrain(int rows, int columns);
  /**
   * Destroys the terrain (I really wanted to call that one Bulldoze(), but conventions).
   */
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
  /**
   * Print the heightmap.
   */
  void printHeightMap(char *message);
  /**
   * Set the level of detail of the terrain (0 = lowest).
   */
  void setSubdivisions(int subdivisions);
  /**
   * Get the level of detail of the terrain.
   */
  int getSubdivisions();
};

#endif