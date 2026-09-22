#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

// Coordenadas con Posición (X,Y,Z), Color (R,G,B) y Textura (S,T) -> Total 8 floats por vértice
GLfloat vertices[] =
{
	// SOMBRERO ROJO Y MANCHAS BLANCAS
	// Base del sombrerito (Color Rojo)
	-0.6f, -0.1f, 0.0f,   0.9f, 0.1f, 0.1f,   0.0f, 0.0f,
	 0.6f, -0.1f, 0.0f,   0.9f, 0.1f, 0.1f,   1.0f, 0.0f,
	 0.6f,  0.3f, 0.0f,   0.9f, 0.1f, 0.1f,   1.0f, 0.5f,
	-0.6f,  0.3f, 0.0f,   0.9f, 0.1f, 0.1f,   0.0f, 0.5f,

	// Parte superior del sombrero (Color Rojo)
	-0.4f,  0.3f, 0.0f,   0.9f, 0.1f, 0.1f,   0.1f, 0.5f,
	 0.4f,  0.3f, 0.0f,   0.9f, 0.1f, 0.1f,   0.9f, 0.5f,
	 0.4f,  0.6f, 0.0f,   0.9f, 0.1f, 0.1f,   0.9f, 1.0f,
	-0.4f,  0.6f, 0.0f,   0.9f, 0.1f, 0.1f,   0.1f, 1.0f,

	// 8 a 19: MANCHAS BLANCAS FRONTALES (Z = +0.002f)
	// Mancha Central Frente
	-0.2f,  0.1f, 0.002f,  1.0f, 1.0f, 1.0f,  0.3f, 0.3f,
	 0.2f,  0.1f, 0.002f,  1.0f, 1.0f, 1.0f,  0.7f, 0.3f,
	 0.2f,  0.5f, 0.002f,  1.0f, 1.0f, 1.0f,  0.7f, 0.8f,
	-0.2f,  0.5f, 0.002f,  1.0f, 1.0f, 1.0f,  0.3f, 0.8f,

	// Mancha Izquierda Frente
	-0.6f,  0.0f, 0.002f,  1.0f, 1.0f, 1.0f,  0.0f, 0.2f,
	-0.4f,  0.0f, 0.002f,  1.0f, 1.0f, 1.0f,  0.2f, 0.2f,
	-0.4f,  0.3f, 0.002f,  1.0f, 1.0f, 1.0f,  0.2f, 0.5f,
	-0.6f,  0.3f, 0.002f,  1.0f, 1.0f, 1.0f,  0.0f, 0.5f,

	// Mancha Derecha Frente
	 0.4f,  0.0f, 0.002f,  1.0f, 1.0f, 1.0f,  0.8f, 0.2f,
	 0.6f,  0.0f, 0.002f,  1.0f, 1.0f, 1.0f,  1.0f, 0.2f,
	 0.6f,  0.3f, 0.002f,  1.0f, 1.0f, 1.0f,  1.0f, 0.5f,
	 0.4f,  0.3f, 0.002f,  1.0f, 1.0f, 1.0f,  0.8f, 0.5f,

	 // MANCHAS BLANCAS TRASERAS (Z = -0.002f)
	 // Mancha Central Atrás
	 -0.2f,  0.1f, -0.002f,  1.0f, 1.0f, 1.0f,  0.3f, 0.3f,
	  0.2f,  0.1f, -0.002f,  1.0f, 1.0f, 1.0f,  0.7f, 0.3f,
	  0.2f,  0.5f, -0.002f,  1.0f, 1.0f, 1.0f,  0.7f, 0.8f,
	 -0.2f,  0.5f, -0.002f,  1.0f, 1.0f, 1.0f,  0.3f, 0.8f,

	 // Mancha Izquierda Atrás
	 -0.6f,  0.0f, -0.002f,  1.0f, 1.0f, 1.0f,  0.0f, 0.2f,
	 -0.4f,  0.0f, -0.002f,  1.0f, 1.0f, 1.0f,  0.2f, 0.2f,
	 -0.4f,  0.3f, -0.002f,  1.0f, 1.0f, 1.0f,  0.2f, 0.5f,
	 -0.6f,  0.3f, -0.002f,  1.0f, 1.0f, 1.0f,  0.0f, 0.5f,

	 // Mancha Derecha Atrás
	  0.4f,  0.0f, -0.002f,  1.0f, 1.0f, 1.0f,  0.8f, 0.2f,
	  0.6f,  0.0f, -0.002f,  1.0f, 1.0f, 1.0f,  1.0f, 0.2f,
	  0.6f,  0.3f, -0.002f,  1.0f, 1.0f, 1.0f,  1.0f, 0.5f,
	  0.4f,  0.3f, -0.002f,  1.0f, 1.0f, 1.0f,  0.8f, 0.5f,

	  // BASE / TALLO (Color Piel)
	  -0.4f, -0.6f, 0.0f,  1.0f, 0.8f, 0.6f,  0.1f, 0.0f,
	   0.4f, -0.6f, 0.0f,  1.0f, 0.8f, 0.6f,  0.9f, 0.0f,
	   0.4f, -0.1f, 0.0f,  1.0f, 0.8f, 0.6f,  0.9f, 0.4f,
	  -0.4f, -0.1f, 0.0f,  1.0f, 0.8f, 0.6f,  0.1f, 0.4f,

	  // OJOS (Color Negro)
	  // Ojo Izquierdo
	  -0.25f, -0.45f, -0.005f, 0.0f, 0.0f, 0.0f,  0.3f, 0.1f,
	  -0.15f, -0.45f, -0.005f, 0.0f, 0.0f, 0.0f,  0.4f, 0.1f,
	  -0.15f, -0.20f, -0.005f, 0.0f, 0.0f, 0.0f,  0.4f, 0.3f,
	  -0.25f, -0.20f, -0.005f, 0.0f, 0.0f, 0.0f,  0.3f, 0.3f,

	  // Ojo Derecho
	  0.15f, -0.45f, -0.005f, 0.0f, 0.0f, 0.0f,  0.6f, 0.1f,
	  0.25f, -0.45f, -0.005f, 0.0f, 0.0f, 0.0f,  0.7f, 0.1f,
	  0.25f, -0.20f, -0.005f, 0.0f, 0.0f, 0.0f,  0.7f, 0.3f,
	  0.15f, -0.20f, -0.005f, 0.0f, 0.0f, 0.0f,  0.6f, 0.3f,

	  // BORDE COLOR NEGRO INFERIOR
	  -0.4f, -0.7f, 0.002f,  0.0f, 0.0f, 0.0f,  0.1f, 0.0f,
	   0.4f, -0.7f, 0.002f,  0.0f, 0.0f, 0.0f,  0.9f, 0.0f,
	   0.4f, -0.6f, 0.002f,  0.0f, 0.0f, 0.0f,  0.9f, 0.1f,
	  -0.4f, -0.6f, 0.002f,  0.0f, 0.0f, 0.0f,  0.1f, 0.1f
};

