#include "Geometry.h"

void Mesh::set_mesh(const std::vector<GLfloat>& vertexes, const std::vector<GLuint>& indexes, const AttributeLine& line)
{
	vbo = std::make_unique<VBO<GLfloat>>(vertexes);
    instance_vbo = std::make_unique<VBO<GLuint>>();
	ebo = std::make_unique<EBO>(indexes);
    vao = std::make_unique<VAO>(vbo, instance_vbo, ebo, line);
}



Mesh::Mesh()
{
	AttributeLine line;
	line.push_back(3, GL_FLOAT);
	line.push_back(3, GL_FLOAT);

	//const int numSegments = 32; // вдоль большого круга
	//const int numRings = 16;    // вдоль малой окружности
 //   const float M_PI = 3.1415926;
	//const float R = 1.0f; // большой радиус тора
	//const float r = 0.4f; // малый радиус

	std::vector<GLfloat> vertexes = {
		-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // 0
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f, // 1
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f, // 2
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f, // 3
		-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f, // 4
		 0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f, // 5
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f, // 6
		-0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 1.0f  // 7
	};

    
	std::vector<GLuint> indices = {
		4, 1, 5,  4, 0, 1, // left
		1, 5, 6,  1, 2, 6, // up
		0, 2, 1,  0, 3, 2, // front
		4, 3, 0,  4, 7, 3, // down
		3, 6, 2,  3, 7, 6, // right
		7, 5, 6,  7, 4, 5, // back
	};

    //std::vector<GLfloat> vertexes;
    //std::vector<GLuint> indices;

    //for (int i = 0; i <= numSegments; ++i) {
    //    float theta = (float)i / numSegments * 2.0f * M_PI;
    //    float cosTheta = cos(theta);
    //    float sinTheta = sin(theta);

    //    for (int j = 0; j <= numRings; ++j) {
    //        float phi = (float)j / numRings * 2.0f * M_PI;
    //        float cosPhi = cos(phi);
    //        float sinPhi = sin(phi);

    //        float x = (R + r * cosPhi) * cosTheta;
    //        float y = (R + r * cosPhi) * sinTheta;
    //        float z = r * sinPhi;

    //        // Простейшее окрашивание: по координатам
    //        float red = (x + R + r) / (2.0f * (R + r));
    //        float green = (y + R + r) / (2.0f * (R + r));
    //        float blue = (z + r) / (2.0f * r);

    //        vertexes.push_back(x);
    //        vertexes.push_back(y);
    //        vertexes.push_back(z);
    //        vertexes.push_back(red);
    //        vertexes.push_back(green);
    //        vertexes.push_back(blue);
    //    }
    //}

    //for (int i = 0; i < numSegments; ++i) {
    //    for (int j = 0; j < numRings; ++j) {
    //        int first = i * (numRings + 1) + j;
    //        int second = (i + 1) * (numRings + 1) + j;

    //        indices.push_back(first);
    //        indices.push_back(second);
    //        indices.push_back(first + 1);

    //        indices.push_back(second);
    //        indices.push_back(second + 1);
    //        indices.push_back(first + 1);
    //    }
    //}
	set_mesh(vertexes, indices, line);
}

void Mesh::add_index(GLuint index)
{
    instance_vbo->push_back(index);
}

void Mesh::remove_el(GLuint index)
{
    instance_vbo->remove_el(index);
}

GLuint Mesh::get_indices()
{
    return ebo->get_indices();
}

decltype(auto) Mesh::get_data_from_vbo()
{
    return instance_vbo->get_data();
}
