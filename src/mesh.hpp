#include <vector>
#include "GL/gl.h"

#ifndef MESH_HPP
#define MESH_HPP

/**
 * A vertex is a point in 3D space.
 */
struct vertex
{
  float x, y, z;
  float r, g, b;
};

/**
 * A primitive is either a triangle or a quad.
 */
struct primitive
{
  int type;
};

/**
 * A triangle is a primitive composed of 3 vertices.
 */
struct triangle : public primitive
{
  int v1, v2, v3;
};

/**
 * A quad is a primitive composed of 4 vertices.
 */
struct quad : public primitive
{
  int v1, v2, v3, v4;
};

/**
 * A mesh is a collection of vertices and primitives.
 */
class Mesh
{
private:
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
   * Create a mesh with the given number of vertices and primitives.
   */
  Mesh(int vertices, int primitives);
  /**
   * Destroy the mesh.
   */
  ~Mesh();
  /**
   * Draw the mesh.
   */
  void draw();
  /**
   * Set the position of a vertex.
   */
  void setVertex(int index, vertex v);
  /**
   * Set the position of a primitive.
   */
  void setPrimitive(int index, primitive p);
};

#endif // MESH_HPP