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
  // Create the heightmap
  this->heightMap = std::vector<float>(rows * columns);
  // Create the mesh (the primitives are triangles)
  this->mesh = Mesh(rows * columns, (rows - 1) * (columns - 1) * 2);
  // Temporary: set rendering mode to wireframe
  mesh.setWireframe(true);
  // Update the mesh
  updateMesh();
}

Terrain::~Terrain()
{
}

void Terrain::updateMesh()
{
  vertex vertices[rows * columns];
  primitive primitives[(rows - 1) * (columns - 1) * 2];
  float originX = -(rows / 2.0f) * 1.0f;
  float originY = -(columns / 2.0f) * 1.0f;
  // For each row
  for (int i = 0; i < rows; i++)
  {
    // For each column
    for (int j = 0; j < columns; j++)
    {
      float height = heightMap[i * columns + j];
      vertices[i * columns + j] = vertex();
      vertices[i * columns + j].x = j + originX;
      vertices[i * columns + j].y = height;
      vertices[i * columns + j].z = i + originY;
      // Set color according to height
      vertices[i * columns + j].r = 0.5f;
      vertices[i * columns + j].g = 0.2f;
      vertices[i * columns + j].b = 0.2f;
      vertices[i * columns + j].a = 1.f;

      // Update the max and min height
      if (height > maxHeight)
      {
        maxHeight = height;
      }
      if (height < minHeight)
      {
        minHeight = height;
      }

      // if the current vertex is not the last one
      if (j < columns - 1 && i < rows - 1)
      {
        // Create the two triangles
        primitives[(i * (columns - 1) + j) * 2] = primitive();
        primitives[(i * (columns - 1) + j) * 2].a = i * columns + j;
        primitives[(i * (columns - 1) + j) * 2].b = i * columns + j + 1;
        primitives[(i * (columns - 1) + j) * 2].c = (i + 1) * columns + j + 1;
        primitives[(i * (columns - 1) + j) * 2 + 1] = primitive();
        primitives[(i * (columns - 1) + j) * 2 + 1].a = i * columns + j;
        primitives[(i * (columns - 1) + j) * 2 + 1].b = (i + 1) * columns + j + 1;
        primitives[(i * (columns - 1) + j) * 2 + 1].c = (i + 1) * columns + j;
      }
    }
  }
  // Set the vertices and primitives
  mesh.setVertices(std::vector<vertex>(vertices, vertices + rows * columns));
  mesh.setPrimitives(std::vector<primitive>(primitives, primitives + (rows - 1) * (columns - 1) * 2));
}

void Terrain::draw()
{
  glPushMatrix();

  // Draw the mesh
  mesh.draw();

  glPopMatrix();
}

void Terrain::randomize()
{
  std::vector<float> newHeightMap(rows * columns);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      // Generate a random height between -1 and 1
      newHeightMap[i * columns + j] = (rand() % 100) / 100.0;
    }
  }
  setHeightMap(newHeightMap);
  // Print the new heightmap (debug)
  printHeightMap("New heightmap (generated):");
  // Update the mesh
  updateMesh();
}

void Terrain::setHeight(int x, int y, float height)
{
  // Update the heightmap
  heightMap[y * columns + x] = height;
  // Update the mesh
  updateMesh();
}

float Terrain::getHeight(int x, int y)
{
  return heightMap[x * columns + y];
}

void Terrain::setHeightMap(std::vector<float> heightMap)
{
  this->heightMap = heightMap;
  // Update the mesh
  updateMesh();
}

std::vector<float> Terrain::getHeightMap()
{
  return heightMap;
}

void Terrain::printHeightMap(char *message = "Heightmap: ")
{
  std::cout << message << std::endl;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      std::cout << this->heightMap[i * columns + j] << ", ";
    }
    std::cout << std::endl;
  }
}