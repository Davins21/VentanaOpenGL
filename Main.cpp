#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

//Coordenadas de los vertices
GLfloat vertices[] =
{ //				COORDINADAS					  /			COLORES		//	
	-0.5f,	-0.5f *  float(sqrt(3)) / 3,	0.0f,	0.0f, 1.0f, 0.0f,	// Esquina inferior Izquierda
	0.5f,	-0.5f *  float(sqrt(3)) / 3,	0.0f,	0.0f, 0.7f, 0.0f,  // Esquina inferior Derecha
	0.0f,	0.5f  *  float(sqrt(3)) * 2 / 3,0.0f,	0.0f, 0.4f, 0.0f,	// Esquina Superior
	-0.25f, 0.5f  *  float(sqrt(3)) / 6,	0.0f,	0.0f, 1.0f, 0.0f, // Interior izquierdo
	0.25f,	0.5f  *  float(sqrt(3)) / 6,	0.0f,	0.0f, 0.4f, 0.0f,	// Interior Derecho
	0.0f,	-0.5f *  float(sqrt(3)) / 3,	0.0f,	0.0f, 0.8f,	0.0f	// Interior hacia abajo
};

GLuint indices[] =
{
	0, 3, 5, // Triángulo inferior izquierdo
	3, 2, 4, // Triángulo derecho inferior
	5, 4, 1 // Triángulo superior
};


int main()
{
	//Inicializa GLFW
	glfwInit();

	//Le informa a GLFW que version de OpenGL se está usando
	//En este caso la versión es OpenGL 4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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

	// Introduce la ventana al contexto actual
	glfwMakeContextCurrent(window);

	// Carga GLAD para que se configure OpenGL
	gladLoadGL();
	// Especifica la ventana gráfica de OpenGl en la ventana
	// En este caso, la ventana gráfica va desde x=0, y=0; hasta x=800, y=800
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//Bucle Principal
	while (!glfwWindowShouldClose(window)) 
	{
		glClearColor(119.0f / 255.0f, 221.0f / 255.0f, 119.0f / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Le cuenta a OpenGL que shaderProgram quiero usar
		shaderProgram.Activate();
		VAO1.Bind();
		// Dibuja el triangulo	
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		//Cuida todos los eventos de GLFW
		glfwPollEvents();
	}

	// Elimina todos los objetos creados
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	//Elimina la ventana antes de que el programa termine
	glfwDestroyWindow(window);
	//Termina GLFW antes de que el programa termine
	glfwTerminate();
	return 0;
}
