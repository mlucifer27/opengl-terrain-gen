#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include "GL/gl.h"
#include "drawable.hpp"

/**
 * A vertex is a point in 3D space.
 */
struct vertex
{
  float x, y, z;
  float r, g, b;
  vertex() : x(0.0f), y(0.0f), z(0.0f), r(1.0f), g(1.0f), b(1.0f) {}
  vertex(float x, float y, float z) : x(x), y(y), z(z), r(1.0f), g(1.0f), b(1.0f) {}
  vertex(float x, float y, float z, float r, float g, float b) : x(x), y(y), z(z), r(r), g(g), b(b) {}
  bool equals(vertex v)
  {
    return x == v.x && y == v.y && z == v.z;
  }
};

/**
 * A primitive is a set of linked vertices forming a face or a set of faces.
 * It can only contain three vertices for now (triangle primitive).
 */
struct primitive
{
  int a, b, c;
  primitive() : a(-1), b(-1), c(-1) {}
  primitive(int a, int b, int c) : a(a), b(b), c(c) {}
  bool equals(primitive p)
  {
    return a == p.a && b == p.b && c == p.c;
  }
};

/**
 * A mesh is a collection of vertices and primitives.
 */
class Mesh : public Drawable
{
private:
  /* Polygon mode set to wireframe or fill */
  bool wireframe = false;
  /* The buffer containing the vertices. */
  GLuint vertex_buffer;
  /* The buffer containing the primitives. */
  GLuint primitive_buffer;
  /* Vertices define the position of each point in the mesh. */
  std::vector<vertex> vertices;
  /* Primitives define the topology of the mesh. */
  std::vector<primitive> primitives;
  /* Updates the vertex and primitive buffers. */
  void updateGLBuffers();

public:
  /**
   * Creates an empty mesh.
   */
  Mesh();
  /**
   * Create a mesh with the given number of vertices and primitives.
   */
  Mesh(int vertices, int primitives);
  /**
   * Creates a mesh from the given vertices and primitives.
   */
  Mesh(std::vector<vertex> vertices, std::vector<primitive> primitives);
  /**
   * Destroy the mesh.
   */
  ~Mesh();
  /**
   * Draw the mesh.
   */
  void draw();
  /**
   * Set the vertices of the mesh.
   */
  void setVertices(std::vector<vertex> vertices);
  /**
   * Set the primitives of the mesh.
   */
  void setPrimitives(std::vector<primitive> primitives);
  /**
   * Set the position of a vertex.
   */
  void setVertex(int index, vertex v);
  /**
   * Set the position of a primitive.
   */
  void setPrimitive(int index, primitive p);
  /**
   * Switch polygon mode (wireframe or fill).
   */
  void setWireframe(bool wireframe);
  /**
   * Apply a modidier to the mesh.
   */
  void apply(std::tuple<std::vector<vertex>, std::vector<primitive>> (*algorithm)(std::vector<vertex> vertices, std::vector<primitive> primitives), int iterations);
};

#endif // MESH_HPP