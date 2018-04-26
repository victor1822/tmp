#ifndef SCENE_H_
#define SCENE_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "primitive.h"
#include "sphere.h" 
#include "triangle.h"

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/types.h>
#include <assimp/Importer.hpp>


class Scene
{

//private:

    //std::vector<Triangle> _triangles;     // Triangles

public:

    Scene( void );

    ~Scene( void );

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    void load( const char* argx/*, glm::vec3 cores*/);
    void loadspheres();

    //L(const Ray &ray,
      //IntersectionRecord &intersection_record ) const;


    std::vector< Primitive::PrimitiveUniquePtr > primitives_;

};

#endif /* SCENE_H_ */

