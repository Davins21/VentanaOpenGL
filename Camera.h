#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	// Atributos de transformación
	glm::vec3 Position;
	glm::vec3 Orientation;
	glm::vec3 Up;

	// Dimensiones de la ventana
	int width;
	int height;

	// Configuración de movimiento y sensibilidad
	float speed;
	float sensitivity;

	// Variables para el control de rotación del mouse
	float yaw;
	float pitch;
	bool firstMouse;
	float lastX;
	float lastY;

	// Constructor
	Camera(int width, int height, glm::vec3 position);

	// Métodos de matrices
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float FOVdeg, float nearPlane, float farPlane);

	// Métodos de control de entradas
	void ProcessInputs(GLFWwindow* window, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
};

#endif