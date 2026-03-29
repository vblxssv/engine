#pragma once
#include "Mesh.h"
#include <glm/gtc/constants.hpp>

class MeshFactory
{
public:
    static Mesh CreateTriangle();
    static Mesh CreateQuad();
    static Mesh CreateTexturedCube();
    static Mesh CreateColoredCube();
    static Mesh CreateTexturedTorus(float mainRadius = 1.0f, float tubeRadius = 0.4f, int mainSegments = 32, int tubeSegments = 16);
};

