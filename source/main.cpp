
#define GLM_ENABLE_EXPERIMENTAL 
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/string_cast.hpp>

int main()
{
	glm::vec3 v(5, 6, 1);
	glm::mat3 t(1.0);
	t = glm::translate(t, glm::vec2(2, 3));
	v = t * v;
	std::cout << to_string(t) << std::endl;
	std::cout << to_string(v) << std::endl;
	return 0;
}