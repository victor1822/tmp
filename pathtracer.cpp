#include "randfn.h"
#include "pathtracer.h"


PathTracer::PathTracer( Camera &camera,
                      const Scene &scene,
                      const glm::vec3 background_color,
                      Buffer &buffer ) :
        camera_( camera ),
        scene_( scene ),
        background_color_{ background_color },
        buffer_( buffer )
{}


glm::vec3 PathTracer::L( Ray &ray,/*IntersectionRecord &intersection_record,*/ std::size_t & curr_deph ){

	IntersectionRecord intersection_record;
	
	intersection_record.t_ = std::numeric_limits< double >::max(); 

	glm::vec3 Lo = glm::vec3(0,0,0);
	glm::vec3 Li = glm::vec3(0,0,0);

	if(curr_deph < max_deph)
	{
		if(scene_.intersect(ray,intersection_record))
		{
			Ray refl_ray = intersection_record.get_reflected_ray(ray.direction_);
			curr_deph++;
	
			//float num_= glm::dot(intersection_record.normal_,refl_ray.direction_);
			//intersection_record.brdf[0] = intersection_record.cor[0]/M_PI;
			//intersection_record.brdf[1] = intersection_record.cor[1]/M_PI;
			//intersection_record.brdf[2] = intersection_record.cor[2]/M_PI;

			Li=L(refl_ray/*,intersection_record*/,curr_deph);

			if(intersection_record.material_type == 0){
			Lo[0] = intersection_record.emission[0] + intersection_record.brdf[0]*2*M_PI*dot(intersection_record.normal_,refl_ray.direction_)*Li[0];
			Lo[1] = intersection_record.emission[1] + intersection_record.brdf[1]*2*M_PI*dot(intersection_record.normal_,refl_ray.direction_)*Li[1];
			Lo[2] = intersection_record.emission[2] + intersection_record.brdf[2]*2*M_PI*dot(intersection_record.normal_,refl_ray.direction_)*Li[2];
			}
			 if(intersection_record.material_type == 1) 
				Lo = Li;
		}
	}
	return Lo;
}


void PathTracer::integrate( void )
{
    //IntersectionRecord intersection_record;

    // Image space origin (i.e. x = 0 and y = 0) at the top left corner.

    // Loops over image rows

	float randfx,randfy;
	std::size_t num_amostras;
	int cond=-1;
	while(cond<0){
	std::cout<<"Digite o numero de amostras por pixel(entre 1 e 100.000):"<<std::endl;
	std::cin>>num_amostras;
	if(num_amostras==0||num_amostras>100000){
		std::cout<<"Entrada invalida. Digite um numero entre 1 e 100.000."<<std::endl;
		}
		else cond=2;
	}
	std::cout<<"O numero de amostras escolhido foi "<<num_amostras<<std::endl;

	cond=-1;
	while(cond<0){
	std::cout<<"Digite o numero de raios secundarios(entre 1 e 200):"<<std::endl;
	std::cin>>max_deph;
	if(max_deph==0||max_deph>200){
		std::cout<<"Entrada invalida. Digite um numero entre 1 e 200."<<std::endl;
		}
		else cond=2;
	}
	std::cout<<"O numero de raios secundarios escolhido foi "<<max_deph<<std::endl;


	//glm::vec3* amostras = new glm::vec3[num_amostras];
	glm::vec3 amostras;
	glm::vec3 tmp;

    for ( std::size_t y = 0; y < buffer_.v_resolution_; y++ )
    {
        std::stringstream progress_stream;
        progress_stream << "\r  progress .........................: "
                        << std::fixed << std::setw( 6 )
                        << std::setprecision( 2 )
                        << 100.0 * y / ( buffer_.v_resolution_ - 1 )
                        << "%";

        std::clog << progress_stream.str();

        // Loops over image columns
        for ( std::size_t x = 0; x < buffer_.h_resolution_; x++ )
        {	
		amostras[0]=0;//r
		amostras[1]=0;//g
		amostras[2]=0;//b

		for(std::size_t z=0;z<num_amostras;z++)
		{

           		//intersection_record.t_ = std::numeric_limits< double >::max(); 

				randfx = random_float(-0.5,0.5) + 0.5f;
				randfy = random_float(-0.5,0.5) + 0.5f;
				//if(z==0)
				//{
				
				//randfx = 0.5f;
				//randfy = 0.5f;				

				//}
		
            			Ray ray{ camera_.getWorldSpaceRay( glm::vec2{ x + randfx , y + randfy } ) };
				std::size_t curr_deph = 0;
				tmp = L(ray,/*intersection_record,*/curr_deph); 
				amostras[0]+=tmp[0]/num_amostras;
				amostras[1]+=tmp[1]/num_amostras;
				amostras[2]+=tmp[2]/num_amostras;
	
		}


		buffer_.buffer_data_[x][y][0] = amostras[0];///num_amostras;//media aritmetica das amostras
		buffer_.buffer_data_[x][y][1] = amostras[1];///num_amostras;
		buffer_.buffer_data_[x][y][2] = amostras[2];///num_amostras;
        }
    }

    std::clog << std::endl;
}

