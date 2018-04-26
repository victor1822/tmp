#ifndef PATHTRACER_H_
#define PATHTRACER_H_

#include <sstream>
#include <iomanip>
#include <cmath>

#include "camera.h"
#include "scene.h"
#include "buffer.h"

#define _USE_MATH_DEFINES
#include <math.h>

class PathTracer
{
public:

    PathTracer( Camera &camera,
               const Scene &scene,
               const glm::vec3 background_color,
               Buffer &buffer );
    glm::vec3 L( Ray& ray/*,IntersectionRecord &intersection_record*/, std::size_t& curr_deph);

    void integrate( void );

private:

    const Camera &camera_;

    const Scene &scene_;

    glm::dvec3 background_color_;

    Buffer &buffer_;

    std::size_t max_deph;

};

#endif /* PATHTRACER_H_ */
