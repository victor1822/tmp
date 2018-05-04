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
	int material_type;

	Ray get_reflected_ray(glm::vec3 ray_dir){

		glm::vec3 pos={0.0f,0.0f,0.0f},dir={0.0f,0.0f,0.0f};

		if(material_type == 0){
			float r1 = ((float) rand())/RAND_MAX;
			float r2 = ((float) rand())/RAND_MAX;
			float sinTheta = sqrtf(1 - r1 * r1); 
			float phi = 2 * M_PI * r2; 
			float x = sinTheta * cosf(phi); 
			float z = sinTheta * sinf(phi);  

			ONB normal_basis;
			normal_basis.setFromV(normal_);
			dir = glm::normalize(normal_basis.getBasisMatrix() * glm::vec3(x, r1, z) );
		}

		if(material_type == 1){

			//ray_dir = -glm::normalize(ray_dir);

			//ONB normal_basis;
			//normal_basis.setFromV(normal_);
			glm::vec3 temp = -ray_dir;
			//glm::vec3 temp =  - (glm::normalize(normal_basis.getBasisMatrix() * ray_dir));
			dir = 2*glm::dot(temp,normal_)*normal_ - temp;
			//dir.x = -temp.x;
			//dir.y = -temp.y;
		 	//dir.z = temp.z; 

		}

		ONB world_basis;
		dir = glm::normalize(world_basis.getBasisMatrix()*dir);
		pos = position_ + 0.00001f*dir;//epsilon
 
		return Ray{ pos/*position_*/, 
                	    dir/*direction*/};

	}
};

#endif /* INTERSECTION_RECORD_H_ */

