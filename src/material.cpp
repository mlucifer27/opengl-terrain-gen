#include "material.hpp"

Material::Material()
{
  ambient = glm::vec3(0.0f, 0.0f, 0.0f);
  diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
  specular = glm::vec3(0.0f, 0.0f, 0.0f);
  shininess = 0.0f;
}

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
  this->ambient = ambient;
  this->diffuse = diffuse;
  this->specular = specular;
  this->shininess = shininess;
}

glm::vec3 Material::getAmbient()
{
  return ambient;
}

glm::vec3 Material::getDiffuse()
{
  return diffuse;
}

glm::vec3 Material::getSpecular()
{
  return specular;
}

float Material::getShininess()
{
  return shininess;
}

void Material::setAmbient(glm::vec3 ambient)
{
  this->ambient = ambient;
}

void Material::setDiffuse(glm::vec3 diffuse)
{
  this->diffuse = diffuse;
}

void Material::setSpecular(glm::vec3 specular)
{
  this->specular = specular;
}

void Material::setShininess(float shininess)
{
  this->shininess = shininess;
}

void Material::apply()
{
  glMaterialfv(GL_FRONT, GL_AMBIENT, glm::value_ptr(ambient));
  glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(diffuse));
  glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(specular));
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}