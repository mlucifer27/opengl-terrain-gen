#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include "terrain.hpp"

#include <limits>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

Terrain::Terrain(int rows, int columns)
{
  this->rows = rows;
  this->columns = columns;
  // maxHeight is negative infinity
  this->maxHeight = -std::numeric_limits<float>::infinity();
  // minHeight is positive infinity
  this->minHeight = std::numeric_limits<float>::infinity();
  heightMap = std::vector<float>(rows * columns);
  vertices = std::vector<vertex>(rows * columns);
  // initialize vertices x and z components
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      vertices[i * columns + j].x = i;
      vertices[i * columns + j].z = j;
    }
  }
  // Create vertex buffer
  glGenBuffers(1, &vertex_buffer);
}

Terrain::~Terrain()
{
}

void Terrain::draw()
{
  glPushMatrix();
  // center the terrain
  glTranslatef(-rows / 2, 0, -columns / 2);

  // render the terrain as a mesh of parallel quad strips
  for (int i = 0; i < rows; i++)
  {
    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= columns; j++)
    {
      // color the vertices based on the height
      glColor3f(getHeight(i, j), 0.0f, 0.0f); // TODO: replace this with a proper coloring system
      glVertex3f(i, getHeight(i, j), j);
      glColor3f(getHeight(i, j + 1), 0.0f, 0.0f);
      glVertex3f(i + 1, getHeight(i + 1, j), j); // TODO : replace this
    }
    glEnd();
  }

  // render the buffer contents
  glDrawArrays(GL_QUAD_STRIP, 0, vertices.size());

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
  std::vector<float> newHeightMap(rows * columns);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      newHeightMap[i * columns + j] = (rand() % 100) / 100.0;
    }
  }
  setHeightMap(newHeightMap);
}

void Terrain::setHeight(int x, int y, float height)
{
  heightMap[x * columns + y] = height;
  // update vertex
  vertices[x * columns + y].y = height;
  updateGLBuffer(x, y, height);
}

void Terrain::setHeightMap(std::vector<float> heightMap)
{
  this->heightMap = heightMap;
  // update vertices
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      vertices[i * columns + j].y = heightMap[i * columns + j];
    }
  }
  // update the buffer
  updateGLBuffer();
}

std::vector<float> Terrain::getHeightMap()
{
  return heightMap;
}

float Terrain::getHeight(int x, int y)
{
  return heightMap[x * columns + y];
}

void Terrain::updateGLBuffer()
{
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
}

void Terrain::updateGLBuffer(int x, int y, float height)
{
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex) * (x * columns + y), sizeof(vertex), &vertices[x * columns + y]);
}