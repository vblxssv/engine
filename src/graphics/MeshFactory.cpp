#include "MeshFactory.h"


Mesh MeshFactory::CreateTriangle()
{
    std::vector<float> vertices = {
        0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
   };
    std::vector<uint32_t> indices = { 0, 1, 2 };

    AttributeLayout layout;
    layout.add_attribute<float>(0, 3);
    layout.add_attribute<float>(1, 3);

    return Mesh(vertices, indices, layout);
}

Mesh MeshFactory::CreateQuad() {
    std::vector<float> vertices = {
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f, // 0
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // 1
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // 2
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // 3
    };
    std::vector<uint32_t> indices = { 0, 1, 2, 2, 3, 0 };

    AttributeLayout layout;
    layout.add_attribute<float>(0, 3); // Position
    layout.add_attribute<float>(1, 3); // Color

    return Mesh(vertices, indices, layout);
}


Mesh MeshFactory::CreateTexturedCube()
{
    std::vector<float> vertices = {
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,

         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f
    };

    std::vector<uint32_t> indices = {
        0,  1,  2,  2,  3,  0,
        4,  5,  6,  6,  7,  4,
        8,  9, 10, 10, 11,  8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };

    AttributeLayout layout;
    layout.add_attribute<float>(0, 3);
    layout.add_attribute<float>(1, 2);
    return Mesh(vertices, indices, layout);
}

Mesh MeshFactory::CreateColoredCube()
{
    std::vector<float> vertices = {
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f
    };

    std::vector<uint32_t> indices = {
        0, 1, 2,  2, 3, 0,
        4, 5, 6,  6, 7, 4,
        3, 2, 6,  6, 7, 3,
        0, 1, 5,  5, 4, 0,
        1, 5, 6,  6, 2, 1,
        0, 4, 7,  7, 3, 0
    };

    AttributeLayout layout;
    layout.add_attribute<float>(0, 3);
    layout.add_attribute<float>(1, 3);

    return Mesh(vertices, indices, layout);
}


Mesh MeshFactory::CreateTexturedTorus(float mainRadius, float tubeRadius, int mainSegments, int tubeSegments) {
    std::vector<float> vertices;
    std::vector<uint32_t> indices;

    for (int i = 0; i <= mainSegments; ++i) {
        float theta = i * 2.0f * glm::pi<float>() / mainSegments;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);

        for (int j = 0; j <= tubeSegments; ++j) {
            float phi = j * 2.0f * glm::pi<float>() / tubeSegments;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            float x = (mainRadius + tubeRadius * cosPhi) * cosTheta;
            float y = (mainRadius + tubeRadius * cosPhi) * sinTheta;
            float z = tubeRadius * sinPhi;

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            vertices.push_back((float)i / mainSegments);
            vertices.push_back((float)j / tubeSegments);
        }
    }
    for (int i = 0; i < mainSegments; ++i) {
        for (int j = 0; j < tubeSegments; ++j) {
            int first = i * (tubeSegments + 1) + j;
            int second = first + tubeSegments + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    AttributeLayout layout;
    layout.add_attribute<float>(0, 3);
    layout.add_attribute<float>(1, 2);
    return Mesh(vertices, indices, layout);
}