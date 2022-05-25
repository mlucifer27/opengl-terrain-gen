#ifndef SUBDIVISION_HPP
#define SUBDIVISION_HPP

#include "mesh.hpp"

#include <vector>
#include <tuple>
#include <list>
#include <iterator>
#include <algorithm>
#include <map>
#include <math.h>
#include <glm/glm.hpp>

/**
 * @brief Add noise to a mesh.
 */
std::tuple<std::vector<vertex>, std::vector<primitive>> additiveNoise(std::vector<vertex> vertices, std::vector<primitive> primitives);

/**
 * @brief Subdivides a mesh using the Catmull-Clark algorithm.
 */
std::tuple<std::vector<vertex>, std::vector<primitive>> catmullClark(std::vector<vertex> vertices, std::vector<primitive> primitives);

/**
 * @brief Apply a sine wave to the vertices of a mesh.
 */
std::tuple<std::vector<vertex>, std::vector<primitive>> wave(std::vector<vertex> vertices, std::vector<primitive> primitives);

/**
 * @brief Subdivides a mesh using a loop subdivision algorithm.
 */
std::tuple<std::vector<vertex>, std::vector<primitive>> loopSub(std::vector<vertex> vertices, std::vector<primitive> primitives);

/**
 * @brief Subdivides a mesh using a blur algorithm.
 */
std::tuple<std::vector<vertex>, std::vector<primitive>> blur(std::vector<vertex> vertices, std::vector<primitive> primitives);

/**
 * @brief Subdivides a mesh using a simple subdivision algorithm.
 */
std::tuple<std::vector<vertex>, std::vector<primitive>> subdivision(std::vector<vertex> vertices, std::vector<primitive> primitives);

#endif // SUBDIVISION_HPP