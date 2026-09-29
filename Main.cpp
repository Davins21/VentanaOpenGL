#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

// Estructura para organizar los atributos en vértices
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec2 TexCoords;
};

// Estructura para almacenar las propiedades de cada hongo
struct Hongo {
	glm::vec3 pos;
	float escala;
	glm::vec3 colorSombrero;
	float alpha;
};

// Evento del Mouse - Callback para movimiento
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	//Conversión de coordenadas del mouse a float
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	// Recuperar el puntero de la cámara asociada a la ventana
	Camera* camera = reinterpret_cast<Camera*>(glfwGetWindowUserPointer(window));
	if (!camera) return;

	if (camera->firstMouse)
	{
		camera->lastX = xpos;
		camera->lastY = ypos;
		camera->firstMouse = false;
	}

	// Calcula el desplazamiento del mouse entre frames
	float xoffset = xpos - camera->lastX;
	float yoffset = camera->lastY - ypos; // Invertido porque las coordenadas Y van de abajo hacia arriba

	// Actualiza la última posición registrada del mouse
	camera->lastX = xpos;
	camera->lastY = ypos;

	camera->ProcessMouseMovement(xoffset, yoffset);
}

//Construccion de Geometrías (Definición de coordenadas para posición, color y textura)
Vertex vertices[] = {
	// Tallo (Caja Inferior: Vértices 0 a 7) - Color Piel
	{ {-0.35f, -0.7f,  0.35f}, {1.0f, 0.8f, 0.6f}, {0.0f, 0.0f} }, // 0
	{ { 0.35f, -0.7f,  0.35f}, {1.0f, 0.8f, 0.6f}, {1.0f, 0.0f} }, // 1
	{ { 0.35f,  0.0f,  0.35f}, {1.0f, 0.8f, 0.6f}, {1.0f, 1.0f} }, // 2
	{ {-0.35f,  0.0f,  0.35f}, {1.0f, 0.8f, 0.6f}, {0.0f, 1.0f} }, // 3
	{ {-0.35f, -0.7f, -0.35f}, {1.0f, 0.8f, 0.6f}, {1.0f, 0.0f} }, // 4
	{ { 0.35f, -0.7f, -0.35f}, {1.0f, 0.8f, 0.6f}, {0.0f, 0.0f} }, // 5
	{ { 0.35f,  0.0f, -0.35f}, {1.0f, 0.8f, 0.6f}, {0.0f, 1.0f} }, // 6
	{ {-0.35f,  0.0f, -0.35f}, {1.0f, 0.8f, 0.6f}, {1.0f, 1.0f} }, // 7

	// SombreroPrincipal (Caja Superior: Vértices 8 a 15) - Blanco Neutro
	{ {-0.5f,  0.0f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} }, // 8
	{ { 0.5f,  0.0f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} }, // 9
	{ { 0.5f,  0.6f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} }, // 10
	{ {-0.5f,  0.6f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} }, // 11
	{ {-0.5f,  0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} }, // 12
	{ { 0.5f,  0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} }, // 13
	{ { 0.5f,  0.6f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} }, // 14
	{ {-0.5f,  0.6f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} }, // 15

	// Ojos Negros en el tallo (Vértices 16 a 23) - Z = -0.351f (Frontal)
	// Ojo Izquierdo (Rectángulo vertical centrado)
	{ {-0.18f, -0.45f, -0.351f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} }, // 16
	{ {-0.06f, -0.45f, -0.351f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f} }, // 17
	{ {-0.06f, -0.15f, -0.351f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f} }, // 18
	{ {-0.18f, -0.15f, -0.351f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f} }, // 19

	// Ojo Derecho (Rectángulo vertical centrado)
	{ { 0.06f, -0.45f, -0.351f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} }, // 20
	{ { 0.18f, -0.45f, -0.351f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f} }, // 21
	{ { 0.18f, -0.15f, -0.351f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f} }, // 22
	{ { 0.06f, -0.15f, -0.351f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f} }, // 23

	// Manchas blancas en el Sombrero (Vértices 24 a 43)
	// Mancha Frontal (Z = +0.501f)
	{ {-0.2f,  0.15f, 0.501f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} }, // 24
	{ { 0.2f,  0.15f, 0.501f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} }, // 25
	{ { 0.2f,  0.45f, 0.501f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} }, // 26
	{ {-0.2f,  0.45f, 0.501f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} }, // 27

	// Mancha Trasera (Z = -0.501f)
	{ {-0.2f,  0.15f, -0.501f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} }, // 28
	{ { 0.2f,  0.15f, -0.501f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} }, // 29
	{ { 0.2f,  0.45f, -0.501f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} }, // 30
	{ {-0.2f,  0.45f, -0.501f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} }, // 31

	// Mancha Izquierda (X = -0.501f)
	{ {-0.501f, 0.15f, -0.2f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} }, // 32
	{ {-0.501f, 0.15f,  0.2f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} }, // 33
	{ {-0.501f, 0.45f,  0.2f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} }, // 34
	{ {-0.501f, 0.45f, -0.2f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} }, // 35

	// Mancha Derecha (X = +0.501f)
	{ {0.501f, 0.15f, -0.2f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} },  // 36
	{ {0.501f, 0.15f,  0.2f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} },  // 37
	{ {0.501f, 0.45f,  0.2f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} },  // 38
	{ {0.501f, 0.45f, -0.2f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} },  // 39

	// Mancha Superior (Y = +0.601f)
	{ {-0.2f, 0.601f, -0.2f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} },  // 40
	{ { 0.2f, 0.601f, -0.2f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} },  // 41
	{ { 0.2f, 0.601f,  0.2f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} },  // 42
	{ {-0.2f, 0.601f,  0.2f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} }   // 43
};

