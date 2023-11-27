//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture DadoTexture;
Texture llantaTexture;
Texture Lampara;


Model Kitt_M;
Model Llanta_M;
Model Camino_M;
Model Blackhawk_M;
Model Dado_M;
Model Dado12_M;
Model lamp_M;

//COCHE

Model CocheCofre_M;
Model CocheCuerpo_M;
Model CocheRueda_M;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;



// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
PointLight pointLights2[MAX_POINT_LIGHTS];

SpotLight spotLights[MAX_SPOT_LIGHTS];
SpotLight spotLights2[MAX_SPOT_LIGHTS];
SpotLight spotLights3[MAX_SPOT_LIGHTS];

GLboolean luzHeli = false;


GLfloat lightTime = 0.0f;
GLfloat lightPeriod = 10.0f;

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}
void CrearDodecaedro()

{

	unsigned int dodecaedro_indices[] = {

		4,1,0,
		3,2,1,
		3,1,4,

		9,6,5,
		8,7,6,
		8,6,9,

		14,11,10,
		13,12,11,
		13,11,14,

		19,16,15,
		18,17,16,
		18,16,19,

		24,21,20,
		23,22,21,
		23,21,24,

		29,26,25,
		28,27,26,
		28,26,29,

		34,31,30,
		33,32,31,
		33,31,34,

		39,36,35,
		38,37,36,
		38,36,39,

		44,41,40,
		43,42,41,
		43,41,44,

		49,46,45,
		48,47,46,
		48,46,49,

		54,51,50,
		53,52,51,
		53,51,54,

		59,56,55,
		58,57,56,
		58,56,59,

	};

	GLfloat dodecaedro_vertices[] = {

		//x			y			z			S		T				NX		NY		NZ
		//Cara 1
		1.5f,		0.0f,	1 / 1.5f,		0.42f,		0.15f,		-0.88f,		0.46f,	0.06f,
		1.0f,		1.0f,	1.0f,		0.26f,		0.21f,		-0.88f,		0.46f,	0.06f,
		1 / 1.5f,		1.5f,	0.0f,		0.31f,		0.34f,		-0.88f,		0.46f,	0.06f,
		1.0f,		1.0f,	-1.0f,		0.52f,		0.35f,		-0.88f,		0.46f,	0.06f,
		1.5f,		0,		-1 / 1.5f,	0.57f,		0.21f,		-0.88f,		0.46f,	0.06f,

		//Cara 2
		1.0f,		1.0f,	1.0f,		0.26f,		0.21f,		0.0f,		-1.0f,	-0.55f,
		0,			1 / 1.5f,	1.5f,		0.06f,		0.21f,		0.0f,		-1.0f,	-0.55f,
		-1.0f,		1.0f,	1.0f,		0.0f,		0.34f,		0.0f,		-1.0f,	-0.55f,
		-1 / 1.5f,	1.5f,	0.0f,		0.15f,		0.42f,		0.0f,		-1.0f,	-0.55f,
		1 / 1.5f,		1.5f,	0.0f,		0.31f,		0.34f,		0.0f,		-1.0f,	-0.55f,

		//Cara 3
		1 / 1.5f,		1.5f,	0.0f,		0.31f,		0.34f,		0.0f,		-1.0f,	1.0f,
		-1 / 1.5f,	1.5f,	0.0f,		0.26f,		0.46f,		0.0f,		-1.0f,	1.0f,
		-1.0f,		1.0f,	-1.0f,		0.41f,		0.54f,		0.0f,		-1.0f,	1.0f,
		0.0f,		1 / 1.5f,	-1.5f,		0.57f,		0.46f,		0.0f,		-1.0f,	1.0f,
		1.0f,		1.0f,	-1.0f,		0.52f,		0.35f,		0.0f,		-1.0f,	1.0f,

		//CARA 4
		-1 / 1.5f,	1.5f,	0.0f,		0.16f,		0.66f,		0.88f,		0.46f,	0.06f,
		-1.0f,		1.0f,	1.0f,		0.22f,		0.78f,		0.88f,		0.46f,	0.06f,
		-1.5f,		0.0f,	1 / 1.5f,		0.42f,		0.79f,		0.88f,		0.46f,	0.06f,
		-1.5f,		0.0f,	-1 / 1.5f,	0.48f,		0.67f,		0.88f,		0.46f,	0.06f,
		-1.0f,		1.0f,	-1.0f,		0.32f,		0.59f,		0.88f,		0.46f,	0.06f,

		//Cara 5
		-1.5f,		0.0f,	1 / 1.5f,		0.42f,		0.79f,		0.88f,		-0.46f,	0.06f,
		-1.0f,		-1.0f,	1.0f,		0.58f,		0.86f,		0.88f,		-0.46f,	0.06f,
		-1 / 1.5f,	-1.5f,	0.0f,		0.72f,		0.79f,		0.88f,		-0.46f,	0.06f,
		-1.0f,		-1.0f,	-1.0f,		0.66f,		0.66f,		0.88f,		-0.46f,	0.06f,
		-1.5f,		0.0f,	-1 / 1.5f,	0.48f,		0.67f,		0.88f,		-0.46f,	0.06f,

		//Cara 6
		-1.0f,		-1.0f,		1.0f,		0.58f,		0.86f,		0.0f,	1.0f,	-0.55f,
		0.0f,		-1 / 1.5f,	1.5f,		0.63f,		1.0f,		0.0f,	1.0f,	-0.55f,
		1.0f,		-1.0f,		1.0f,		0.82f,		1.0f,		0.0f,	1.0f,	-0.55f,
		1 / 1.5f,		-1.5f,		0.0f,		0.88f,		0.87f,		0.0f,	1.0f,	-0.55f,
		-1 / 1.5f,	-1.5f,		0.0f,		0.72f,		0.79f,		0.0f,	1.0f,	-0.55f,

		//Cara 7
		-1 / 1.5f,	-1.5f,		0.0f,		0.72f,		0.79f,		0.0f,	1.0f,	0.45f,
		1 / 1.5f,		-1.5f,		0.0f,		0.92f,		0.8f,		0.0f,	1.0f,	0.45f,
		1.0f,		-1.0f,		-1.0f,		1.0f,		0.66f,		0.0f,	1.0f,	0.45f, //abajo
		0.0f,		-1 / 1.5f,	-1.5f,		0.82f,		0.59f,		0.0f,	1.0f,	0.45f,
		-1.0f,		-1.0f,		-1.0f,		0.66f,		0.66f,		0.0f,	1.0f,	0.45f,

		//Cara 8
		1 / 1.5f,		-1.5f,		0.0f,		0.67f,		0.0f,		-0.88f,		-0.46f,	0.06f,
		1.0f,		-1.0f,		1.0f,		0.48f,		0.0f,		-0.88f,		-0.46f,	0.06f,
		1.5f,		0.0f,		1 / 1.5f,		0.42f,		0.15f,		-0.88f,		-0.46f,	0.06f,
		1.5f,		0,			-1 / 1.5f,	0.57f,		0.21f,		-0.88f,		-0.46f,	0.06f,
		1.0f,		-1.0f,		-1.0f,		0.73f,		0.14f,		-0.88f,		-0.46f,	0.06f,

		//Cara 9
		0.0f,		-1 / 1.5f,	1.5f,		0.16f,		0.0f,		-0.45f,		0.0f,	-0.89f,
		0,			1 / 1.5f,		1.5f,		0.1f,		0.13f,		-0.45f,		0.0f,	-0.89f,
		1.0f,		1.0f,		1.0f,		0.26f,		0.21f,		-0.45f,		0.0f,	-0.89f,
		1.5f,		0.0f,		1 / 1.5f,		0.42f,		0.15f,		-0.45f,		0.0f,	-0.89f,
		1.0f,		-1.0f,		1.0f,		0.35f,		0.0f,		-0.45f,		0.0f,	-0.89f,

		//Caro 10
		0,			1 / 1.5f,		1.5f,		0.31f,		1.0f,		0.45f,		0.0f,	-0.89f,
		0.0f,		-1 / 1.5f,	1.5f,		0.51f,		1.0f,		0.45f,		0.0f,	-0.89f,
		-1.0f,		-1.0f,		1.0f,		0.58f,		0.86f,		0.45f,		0.0f,	-0.89f,
		-1.5f,		0.0f,		1 / 1.5f,		0.42f,		0.79f,		0.45f,		0.0f,	-0.89f,
		-1.0f,		1.0f,		1.0f,		0.25f,		0.86f,		0.45f,		0.0f,	-0.89f,

		//Caro 11
		1.0f,		-1.0f,		-1.0f,		0.77f,		0.22f,		-0.55f,		0.0f,	0.83f,
		1.5f,		0,			-1 / 1.5f,	0.57f,		0.21f,		-0.55f,		0.0f,	0.83f,
		1.0f,		1.0f,		-1.0f,		0.52f,		0.35f,		-0.55f,		0.0f,	0.83f,
		0.0f,		1 / 1.5f,		-1.5f,		0.66f,		0.41f,		-0.55f,		0.0f,	0.83f,
		0.0f,		-1 / 1.5f,	-1.5f,		0.82f,		0.35f,		-0.55f,		0.0f,	0.83f,

		//Cara 12
		-1.0f,		1.0f,		-1.0f,		0.41f,		0.54f,		0.55f,		0.0f,	0.83f,
		-1.5f,		0.0f,		-1 / 1.5f,	0.48f,		0.67f,		0.55f,		0.0f,	0.83f,
		-1.0f,		-1.0f,		-1.0f,		0.66f,		0.66f,		0.55f,		0.0f,	0.83f,
		0.0f,		-1 / 1.5f,	-1.5f,		0.72f,		0.54f,		0.55f,		0.0f,	0.83f,
		0.0f,		1 / 1.5f,		-1.5f,		0.57f,		0.46f,		0.55f,		0.0f,	0.83f,
	};

	Mesh* dodecaedro = new Mesh();
	dodecaedro->CreateMesh(dodecaedro_vertices, dodecaedro_indices, 480, 108);
	meshList.push_back(dodecaedro);

}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, -1.0f, -1.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, -1.0f, -1.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, -1.0f, -1.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, -1.0f, -1.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,


	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	//calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();
	CrearDodecaedro();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	DadoTexture = Texture("Textures/tEMPLATE_DADO.tga");
	DadoTexture.LoadTextureA();
	llantaTexture = Texture("Textures/tire.tga");
	llantaTexture.LoadTextureA();

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");
	Dado12_M = Model();
	Dado12_M.LoadModel("Models/dado_docecaras.obj");
	lamp_M = Model();
	lamp_M.LoadModel("Models/lamp.obj");

	//COCHE

	CocheCofre_M = Model();
	CocheCofre_M.LoadModel("Models/cofrec.obj");

	CocheCuerpo_M = Model();
	CocheCuerpo_M.LoadModel("Models/cuerpo_coche.obj");

	CocheRueda_M = Model();
	CocheRueda_M.LoadModel("Models/rueda_c.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);

	//contador de luces puntuales

	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		-6.0f, 1.5f, 1.5f,
		0.3f, 0.2f, 0.1f); 
	pointLightCount++;

	//lampara
	pointLights[1] = PointLight(1.0f, 1.0f, 1.0f,
		1.0f, 0.1f,
		10.0f, 1.7f, 12.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;



	unsigned int spotLightCount = 0;

	//Helicoptero
	spotLights[0] = SpotLight(1.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		2.0f, 5.0f, 6.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;

	//linterna
	spotLights[1] = SpotLight(1.0f, 1.0f, 1.0f,  
		0.0f, 2.0f,  
		0.0f, 0.0f, 0.0f,   
		0.0f, -1.0f, 0.0f,   
		0.0f, 1.0f, 0.0f,    
		5.0f); 
	spotLightCount++;

	//Faro AzulCoche delantera
	spotLights[2] = SpotLight(0.0f, 0.0f, 1.0f,
		1.0f, 0.05f,
		2.5f, 0.0f, -3.5f,
		-4.5f, -2.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f); 
	spotLightCount++;

	//Faro verde trasera
	spotLights[3] = SpotLight(0.0f, 1.0f, 0.f,
		0.0f, 1.0f,
		13.5f, 1.9f, -1.5f,
		17.5f, -1.6f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;

	//ARREGLOS

	spotLights2[0] = spotLights[0]; 
	spotLights2[1] = spotLights[1];
	spotLights2[2] = spotLights[3];


	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{


		GLfloat now = glfwGetTime();


		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;




		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[1].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		//Prender y apagar la lampara

		if (mainWindow.getarreglos() == 1)
		{

			if (mainWindow.getlampara() == true)
			{
				shaderList[0].SetPointLights(pointLights, 2);
			}
			else
			{
				shaderList[0].SetPointLights(pointLights, 1);
			}

		}

		if (mainWindow.getarreglos() == 1) {

			if (mainWindow.getcarroX() == true) {
				shaderList[0].SetSpotLights(spotLights, spotLightCount - 1);


			}
			else {
				shaderList[0].SetSpotLights(spotLights, spotLightCount - 2);
				shaderList[0].SetSpotLights(spotLights2, spotLightCount);


			}


		}
		else {


			lightTime += deltaTime;
			GLfloat sinV = sin(lightTime / lightPeriod);

			if (sinV > 0) {
				luzHeli = true;

			}
			else {
				luzHeli = false;

			}

			if (luzHeli) {

				spotLights3[0] = spotLights2[0];
				shaderList[0].SetSpotLights(spotLights3, 0);

			}
			else {
				spotLights3[0] = spotLights2[0];
				shaderList[0].SetSpotLights(spotLights3, -1);

			}
		}







		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//DADO 12

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.5f, 4.5f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		DadoTexture.UseTexture();
		meshList[4]->RenderMesh();


		//Instancia del coche
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(12.0f + mainWindow.getmuevex(), -0.5f, -3.0f));
		spotLights[2].SetPos(glm::vec3(9.0f + mainWindow.getmuevex(), 2.5, -6.0));
		spotLights2[2].SetPos(glm::vec3(5.0f + mainWindow.getmuevex(), 1.5f, -0.5f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheCuerpo_M.RenderModel();

		//COFRE
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.5f, 2.1f, -3.3f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getangulocola()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheCofre_M.RenderModel();
		//Llanta delantera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.7f, 0.6f, 1.7f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getruedat()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheRueda_M.RenderModel();


		//Llanta trasera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(4.7f, 0.6f, 1.7f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getruedat()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheRueda_M.RenderModel();

		//Llanta delantera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.6f, 0.6f, -3.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getruedat()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheRueda_M.RenderModel();

		//Llanta trasera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(4.7f, 0.6f, -3.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getruedat()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CocheRueda_M.RenderModel();

		//helicoptero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmueveh(), 5.0f, 6.0));

		spotLights2[0].SetPos(glm::vec3(0.0f + mainWindow.getmueveh(), 5.0f, 6.0));

		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();

		//Lampara

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, -1.0f, 12.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lamp_M.RenderModel();


		//Agave ¿qué sucede si lo renderizan antes del coche y el helicóptero?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
