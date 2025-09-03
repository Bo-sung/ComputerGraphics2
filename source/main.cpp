
#define GLM_ENABLE_EXPERIMENTAL 
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/common.hpp>
#include <glm/matrix.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vector_relational.hpp>

int main()
{
	glm::vec3 p(1, 4, -5);
	glm::vec3 v(5, 1, 4);

	std::cout << "1. p + v = " << glm::to_string(p + v) << std::endl;

	glm::vec3 v1(1, 0, 0);
	glm::vec3 v2(0, 1, 0);

	std::cout << "2. v1 + v2 = " << glm::to_string(v1 + v2) << std::endl;

	std::cout << "3. v1 X 2 = " << glm::to_string(v1 * 2.0f) << std::endl;

	glm::vec3 s(8, 2, 5);
	glm::vec3 e(1, -1, 4);

	std::cout << "4. s - e = " << glm::to_string(s - e) << std::endl;

	glm::vec3 V(1, 3, 4);

	glm::vec3 v_h = glm::normalize(V);
	std::cout << "5. Normalized V = " << glm::to_string(v_h) << std::endl;

	glm::vec3 v3(1, -1, 4);
	glm::vec4 v4(v3, 0);

	std::cout << "6. 3D -> 4D v3 = " << glm::to_string(v3) << " v4 = " << glm::to_string(v4) << std::endl;


	return 0;
}