#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <GLFW/glfw3.h>
#define M_PI 3.1415926


#define GREEN {0, 1, 0, 1}
#define WHITE {1, 1, 1, 1}
#define RED {1, 0, 0, 1}
#define BLUE {0, 0, 1, 1}



namespace Math {

	float toRads(float angle);

	struct vec4 {
		float x = 0, y = 0, z = 0, f = 1;

		vec4(float x, float y, float z, float f) :x(x), y(y), z(z), f(f) {};
		vec4() = default;
		vec4(const vec4& other) {
			this->x = other.x;
			this->y = other.y;
			this->z = other.z;
			this->f = other.f;
		}

		bool operator==(const vec4& other) const {
			return x == other.x && y == other.y && z == other.z && f == other.f;
		}//

		vec4 operator/ (float div) {
			if (div == 0.f) {
				return { 0, 0, 0, 0 };  
			}
			vec4 result = *this;  
			result /= div;        
			return result;        
		}//

		vec4& operator /= (float div) {
			if (div == 0.f) {  
				return *this;  
			}
			x /= div;  
			y /= div; 
			z /= div;  
			return *this; 
		}//

		vec4 operator-(const vec4& other) {
			return { x - other.x, y - other.y, z - other.z, 1 };
		}//

		vec4 operator+(const vec4& other) {
			return { x + other.x, y + other.y, z + other.z, 1 };
		}//

		vec4 operator*(const float& w) {
			return { x * w, y * w, z * w, f };
		}//

		float mod() {
			return sqrt(x * x + y * y + z * z);
		}//

		static void normalize(vec4& vec) {
			vec /= vec.mod();
		}//

		float static dot(const vec4& a, const vec4& b) {
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}//

		static vec4 vecMult(const vec4& a, const vec4& b);//

		void print() {
			std::cout << "x: " << x << ", y: " << y << ", z: " << z << ", f: " << f << std::endl;
		}


	};



	struct Matrix4x4 {
		float mat[4][4];

		Matrix4x4(const std::vector<float>& vec1d);

		Matrix4x4() {
			mat[0][0] = 0; mat[0][1] = 0; mat[0][2] = 0; mat[0][3] = 0;
			mat[1][0] = 0; mat[1][1] = 0; mat[1][2] = 0; mat[1][3] = 0;
			mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = 0; mat[2][3] = 0;
			mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 0; mat[3][3] = 0;
		}

		static Matrix4x4 eye();

		static Matrix4x4 perspective(float fov, float aspect, float near, float far);

		static Matrix4x4 shift(float x, float y, float z);

		static Matrix4x4 scale(float x, float y, float z);

		static Matrix4x4 rotate(float angle);

		void show();

		Matrix4x4 operator*(const Matrix4x4& other);

		vec4 operator*(const vec4& other);
	
		 
	};



}




