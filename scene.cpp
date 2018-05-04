#include "scene.h"
//#define _USE_MATH_DEFINES
//#include <math.h>

Scene::Scene( void )
{}

Scene::~Scene( void )
{}

bool Scene::intersect( const Ray &ray,
                       IntersectionRecord &intersection_record ) const
{
    bool intersection_result = false;
    IntersectionRecord tmp_intersection_record;
    std::size_t num_primitives = primitives_.size();

    // Loops over the list of primitives, testing the intersection of each primitive against the given ray 
    for ( std::size_t primitive_id = 0; primitive_id < num_primitives; primitive_id++ )
        if ( primitives_[primitive_id]->intersect( ray, tmp_intersection_record ) )
            if ( ( tmp_intersection_record.t_ < intersection_record.t_ ) && ( tmp_intersection_record.t_ > 0.0 ) )
            {
                intersection_record = tmp_intersection_record;
		//glm::vec3 lightd = -intersection_record.position_;//direcao do raio para a luz(intersection_pos-{0,0,0})
		//lightd.x = 0.0001; ///direcao da fonte de luz
		//lightd.y = -1.0000; 
		//lightd.z = -0.0000;
		//float num = dot(primitives_[primitive_id]->normal,lightd);
		intersection_record.cor[0] = primitives_[primitive_id]->cor[0];
		intersection_record.cor[1] = primitives_[primitive_id]->cor[1];
		intersection_record.cor[2] = primitives_[primitive_id]->cor[2];
		intersection_record.emission = primitives_[primitive_id]->emission;
			///LAMBERTIAN BRDF	
		intersection_record.brdf[0] = primitives_[primitive_id]->brdf[0];
		intersection_record.brdf[1] = primitives_[primitive_id]->brdf[1];
		intersection_record.brdf[2] = primitives_[primitive_id]->brdf[2];

		intersection_record.material_type = primitives_[primitive_id]->material_type;
		//intersection_record.normal_ = primitives_[primitive_id]->normal; //já é calculado dentro de intersect()

		//intersection_record.cor[0] = (primitives_[primitive_id]->emission[0]+primitives_[primitive_id]->cor[0])*num;
		//intersection_record.cor[1] = (primitives_[primitive_id]->emission[1]+primitives_[primitive_id]->cor[1])*num;
		//intersection_record.cor[2] = (primitives_[primitive_id]->emission[2]+primitives_[primitive_id]->cor[2])*num;

                intersection_result = true; // the ray intersects a primitive!
            }

    return intersection_result;
}

void Scene::load(const char* argx, int &mt/*material type*/) 
{

 Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile(/*"cena/monkey2.obj"*//*"cena/cornellbox_spheres.obj"*//*"cena/entire_scene1.obj"*/argx, aiProcess_Triangulate );

   if (!scene) {
    std::ostringstream ss;
    ss << "Error loading scene: " << importer.GetErrorString();
  }

  if (scene->HasMeshes()) {
    for (unsigned int mesh_id = 0; mesh_id < scene->mNumMeshes; mesh_id++) {
      const aiMesh* mesh_ptr = scene->mMeshes[mesh_id];
      const aiMaterial* mtl = scene->mMaterials[mesh_ptr->mMaterialIndex];
      aiColor4D ke{0.0f};
      mtl->Get(AI_MATKEY_COLOR_EMISSIVE, ke);
      aiColor4D kd{1.0f};
      mtl->Get(AI_MATKEY_COLOR_DIFFUSE, kd);

      for (size_t vertex_id = 0; vertex_id < mesh_ptr->mNumVertices;
           vertex_id += 3) 
	{
        const aiVector3D* vertex_ptr = &mesh_ptr->mVertices[vertex_id];
	const aiVector3D* normal_ptr = &mesh_ptr->mNormals[vertex_id];

        Triangle triangle(
            glm::vec3(vertex_ptr[0].x, vertex_ptr[0].y, vertex_ptr[0].z),
            glm::vec3(vertex_ptr[1].x, vertex_ptr[1].y, vertex_ptr[1].z),
            glm::vec3(vertex_ptr[2].x, vertex_ptr[2].y, vertex_ptr[2].z));

	primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{triangle.a_,triangle.b_,triangle.c_}));

	size_t indice = primitives_.size()-1;

	primitives_[indice]->normal[0] = glm::normalize(normal_ptr[0].x);
	primitives_[indice]->normal[1] = glm::normalize(normal_ptr[0].y);
	primitives_[indice]->normal[2] = glm::normalize(normal_ptr[0].z);

	//COR DIFUSA DO MTL
	primitives_[indice]->cor[0] = kd.r;
	primitives_[indice]->cor[1] = kd.g;
	primitives_[indice]->cor[2] = kd.b;

	///PARA CORES RANDOMICAS
	//primitives_[indice]->cor[0] = ((float)(rand())/RAND_MAX);
	//primitives_[indice]->cor[1] = ((float)(rand())/RAND_MAX);
	//primitives_[indice]->cor[2] = ((float)(rand())/RAND_MAX);

	///PARA A MESMA COR
	//primitives_[indice]->cor[0] = 0;
	//primitives_[indice]->cor[1] = 0;
	//primitives_[indice]->cor[2] = 255;

	//COR POR PARAMETRO
	//primitives_[indice]->cor[0] = cores[0];
	//primitives_[indice]->cor[1] = cores[1];
	//primitives_[indice]->cor[2] = cores[2];
	
	//EMISSIVE COLOR DO MTL
	primitives_[indice]->emission[0] = ke.r;
	primitives_[indice]->emission[1] = ke.g;
	primitives_[indice]->emission[2] = ke.b;

		primitives_[indice]->material_type = mt;//lambertian diffuse or metalic

	if(mt==0){	
		primitives_[indice]->brdf[0] = kd.r/M_PI; //lambertian diffuse
		primitives_[indice]->brdf[1] = kd.g/M_PI;
		primitives_[indice]->brdf[2] = kd.b/M_PI;
	}
	if(mt==1){	 
		primitives_[indice]->brdf[0] = 1.0f;//metalic
		primitives_[indice]->brdf[1] = 1.0f;
		primitives_[indice]->brdf[2] = 1.0f;
	}

      }
    }
  }

	//primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.0f, -1.0f }, 0.2f } ) );

	//size_t indice = primitives_.size()-1;
	//primitives_[indice]->emission[0] = 0.0f;
	//primitives_[indice]->emission[1] = 0.0f;
	//primitives_[indice]->emission[2] = 0.0f;

