#include "terrain.h"

void Terrain::Terrain(int width, int height, int depth)
{
  glWidth = width;
  glHeight = height;
  glDepth = depth;
  heightMap = std::vector<float>(width * height);
}

void Terrain::~Terrain()
{
  delete[] heightMap;
}

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(-6, 5, -6, 0, 0, 2, 0, 1, 0);
  glPushMatrix();
  DrawReferenceSystem();
  glPopMatrix();
  glutSwapBuffers();
}
