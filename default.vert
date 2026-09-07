#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

// Las tres matrices de transformación
uniform mat4 uMVP;

void main()
{
    // El orden de multiplicación de derecha a izquierda es CRUCIAL
        gl_Position = uMVP * vec4(aPos, 1.0);
        color = aColor;;
}