GLuint indices[] =
{
	// Sombrero
	0, 1, 2,   2, 3, 0,
	4, 5, 6,   6, 7, 4,

	// Manchas blancas
	8, 9, 10,     10, 11, 8,
	12, 13, 14,   14, 15, 12,
	16, 17, 18,   18, 19, 16,

	// Manchas blancas TRASERAS
	20, 21, 22,   22, 23, 20,
	24, 25, 26,   26, 27, 24,
	28, 29, 30,   30, 31, 28,

	// Tallo 
	32, 33, 34,   34, 35, 32,

	// Ojos 
	36, 37, 38,   38, 39, 36,   // Ojo Izquierdo
	40, 41, 42,   42, 43, 40,   // Ojo Derecho

	// Borde inferior 
	44, 45, 46,   46, 47, 44
};

// Función de carga de textura con protección contra archivos ausentes
GLuint CargarTextura(const char* filepath)
{
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	// Forzamos 4 canales (RGBA) para estandarizar la carga
	unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, STBI_rgb_alpha);

	if (!data)
	{
		std::cout << "[ERROR]: No se pudo encontrar o leer la imagen: " << filepath << std::endl;
		return 0;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// FIX PARA EL CRASH EN AMD:
	// Desactiva la alineación de 4 bytes por fila en el unpack de la textura
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Restaurar alineación por defecto de OpenGL
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	stbi_image_free(data);
	std::cout << "Textura cargada correctamente (" << width << "x" << height << "): " << filepath << std::endl;
	return textureID;
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Ventana HongoDeMario", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Error al crear la ventana" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	// Crear VAO, VBO y EBO
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Atributos de vértices (Layout)
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// IMPORTANTE: Primero desvincular VAO y luego VBO/EBO para no romper la referencia en la VRAM
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint hongoTex = CargarTextura("texthongo.png");

	GLint mvpLoc = glGetUniformLocation(shaderProgram.ID, "uMVP");
	GLint tintLoc = glGetUniformLocation(shaderProgram.ID, "uColorTint");
	GLint texLoc = glGetUniformLocation(shaderProgram.ID, "tex0");

	struct Hongo {
		glm::vec3 pos;
		float escala;
		glm::vec3 colorSombrero;
		float alpha;
	};

	Hongo hongos[] = {
		{ glm::vec3(0.0f, 0.0f,  0.0f), 0.6f, glm::vec3(0.0f, 0.4f, 1.0f), 1.0f }, // Azul
		{ glm::vec3(0.0f, 0.0f, -0.6f), 0.8f, glm::vec3(0.0f, 1.0f, 0.0f), 0.9f }, // Verde
		{ glm::vec3(0.0f, 0.0f, -1.2f), 1.0f, glm::vec3(1.0f, 0.0f, 0.0f), 1.0f }  // Rojo
	};

	GLsizei totalIndices = sizeof(indices) / sizeof(GLuint);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();
		VAO1.Bind();

		if (hongoTex != 0)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, hongoTex);
			glUniform1i(texLoc, 0);
		}

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		float aspect = (height > 0) ? (float)width / (float)height : 1.0f;

		glm::mat4 projection = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(
			glm::vec3(0.0f, 0.0f, 3.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		float t = (float)glfwGetTime();
		glm::mat4 globalRotation = glm::rotate(glm::mat4(1.0f), t * glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		for (const auto& h : hongos)
		{
			glm::mat4 model = glm::scale(glm::translate(globalRotation, h.pos), glm::vec3(h.escala));
			glm::mat4 mvp = projection * view * model;
			glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

			// 1. Dibujar Sombrero: Aplica el tinte del sombrero (Azul/Verde/Rojo)
			glUniform4f(tintLoc, h.colorSombrero.r, h.colorSombrero.g, h.colorSombrero.b, h.alpha);
			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)0);

			// 2. Dibujar Cuerpo (Tallo, Ojos, Bordes): Tinte neutro (1.0) para no alterar el color piel ni el negro
			glUniform4f(tintLoc, 1.0f, 1.0f, 1.0f, h.alpha);
			glDrawElements(GL_TRIANGLES, totalIndices - 12, GL_UNSIGNED_INT, (void*)(uintptr_t)(12 * sizeof(GLuint)));
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	if (hongoTex != 0) glDeleteTextures(1, &hongoTex);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}