#include "algorithms.hpp"

#include <list>
#include <algorithm>
#include <map>
#include <math.h>

struct edge
{
  int v1;
  int v2;
  int e = -1;
  edge(int v1, int v2) : v1(v1), v2(v2) {}
  bool equals(edge e)
  {
    return (v1 == e.v1 && v2 == e.v2) || (v1 == e.v2 && v2 == e.v1);
  }
};

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
std::tuple<std::vector<vertex>, std::vector<primitive>> loop(std::vector<vertex> vertices, std::vector<primitive> primitives)
{
  // Create the new vertices (initialize with the original vertices)
  std::vector<vertex> new_vertices;
  // Create the new primitives (initialize with the original primitives)
  std::vector<primitive> new_primitives;

  return std::make_tuple(new_vertices, new_primitives);
}

std::tuple<std::vector<vertex>, std::vector<primitive>> simpleSubd(std::vector<vertex> vertices, std::vector<primitive> primitives)
{
  // Create the new vertices (initialize with the original vertices)
  std::vector<vertex> new_vertices;
  // Create the new primitives (initialize with the original primitives)
  std::vector<primitive> new_primitives;

  // For each primitive
  for (int i = 0; i < (int)primitives.size(); i++)
  {
    // Get the primitive's vertices
    vertex v1 = vertices[primitives[i].a];
    vertex v2 = vertices[primitives[i].b];
    vertex v3 = vertices[primitives[i].c];

    vertex v4 = vertex((v1.x + v2.x) / 2, (v1.y + v2.y) / 2, (v1.z + v2.z) / 2);
    vertex v5 = vertex((v2.x + v3.x) / 2, (v2.y + v3.y) / 2, (v2.z + v3.z) / 2);
    vertex v6 = vertex((v1.x + v3.x) / 2, (v1.y + v3.y) / 2, (v1.z + v3.z) / 2);

    new_vertices.push_back(v1);
    new_vertices.push_back(v2);
    new_vertices.push_back(v3);
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