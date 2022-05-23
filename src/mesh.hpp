#include <vector>
#include "GL/gl.h"
#include "drawable.hpp"

#ifndef MESH_HPP
#define MESH_HPP

/**
 * A vertex is a point in 3D space.
 */
struct vertex
{
  float x, y, z;
  float r, g, b, a;
};

/**
 * A primitive can only be a triangle for now.
 */
struct primitive
{
  int a, b, c;
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
};

#endif // MESH_HPP