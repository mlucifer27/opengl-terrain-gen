#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include "terrain.hpp"
#include "algorithms.hpp"

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
  // Shift the heightmap to the center of the mesh
  float originX = -((rows - 1) / 2.0f) * 1.0f;
  float originY = -((columns - 1) / 2.0f) * 1.0f;
  // For each row
  for (int i = 0; i < rows; i++)
  {
    // For each column
    for (int j = 0; j < columns; j++)
    {
      float height = heightMap[i * columns + j];
      vertices[i * columns + j] = vertex(j + originX, height, i + originY, 1.0f, 0.2f, 0.2f);

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
        primitives[(i * (columns - 1) + j) * 2] = primitive(i * columns + j, i * columns + j + 1, (i + 1) * columns + j + 1);
        primitives[(i * (columns - 1) + j) * 2 + 1] = primitive(i * columns + j, (i + 1) * columns + j + 1, (i + 1) * columns + j);
      }
    }
  }
  // Set the vertices and primitives
  mesh.setVertices(std::vector<vertex>(vertices, vertices + rows * columns));
  mesh.setPrimitives(std::vector<primitive>(primitives, primitives + (rows - 1) * (columns - 1) * 2));
  // Apply subdivision
  mesh.apply(&subdivision, subdivisions);
  mesh.apply(&blur, 2 * subdivisions);
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

void Terrain::printHeightMap(std::string message = "Heightmap: ")
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

void Terrain::setSubdivisions(int subdivisions)
{
  if (subdivisions >= 0)
  {
    this->subdivisions = subdivisions;
    // print the new number of subdivisions (for debugging)
    std::cout << "Subdivisions: " << subdivisions << std::endl;
    // Update the mesh
    updateMesh();
  }
}

int Terrain::getSubdivisions()
{
  return subdivisions;
}