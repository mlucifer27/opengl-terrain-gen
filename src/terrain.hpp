#include <iostream>
#include <cmath>
#include <vector>

#ifndef TERRAIN_HPP
#define TERRAIN_HPP

class Terrain
{
private:
  int glWidth;
  int glHeight;
  int glDepth;
  std::vector<float> heightMap;

public:
  Terrain(int width, int height, int depth);
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