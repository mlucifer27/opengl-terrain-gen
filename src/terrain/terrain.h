#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <vector>

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
  void draw();
  void setHeight(int x, int y, float height);
  float getHeight(int x, int y);
  void setHeightMap(std::vector<float> heightMap);
  std::vector<float> getHeightMap();
};