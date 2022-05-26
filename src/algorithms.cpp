#include "algorithms.hpp"
#include "terrain.hpp"

struct edge
{
  int a;
  int b;
  edge(int a, int b) : a(a), b(b) {}
  bool equals(edge e)
  {
    return (a == e.a && b == e.b) || (a == e.b && b == e.a);
  }
};

std::tuple<std::vector<vertex>, std::vector<primitive>> additiveNoise(std::vector<vertex> vertices, std::vector<primitive> primitives)
{
  // Create the new vertices
  std::vector<vertex> new_vertices = vertices;
  // Create the new primitives
  std::vector<primitive> new_primitives = primitives;

  // For each vertex
  for (int i = 0; i < (int)vertices.size(); i++)
  {
    // Add noise
    new_vertices[i].x += (rand() % 100) / 2000.0;
    new_vertices[i].y += (rand() % 100) / 2000.0;
    new_vertices[i].z += (rand() % 100) / 2000.0;
  }

  return std::make_tuple(new_vertices, new_primitives);
}

std::tuple<std::vector<vertex>, std::vector<primitive>> catmullClark(std::vector<vertex> vertices, std::vector<primitive> primitives)
{
  // Create the new vertices
  std::vector<vertex> new_vertices = vertices;
  // Create the new primitives
  std::vector<primitive> new_primitives = primitives;
  // TODO: Implement the Catmull-Clark algorithm
  return std::make_tuple(new_vertices, new_primitives);
}

std::tuple<std::vector<vertex>, std::vector<primitive>> wave(std::vector<vertex> vertices, std::vector<primitive> primitives)
{
  // Create the new vertices
  std::vector<vertex> new_vertices = vertices;
  // Create the new primitives
  std::vector<primitive> new_primitives = primitives;

  // For each vertex
  for (int i = 0; i < vertices.size(); i++)
  {
    // Apply a sine wave to the vertex's position
    new_vertices[i].y += sin(vertices[i].x * vertices[i].z) * 0.1f;
  }

  return std::make_tuple(new_vertices, new_primitives);
}

std::tuple<std::vector<vertex>, std::vector<primitive>> blur(std::vector<vertex> vertices, std::vector<primitive> primitives)
{
  // Create the new vertices
  std::vector<vertex> new_vertices = vertices;
  // Create the new primitives
  std::vector<primitive> new_primitives = primitives;

  // For each vertex
  for (int i = 0; i < (int)vertices.size(); i++)
  {
    // Retrieve the vertex's horizontal and vertical neighbors (not diagonal)
    std::vector<int> neighbors;
    for (primitive p : primitives)
    {
      if (p.a == i || p.b == i || p.c == i)
      {
        if (p.a != i && (vertices[p.a].x == vertices[i].x || vertices[p.a].z == vertices[i].z))
        {
          neighbors.push_back(p.a);
        }
        if (p.b != i && (vertices[p.b].x == vertices[i].x || vertices[p.b].z == vertices[i].z))
        {
          neighbors.push_back(p.b);
        }
        if (p.c != i && (vertices[p.b].x == vertices[i].x || vertices[p.b].z == vertices[i].z))
        {
          neighbors.push_back(p.c);
        }
      }
    }

    // Average the vertex's neighbors
    std::vector<float> vertexAttributes = vertices[i].getAttributes();
    std::vector<float> neighborAttributes;
    for (int neighborIndex : neighbors)
    {
      neighborAttributes = vertices[neighborIndex].getAttributes();
      for (int j = 0; j < (int)vertexAttributes.size(); j++)
      {
        vertexAttributes[j] += neighborAttributes[j];
      }
    }

    // Divide the vertex's attributes by the number of neighbors
    for (int j = 0; j < (int)vertexAttributes.size(); j++)
    {
      vertexAttributes[j] /= (float)(neighbors.size() + 1);
    }

    new_vertices[i].setAttributes(vertexAttributes);
  }

  return std::make_tuple(new_vertices, new_primitives);
}

