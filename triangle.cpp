#include "triangle.h"

Triangle::Triangle( void )
{}

Triangle::Triangle( const glm::vec3 &a,const glm::vec3 &b,const glm::vec3 &c ) :
        a_{ a },
        b_{ b },
	c_{ c }
{}

bool Triangle::intersect( const Ray &ray,
                        IntersectionRecord &intersection_record ) const
{
    /* Ray-Triangle intersection test adapted from the very efficient algorithm presented in the article:
     *
     *     "FastMinimum Storage Ray/Triangle Intersection".
     *     Made by Tomas Moller and Ben Trumbore.
     */

        glm::vec3 edge1,edge2,tvec,pvec,qvec;
	float u,v;

        float det,inv_det;

        /* Find vectors for two edges sharing vert0 */
	edge1 = b_ - a_;///ab vector 

	edge2 = c_ - a_;//ac vector

        /* Begin calculating determinant - also used to calculate U parameter*/
        pvec = glm::cross(ray.direction_,edge2);

        /* If determinant is near zero, ray lies in plane or triangle */
        det = glm::dot(edge1,pvec);

        if(det > -EPSILON && det < EPSILON)
            return false;
        inv_det = 1.0/det;

        /* Calculate distance from vert0 to ray origin */

	tvec = ray.origin_ - a_;

        /* Calculate U parameter and test bounds */
        u = glm::dot(tvec,pvec)*inv_det;
        if(u < 0.0 || u > 1.0)
            return false;

        /* Prepare to test V parameter */
        qvec = glm::cross(tvec,edge1);

        /* Calculate V parameter and test bounds */
        v = glm::dot(ray.direction_,qvec)* inv_det;
        if(v < 0.0 || u + v > 1.0)
            return false;

        /* Calculate t, ray intersects triangle */

	intersection_record.t_ = glm::dot(edge2,qvec)*inv_det;


	intersection_record.normal_ = glm::cross(edge1,edge2);

        ///The point that the ray intercects the triangle

	intersection_record.position_ = ray.origin_ + ray.direction_*(intersection_record.t_);

	    ///raio refletido (to be continued...)
            //Ray r2;

            //r2.direction_.x = ray.direction_.x - glm::dot(ray.direction_,intersection_record.normal_)*intersection_record.normal_.x*2;
            //r2.direction_.y = ray.direction_.y - glm::dot(ray.direction_,intersection_record.normal_)*intersection_record.normal_.y*2;
            //r2.direction_.z = ray.direction_.z - glm::dot(ray.direction_,intersection_record.normal_)*intersection_record.normal_.z*2;

            //r2.origem = intersection_record.position_;

	return true;

}
