#include "geomutils.hpp"

float smoothstep(float value, float xBegin, float xEnd, float yBegin, float yEnd)
{
  if (value < xBegin)
    return yBegin;
  if (value > xEnd)
    return yEnd;
  return yBegin + (yEnd - yBegin) * (value - xBegin) / (xEnd - xBegin);
}
