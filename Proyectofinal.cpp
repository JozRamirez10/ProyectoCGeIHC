/* Semestre 2024-1
Animaci�n por keyframes
La textura del skybox fue conseguida desde la p�gina https://opengameart.org/content/elyvisions-skyboxes?page=1
y edit� en Gimp rotando 90 grados en sentido antihorario la imagen  sp2_up.png para poder ver continuidad.
Fuentes :
	https ://www.khronos.org/opengl/wiki/Keyframe_Animation
	http ://what-when-how.com/wp-content/uploads/2012/07/tmpcd0074_thumb.png
	*/
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

//para iluminaci�n
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

int cameraActive = 1;

//variables para animaci�n
float movCoche;
float movOffset;
float rotllanta;
float rotllantaOffset;
bool avanza;
float toffsetflechau = 0.0f;
float toffsetflechav = 0.0f;
float toffsetnumerou = 0.0f;
float toffsetnumerov = 0.0f;
float toffsetnumerocambiau = 0.0;
float angulovaria = 0.0f;
//----------TIMMY TURNER-------------------


//-------------------PINBALL------------------------

//variables para animaci�n
float movMoneda;
float movBola;
float rotBola;
float movBolaZOffset;
float movBolaOffset;
float rotBolaOffset;
float movBolaZ;
//--------------------------------------------

//variables para keyframes
float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;

glm::mat4 modelTorsoPosition = glm::mat4(1.0);

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture FlechaTexture;
Texture NumerosTexture;
Texture Numero1Texture;
Texture Numero2Texture;

//-----------HABITACION Texturas------------
Texture PisoTexture;
Texture MaderaTexture;
Texture PuertaTexture;
Texture TechoTexture;
Texture VidrioTexture;
Texture Piso1Texture;
Texture ManijaTexture;
Texture VenatanTexture;
Texture CortinaTexture;


//-----------MESA DE PINBALL TEXTURAS----------------

Texture ResorteTexture;
Texture pinballFTexture;
Texture SuperiorTexture;
Texture AguaTexture;
Texture TableroTexture;
Texture MonedaTexture;

//Asteroid Arcade Textures-------------------
Texture ArcadeCoinSlots;
Texture ArcadeDoors;
Texture AsterFire_Title_screen;
Texture AsterFireCabinet;
Texture AsterFireFrontArt;
Texture AsterFireSideArt;
Texture AsterMesh;

//Arcade Textures----------------------------
Texture arcadeEmissive;
Texture arcadeEetall;
Texture arcadeNormall;
Texture arcadeRoughness;
Texture arcadeOk;

//-------------Timmy Turner------------------

Model Torso_M;
Model PierDere_M;
Model PierIzq_M;
Model BrazoDer_M;
Model BrazoIzq_M;
Model Cabeza_M;

Texture TimmyTexture;

//-------------MESA DE PINBALL MODELOS--------------
Model Pinball_M;
Model Moneda_M;
Model Bola_M;
Model Resorte_M;
Model Superior_M;
Model PaletaDere_M;
Model PaletaIzq_M;
Model PaletaCent_M;
Model PeceraA_M;
Model Agua_M;
Model Peces_M;
Model Muffin_M;
Model Tablero_M;
Model Estrella_M;
Model Palo_M;
//---------------------------------------------------

Model Cuarto_M;
Model Ventana_M;
Model Cortina_M;

Model Asteroid;
Model Arcade;
Texture ArrowTexture;

// ----------------------------------------------------
Model Termo;
Texture TermoGris;
Texture TermoGrisOscuro;
Texture TermoVerde;
Texture TermoBlanco;

Model Plataforma;
Texture plataformaBI;
Texture plataformaBN;
Texture plataformaBS;
Texture plataformaCaja;
Texture plataformaCentro;
Texture plataformaCE;
Texture plataformaCI;
Texture plataformaSuperior;
Texture plataformaZB;

Model Pizarron;
Texture pizarronBorde;
Texture pizarronFondo;
Texture pizarronPatas;

Model avatarDanny;
Texture a1;
Texture a2;
Texture a3;
Texture a4;
Texture a5;
Texture a6;
Texture a7;
Texture a8;
Texture a9;
Texture a10;
Texture a11;
Texture a12;
Texture a13;


Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;

bool esDeDia = true;  // Variable para indicar si es de d�a o de noche


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];


// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";

//funci�n para teclado de keyframes 
void inputKeyframes(bool* keys);

void changeCamera(int cameraActive) {
	if (cameraActive == 1) {
		camera.setYaw(60.0f);
		camera.setPitch(0.0f);
		camera.mouseControl(0.0f, 0.0f);
		camera.setCameraPosition(glm::vec3(0.0f, 300.0f, 260.0f));
		camera.setCameraDirection(glm::vec3(0.0f, -0.4f, -1.0f));
	}
	else if (cameraActive == 2) {		
		camera.setCameraPosition(glm::vec3(modelTorsoPosition[3].x, modelTorsoPosition[3].y, modelTorsoPosition[3].z+12));	
		camera.setCameraDirection(glm::vec3(0.0f, 0.0f, 1.0f));
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
	}
	else if (cameraActive == 3) {
		camera.setYaw(1.0f);
		camera.setPitch(10.0f);
		camera.mouseControl(0.0f, 0.0f);
		camera.setCameraPosition(glm::vec3(-5.0f, 300.0f, 65.0f));
		camera.setCameraDirection(glm::vec3(0.0f, -1.0f, 0.0f));
	}
}

