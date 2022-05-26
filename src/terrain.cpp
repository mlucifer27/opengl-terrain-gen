#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include "terrain.hpp"

Terrain::Terrain(int rows, int cols)
{
  this->rows = rows;
  this->cols = cols;
  // maxHeight is negative infinity
  this->maxHeight = -std::numeric_limits<float>::infinity();
  // minHeight is positive infinity
  this->minHeight = std::numeric_limits<float>::infinity();
  // Create the heightmap
  this->heightMap = std::vector<float>(rows * cols);
  // Create the mesh (the primitives are triangles)
  this->mesh = Mesh(
      rows * cols,
      (rows - 1) * (cols - 1) * 2,
      Material(
          glm::vec3(1.0f, 1.0f, 1.0f),
          glm::vec3(1.0f, 1.0f, 1.0f),
          glm::vec3(1.0f, 1.0f, 1.0f),
          0.0f));
  // Temporary: set rendering mode to wireframe
  mesh.setWireframe(false);
  // Update the mesh
  updateMesh();
}

Terrain::~Terrain()
{
}

void Terrain::updateMesh()
{
  vertex vertices[rows * cols];
  primitive primitives[(rows - 1) * (cols - 1) * 2];
  // Shift the heightmap to the center of the mesh
  float originX = -((rows - 1) / 2.0f) * 1.0f;
  float originY = -((cols - 1) / 2.0f) * 1.0f;
  // For each row
  for (int i = 0; i < rows; i++)
  {
    // For each column
    for (int j = 0; j < cols; j++)
    {
      float height = heightMap[i * cols + j];
      glm::vec3 normal = getNormal(i, j);
      glm::vec3 color = getColor(normal, height);
      vertices[i * cols + j] = vertex(
          j + originX, height, i + originY,
          color.x, color.y, color.y,
          normal.x, normal.y, normal.z);

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
      if (j < cols - 1 && i < rows - 1)
      {
        // Create the two triangles
        primitives[(i * (cols - 1) + j) * 2] = primitive(i * cols + j, i * cols + j + 1, (i + 1) * cols + j + 1);
        primitives[(i * (cols - 1) + j) * 2 + 1] = primitive(i * cols + j, (i + 1) * cols + j + 1, (i + 1) * cols + j);
      }
    }
  }
  // Set the vertices and primitives
  mesh.setVertices(std::vector<vertex>(vertices, vertices + rows * cols));
  mesh.setPrimitives(std::vector<primitive>(primitives, primitives + (rows - 1) * (cols - 1) * 2));
  // Apply subdivision
  mesh.apply(&subdivision, lod);
  mesh.apply(&blur, lod);
  mesh.apply(&additiveNoise, 1);
}

glm::vec3 Terrain::getColor(glm::vec3 normal, float height)
{
  glm::vec3 snow = glm::vec3(TERRAIN_COLOR_SNOW);
  glm::vec3 grass = glm::vec3(TERRAIN_COLOR_GRASS);
  glm::vec3 water = glm::vec3(TERRAIN_COLOR_WATER);
  glm::vec3 rock = glm::vec3(TERRAIN_COLOR_ROCK);
  glm::vec3 sand = glm::vec3(TERRAIN_COLOR_SAND);

  float terrainHorizontality = abs(glm::dot(normal, glm::vec3(0.0f, 1.0f, 0.0f)));
  float lightIntensity = smoothstep(height, TERRAIN_WATER_HEIGHT, 1.2 * TERRAIN_SNOW_HEIGHT, 0.4f, 1.0f);
  float heightError = (rand() % 100) / 400.0f - 0.125f;
  if (height > TERRAIN_SNOW_HEIGHT * (1.0f + heightError) && terrainHorizontality > 0.3f)
  {
    return snow * lightIntensity;
  }
  else if (height < TERRAIN_WATER_HEIGHT)
  {
    return water * lightIntensity;
  }
  else if (terrainHorizontality > 0.75f && terrainHorizontality < 0.9f)
  {
    return grass * lightIntensity;
  }
  else if (terrainHorizontality <= 0.75f)
  {
    return rock * lightIntensity;
  }
  else if (terrainHorizontality >= 0.9f)
  {
    return sand * lightIntensity;
  }
}

glm::vec3 Terrain::getNormal(int row, int column)
{
  // Get the height of the current vertex
  float height = heightMap[row * cols + column];
  // Get the height of the left vertex
  float leftHeight = heightMap[row * cols + (column - 1)];
  // Get the height of the right vertex
  float rightHeight = heightMap[row * cols + (column + 1)];
  // Get the height of the top vertex
  float topHeight = heightMap[(row - 1) * cols + column];
  // Get the height of the bottom vertex
  float bottomHeight = heightMap[(row + 1) * cols + column];
  // Compute the normal
  glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.0f);
  if (column > 0)
  {
    normal.x += (leftHeight - height) / 1.0f;
  }
  if (column < cols - 1)
  {
    normal.x -= (rightHeight - height) / 1.0f;
  }
  if (row > 0)
  {
    normal.z += (topHeight - height) / 1.0f;
  }
  if (row < rows - 1)
  {
    normal.z -= (bottomHeight - height) / 1.0f;
  }
  // Normalize the normal
  normal = glm::normalize(normal);
  return normal;
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
  std::vector<float> newHeightMap(rows * cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      // Generate a random height between 0 and 2
      newHeightMap[i * cols + j] = (rand() % 100) / 50.0;
    }
  }
  setHeightMap(newHeightMap);
  // Update the mesh
  updateMesh();
}

void Terrain::setHeight(int x, int y, float height)
{
  // Update the heightmap
  heightMap[y * cols + x] = height;
  // Update the mesh
  updateMesh();
}

float Terrain::getHeight(int x, int y)
{
  return heightMap[x * cols + y];
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
    for (int j = 0; j < cols; j++)
    {
      std::cout << this->heightMap[i * cols + j] << ", ";
    }
    std::cout << std::endl;
  }
}

void Terrain::setLod(int lod)
{
  if (lod >= 0)
  {
    this->lod = lod;
    // print the new number of lod (for debugging)
    std::cout << "lod: " << lod << std::endl;
    // Update the mesh
    updateMesh();
  }
}

int Terrain::getLod()
{
  return lod;
}