#define GLM_ENABLE_EXPERIMENTAL 
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

glm::mat4 CreatePerspectiveMatrix(float _fovY, float _width, float _height, float _nearZ, float _farZ)
{
    glm::mat4 result(0.0f);

    float aspectRatio = _width / _height;
    const float tanHalfFovY = tan(glm::radians(_fovY) / 2.0f);

    result[0][0] = 1.0f / (aspectRatio * tanHalfFovY);
    result[1][1] = 1.0f / tanHalfFovY;
    result[2][2] = -(_farZ + _nearZ) / (_farZ - _nearZ);
    result[2][3] = -1.0f;
    result[3][2] = -(2.0f * _farZ * _nearZ) / (_farZ - _nearZ);

    return result;
}

int main()
{
    const float WIDTH = 780.0f;
    const float HEIGHT = 750.0f;
    const float FOV_Y = 45.0f;
    const float NEAR_Z = 0.1f;
    const float FAR_Z = 500.0f;

    glm::mat4 perspectiveMatrix = CreatePerspectiveMatrix(FOV_Y, WIDTH, HEIGHT, NEAR_Z, FAR_Z);
    std::cout << "투영 행렬:\n" << glm::to_string(perspectiveMatrix) << std::endl;

    return 0;
}