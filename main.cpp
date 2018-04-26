#include "main.h"

int main( void )
{

    unsigned int x_resolution = 512;
    unsigned int y_resolution = 512;

  /* OrthographicCamera camera{ -1.25f, 
                                1.25f, 
                               -1.25f, 
                                1.25f,
                                glm::ivec2{ x_resolution, y_resolution }, 
                                glm::vec3{ 0.0f, 0.0f,  10.0f },     // position to comment to edit
				//glm::vec3{ 0.3f, 0.0f,  1.0f },     // position to edit
                                glm::vec3{ 0.0f, 1.0f,  0.0f },     // up
                                glm::vec3{ 0.0f, 0.0f, -1.0f } };   // look at
*/

   PerspectiveCamera camera{ -1.25f, 
                                1.25f, 
                               -1.25f, 
                                1.25f,
				1.0f,
                                glm::ivec2{ x_resolution, y_resolution }, 
                                //glm::vec3{ 0.0f, 0.0f,  1.0f },     // position to comment to edit
				glm::vec3{ 0.0f, 0.0f,  15.0f },     // position to edit
                                glm::vec3{ 0.0f, 1.0f,  0.0f },     // up
                                glm::vec3{ 0.0f, 0.0f, -1.0f } };   // look at


    Scene scene{};

    
	std::vector<const char*>arq;
	//std::vector<glm::vec3> cores;
	//glm::vec3 cor_temp;

	//#1 macaco
	//arq.push_back("cena/objetos/monkey2.obj");
	//arq.push_back("cena/objetos/macaco_torto.obj");
	//cor_temp[0] = 0.579;
	//cor_temp[1] = 0.210;
	//cor_temp[2] = 0.068;
	//cores.push_back(cor_temp);

	//#2 plano de trás
	//.push_back("cena/objetos/back_plane.obj");
	//cor_temp[0] = 0.110;
	//cor_temp[1] = 0.061;
	//cor_temp[2] = 0.640;
	//cores.push_back(cor_temp);

	//#3 plano do chão
	//arq.push_back("cena/objetos/floor_plane.obj");
	//cor_temp[0] = 0.640;
	//cor_temp[1] = 0.640;
	//cor_temp[2] = 0.640;
	//cores.push_back(cor_temp);

	//#4 plano do teto
	//arq.push_back("cena/objetos/teto_plane.obj");
	///mesma cor que o chão
	//cores.push_back(cor_temp);

	//#5 plano da esquerda
	//arq.push_back("cena/objetos/left_plane.obj");
	//cor_temp[0] = 0.640;
	//cor_temp[1] = 0.023;
	//cor_temp[2] = 0.035;
	//cores.push_back(cor_temp);

	//#6 plano da direita
	//arq.push_back("cena/objetos/right_plane.obj");
	//cor_temp[0] = 0.21;
	//cor_temp[1] = 0.640;
	//cor_temp[2] = 0.146;
	//cores.push_back(cor_temp);

	//#7 sólido cúbico da luminária
	//arq.push_back("cena/objetos/light_cube.obj");
	//cor_temp[0] = 0.640;
	//cor_temp[1] = 0.093;
	//cor_temp[2] = 0.030;
	//cores.push_back(cor_temp);

	//#8 plano que representa a luz(objeto emissivo)
	//arq.push_back("cena/objetos/light_plane.obj");
	//cor_temp[0] = 0.640;
	//cor_temp[1] = 0.640;
	//cor_temp[2] = 0.640;
	//cores.push_back(cor_temp);

	//#9 esfera1
	//arq.push_back("cena/objetos/sphere1.obj");
	//cor_temp[0] = 0.531;
	//cor_temp[1] = 0.640;
	//cor_temp[2] = 0.0;
	//cores.push_back(cor_temp);

	//#10 esfera1
	//arq.push_back("cena/objetos/sphere2.obj");
	//cor_temp[0] = 0.490;
	//cor_temp[1] = 0.640;
	//cor_temp[2] = 0.900;
	//cores.push_back(cor_temp);

	//#11 esfera1
	//arq.push_back("cena/objetos/pink_object.obj");

	//arq.push_back("cena/objetos/super_light_plane.obj");
	arq.push_back("cena/tudo.obj");
		
	//arq.push_back("cena/monkey2.obj");
	//arq.push_back("cena/monkey.obj");
	//for(std::size_t e=0;e<arq.size();e++)
    	scene.load(arq[0]/*,cores[e]*/);

	//scene.loadspheres();


    Buffer rendering_buffer{ x_resolution, y_resolution };
    glm::vec3 background_color{ 0.0f, 0.0f, 0.0f };

    // Set up the renderer.
    //RayTracer rt( camera,
      //            scene,
        //          background_color,
          //        rendering_buffer );

    //rt.integrate(); // Renders the final image.

    PathTracer pt(camera,
                  scene,
                  background_color,
                  rendering_buffer );
    pt.integrate(); //Renders the final image


    // Save the rendered image to a .ppm file.
    rendering_buffer.save( "output_image2.ppm" );

    return EXIT_SUCCESS;
}

