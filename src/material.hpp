#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
private:
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float shininess;

public:
  Material();
  Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
  glm::vec3 getAmbient();
  glm::vec3 getDiffuse();
  glm::vec3 getSpecular();
  float getShininess();
  void setAmbient(glm::vec3 ambient);
  void setDiffuse(glm::vec3 diffuse);
  void setSpecular(glm::vec3 specular);
  void setShininess(float shininess);
  void apply();
};

#endif