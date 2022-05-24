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
  std::vector<vertex> new_vertices = vertices;
  // Create the new primitives (initialize with the original primitives)
  std::vector<primitive> new_primitives = primitives;
  // Create map of edges
  std::vector<edge> edges;

  /*

  // For each primitive
  for (int i = 0; i < (int)primitives.size(); i++)
  {
    // Add the edges to the edge list if they are not already in the list
    if (std::find(edges.begin(), edges.end(), edge(primitives[i].a, primitives[i].b)) == edges.end())
      edges.push_back(edge(primitives[i].a, primitives[i].b));
    if (std::find(edges.begin(), edges.end(), edge(primitives[i].b, primitives[i].c)) == edges.end())
      edges.push_back(edge(primitives[i].b, primitives[i].c));
    if (std::find(edges.begin(), edges.end(), edge(primitives[i].c, primitives[i].a)) == edges.end())
      edges.push_back(edge(primitives[i].c, primitives[i].a));
  }


  // For each vertex
  for (int i = 0; i < (int)vertices.size(); i++)
  {
    vertex v = vertices[i];
    // Find all the edges that contain the current vertex
    std::vector<int> vertex_edge_indices;
    for (int j = 0; j < (int)edges.size(); j++)
    {
      if (edges[j].v1 == i || edges[j].v2 == i)
        vertex_edge_indices.push_back(j);
    }

    // For each edge
    for (int current_edge : vertex_edge_indices)
    {
      if (edges[current_edge].e != -1) // If the edge has already been subdivided
        break;

      // Find the other vertex of the current edge
      vertex vi;
      if (edges[current_edge].v1 != i)
        vi = vertices[edges[current_edge].v1];
      else
        vi = vertices[edges[current_edge].v2];

      // Find the primitives that contains both the current vertex and vi
      std::vector<primitive> primitives_vi;
      for (int k = 0; k < (int)primitives.size(); k++)
      {
        if (primitives[k].a == i && primitives[k].b == edges[current_edge].v1)
          primitives_vi.push_back(primitives[k]);
        if (primitives[k].b == i && primitives[k].c == edges[current_edge].v1)
          primitives_vi.push_back(primitives[k]);
        if (primitives[k].c == i && primitives[k].a == edges[current_edge].v1)
          primitives_vi.push_back(primitives[k]);
      }

      vertex e = vertex(3.0 / 8.0 * (v.x + vi.x), 3.0 / 8.0 * (v.y + vi.y), 3.0 / 8.0 * (v.z + vi.z));

      // For each primitive
      for (int l = 0; l < (int)primitives_vi.size(); l++)
      {
        int third_vertex; // vertex that is not the current vertex and not vi
        if (primitives_vi[l].a != i && primitives_vi[l].a != edges[current_edge].v1)
          third_vertex = primitives_vi[l].a;
        else if (primitives_vi[l].b != i && primitives_vi[l].b != edges[current_edge].v1)
          third_vertex = primitives_vi[l].b;
        else
          third_vertex = primitives_vi[l].c;

        e.x = e.x + 1.0 / 8.0 * (vertices[third_vertex].x);
        e.y = e.y + 1.0 / 8.0 * (vertices[third_vertex].y);
        e.z = e.z + 1.0 / 8.0 * (vertices[third_vertex].z);
      }

      // Store the new vertex
      new_vertices.push_back(e);
      edges[current_edge].e = new_vertices.size() - 1;
    }
  }
  */

  return std::make_tuple(new_vertices, new_primitives);
}