//c�lculo del promedio de las normales para sombreado de Phong
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
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};


	unsigned int flechaIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat flechaVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int scoreIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat scoreVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int numeroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat numeroVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.25f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.25f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

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

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(flechaVertices, flechaIndices, 32, 6);
	meshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(scoreVertices, scoreIndices, 32, 6);
	meshList.push_back(obj6);

	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(numeroVertices, numeroIndices, 32, 6);
	meshList.push_back(obj7);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


///////////////////////////////KEYFRAMES/////////////////////


bool animacion = false;

bool lightIsOn = true;


//NEW// Keyframes
float posXavion = 2.0, posYavion = 5.0, posZavion = -3.0;
float	movAvion_x = 0.0f, movAvion_y = 0.0f, movAvion_z = 0.0f;;
float giroAvion = 0;

#define MAX_FRAMES 100
int i_max_steps = 90;
int i_curr_steps = 40; //AQUI TAMBIEN AGREGAR FRAMES
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movAvion_x;		//Variable para PosicionX
	float movAvion_y;		//Variable para PosicionY
	float movAvion_z;		//Variable para PosicionZ

	float movAvion_xInc;		//Variable para IncrementoX
	float movAvion_yInc;		//Variable para IncrementoY
	float movAvion_zInc;		//Variable para IncrementoZ

	float giroAvion;
	float giroAvionInc;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 40;			//introducir datos  aumentar cada vez que agregues frames
bool play = false;
int playIndex = 0;

void saveFrame(void) //tecla L
{

	printf("frameindex %d\n", FrameIndex);


	KeyFrame[FrameIndex].movAvion_x = movAvion_x;
	KeyFrame[FrameIndex].movAvion_y = movAvion_y;
	KeyFrame[FrameIndex].movAvion_z = movAvion_z;

	KeyFrame[FrameIndex].giroAvion;//completar  //PARA GIRAR EL AVION
	//no volatil, agregar una forma de escribir a un archivo para guardar los frames
	FrameIndex++;
}

void resetElements(void) //Tecla 0
{

	movAvion_x = KeyFrame[0].movAvion_x;
	movAvion_y = KeyFrame[0].movAvion_y;
	movAvion_z = KeyFrame[0].movAvion_z;

	giroAvion = KeyFrame[0].giroAvion;
}

void interpolation(void)
{
	KeyFrame[playIndex].movAvion_xInc = (KeyFrame[playIndex + 1].movAvion_x - KeyFrame[playIndex].movAvion_x) / i_max_steps;
	KeyFrame[playIndex].movAvion_yInc = (KeyFrame[playIndex + 1].movAvion_y - KeyFrame[playIndex].movAvion_y) / i_max_steps;
	KeyFrame[playIndex].movAvion_zInc = (KeyFrame[playIndex + 1].movAvion_z - KeyFrame[playIndex].movAvion_z) / i_max_steps;

	KeyFrame[playIndex].giroAvionInc = (KeyFrame[playIndex + 1].giroAvion - KeyFrame[playIndex].giroAvion) / i_max_steps;

}


void animate(void)

{
	//Movimiento del objeto con barra espaciadora
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //fin de animaci�n entre frames?
		{
			playIndex++;
			printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2)	//Fin de toda la animaci�n con �ltimo frame?
			{
				printf("Frame index= %d\n", FrameIndex);
				printf("termino la animacion\n");
				playIndex = 0;
				play = false;
			}
			else //Interpolaci�n del pr�ximo cuadro
			{

				i_curr_steps = 0; //Resetea contador
				//Interpolar
				interpolation();
			}
		}
		else
		{
			//Dibujar Animaci�n
			movAvion_x += KeyFrame[playIndex].movAvion_xInc * deltaTime;
			movAvion_y += KeyFrame[playIndex].movAvion_yInc * deltaTime;
			movAvion_z += KeyFrame[playIndex].movAvion_zInc * deltaTime;

			giroAvion += KeyFrame[playIndex].giroAvionInc * deltaTime;
			i_curr_steps++;
		}

	}
}

