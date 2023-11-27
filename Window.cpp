#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	muevex = 2.0f;
	muevez = 2.0f;
	mueveh = 2.0f;
	luzHeli = 0;
	linterna = false;
	carroX = false;
	carroZ = false;
	helip = false;
	lampara = false;
	arreglos = 1;
	bool animacionActiva = false;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicializaci�n de GLFW
	if (!glfwInit())
	{
		printf("Fall� inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Proyecto Final", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tama�o de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Fall� inicializaci�n de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
	// Asignar valores de la ventana y coordenadas

	//Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se est� usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_F)
	{
		theWindow->muevex += 1.0;
		theWindow->carroX = false;
	}
	if (key == GLFW_KEY_G)
	{
		theWindow->muevex -= 1.0;
		theWindow->carroX = true;
	}
	if (key == GLFW_KEY_H)
	{
		theWindow->muevez += 1.0;
		theWindow->carroZ = false;
	}
	if (key == GLFW_KEY_J)
	{
		theWindow->muevez -= 1.0;
		theWindow->carroZ = true;
	}

	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		if (theWindow->luzHeli == 1) {
			theWindow->luzHeli = 0;
			printf("Luz encendida\n");
		}
		else if (theWindow->luzHeli == 0) {
			theWindow->luzHeli = 1;
			printf("Luz apagada\n");
		}
	}

	if (key == GLFW_KEY_J)
	{
		theWindow->mueveh += 1.0;
	}
	if (key == GLFW_KEY_K)
	{
		theWindow->mueveh -= 1.0;
	}
	if (key == GLFW_KEY_I)
	{
		// Subir o bajar la paleta derecha
		if (theWindow->paletader < 0.0)
		{
			theWindow->paletader += 35.0;
			if (theWindow->paletader > 0.0)
			{
				theWindow->paletader = 0.0;
			}
		}
		else if (theWindow->paletader > -90.0)
		{
			theWindow->paletader -= 35.0;
			if (theWindow->paletader < -90.0)
			{
				theWindow->paletader = -100.0; // Limitar la apertura al m�nimo
			}
		}
	}

		if (key == GLFW_KEY_Y)
		{
			// Subir o bajar la paleta derecha
			if (theWindow->paletader < 0.0)
			{
				theWindow->paletader += 35.0;
				if (theWindow->paletader > 0.0)
				{
					theWindow->paletader = 0.0;
				}
			}
			else if (theWindow->paletader > -90.0)
			{
				theWindow->paletader -= 35.0;
				if (theWindow->paletader < -90.0)
				{
					theWindow->paletader = -100.0; // Limitar la apertura al m�nimo
				}
			}
		}

	// Asignaciones para la paleta izquierda
	if (key == GLFW_KEY_O)
	{
		// Subir o bajar la paleta izquierda
		if (theWindow->paletaizq < 0.0)
		{
			theWindow->paletaizq += 35.0;
			if (theWindow->paletaizq > 0.0)
			{
				theWindow->paletaizq = 0.0;
			}
		}
		else if (theWindow->paletaizq > -90.0)
		{
			theWindow->paletaizq -= 35.0;
			if (theWindow->paletaizq < -90.0)
			{
				theWindow->paletaizq = -100.0; // Limitar la apertura al m�nimo
			}
		}
	}
	// Asignaciones para la paleta izquierda
	if (key == GLFW_KEY_U)
	{
		// Subir o bajar la paleta izquierda
		if (theWindow->paletacentral < 0.0)
		{
			theWindow->paletacentral += 35.0;
			if (theWindow->paletacentral > 0.0)
			{
				theWindow->paletacentral = 0.0;
			}
		}
		else if (theWindow->paletacentral > -90.0)
		{
			theWindow->paletacentral -= 35.0;
			if (theWindow->paletacentral < -90.0)
			{
				theWindow->paletacentral = -100.0; // Limitar la apertura al m�nimo
			}
		}
	}


	///LANATAS


	if (key == GLFW_KEY_T)
	{
		if (theWindow->ruedat > 360.0)
		{
		}
		else
		{
			theWindow->ruedat += 10.0;
		}
	}

	if (key == GLFW_KEY_F)
	{
		if (theWindow->ruedat < -360)
		{
		}
		else
		{
			theWindow->ruedat -= 10.0;
		}
	}
	if (key == GLFW_KEY_F)
	{
		theWindow->linterna = true;
	}

	if (key == GLFW_KEY_G)
	{
		theWindow->linterna = false;
	}

	if (key == GLFW_KEY_Z)
	{
		theWindow->arreglos = 1;
	}

	if (key == GLFW_KEY_X)
	{
		theWindow->arreglos = 2;
	}

	if (key == GLFW_KEY_E)
	{
		theWindow->lampara = true;
	}

	if (key == GLFW_KEY_R)
	{
		theWindow->lampara = false;
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	// Verifica si el bot�n derecho del mouse est� presionado
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		// Activa la animaci�n
		theWindow->animacionActiva = true;
	}
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}