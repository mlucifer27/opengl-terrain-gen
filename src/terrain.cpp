#include "terrain.hpp"
#include <GLFW/glfw3.h>

Terrain::Terrain(int width, int height, int depth)
{
  glWidth = width;
  glHeight = height;
  glDepth = depth;
  heightMap = std::vector<float>(width * height);
}

Terrain::~Terrain()
{
}

void Terrain::draw()
{
  glPushMatrix();
  // render the terrain as parallel quad strips
  glBegin(GL_QUAD_STRIP);
  for (int i = 0; i <= glWidth; i++)
  {
    for (int j = 0; j <= glHeight; j++)
    {
      glVertex3f(i, heightMap[i * glHeight + j], j);
      glVertex3f(i, heightMap[i * glHeight + j], j + 1);
    }
  }
  glEnd();
  glPopMatrix();
}

void Terrain::drawReferenceSystem()
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

void Terrain::randomize()
{
  for (int i = 0; i < glWidth; i++)
  {
    for (int j = 0; j < glHeight; j++)
    {
      heightMap[i * glHeight + j] = (rand() % 100) / 100.0;
    }
  }
}

void Terrain::setHeight(int x, int y, float height)
{
  heightMap[x * glHeight + y] = height;
}

void Terrain::setHeightMap(std::vector<float> heightMap)
{
  this->heightMap = heightMap;
}

std::vector<float> Terrain::getHeightMap()
{
  return heightMap;
}

float Terrain::getHeight(int x, int y)
{
  return heightMap[x * glHeight + y];
}