#include "Math.h"


Math::Matrix4x4::Matrix4x4(const std::vector<float>& vec1d)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat[i][j] = vec1d[i * 4 + j];
        }
    }
}

Math::Matrix4x4 Math::Matrix4x4::eye()
{
    return Matrix4x4({
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    });
}

Math::Matrix4x4 Math::Matrix4x4::perspective(float fov, float aspect, float near, float far)
{
    float rad = toRads(fov);
    float ctgHalf = 1.f / tanf(rad / 2.f);

    return Matrix4x4({
        ctgHalf / aspect, 0, 0, 0,
        0, ctgHalf, 0, 0,
        0, 0, (far + near) / (near - far), (2 * far * near) / (near - far),
        0, 0, -1, 0,
        });
}

Math::Matrix4x4 Math::Matrix4x4::shift(float x, float y, float z)
{
    return Matrix4x4({
           1,0,0,x,
           0,1,0,y,
           0,0,1,z,
           0,0,0,1,
    });
}

Math::Matrix4x4 Math::Matrix4x4::scale(float x, float y, float z)
{
    return Matrix4x4({
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1,
    });
}

Math::Matrix4x4 Math::Matrix4x4::rotate(float angle)
{
    float rad = toRads(angle);
    return Matrix4x4({
        cosf(rad), 0 ,sinf(rad), 0,
        0, 1 ,0, 0,
        -sinf(rad), 0 ,cosf(rad), 0,
        0, 0, 0, 1
    });
}



//Math::Matrix4x4 Math::Matrix4x4::view(vec4 camPos, vec4 lookAt, vec4 vecUp)
//{
//
//    vec4 forward = (lookAt - camPos);
//    forward.normalize();
//  
//    vec4 right = vec4::vecMult(vecUp, forward);
//    right.normalize();
//    
//    vec4 trueUp = vec4::vecMult(forward, right);  
//    trueUp.normalize();
//
//    auto rotationMatrix = Matrix4x4({
//         right.x,    right.y,    right.z,    0.f,
//         trueUp.x,   trueUp.y,   trueUp.z,   0.f,
//        -forward.x, -forward.y, -forward.z,  0.f,
//         0.f,        0.f,        0.f,        1.f
//        });
//
//    
//    auto translationMatrix = Matrix4x4({
//         1.f, 0.f, 0.f, -camPos.x,
//         0.f, 1.f, 0.f, -camPos.y,
//         0.f, 0.f, 1.f, -camPos.z,
//         0.f, 0.f, 0.f, 1.f
//        });
//
// 
//    return rotationMatrix * translationMatrix;
//}


void Math::Matrix4x4::show()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << mat[i][j];
            if (j != 3) {
                std::cout << ",\t";
            }
        }
        std::cout << std::endl;
    }
}

Math::Matrix4x4 Math::Matrix4x4::operator*(const Matrix4x4& other)
{
    
    Matrix4x4 result;

    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.mat[i][j] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                result.mat[i][j] += mat[i][k] * other.mat[k][j];
            }
        }
    }

    return result;
}

Math::vec4 Math::Matrix4x4::operator*(const vec4& other)
{
    vec4 result;
    result.x = mat[0][0] * other.x + mat[0][1] * other.y + mat[0][2] * other.z + mat[0][3] * other.f;
    result.y = mat[1][0] * other.x + mat[1][1] * other.y + mat[1][2] * other.z + mat[1][3] * other.f;
    result.z = mat[2][0] * other.x + mat[2][1] * other.y + mat[2][2] * other.z + mat[2][3] * other.f;
    result.f = mat[3][0] * other.x + mat[3][1] * other.y + mat[3][2] * other.z + mat[3][3] * other.f;

    return result;
}



float Math::toRads(float angle)
{
    return angle * M_PI / 180.0;
}





Math::vec4 Math::vec4::vecMult(const vec4& a, const vec4& b)
{
    return vec4(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x, 
        1.f);
}//