#version 450 core

out vec4 FragColor;

in vec3 color;      // Color que viene del Vertex Shader (aColor)
in vec2 texCoord;   // Coordenadas de textura (aTex)

uniform sampler2D tex0;
uniform vec4 uColorTint;

void main()
{
    // Carga el píxel de la textura
    vec4 texColor = texture(tex0, texCoord);

    // Si la textura tiene zonas transparentes (alpha < 0.1), descartar
    if (texColor.a < 0.1)
        discard;

    // Multiplica el color base del vértice * el tinte uniforme * el color de la textura
    FragColor = vec4(color, 1.0) * uColorTint * texColor;
}