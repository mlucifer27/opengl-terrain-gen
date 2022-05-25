
#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "algorithms.hpp"
#include "mesh.hpp"
#include "drawable.hpp"

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define TERRAIN_COLOR_GRASS 0.09, 0.34, 0.26
#define TERRAIN_COLOR_ROCK 0.22, 0.25, 0.34
#define TERRAIN_COLOR_SAND 0.32, 0.35, 0.30
#define TERRAIN_COLOR_SNOW 1, 1, 1
#define TERRAIN_COLOR_WATER 0.09, 0.14, 0.29

#define TERRAIN_SNOW_HEIGHT 0.5f
#define TERRAIN_GRASS_HEIGHT 0.2f
#define TERRAIN_WATER_HEIGHT 0.0f

class Terrain : public Drawable
{
private:
  /* Level of detail of the terrain (defaults to zero, ie. lowest). */
  int lod = 0;
  /* The number of rows in the terrain. */
  int rows;
  /* The number of columns in the heightmap. */
  int cols;
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

  /**
   * Retrieves the normal of the terrain at the given row and column.
   * @param row The row of the vertex.
   * @param column The column of the vertex.
   */
  glm::vec3 getNormal(int row, int column);

public:
  /**
   * Creates a terrain with the given number of rows and columns.
   */
  Terrain(int rows, int cols);
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
   * Retrieves the color of the terrain for a given height and normal.
   * @param normal The normal of the terrain.
   * @param height The height of the terrain.
   */
  static glm::vec3 getColor(glm::vec3 normal, float height);
  /**
   * Set the height of a specific point.
   * @param x The x coordinate of the point.
   * @param y The y coordinate of the point.
   * @param height The height of the point.
   */
  void setHeight(int x, int y, float height);
  /**
   * Get the height of a specific point.
   * @param x The x coordinate of the point.
   * @param y The y coordinate of the point.
   */
  float getHeight(int x, int y);
  /**
   * Set the heightmap.
   * @param heightMap The heightmap.
   */
  void setHeightMap(std::vector<float> heightMap);
  /**
   * Get the heightmap.
   * @return The heightmap.
   */
  std::vector<float> getHeightMap();
  /**
   * Print the heightmap.
   * @param message The message to print.
   */
  void printHeightMap(std::string message);
  /**
   * Set the level of detail of the terrain (0 = lowest).
   * @param lod The level of detail.
   */
  void setLod(int lod);
  /**
   * Get the level of detail of the terrain.
   */
  int getLod();
};

#endif