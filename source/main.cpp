#define GLM_ENABLE_EXPERIMENTAL 
#include <iostream>
#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/string_cast.hpp>

glm::mat4 CreateViewMatrix(glm::vec3 _cameraPos, glm::vec3 _targetPos, glm::vec3 _upVector)
{
    // 좌표계 축 계산
    glm::vec3 forward = glm::normalize(_cameraPos - _targetPos);
    glm::vec3 rightVector = glm::normalize(glm::cross(_upVector, forward));

    // 만약 rightVector가 제대로 계산되지 않았다면 (up과 forward가 평행할 경우)
    if (glm::length(rightVector) < 0.001f)
    {
        // 대안 rightVector 설정
        rightVector = glm::vec3(1.0f, 0.0f, 0.0f);
    }

    glm::vec3 upDir = glm::normalize(glm::cross(forward, rightVector));

    // 회전 행렬 생성 - 다른 초기화 방식 사용
    glm::mat4 rotMatrix = glm::mat4(1.0f);

    // 행렬의 열을 직접 설정하는 방식
    rotMatrix[0] = glm::vec4(rightVector, 0.0f);
    rotMatrix[1] = glm::vec4(upDir, 0.0f);
    rotMatrix[2] = glm::vec4(forward, 0.0f);

    // 이동 행렬 생성
    glm::mat4 transMatrix = glm::translate(glm::mat4(1.0f), -_cameraPos);

    // 최종 뷰 행렬 계산
    return rotMatrix * transMatrix;
}

void PrintMatrixInfo(const glm::mat4& _matrix, const std::string& _name)
{
    std::cout << _name << ":\n" << glm::to_string(_matrix) << std::endl;
}

int main()
{
    // 변환 매개변수 정의
    const float X_TRANSLATION = 0.0f;
    const float Y_TRANSLATION = 5.0f;
    const float Z_TRANSLATION = 0.0f;
    const float X_ROTATION = 40.0f;  // degrees
    const float Y_ROTATION = 56.0f;  // degrees
    const float Z_ROTATION = 0.0f;   // degrees
    const float SCALE_VALUE = 1.3f;

    // 로컬 좌표 정의
    glm::vec4 localPoint(4.0f, 5.0f, 3.0f, 1.0f);

    // 변환 행렬 생성
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(SCALE_VALUE, SCALE_VALUE, SCALE_VALUE));
    glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f),
        glm::vec3(X_TRANSLATION, Y_TRANSLATION, Z_TRANSLATION));

    // 회전 행렬 생성
    glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(X_ROTATION), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateMatrix = glm::rotate(rotateMatrix, glm::radians(Y_ROTATION), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateMatrix = glm::rotate(rotateMatrix, glm::radians(Z_ROTATION), glm::vec3(0.0f, 0.0f, 1.0f));

    // 모델 행렬 계산 및 적용
    glm::mat4 modelMatrix = translateMatrix * rotateMatrix * scaleMatrix;
    glm::vec4 worldPoint = modelMatrix * localPoint;

    // 결과 출력
    std::cout << "World Point: " << glm::to_string(worldPoint) << std::endl;

    // 주어진 뷰 행렬
    glm::mat4 viewMatrix = {
        {0.83f, -0.00f, -0.56f, 0.00f},
        {-0.3f, 0.84f, -0.45f, 0.00f},
        {0.47f, 0.54f, 0.70f, -44.47f},
        {0.0f, 0.00f, 0.00f, 1.00f}
    };

    // 뷰 행렬 역변환하여 카메라 정보 추출
    glm::mat4 inverseViewMatrix = glm::inverse(viewMatrix);
    glm::vec3 cameraPosition = inverseViewMatrix[3];
    glm::vec3 zAxis = glm::normalize(-inverseViewMatrix[2]);
    glm::vec3 lookTarget = cameraPosition + zAxis * 10.0f;
    glm::vec3 upDirection(0.0f, 1.0f, 0.0f);

    // 새로운 뷰 행렬 생성
    glm::mat4 newViewMatrix = CreateViewMatrix(cameraPosition, lookTarget, upDirection);

    // 결과 출력
    PrintMatrixInfo(newViewMatrix, "새로 생성한 뷰 행렬");

    return 0;
}