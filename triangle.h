#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <glm/glm.hpp>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

#define EPSILON 0.000001

class Triangle : public Primitive
{
public:

	Triangle( void );

	Triangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c);

	bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

	glm::vec3 a_ = { 0.0f, 0.0f, 0.0f };
	glm::vec3 b_ = { 0.0f, 0.0f, 0.0f };
	glm::vec3 c_ = { 0.0f, 0.0f, 0.0f };

private:

    static const float kIntersectionTestEpsilon_;
};

#endif /* TRIANGLE_H_ */
