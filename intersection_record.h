#ifndef INTERSECTION_RECORD_H_
#define INTERSECTION_RECORD_H_

#include <glm/glm.hpp>
#include "onb.h"

class IntersectionRecord
{
	public:
	float t_;
	glm::vec3 position_;
	glm::vec3 normal_;
	glm::vec3 cor;//difuse color
	glm::vec3 emission;//emission color
	glm::vec3 brdf;//lambertian

	Ray get_reflected_ray(){

	        /*float r1 = ((float) std::rand() / (RAND_MAX));
	        float r2 = ((float) std::rand() / (RAND_MAX));  
		const glm::vec3 n2 = glm::normalize(fabs(normal_.x) > fabs(normal_.y) ? glm::vec3(normal_.z, 0.0f, -normal_.x) : glm::vec3(0.0f, -normal_.z, normal_.y));
		const glm::vec3 n1 = glm::cross(normal_, n2);
		float sinTheta = sqrtf(1 - r1 * r1); 
		float phi = 2 * M_PI * r2; 
		float x = sinTheta * std::cos(phi); 
		float z = sinTheta * std::sin(phi);
	
		//return Ray{ position_, 
               //glm::normalize( onb_.getBasisMatrix() * glm::normalize(glm::cross(normal_, glm::Vec3(x, r1, z)) )) };

		ONB normal_basis; 
		normal_basis.setFromV(normal_);
		return Ray{ position_, 
                glm::normalize(glm::vec3(    x * n1.x + r1 * normal_.x + z * n2.x,
                                        x * n1.y + r1 * normal_.y + z * n2.y,
                                        x * n1.z + r1 * normal_.z + z * n2.z     ))};*/
		float r1 = ((float) rand())/RAND_MAX;
		float r2 = ((float) rand())/RAND_MAX;
		float sinTheta = sqrtf(1 - r1 * r1); 
		float phi = 2 * M_PI * r2; 
		float x = sinTheta * cosf(phi); 
		float z = sinTheta * sinf(phi);  
	
		//return Ray{ position_, 
               //glm::normalize( onb_.getBasisMatrix() * glm::normalize(glm::cross(normal_, glm::Vec3(x, r1, z)) )) };

		ONB normal_basis; 
		normal_basis.setFromV(normal_);
		glm::vec3 pos;
		pos[0] = position_[0]+0.00001f*t_;//epsilon
		pos[1] = position_[1]+0.00001f*t_;//epsilon
		pos[2] = position_[2]+0.00001f*t_;//epsilon
		//dir[0]+=0.000002;//epsilon
		//dir[1]+=0.000002;
		//dir[2]+=0.000002; 
		return Ray{ pos/*position_*/, 
                glm::normalize( normal_basis.getBasisMatrix() * glm::vec3(x, r1, z) )};

	}
};

#endif /* INTERSECTION_RECORD_H_ */