//	primitives_[indice]->cor[0] = 0.640f;
//	primitives_[indice]->cor[1] = 0.0f;
//	primitives_[indice]->cor[2] = 0.0f;
	


	//==========================================

	///************************ três bolas e um triângulo, imagens da primeira atividade
	/*primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.0f,  0.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.0f, -1.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f,-0.5f, -2.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.5f, -3.0f }, 0.2f } ) );
	
	int value = 0;

	glm::vec3 a = { -0.5f , 0.0f , value}, 
		  c = { 0.0f , -0.5f , value}, 
		  b = { 0.0f , 0.5f , value}; 
	
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{a,b,c} ) );*/

	//value_front = -1.0f;
	//value_back = -2.0f;

		///***************** 8 esferas posicionadas simétricamente
/*
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f, -1.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, -0.5f, -1.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f, -1.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.5f, -1.0f }, 0.2f } ) );

	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, -0.5f, -2.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f, -2.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f, -2.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.5f, -2.0f }, 0.2f } ) );
*/

		///****************
/*
}*/

}

void Scene::loadspheres(int &mt/*material type*/) 
{
	
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ 0.0f, 0.0f, -0.6f }, 0.65f }  ) );

	size_t indice = primitives_.size()-1;
	primitives_[indice]->emission[0] = 0.0f;
	primitives_[indice]->emission[1] = 0.0f;
	primitives_[indice]->emission[2] = 0.0f;

	primitives_[indice]->cor[0] = 0.640f;
	primitives_[indice]->cor[1] = 0.640f;
	primitives_[indice]->cor[2] = 0.0f;

	primitives_[indice]->material_type = mt;

	if(mt == 0){
		primitives_[indice]->brdf[0] = 0.240f/M_PI;
		primitives_[indice]->brdf[1] = 0.240f/M_PI;
		primitives_[indice]->brdf[2] = 0.0f/M_PI;
	}
	if(mt == 1){
		primitives_[indice]->brdf[0] = 1.0f;
		primitives_[indice]->brdf[1] = 1.0f;
		primitives_[indice]->brdf[2] = 1.0f;
	}

	
	/*primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ 0.0f+0.50f, 0.65f, -0.6f }, 0.37f } ) );

	size_t indice = primitives_.size()-1;
	primitives_[indice]->emission[0] = 0.0f;
	primitives_[indice]->emission[1] = 0.0f;
	primitives_[indice]->emission[2] = 0.0f;

	primitives_[indice]->cor[0] = 0.640f;
	primitives_[indice]->cor[1] = 0.640f;
	primitives_[indice]->cor[2] = 0.0f;

	primitives_[indice]->brdf[0] = 0.640f/M_PI;
	primitives_[indice]->brdf[1] = 0.640f/M_PI;
	primitives_[indice]->brdf[2] = 0.0f/M_PI;

	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ 0.0f-0.50f, 0.65f, -0.6f }, 0.37f } ) );

	indice++;
	primitives_[indice]->emission[0] = 0.0f;
	primitives_[indice]->emission[1] = 0.0f;
	primitives_[indice]->emission[2] = 0.0f;

	primitives_[indice]->cor[0] = 0.640f;
	primitives_[indice]->cor[1] = 0.640f;
	primitives_[indice]->cor[2] = 0.0f;

	primitives_[indice]->brdf[0] = 0.640f/M_PI;
	primitives_[indice]->brdf[1] = 0.640f/M_PI;
	primitives_[indice]->brdf[2] = 0.0f/M_PI;*/
	
	
	//==========================================

	///************************ três bolas e um triângulo, imagens da primeira atividade
	/*primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.0f,  0.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.0f, -1.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f,-0.5f, -2.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.5f, -3.0f }, 0.2f } ) );
	
	int value = 0;

	glm::vec3 a = { -0.5f , 0.0f , value}, 
		  c = { 0.0f , -0.5f , value}, 
		  b = { 0.0f , 0.5f , value}; 
	
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle{a,b,c} ) );*/

	//value_front = -1.0f;
	//value_back = -2.0f;

		///***************** 8 esferas posicionadas simétricamente
/*
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f, -1.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, -0.5f, -1.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f, -1.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.5f, -1.0f }, 0.2f } ) );

	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, -0.5f, -2.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f, -2.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f, -2.0f }, 0.2f } ) );
	primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.5f, -2.0f }, 0.2f } ) );
*/

		///****************
/*
}*/

}

