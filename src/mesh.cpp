#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1

#include "mesh.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <tuple>

Mesh::Mesh()
{
  // Create vertex buffer
  glGenBuffers(1, &vertex_buffer);
  // Create primitive buffer
  glGenBuffers(1, &primitive_buffer);
}

Mesh::Mesh(int vertices, int primitives) : Mesh()
{
  this->vertices = std::vector<vertex>(vertices);
  this->primitives = std::vector<primitive>(primitives);
  // Update the buffers
  updateGLBuffers();
}

Mesh::Mesh(std::vector<vertex> vertices, std::vector<primitive> primitives) : Mesh()
{
  this->vertices = vertices;
  this->primitives = primitives;
  // Update the buffers
  updateGLBuffers();
}

Mesh::~Mesh()
{
}

void Mesh::updateGLBuffers()
{
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, primitive_buffer);
  glBufferData(GL_ARRAY_BUFFER, primitives.size() * sizeof(primitive), &primitives[0], GL_STATIC_DRAW);
}

void Mesh::draw()
{
  if (this->wireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // activate wireframe mode
  glPushMatrix();
  {
    // Draw the colored vertices and primitives
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, primitive_buffer);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)12);

    glDrawElements(GL_TRIANGLES, primitives.size() * 3, GL_UNSIGNED_INT, (void *)0);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  glPopMatrix();
  if (this->wireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Mesh::setVertices(std::vector<vertex> vertices)
{
  this->vertices = vertices;
  updateGLBuffers();
}

void Mesh::setPrimitives(std::vector<primitive> primitives)
{
  this->primitives = primitives;
  updateGLBuffers();
}

void Mesh::setVertex(int index, vertex v)
{
  vertices[index] = v;
  updateGLBuffers();
}

void Mesh::setPrimitive(int index, primitive p)
{
  primitives[index] = p;
  updateGLBuffers();
}

void Mesh::setWireframe(bool wireframe)
{
  this->wireframe = wireframe;
}

void Mesh::subdivide(std::tuple<std::vector<vertex>, std::vector<primitive>> (*algorithm)(std::vector<vertex> vertices, std::vector<primitive> primitives))
{
  std::tie(vertices, primitives) = algorithm(vertices, primitives);
  updateGLBuffers();
}