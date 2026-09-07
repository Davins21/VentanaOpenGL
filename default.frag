#version 450 core
out vec4 FragColor;

in vec3 color;

uniform vec4 uColorTint; // Tinte enviado desde C++ (vec3(1.0) para mantener color original)

void main()
{
// Si el tinte RGB está cerca de (1, 1, 1), usa el color original del vértice
    if (distance(uColorTint.rgb, vec3(1.0)) < 0.01) 
    {
        FragColor = vec4(color, uColorTint.a); // Usa color de vértice con el Alpha indicado
    } 
    else 
    {
        FragColor = uColorTint; // Usa el color del tinte completo con su Alpha
    }
}