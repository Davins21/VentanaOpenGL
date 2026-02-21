#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() 
{
	//Inicializa GLFW
	glfwInit();

	//Le informa a GLFW que version de OpenGL se está usando
	//En este caso la versión es OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Le informa a GLFW que se esta usando el núcleo o (CORE profile)
	//Solo tenemos funciones modernas
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Crea una ventana GLFW de 800*800 pixeles con un nombre
	GLFWwindow* window = glfwCreateWindow(800, 800, "MiPrimeraVentana", NULL, NULL);
	//Maneja errores si la ventana al crearla falla
	if (window == NULL)
	{
		std::cout << "Error al crear la ventana" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Introduce la ventana al contexto actual
	glfwMakeContextCurrent(window);

	//Carga GLAD para que se configure OpenGL
	gladLoadGL();

	//Especifica la ventana gráfica de OpenGl en la ventana
	//En este caso, la ventana gráfica va desde x=0, y=0; hasta x=800, y=800
	glViewport(0, 0, 800, 800);


	//Especifica el color del fondo en RGBA
	glClearColor(119.0f / 255.0f, 221.0f / 255.0f, 119.0f / 255.0f, 1.0f);
	//Limpia el anterior Buffer y asigna un nuevo color en el
	glClear(GL_COLOR_BUFFER_BIT);
	//Intercambia el anterior buffer con el buffer actual
	glfwSwapBuffers(window);

	//Bucle Principal
	while (!glfwWindowShouldClose(window)) 
	{
		//Cuida todos los eventos de GLFW
		glfwPollEvents();
	}

	//Elimina la ventana antes de que el programa termine
	glfwDestroyWindow(window);
	//Termina GLFW antes de que el programa termine
	glfwTerminate();
	return 0;
}