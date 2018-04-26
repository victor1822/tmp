#ifndef RANDFN_H_
#define RANDFN_H_

#include <cstdlib>

float random_float(const float min, const float max)
{
    if (max == min) return min;
    else if (min < max) return (max - min) * ((float)rand() / RAND_MAX) + min;

    // return 0 if min > max
    return 0;
}

/*glm::vec3 uniformSampleHemisphere(const float &r1, const float &r2) 
{ 
    // cos(theta) = r1 = y
    // cos^2(theta) + sin^2(theta) = 1 -> sin(theta) = srtf(1 - cos^2(theta))
    float sinTheta = sqrtf(1 - r1 * r1); 
    float phi = 2 * M_PI * r2; 
    float x = sinTheta * cosf(phi); 
    float z = sinTheta * sinf(phi); 
    return glm::vec3(x, r1, z); 
} */

#endif /* RANDFN_H_ */

