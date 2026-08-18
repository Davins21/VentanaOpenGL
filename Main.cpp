#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"ShaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// Coordenadas Normalizadas (-1.0 a 1.0) con sus respectivos colores
GLfloat vertices[] =
{
	// SOMBRERO ROJO Y MANCHAS BLANCAS
	// Base del sombrerito (Color Rojo)
	-0.6f, -0.1f, 0.0f, 0.9f, 0.1f, 0.1f ,
	 0.6f, -0.1f, 0.0f, 0.9f, 0.1f, 0.1f ,
	 0.6f,  0.2f, 0.0f, 0.9f, 0.1f, 0.1f ,
	-0.6f,  0.2f, 0.0f, 0.9f, 0.1f, 0.1f ,

	// Parte superior del sombrero (Color Rojo)
	-0.4f,  0.2f, 0.0f, 0.9f, 0.1f, 0.1f ,
	 0.4f,  0.2f, 0.0f, 0.9f, 0.1f, 0.1f ,
	 0.4f,  0.6f, 0.0f, 0.9f, 0.1f, 0.1f ,
	-0.4f,  0.6f, 0.0f, 0.9f, 0.1f, 0.1f ,

	// Mancha color blanca central
	-0.2f,  0.1f, 0.0f,  1.0f, 1.0f, 1.0f,
	 0.2f,  0.1f, 0.0f,  1.0f, 1.0f, 1.0f,
	 0.2f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,
	-0.2f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,

	// Mancha color blanca izquierda
	-0.6f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f,
	-0.4f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f,
	-0.4f,  0.3f, 0.0f,  1.0f, 1.0f, 1.0f,
	-0.6f,  0.3f, 0.0f,  1.0f, 1.0f, 1.0f,

	// Mancha color blanca derecha
	 0.4f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f,
	 0.6f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f,
	 0.6f,  0.3f, 0.0f,  1.0f, 1.0f, 1.0f,
	 0.4f,  0.3f, 0.0f,  1.0f, 1.0f, 1.0f,

	 //  BASE / TALLO (Color Piel)
	 -0.4f, -0.6f, 0.0f,  1.0f, 0.8f, 0.6f,
	  0.4f, -0.6f, 0.0f,  1.0f, 0.8f, 0.6f,
	  0.4f, -0.1f, 0.0f,  1.0f, 0.8f, 0.6f,
	 -0.4f, -0.1f, 0.0f,  1.0f, 0.8f, 0.6f,

	 // OJOS (Color Negro)
	 // Ojo Izquierdo
	 -0.25f, -0.45f, 0.0f, 0.0f, 0.0f, 0.0f,
	 -0.15f, -0.45f, 0.0f, 0.0f, 0.0f, 0.0f,
	 -0.15f, -0.20f, 0.0f, 0.0f, 0.0f, 0.0f,
	 -0.25f, -0.20f, 0.0f, 0.0f, 0.0f, 0.0f,

	 // Ojo Derecho
	  0.15f, -0.45f, 0.0f, 0.0f, 0.0f, 0.0f,
	  0.25f, -0.45f, 0.0f, 0.0f, 0.0f, 0.0f,
	  0.25f, -0.20f, 0.0f, 0.0f, 0.0f, 0.0f,
	  0.15f, -0.20f, 0.0f, 0.0f, 0.0f, 0.0f,

	  // BORDE COLORNEGRO INFERIOR
	  -0.4f, -0.7f, 0.0f,  0.0f, 0.0f, 0.0f,
	   0.4f, -0.7f, 0.0f,  0.0f, 0.0f, 0.0f,
	   0.4f, -0.6f, 0.0f,  0.0f, 0.0f, 0.0f,
	  -0.4f, -0.6f, 0.0f,  0.0f, 0.0f, 0.0f
};

// Definir rectángulos divididos en 2 triángulos aplicando índices que se guardan en EBO
GLuint indices[] =
{
	// Sombrero
	0, 1, 2,   2, 3, 0,
	4, 5, 6,   6, 7, 4,

	// Manchas blancas
	8, 9, 10,     10, 11, 8,
	12, 13, 14,   14, 15, 12,
	16, 17, 18,   18, 19, 16,

	// Tallo
	20, 21, 22,   22, 23, 20,

	// Ojos
	24, 25, 26,   26, 27, 24,
	28, 29, 30,   30, 31, 28,

	// Borde inferior
	32, 33, 34,   34, 35, 32
};

int main()
{
	//Inicializa GLFW
	glfwInit();
	//Le informa a GLFW que version de OpenGL se está usando
	//En este caso la versión es OpenGL 4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Crea la ventana GLFW de 800*800 pixeles con un nombre
	GLFWwindow* window = glfwCreateWindow(800, 800, "Ventana HongoDeMario", NULL, NULL);
	if (window == NULL)
	{
		//Maneja errores si la ventana falla al crearla
		std::cout << "Error al crear la ventana" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	// Carga GLAD para que se configure OpenGL
	gladLoadGL();
	// Especifica la ventana gráfica de OpenGl en la ventana
	// En este caso, la ventana gráfica va desde x=0, y=0; hasta x=800, y=800
	glViewport(0, 0, 800, 800);

	// Compila y vincula los archivos de código fuente de los shaders
	Shader shaderProgram("default.vert", "default.frag");

	// Crea VAO para empezar a guardar la configuración
	VAO VAO1;
	VAO1.Bind();

	// Crea el VBO transfiriendo las coordenadas y colores de los vértices a la GPU
	VBO VBO1(vertices, sizeof(vertices));
	// Crea el EBO transfiriendo la lista de índices de dibujo a la GPU
	// la referencia de este EBO queda registrada internamente en el VAO
	EBO EBO1(indices, sizeof(indices));

	// Define la estructura de los datos dentro del VBO para OpenGL:
	// Atributo 0: Posición -> 3 floats (X, Y, Z), inicia en el byte 0
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	// Atributo 1: Color -> 4 floats (R, G, B, A), inicia en el byte 12 (3 * sizeof(float))
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	//Desvincula los objetos
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	while (!glfwWindowShouldClose(window))
	{
		// Fondo gris
		glClearColor(0.2f, 0.2f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		// Para ajustar la escala en general
		glUniform1f(uniID, 0.1f);

		VAO1.Bind();
		// Dibujar los 54 índices (18 triángulos que forman los rectángulos)
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Libera los recursos asignados en la memoria de la GPU
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Destruye la ventana y finaliza el contexto de GLFW
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}