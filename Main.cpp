#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//Core(Núcleo) del vertexShader
const char* vertexShaderSource = "#version 450 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Core(Núcleo) del FragmentShader
const char* fragmentShaderSource = "#version 450 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.0f, 100.0f / 255.0f, 0.0f, 1.0f);\n"
"}\n\0";


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

	// Crear el Objeto vertexShader y obtener referencia
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Adjuntar la fuente de sombreador al vertexShader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compilar el vertexShader por medio de código
	glCompileShader(vertexShader);

	// Crear el fragmentShader y obtener referencia
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Adjuntar la fuente de sombreador de fragmentos al fragmentShader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compilar fragmentShader por medio de cóidigo.
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Elimina el fragment y vertex que no sirven
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//Coordenadas de los vertices
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Esquina inferior Izquierda
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Esquina inferior Derecha
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Esquina Superior
		- 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Interior izquierdo
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Interior Derecho
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Interior hacia abajo
	};

	GLuint indices[] =
	{
		0, 3, 5, // Triángulo inferior izquierdo
		3, 2, 4, // Triángulo derecho inferior
		5, 4, 1 // Triángulo superior
	};

	// Crear referencia de los contenedores para el arreglo de vertices y el buffer de vertices
	GLuint VAO, VBO, EBO;

	// Generar el VAO y VBO con cada objeto
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Vincula la matriz de vertices actual
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//Especifica el color del fondo en RGBA
	glClearColor(119.0f / 255.0f, 221.0f / 255.0f, 119.0f / 255.0f, 1.0f);
	//Limpia el anterior Buffer y asigna un nuevo color en el
	glClear(GL_COLOR_BUFFER_BIT);
	//Intercambia el anterior buffer con el buffer actual
	glfwSwapBuffers(window);

	//Bucle Principal
	while (!glfwWindowShouldClose(window)) 
	{
		glClearColor(119.0f / 255.0f, 221.0f / 255.0f, 119.0f / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Le cuenta a OpenGL que shaderProgram quiero usar
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// Dibuja el triangulo
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		//Cuida todos los eventos de GLFW
		glfwPollEvents();
	}

	// Elimina todos los objetos creados
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	//Elimina la ventana antes de que el programa termine
	glfwDestroyWindow(window);
	//Termina GLFW antes de que el programa termine
	glfwTerminate();
	return 0;
}