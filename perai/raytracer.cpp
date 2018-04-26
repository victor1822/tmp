#include "raytracer.h"
#include "randfn.h"

RayTracer::RayTracer( Camera &camera,
                      const Scene &scene,
                      const glm::vec3 background_color,
                      Buffer &buffer ) :
        camera_( camera ),
        scene_( scene ),
        background_color_{ background_color },
        buffer_( buffer )
{}

void RayTracer::integrate( void )
{
    IntersectionRecord intersection_record;

    // Image space origin (i.e. x = 0 and y = 0) at the top left corner.

    // Loops over image rows

	float randfx,randfy;
	std::size_t num_amostras;
	int cond=-1;
	while(cond<0){
	std::cout<<"Digite o numero de amostras por pixel(entre 1 e 16):"<<std::endl;
	std::cin>>num_amostras;
	if(num_amostras==0||num_amostras>16){
		std::cout<<"Entrada invalida. Digite um numero entre 1 e 10."<<std::endl;
		}
		else cond=2;
	}
	std::cout<<"O número de amostras escolhido foi "<<num_amostras<<std::endl;

	//glm::vec3* amostras = new glm::vec3[num_amostras];
	float amostras[3];

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
		amostras[0]=0;
		amostras[1]=0;
		amostras[2]=0;

		for(std::size_t z=0;z<num_amostras;z++)
		{

           		intersection_record.t_ = std::numeric_limits< double >::max(); 

				randfx = random_float(-0.5,0.5) + 0.5f;
				randfy = random_float(-0.5,0.5) + 0.5f;
		
            			Ray ray{ camera_.getWorldSpaceRay( glm::vec2{ x + randfx , y + randfy } ) };

            			if ( scene_.intersect( ray, intersection_record ) )
				{
					amostras[0]+=intersection_record.cor[0];
					amostras[1]+=intersection_record.cor[1];
					amostras[2]+=intersection_record.cor[2];
				}
	
		}

		buffer_.buffer_data_[x][y][0] = amostras[0]/num_amostras;
		buffer_.buffer_data_[x][y][1] = amostras[1]/num_amostras;
		buffer_.buffer_data_[x][y][2] = amostras[2]/num_amostras;
        }
    }

    std::clog << std::endl;
}