GLuint indices[] = {
	// Tallo (36 Índices)
	0, 1, 2,   2, 3, 0,    5, 4, 7,   7, 6, 5,
	4, 0, 3,   3, 7, 4,    1, 5, 6,   6, 2, 1,
	4, 5, 1,   1, 0, 4,    3, 2, 6,   6, 7, 3,

	// SomberoPrincipal (36 Índices) 
	8, 9, 10,   10, 11, 8,      13, 12, 15,   15, 14, 13,
	12, 8, 11,  11, 15, 12,     9, 13, 14,    14, 10, 9,
	12, 13, 9,   9, 8, 12,      11, 10, 14,   14, 15, 11,

	// Ojos (12 Índices) 
	16, 17, 18,   18, 19, 16,
	20, 21, 22,   22, 23, 20,

	// Manchas (30 Índices: 5 caras x 6 índices) 
	24, 25, 26,   26, 27, 24, // Frontal
	28, 29, 30,   30, 31, 28, // Trasera
	32, 33, 34,   34, 35, 32, // Izquierda
	36, 37, 38,   38, 39, 36, // Derecha
	40, 41, 42,   42, 43, 40  // Superior
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Ventana HongoDeMario", NULL, NULL);
	if (!window) { glfwTerminate(); return -1; }

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glEnable(GL_DEPTH_TEST); //Profundidad
	glDepthFunc(GL_LESS); //Criterio de Profundidad
	glEnable(GL_BLEND); //Mezcla de Colores
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Configuración de atributos usando struct Vertex
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Position));
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Color));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Carga de textura
	Texture hongoTex("textuhongo.png");

	//Indica la ubicación de los Uniforms de Shaders, ubicación, de matrices, tinta y textura.
	GLint mvpLoc = glGetUniformLocation(shaderProgram.ID, "uMVP");
	GLint tintLoc = glGetUniformLocation(shaderProgram.ID, "uColorTint");
	GLint texLoc = glGetUniformLocation(shaderProgram.ID, "tex0");

	//Arreglo para crear hongos, posición, escala, color y transparencia.
	Hongo hongos[] = {
		{ glm::vec3(0.0f, 0.0f,  0.0f), 0.6f, glm::vec3(0.0f, 0.4f, 1.0f), 1.0f },
		{ glm::vec3(1.0f, 0.0f, -1.0f), 0.8f, glm::vec3(0.0f, 1.0f, 0.0f), 1.0f },
		{ glm::vec3(-1.0f, 0.0f, -1.0f), 1.0f, glm::vec3(1.0f, 0.0f, 0.0f), 1.0f }
	};

	GLsizei totalIndices = sizeof(indices) / sizeof(GLuint);

	// Instancia de la Cámara
	Camera camera(800, 800, glm::vec3(0.0f, 0.0f, 3.0f));

	// Vincular el puntero de la cámara a la ventana de GLFW
	glfwSetWindowUserPointer(window, &camera);

	// Registrar la función de callback para el movimiento del cursor
	glfwSetCursorPosCallback(window, mouse_callback);

	// Capturar y ocultar el puntero del mouse (Modo FPS)
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	float lastFrame = 0.0f;

	shaderProgram.Activate();
	glUniform1i(texLoc, 0);

	// BUCLE PRINCIPAL DE RENDERIZADO
	while (!glfwWindowShouldClose(window))
	{
		// DeltaTime para un movimiento constante en la ventana 
		float currentFrame = (float)glfwGetTime();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Procesar entradas de teclado para mover la cámara
		camera.ProcessInputs(window, deltaTime);

		// Fondo de la Escena 
		glClearColor(0.0f, 0.56f, 0.25f, 1.0f);
		// Limpia buffers de color y profunidad
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();
		VAO1.Bind(); //Enlazar geometría del hongo
		hongoTex.Bind(GL_TEXTURE0); //Enlaza la textura

		//Actualiza dimensiones de la cámara
		glfwGetFramebufferSize(window, &camera.width, &camera.height);

		// Obtener matrices calculadas por la clase Camera
		glm::mat4 projection = camera.GetProjectionMatrix(60.0f, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();

		//Rotación general respecto al eje Y para todos los hogos, usando el tiempo de GLFW obtenido
		glm::mat4 globalRotation = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		//Ciclo for que me permite hacer un renderizado de cada hongo con sus propiedades individuales (posición, escala, color y transparencia)
		for (const auto& h : hongos)
		{
			// Matriz base con la rotación global, posición del hongo y su escala general
			glm::mat4 hongoBase = glm::scale(glm::translate(globalRotation, h.pos), glm::vec3(h.escala));

			// TALLO (36 índices)
			glm::mat4 modelTallo = glm::scale(hongoBase, glm::vec3(1.2f, 0.8f, 1.0f)); // Escala individual del torso: (X: ancho, Y: alto, Z: profundidad)
			glm::mat4 mvpTallo = projection * view * modelTallo;

			//Dibujo del tallo con tinte blanco para conservar textura aplicada
			glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvpTallo));
			glUniform4f(tintLoc, 1.0f, 1.0f, 1.0f, h.alpha);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

			// SOMBRERO PRINCIPAL (36 índices)
			glm::mat4 mvpSombrero = projection * view * hongoBase; //Matriz base sin transformaciones adicionales para el sombrero

			// Dibujado con el tinte de color dinámico asignado al hongo (Azul / Verde / Rojo)
			glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvpSombrero));
			glUniform4f(tintLoc, h.colorSombrero.r, h.colorSombrero.g, h.colorSombrero.b, h.alpha);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)(uintptr_t)(36 * sizeof(GLuint)));

			// MINI-SOMBRERO ENCIMA (36 índices reutilizados)
			glm::mat4 modelMiniSombrero = glm::translate(hongoBase, glm::vec3(0.0f, 0.55f, 0.0f)); //Traslación hacia arriba para colocar el mini-sombrero encima del sombrero principal
			modelMiniSombrero = glm::scale(modelMiniSombrero, glm::vec3(0.7f, 0.35f, 0.7f));
			glm::mat4 mvpMiniSombrero = projection * view * modelMiniSombrero;

			//Matriz para mini-sombrero
			glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvpMiniSombrero));
			glUniform4f(tintLoc, h.colorSombrero.r, h.colorSombrero.g, h.colorSombrero.b, h.alpha);
			// Reutiliza los vértices del sombrero original (offset 36)
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)(uintptr_t)(36 * sizeof(GLuint)));

			// Manchas del mini-sombrero (Tinte Blanco + Misma matriz mvpMiniSombrero)
			glUniform4f(tintLoc, 1.0f, 1.0f, 1.0f, h.alpha);
			// Corresponde a los 30 índices de las manchas blancas (índices 24 a 43)
			glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, (void*)(uintptr_t)(84 * sizeof(GLuint)));

			// OJOS Y MANCHAS (42 índices)
			glm::mat4 mvpOjosManchas = projection * view * hongoBase;

			glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvpOjosManchas));
			glUniform4f(tintLoc, 1.0f, 1.0f, 1.0f, h.alpha);
			glDrawElements(GL_TRIANGLES, 42, GL_UNSIGNED_INT, (void*)(uintptr_t)(72 * sizeof(GLuint)));
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Limpieza de memoria
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();		
	hongoTex.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}