///////////////* FIN KEYFRAMES*////////////////////////////



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 300.0f, 300.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 0.5f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.png");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	FlechaTexture = Texture("Textures/flechas.tga");
	FlechaTexture.LoadTextureA();
	NumerosTexture = Texture("Textures/numerosbase.tga");
	NumerosTexture.LoadTextureA();
	Numero1Texture = Texture("Textures/numero1.tga");
	Numero1Texture.LoadTextureA();
	Numero2Texture = Texture("Textures/numero2.tga");
	Numero2Texture.LoadTextureA();


	//------------------Timmy Turner-----------------------

	Cabeza_M = Model();
	Cabeza_M.LoadModel("Models/Cabeza.obj");

	Torso_M = Model();
	Torso_M.LoadModel("Models/Torso.obj");

	PierIzq_M = Model();
	PierIzq_M.LoadModel("Models/PierIzq.obj");

	PierDere_M = Model();
	PierDere_M.LoadModel("Models/PierDer.obj");

	BrazoIzq_M = Model();
	BrazoIzq_M.LoadModel("Models/BrazoIzq.obj");

	BrazoDer_M = Model();
	BrazoDer_M.LoadModel("Models/BrazoDer.obj");

	TimmyTexture = Texture("Textures/t0130_0.png");
	TimmyTexture.LoadTextureA();

	//-------------------PINBALL-----------------------------
	Pinball_M = Model();
	Pinball_M.LoadModel("Models/Pinball.obj");

	Superior_M = Model();
	Superior_M.LoadModel("Models/Superior.obj");

	Moneda_M = Model();
	Moneda_M.LoadModel("Models/Moneda.obj");

	Bola_M = Model();
	Bola_M.LoadModel("Models/Bola.obj");

	Resorte_M = Model();
	Resorte_M.LoadModel("Models/Resorte.obj");

	PaletaDere_M = Model();
	PaletaDere_M.LoadModel("Models/PaletaIzq.obj");

	PaletaIzq_M = Model();
	PaletaIzq_M.LoadModel("Models/PaletaIzq.obj");

	PaletaCent_M = Model();
	PaletaCent_M.LoadModel("Models/PaletaCent.obj");

	Peces_M = Model();
	Peces_M.LoadModel("Models/Peces.obj");

	PeceraA_M = Model();
	PeceraA_M.LoadModel("Models/Pecera.obj");

	Agua_M = Model();
	Agua_M.LoadModel("Models/Agua.obj");

	Muffin_M = Model();
	Muffin_M.LoadModel("Models/Muffin.obj");

	Tablero_M = Model();
	Tablero_M.LoadModel("Models/teblero.obj");

	Estrella_M = Model();
	Estrella_M.LoadModel("Models/Estrella.obj");

	Palo_M = Model();
	Palo_M.LoadModel("Models/Palo.obj");

	//TEXTURAS
	ResorteTexture = Texture("Textures/Resorte.png");
	ResorteTexture.LoadTextureA();

	pinballFTexture = Texture("Textures/pinballF.tga");
	pinballFTexture.LoadTextureA();

	SuperiorTexture = Texture("Textures/Superior.tga");
	SuperiorTexture.LoadTextureA();

	AguaTexture = Texture("Textures/Agua.tga");
	AguaTexture.LoadTextureA();

	MonedaTexture = Texture("Textures/moneda.png");
	MonedaTexture.LoadTextureA();

	//___________________CASA TIMMY___________________________

	Cuarto_M = Model();
	Cuarto_M.LoadModel("Models/Cuarto.obj");

	Ventana_M = Model();
	Ventana_M.LoadModel("Models/Ventana.obj");

	Cortina_M = Model();
	Cortina_M.LoadModel("Models/Cortinas.obj");

	PisoTexture = Texture("Textures/Piso.png");
	PisoTexture.LoadTextureA();

	MaderaTexture = Texture("Textures/Madera_Normal1.png");
	MaderaTexture.LoadTextureA();

	PuertaTexture = Texture("Textures/Puerta.png");
	PuertaTexture.LoadTextureA();

	TechoTexture = Texture("Textures/techo.png");
	TechoTexture.LoadTextureA();

	Piso1Texture = Texture("Textures/Piso1.png");
	Piso1Texture.LoadTextureA();

	ManijaTexture = Texture("Textures/Manija.png");
	ManijaTexture.LoadTextureA();

	VidrioTexture = Texture("Textures/Vidrio.png");
	VidrioTexture.LoadTextureA();

	CortinaTexture = Texture("Textures/Cortina.tga");
	CortinaTexture.LoadTextureA();
	//-------------------------------------------------------

	Asteroid = Model();
	Asteroid.LoadModel("Models/Asteroid/AsterFireArcade.obj");

	Arcade = Model();
	Arcade.LoadModel("Models/Arcade/arcade.obj");
	//Textures------------------------------------------------
	ArcadeCoinSlots = Texture("Textures/ArcadeCoinSlots.png");
	ArcadeCoinSlots.LoadTexture();

	ArcadeDoors = Texture("Textures/ArcadeDoors.png");
	ArcadeDoors.LoadTexture();

	AsterFire_Title_screen = Texture("Textures/AsterFire Title screen.png");
	AsterFire_Title_screen.LoadTexture();

	AsterFireCabinet = Texture("Textures/AsterFireCabinet.png");
	AsterFireCabinet.LoadTexture();

	AsterFireFrontArt = Texture("Textures/AsterFireFrontArt.png");
	AsterFireFrontArt.LoadTexture();

	AsterFireSideArt = Texture("Textures/AsterFireSideArt.png");
	AsterFireSideArt.LoadTexture();

	AsterMesh = Texture("Textures/Mesh.png");
	AsterMesh.LoadTexture();

	 arcadeEmissive = Texture("Textures/emissive.png");
	 arcadeEmissive.LoadTexture();

	 arcadeEetall = Texture("Textures/metall.png");
	 arcadeEetall.LoadTexture();

	 arcadeNormall = Texture("Textures/normall.png");
	 arcadeNormall.LoadTexture();

	 arcadeRoughness = Texture("Textures/roughness.png");
	 arcadeRoughness.LoadTexture();

	 arcadeOk = Texture("Textures/ok.png");
	 arcadeOk.LoadTexture();

	 ArrowTexture = Texture("Textures/arrowTexture.png");
	 ArrowTexture.LoadTexture();

	 // -------------------------------------------------------

	 Termo = Model();
	 Termo.LoadModel("Models/DannyPhantom/Thermos/Thermos.obj");

	 TermoGris = Texture("Textures/GrisOscuro.jpg");
	 TermoGris.LoadTextureA();

	 TermoGrisOscuro = Texture("Textures/Gris.jpg");
	 TermoGrisOscuro.LoadTextureA();

	 TermoVerde = Texture("Textures/Verde.jpg");
	 TermoVerde.LoadTextureA();

	 TermoBlanco = Texture("Textures/Tapa_Blanca.jpg");
	 TermoBlanco.LoadTextureA();

	 Plataforma = Model();
	 Plataforma.LoadModel("Models/DannyPhantom/Plataforma/Plataforma.obj");

	 plataformaBI = Texture("Textures/bordeInterior.jpg");
	 plataformaBI.LoadTexture();

	 plataformaBN = Texture("Textures/bordesNegros.jpg");
	 plataformaBN.LoadTexture();

	 plataformaBS = Texture("Textures/bordeSuperior.jpg");
	 plataformaBS.LoadTexture();

	 plataformaCaja = Texture("Textures/caja.jpg");
	 plataformaCaja.LoadTexture();

	 plataformaCentro = Texture("Textures/centroPlataforma.jpg");
	 plataformaCentro.LoadTexture();

	 plataformaCE = Texture("Textures/colorExterior.jpg");
	 plataformaCE.LoadTexture();

	 plataformaCI = Texture("Textures/colorInterior.jpg");
	 plataformaCI.LoadTexture();

	 plataformaSuperior = Texture("Textures/superior.jpg");
	 plataformaSuperior.LoadTexture();

	 plataformaZB = Texture("Textures/zonaBaja.jpg");
	 plataformaZB.LoadTexture();

	 Pizarron = Model();
	 Pizarron.LoadModel("Models/DannyPhantom/Pizarron/Pizarron.obj");

	 pizarronBorde = Texture("Textures/BordePizarron.png");
	 pizarronBorde.LoadTextureA();

	 pizarronFondo = Texture("Textures/FondoPizarron.png");
	 pizarronFondo.LoadTextureA();

	 pizarronPatas = Texture("Textures/PatasPizarron.png");
	 pizarronPatas.LoadTextureA();

	 avatarDanny = Model();
	 avatarDanny.LoadModel("Models/DannyPhantom/Avatar/avatar.obj");

	 a1 = Texture("Textures/Mascot_Occlusion.png");
	 a1.LoadTextureA();

	 a2 = Texture("Textures/Plasma_Albedo.png");
	 a2.LoadTextureA();

	 a3 = Texture("Textures/Plasma_Ao.png");
	 a3.LoadTextureA();

	 a4 = Texture("Textures/Plasma_Emissive.png");
	 a4.LoadTextureA();

	 a5 = Texture("Textures/Plasma_Normal.png");
	 a5.LoadTextureA();

	 a6 = Texture("Textures/Plasma_Props_Albedo.png");
	 a6.LoadTextureA();

	 a7 = Texture("Textures/Plasma_Props_Emissive.png");
	 a7.LoadTextureA();

	 a8 = Texture("Textures/Plasma_Props_Metallic.png");
	 a8.LoadTextureA();

	 a9 = Texture("Textures/Plasma_Props_Normal.png");
	 a9.LoadTextureA();

	 a10 = Texture("Textures/Plasma_Specular_Albedo.png");
	 a10.LoadTextureA();

	 a11 = Texture("Textures/PlasmaCostume_Albedo.png");
	 a11.LoadTextureA();

	 a12 = Texture("Textures/PlasmaCostume_Mirror_Albedo.png");
	 a12.LoadTextureA();

	 a13 = Texture("Textures/white.png");
	 a13.LoadTextureA();

	 // ---------------------------------------------------

	std::vector<std::string> skyboxFacesDia = {
	"Textures/Skybox/rainbow_rt.png",
	"Textures/Skybox/rainbow_lf.png",
	"Textures/Skybox/rainbow_dn.png",
	"Textures/Skybox/rainbow_up.png",
	"Textures/Skybox/rainbow_bk.png",
	"Textures/Skybox/rainbow_ft.png"
	};

	std::vector<std::string> skyboxFacesNoche = {
		"Textures/Skybox/rainbow_rt_noche.png",
		"Textures/Skybox/rainbow_rt_noche.png",
		"Textures/Skybox/rainbow_dn_noche.png",
		"Textures/Skybox/rainbow_up_png.png",
		"Textures/Skybox/rainbow_bk_noche.png",
		"Textures/Skybox/rainbow_ft_noche.png"
	};

	Skybox skybox(skyboxFacesDia);  // Inicializar con las texturas del d�a


	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	unsigned int pointLightCount = 0;
	unsigned int spotLightCount = 0;

	//luz direccional, s�lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);

	//luz stop
	pointLights[0] = PointLight(0.0f, 1.0f, 0.0f,
		7.0f, 3.5f,
		-30.0f, 151.5f, 110.0f,
		1.6f, 0.3f, 0.2f);
	pointLightCount++;

	//luz intermitente
	pointLights[1] = PointLight(1.0f, 0.0f, 0.0f,
		7.0f, 3.5f,
		10.0f, 150.5f, 110.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	//luz intermitente
	pointLights[2] = PointLight(1.0f, 1.0f, 0.0f,
		20.0f, 15.5f,
		-10.0f, 153.0f, 29.0f,
		0.7f, 0.5f, 0.3f);
	pointLightCount++;


	//Linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 0.8f,
		1.0f, 2.0f,
		17.624f, 800.0f, -44.614f,
		-0.3f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		7.0f);
	spotLightCount++;

	//Luz Pinball
	spotLights[1] = SpotLight(1.0f, 0.5f, 0.8f,
		0.5f, -0.3f,
		-200.0f, 800.0f, 10.0f,
		0.3f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		16.0f);
	spotLightCount++;






	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	movCoche = 0.0f;
	movOffset = 0.20f;
	rotllanta = 0.0f;
	rotllantaOffset = 10.0f;
	glm::vec3 posblackhawk = glm::vec3(2.0f, 0.0f, 0.0f);

	//---------PARA TENER KEYFRAMES GUARDADOS NO VOLATILES QUE SIEMPRE SE UTILIZARAN SE DECLARAN AQU�

	KeyFrame[0].movAvion_x = 0.0f;
	KeyFrame[0].movAvion_y = 0.0f;
	KeyFrame[0].giroAvion = 0;

	KeyFrame[1].movAvion_x = 95.0f;
	KeyFrame[1].movAvion_y = 0.0f;
	KeyFrame[1].giroAvion = 0;

	KeyFrame[2].movAvion_x = 95.0f;
	KeyFrame[2].movAvion_y = 0.0f;
	KeyFrame[2].giroAvion = 0;

	KeyFrame[3].movAvion_x = 95.0f;
	KeyFrame[3].movAvion_y = 0.0f;
	KeyFrame[3].movAvion_z = -210.0f;
	KeyFrame[3].giroAvion = 0;

	KeyFrame[4].movAvion_x = 55.0f;
	KeyFrame[4].movAvion_y = 0.0f;
	KeyFrame[4].movAvion_z = -200.0f;
	KeyFrame[4].giroAvion = 0;

	KeyFrame[5].movAvion_x = 5.0f;
	KeyFrame[5].movAvion_y = 0.0f;
	KeyFrame[5].movAvion_z = -190.0f;
	KeyFrame[5].giroAvion = 0;

	KeyFrame[6].movAvion_x = 50.0f;
	KeyFrame[6].movAvion_y = 0.0f;
	KeyFrame[6].movAvion_z = -170.0f;
	KeyFrame[6].giroAvion = 0;

	KeyFrame[7].movAvion_x = -10.0f;
	KeyFrame[7].movAvion_y = 0.0f;
	KeyFrame[7].movAvion_z = -115.0f;
	KeyFrame[7].giroAvion = 0;

	KeyFrame[8].movAvion_x = 20.0f;
	KeyFrame[8].movAvion_y = 0.0f;
	KeyFrame[8].movAvion_z = -109.0f;
	KeyFrame[8].giroAvion = 0;

	KeyFrame[9].movAvion_x = 15.0f;
	KeyFrame[9].movAvion_y = 0.0f;
	KeyFrame[9].movAvion_z = -50.0f;
	KeyFrame[9].giroAvion = 0;

	KeyFrame[10].movAvion_x = 45.0f;
	KeyFrame[10].movAvion_y = 0.0f;
	KeyFrame[10].movAvion_z = -38.0f;
	KeyFrame[10].giroAvion = 0;

	KeyFrame[11].movAvion_x = 45.0f;
	KeyFrame[11].movAvion_y = 0.0f;
	KeyFrame[11].movAvion_z = -38.0f;
	KeyFrame[11].giroAvion = 0;

	KeyFrame[11].movAvion_x = 35.0f;
	KeyFrame[11].movAvion_y = 0.0f;
	KeyFrame[11].movAvion_z = -20.0f;
	KeyFrame[11].giroAvion = 0;

	KeyFrame[11].movAvion_x = 35.0f;
	KeyFrame[11].movAvion_y = 0.0f;
	KeyFrame[11].movAvion_z = -20.0f;
	KeyFrame[11].giroAvion = 0;

	KeyFrame[11].movAvion_x = 35.0f;
	KeyFrame[11].movAvion_y = 0.0f;
	KeyFrame[11].movAvion_z = -5.0f;
	KeyFrame[11].giroAvion = 0;

	printf("\nTeclas para uso de Keyframes:\n1.-Presionar barra espaciadora para reproducir animacion.\n2.-Presionar 0 para volver a habilitar reproduccion de la animacion\n");
	printf("3.-Presiona L para guardar frame\n4.-Presiona P para habilitar guardar nuevo frame\n5.-Presiona 1 para mover en X\n6.-Presiona 2 para habilitar mover en X");

	//DECLARACION VARIABLES BOLA Y MONEDA

	avanza = true;
	movMoneda = 0.0f;
	movBolaOffset = 0.1;
	movBolaZOffset = 0.1;
	rotBolaOffset = 5.0f;
	GLfloat posicionObjetivo = -125.0f;
	GLfloat objetivoBola = 80.0f;
	movBola = 0.0f;  // Inicializa el movimiento de la bola
	rotBola = 0.0f;  // Inicializa la rotaci�n de la bola
	movBolaZ = 0.0f;
	// Variables globales
	float tiempo = 0.0f; // Variable de tiempo
	float escalaZ = 1.0f; // Escala inicial en la direcci�n z

	//CAMBIAR TIEMPO

	double tiempoPrevio = 0.0;
	double tiempoDeCambio = 60.0; // 60 segundos = 1 minuto

	// Variables para la animaci�n de los peces
	float movPezX = 0.0f;
	float movPezY = 0.0f; // Nueva componente para el movimiento vertical

	float movPezZ = 0.0f;
	float rotPez = 0.0f;
	float tempA = 0.0f;
	float pi = 3.1416f;

	bool nado = false;
	bool nado1 = true;
	bool nado2 = false;
	bool nado3 = true;
	bool nado4 = false;

	// Declarar una variable para el desplazamiento en el eje Z
	float zTranslate = 0.0f;
	float xTranslate = 0.0f;

	const float maxZDistance = 198.0f;
	const float maxXDistance = 57.0f; // Ajusta la distancia seg�n tus necesidades
	const float maxZDistance2 = -0.2f;
	int estadoMovimiento = 0.0f;

	//CAMINATA

	// Variables para la animaci�n
	float velocidadAnimacion = 3.5f; // Puedes ajustar la velocidad seg�n sea necesario

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;


		if (nado1) {
			rotPez += (0.18f * pi);
			tempA += 0.01f;
			movPezZ = (0.1f * cos(tempA));
			movPezX = (0.05f * sin(tempA));
			if (tempA >= (0.5f * pi) && tempA < pi) {
				nado1 = false;
				rotPez = 45.0f;
				nado2 = true;
			}
		}

		if (nado2) {
			rotPez += (0.18f * pi);
			tempA += 0.01f;
			movPezZ = (0.1f * cos(tempA));
			movPezX = (0.05f * sin(tempA));
			if (tempA >= pi && tempA < (1.5f * pi)) {
				nado2 = false;
				rotPez = 135.0f;
				nado3 = true;
			}
		}

		if (nado3) {
			rotPez += (0.18f * pi);
			tempA += 0.01f;
			movPezZ = (0.1f * cos(tempA));
			movPezX = (0.05f * sin(tempA));
			if (tempA >= (1.5f * pi) && tempA < (2.0f * pi)) {
				nado3 = false;
				rotPez = -135.0f;
				nado4 = true;
			}
		}

		if (nado4) {
			rotPez += (0.18f * pi);
			tempA += 0.01f;
			movPezZ = (0.1f * cos(tempA));
			movPezX = (0.05f * sin(tempA));
			if (tempA >= (2.0f * pi) && tempA <= (2.5f * pi)) {
				tempA = 0.0f;
				rotPez = -45.0f;
				nado4 = false;
				nado1 = true;
			}
		}

		//-----------CAMBIAR ENTRE DIA Y NOCHE----------------------------------

			// Obt�n el tiempo actual
		double tiempoActual = glfwGetTime();

		// Verifica si ha pasado el tiempo de cambio
		if (tiempoActual - tiempoPrevio >= tiempoDeCambio)
		{
			tiempoPrevio = tiempoActual; // Reinicia el temporizador

			// Cambiar entre d�a y noche
			if (esDeDia)
			{
				// Cambiar a la noche
				esDeDia = false;
				skybox.setSkyboxTextures(skyboxFacesNoche);
			}
			else
			{
				// Cambiar al d�a
				esDeDia = true;
				skybox.setSkyboxTextures(skyboxFacesDia);
			}
		}


		//--------------------------------------------------------------------------------


			//Recibir eventos del usuario
		glfwPollEvents();
		

		//-------Para Keyframes
		inputKeyframes(mainWindow.getsKeys());
		animate();

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
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la c�mara de tipo flash
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);
		shaderList[0].SetPointLights(pointLights, pointLightCount);


		shaderList[0].SetSpotLights(spotLights, spotLightCount - mainWindow.getluzHeli());


		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//-----------------MESA DE PINBALL--------------------


		// Objetos de Danny Phantom

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(52.5f, 155.0f, 120.0f));
		model = glm::scale(model, glm::vec3(1.3f, 1.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Termo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.0f, 152.5f, 69.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Plataforma.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.0f, 160.5f, -60.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pizarron.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 150.0f, 142.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		avatarDanny.RenderModel();

		//Pinball
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Superior_M.RenderModel();

		//Tablero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tablero_M.RenderModel();



		//BOLA1

		switch (estadoMovimiento) {
		case 0:
			// Movimiento en el eje Z
			if (zTranslate < maxZDistance) {
				zTranslate += 0.5f; // Se ajusta la velocidad seg�n tus necesidades
			}
			else {
				estadoMovimiento = 1;
			}
			break;

		case 1:
			// Movimiento en el eje X
			if (xTranslate > -maxXDistance) {
				xTranslate -= 0.5f; // Moverse en direcci�n negativa del eje X
				zTranslate += 0.2f; // Se ajusta la cantidad de desplazamiento en Z para lograr la inclinaci�n
			}
			else {
				estadoMovimiento = 2;
			}
			break;

		case 2:
			// Movimiento en el eje Z (en direcci�n negativa)
			if (zTranslate > -maxZDistance2) {
				zTranslate -= 0.5f; // Se ajusta la velocidad seg�n tus necesidades
			}
			else {
				estadoMovimiento = 3;
			}
			break;

		case 3:
			// Detener el movimiento
			xTranslate = -maxXDistance;
			zTranslate = -maxZDistance2;
			break;
		}

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(67.0f + xTranslate, 78.5f, 68.5f - zTranslate));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bola_M.RenderModel();


		//BOLA 2
		model = glm::mat4(1.0);
		posblackhawk = glm::vec3(30.0f + movAvion_x, 78.5f + movAvion_y, 133.5 + movAvion_z);
		model = glm::translate(model, posblackhawk);
		//model = glm::translate(model, glm::vec3(-30.0f, 78.5f, 73.5f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bola_M.RenderModel();



		//Palate Derecha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 150.5f, 110.0f));
		model = glm::scale(model, glm::vec3(0.25f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getpaletaizq()), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PaletaDere_M.RenderModel();

		//Palate izquierda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, 150.5f, 110.0f));
		model = glm::scale(model, glm::vec3(0.25f));
		model = glm::rotate(model, glm::radians(mainWindow.getpaletader()), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PaletaIzq_M.RenderModel();

		//Palate central
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 150.5f, 25.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getpaletacentral()), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PaletaCent_M.RenderModel();


		//--------------------ANIMACION RESORTE-----------------------------------------
		//RESORTE
		tiempo += 0.025f; // Puedes ajustar la velocidad de la animaci�n cambiando este valor
		// Calcular la escala en la direcci�n z de acuerdo con el tiempo
		escalaZ = 1.0f + 0.5f * sin(tiempo); // La funci�n sinusoidal crea la compresi�n y expansi�n
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(53.0f, 153.0f, 150.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, escalaZ * 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		// Renderizar el modelo
		Resorte_M.RenderModel();
		//-------------------------------------------------------------------------------------

	//----------ESTRELLA (MODELO UNIDO JERARQUICAMENTE)-----------------------

		glm::mat4 estrellaModel = glm::mat4(1.0);
		glm::mat4 paloModel = glm::mat4(1.0);

		float velocidadRotacion = 1.0f; // Ajusta la velocidad de rotaci�n seg�n tus necesidades

		// Actualiza la rotaci�n de la estrella para que haga medias vueltas
		estrellaModel = glm::translate(glm::mat4(1.0), glm::vec3(15.0f, 153.0f, 10.0f));
		estrellaModel = glm::rotate(estrellaModel, glm::radians(180.0f * sin(velocidadRotacion * tiempo)), glm::vec3(0.0f, 1.0f, 0.0f));
		estrellaModel = glm::scale(estrellaModel, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(estrellaModel));
		Estrella_M.RenderModel();

		// Actualiza la rotaci�n del palo
		paloModel = glm::translate(estrellaModel, glm::vec3(0.0f, -0.5f, 0.0f));
		paloModel = glm::scale(paloModel, glm::vec3(1.0f, 2.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(paloModel));
		Palo_M.RenderModel();


		// Actualiza la rotaci�n de la estrella para que haga medias vueltas
		estrellaModel = glm::translate(glm::mat4(1.0), glm::vec3(-45.0f, 153.0f, 65.0f));
		estrellaModel = glm::rotate(estrellaModel, glm::radians(180.0f * sin(velocidadRotacion * tiempo)), glm::vec3(0.0f, 1.0f, 0.0f));
		estrellaModel = glm::scale(estrellaModel, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(estrellaModel));
		Estrella_M.RenderModel();

		// Actualiza la rotaci�n del palo
		paloModel = glm::translate(estrellaModel, glm::vec3(0.0f, -0.5f, 0.0f));
		paloModel = glm::scale(paloModel, glm::vec3(1.0f, 2.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(paloModel));
		Palo_M.RenderModel();


		//------------------CUARTO-----------------------------

		//Habitacion
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cuarto_M.RenderModel();


		//Cortina
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cortina_M.RenderModel();
		//------------------------------------------------------------------------
		// 
		// OBSTACULOS1
		// Peces
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(33.0f + movPezX, 153.0f, 47.0f + movPezZ));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(rotPez), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peces_M.RenderModel();

		//Pecera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(45.0f, 150.5f, 46.0f));
		model = glm::scale(model, glm::vec3(25.0f, 25.0f, 25.0f));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeceraA_M.RenderModel();

		//Agua
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(33.0f, 150.5f, 46.0f));
		model = glm::scale(model, glm::vec3(25.0f, 25.0f, 25.0f));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Agua_M.RenderModel();

		//OBSTACULO 2
		// 
		// Peces
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(8.0f + movPezX, 153.0f, 31.0f + movPezZ));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(rotPez), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peces_M.RenderModel();

		//Pecera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 150.5f, 30.0f));
		model = glm::scale(model, glm::vec3(25.0f, 25.0f, 25.0f));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeceraA_M.RenderModel();

		//Agua
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(7.5f, 150.5f, 30.0f));
		model = glm::scale(model, glm::vec3(25.0f, 25.0f, 25.0f));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Agua_M.RenderModel();

		//OBSTACULO 2
		// 
		// Peces
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-22.0f + movPezX, 153.0f, 31.0f + movPezZ));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(rotPez), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peces_M.RenderModel();

		//Pecera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, 150.5f, 30.0f));
		model = glm::scale(model, glm::vec3(25.0f, 25.0f, 25.0f));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeceraA_M.RenderModel();

		//Agua
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-22.0f, 150.5f, 30.0f));
		model = glm::scale(model, glm::vec3(25.0f, 25.0f, 25.0f));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Agua_M.RenderModel();

		//Obstaculo 4

		// Peces
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f + movPezX, 153.0f, 7.0f + movPezZ));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(rotPez), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Peces_M.RenderModel();

		//Pecera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.0f, 150.5f, 6.0f));
		model = glm::scale(model, glm::vec3(25.0f, 25.0f, 25.0f));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PeceraA_M.RenderModel();

		//Agua
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, 150.5f, 6.0f));
		model = glm::scale(model, glm::vec3(25.0f, 25.0f, 25.0f));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Agua_M.RenderModel();

		//---------SEGUNDOS OBSTACULOS
		// 
		//Muffin
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(23.0f, 150.5f, -45.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Muffin_M.RenderModel();

		//Muffin2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(13.0f, 150.5f, -25.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Muffin_M.RenderModel();

		//Muffin3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-33.0f, 150.5f, -20.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Muffin_M.RenderModel();


		//Muffin2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, 150.5f, 25.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Muffin_M.RenderModel();





		//Timmy Turner

		// Variables globales para almacenar las transformaciones
		glm::mat4 modelTorso = glm::mat4(1.0);
		glm::mat4 modelCabeza = glm::mat4(1.0);
		glm::mat4 modelBrazoIzq = glm::mat4(1.0);
		glm::mat4 modelBrazoDer = glm::mat4(1.0);
		glm::mat4 modelPiernaIzq = glm::mat4(1.0);
		glm::mat4 modelPiernaDer = glm::mat4(1.0);

		// Torso
		modelTorso = glm::mat4(1.0);
		modelTorsoPosition = modelTorso = glm::translate(modelTorso, glm::vec3(-20.0f + mainWindow.getmuevex(), 153.0f, 140.0f + mainWindow.getmuevez()));
		changeCamera(cameraActive);
		modelTorso = glm::rotate(modelTorso, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotaci�n de 180 grados en el eje Z
		spotLights[2].SetPos(glm::vec3(-20.0f + mainWindow.getmuevex(), 153.0f, 140.0f + mainWindow.getmuevez()));
		modelTorso = glm::scale(modelTorso, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelTorso));
		Torso_M.RenderModel();


		// Cabeza
		modelCabeza = modelTorso;  // La cabeza sigue al torso
		// Se modifica la posici�n vertical de la cabeza usando el seno del tiempo para crear una animaci�n oscilante
		float offsetVertical = sin(tiempo) * 0.5f;
		modelCabeza = glm::translate(modelCabeza, glm::vec3(0.0f, 6.0f + offsetVertical, 1.5f));
		modelCabeza = glm::scale(modelCabeza, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelCabeza));
		Cabeza_M.RenderModel();

		// BrazoIzq
		modelBrazoIzq = modelTorso;  // El brazo izquierdo sigue al torso
		float offsetYBrazoIzq = sin(tiempo) * 0.2f; // Ajusta la amplitud seg�n tus necesidades
		modelBrazoIzq = glm::translate(modelBrazoIzq, glm::vec3(1.5f, 2.8f + offsetYBrazoIzq, -1.0f));
		modelBrazoIzq = glm::scale(modelBrazoIzq, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelBrazoIzq));
		BrazoIzq_M.RenderModel();

		// BrazoDer
		modelBrazoDer = modelTorso;  // El brazo derecho sigue al torso
		float offsetYBrazoDer = sin(tiempo) * 0.2f; // Ajusta la amplitud seg�n tus necesidades
		modelBrazoDer = glm::translate(modelBrazoDer, glm::vec3(-0.5f, 2.8f + offsetYBrazoDer, -1.0f));
		modelBrazoDer = glm::scale(modelBrazoDer, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelBrazoDer));
		BrazoDer_M.RenderModel();

		// L�gica de tiempo
		tiempo = tiempoActual;

		// Ajusta el factor de multiplicaci�n para reducir el rango de movimiento
		float factorAjuste = 0.8f; // Ajusta seg�n sea necesario

		// Calcula el desplazamiento horizontal (en el eje z) basado en el tiempo
		float offsetZ = sin(tiempo * velocidadAnimacion) * factorAjuste; // Ajusta seg�n sea necesario

		// PiernaIzq
		modelPiernaIzq = modelTorso;
		modelPiernaIzq = glm::translate(modelPiernaIzq, glm::vec3(0.8f, -2.7f, -0.5f + offsetZ));
		modelPiernaIzq = glm::scale(modelPiernaIzq, glm::vec3(1.0f, 1.0f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelPiernaIzq));
		PierIzq_M.RenderModel();

		// TPiernader
		modelPiernaDer = modelTorso;
		modelPiernaDer = glm::translate(modelPiernaDer, glm::vec3(-1.0f, -2.7f, -0.5f - offsetZ));
		modelPiernaDer = glm::scale(modelPiernaDer, glm::vec3(1.0f, 1.0f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelPiernaDer));
		PierDere_M.RenderModel();

		//Pinball
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pinball_M.RenderModel();

		//Ventana
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ventana_M.RenderModel();

		//Asteroid Arcade
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 230.0f, -10.0f));
		model = glm::rotate(model, glm::radians(-75.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f, 18.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Asteroid.RenderModel();

		//Arcade 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(220.0f, 0.0f, -30.0f));
		model = glm::rotate(model, glm::radians(-105.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(120.0f, 170.0f, 120.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arcade.RenderModel();


		

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}

void inputKeyframes(bool* keys)
{


	if (keys[GLFW_KEY_SPACE])
	{
		if (reproduciranimacion < 1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("\n presiona 0 para habilitar reproducir de nuevo la animaci�n'\n");
				habilitaranimacion = 0;

			}
			else
			{
				play = false;

			}
		}
	}
	if (keys[GLFW_KEY_0])
	{
		if (habilitaranimacion < 1 && reproduciranimacion>0)
		{
			printf("Ya puedes reproducir de nuevo la animaci�n con la tecla de barra espaciadora'\n");
			reproduciranimacion = 0;

		}
	}

	if (keys[GLFW_KEY_L])
	{
		if (guardoFrame < 1)
		{
			saveFrame();
			printf("movAvion_x es: %f\n", movAvion_x);
			printf("movAvion_y es: %f\n", movAvion_y);
			printf("presiona P para habilitar guardar otro frame'\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}
	if (keys[GLFW_KEY_P])
	{
		if (reinicioFrame < 1)
		{
			guardoFrame = 0;
			printf("Ya puedes guardar otro frame presionando la tecla L'\n");
		}
	}


	if (keys[GLFW_KEY_1])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movAvion_x -= 1.0f;
			printf("\n movAvion_x es: %f\n", movAvion_x);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_2] && GLFW_PRESS)
	{
		if (ciclo2 < 1 && ciclo>0)
		{
			ciclo = 0;
			printf("\n Ya puedes modificar tu variable presionando la tecla 1\n");
		}
	}

	if (keys[GLFW_KEY_5] && GLFW_PRESS)
	{
		cameraActive = 1;
		changeCamera(cameraActive);

	}

	if (keys[GLFW_KEY_6] && GLFW_PRESS)
	{
		camera.setYaw(-90.0f);
		camera.setPitch(0.0f);
		cameraActive = 2;
		changeCamera(cameraActive);
	}

	if (keys[GLFW_KEY_7] && GLFW_PRESS)
	{
		cameraActive = 3;
		changeCamera(cameraActive);
	}

}
