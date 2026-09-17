#include"glm/glm.hpp"
struct Rect
{
	glm::vec3 origin;
	float breadth;
	float length;
	glm::vec3 color;

	Rect(glm::vec3 origin, float w, float b, glm::vec3 color)
	{
		this->origin = origin;
		this->length = length;
		this->breadth = breadth;
		this->color = color;
	}
};