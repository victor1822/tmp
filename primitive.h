#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include <memory>

#include "ray.h"
#include "intersection_record.h"

class Primitive
{
public:

	typedef std::unique_ptr< Primitive > PrimitiveUniquePtr;

	Primitive( void );

	virtual ~Primitive( void );

	virtual bool intersect( const Ray &ray,
				IntersectionRecord &intersection_record ) const = 0;

	glm::vec3 cor;//cor difusa

	glm::vec3 emission;//emission color

	glm::vec3 brdf;

	glm::vec3 normal;//vetor normal
};

#endif /* PRIMITIVE_H_ */