std::tuple<std::vector<vertex>, std::vector<primitive>> loopSub(std::vector<vertex> vertices, std::vector<primitive> primitives)
{
  // Create the new vertices (initialize with the original vertices)
  std::vector<vertex> new_vertices;
  // Create the new primitives (initialize with the original primitives)
  std::vector<primitive> new_primitives;

  // For each primitive
  for (int i = 0; i < (int)primitives.size(); i++)
  {
    // Get the primitive's vertices
    vertex a = vertices[primitives[i].a];
    vertex b = vertices[primitives[i].b];
    vertex c = vertices[primitives[i].c];

    vertex v4 = vertex((a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2);
    vertex v5 = vertex((b.x + c.x) / 2, (b.y + c.y) / 2, (b.z + c.z) / 2);
    vertex v6 = vertex((a.x + c.x) / 2, (a.y + c.y) / 2, (a.z + c.z) / 2);

    // Create the new vertices
    new_vertices.push_back(a);
    new_vertices.push_back(b);
    new_vertices.push_back(c);
    new_vertices.push_back(v4);
    new_vertices.push_back(v5);
    new_vertices.push_back(v6);

    int index = new_vertices.size() - 6;
    // Create the new primitive
    new_primitives.push_back(primitive(index, index + 3, index + 5));
    new_primitives.push_back(primitive(index + 3, index + 4, index + 5));
    new_primitives.push_back(primitive(index + 3, index + 1, index + 4));
    new_primitives.push_back(primitive(index + 4, index + 2, index + 5));
  }

  return std::make_tuple(new_vertices, new_primitives);
}

std::tuple<std::vector<vertex>, std::vector<primitive>> subdivision(std::vector<vertex> vertices, std::vector<primitive> primitives)
{
  // Create the new vertices (initialize with the original vertices)
  std::vector<vertex> new_vertices = vertices;
  // Create the new primitives (initialize with the original primitives)
  std::vector<primitive> new_primitives;

  // For each primitive
  for (int i = 0; i < (int)primitives.size(); i++)
  {
    // Get the primitive's vertices
    vertex a = vertices[primitives[i].a];
    vertex b = vertices[primitives[i].b];
    vertex c = vertices[primitives[i].c];

    glm::vec3 color;
    vertex vAB = vertex(
        (a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2,
        0.0f, 0.0f, 0.0f,
        (a.nx + b.nx) / 2, (a.ny + b.ny) / 2, (a.nz + b.nz) / 2);
    color = Terrain::getColor(glm::vec3(vAB.nx, vAB.ny, vAB.nz), vAB.y);
    vAB.r = color.r;
    vAB.g = color.g;
    vAB.b = color.b;
    vertex vBC = vertex(
        (b.x + c.x) / 2, (b.y + c.y) / 2, (b.z + c.z) / 2,
        0.0f, 0.0f, 0.0f,
        (b.nx + c.nx) / 2, (b.ny + c.ny) / 2, (b.nz + c.nz) / 2);
    color = Terrain::getColor(glm::vec3(vBC.nx, vBC.ny, vBC.nz), vBC.y);
    vBC.r = color.r;
    vBC.g = color.g;
    vBC.b = color.b;
    vertex vAC = vertex(
        (a.x + c.x) / 2, (a.y + c.y) / 2, (a.z + c.z) / 2,
        0.0f, 0.0f, 0.0f,
        (a.nx + c.nx) / 2, (a.ny + c.ny) / 2, (a.nz + c.nz) / 2);
    color = Terrain::getColor(glm::vec3(vAC.nx, vAC.ny, vAC.nz), vAC.y);
    vAC.r = color.r;
    vAC.g = color.g;
    vAC.b = color.b;

    int vAB_index, vBC_index, vAC_index;
    // Push the vertices if they are not already in the list,
    // else retrieve the index of the vertex
    if (std::count_if(new_vertices.begin(), new_vertices.end(), [&](vertex v)
                      { return v.equals(vAB); }) == 0)
    {
      new_vertices.push_back(vAB);
      vAB_index = new_vertices.size() - 1;
    }
    else
    {
      vAB_index = std::distance(new_vertices.begin(), std::find_if(new_vertices.begin(), new_vertices.end(), [&](vertex v)
                                                                   { return v.equals(vAB); }));
    }
    if (std::count_if(new_vertices.begin(), new_vertices.end(), [&](vertex v)
                      { return v.equals(vBC); }) == 0)
    {
      new_vertices.push_back(vBC);
      vBC_index = new_vertices.size() - 1;
    }
    else
    {
      vBC_index = std::distance(new_vertices.begin(), std::find_if(new_vertices.begin(), new_vertices.end(), [&](vertex v)
                                                                   { return v.equals(vBC); }));
    }
    if (std::count_if(new_vertices.begin(), new_vertices.end(), [&](vertex v)
                      { return v.equals(vAC); }) == 0)
    {
      new_vertices.push_back(vAC);
      vAC_index = new_vertices.size() - 1;
    }
    else
    {
      vAC_index = std::distance(new_vertices.begin(), std::find_if(new_vertices.begin(), new_vertices.end(), [&](vertex v)
                                                                   { return v.equals(vAC); }));
    }

    // Create the new primitive
    new_primitives.push_back(primitive(primitives[i].a, vAB_index, vAC_index));
    new_primitives.push_back(primitive(vAB_index, primitives[i].b, vBC_index));
    new_primitives.push_back(primitive(vAB_index, vBC_index, vAC_index));
    new_primitives.push_back(primitive(vBC_index, primitives[i].c, vAC_index));
  }

  return std::make_tuple(new_vertices, new_primitives);
}