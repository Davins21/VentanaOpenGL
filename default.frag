#version 450 core

out vec4 FragColor;

in vec3 color;      // Viene de los vértices
in vec2 texCoord;   // Coordenadas UV

uniform sampler2D tex0;
uniform vec4 uColorTint; // Pasa el color del sombrero o vec4(1,1,1,alpha) según la parte

void main()
{
    vec4 texColor = texture(tex0, texCoord);

    // Multiplicamos el color del vértice por el tinte enviado desde C++ y la textura
    vec3 colorFinal = color * uColorTint.rgb * texColor.rgb;

    // Alpha final combinando la textura con la transparencia del uniforme
    float alphaFinal = texColor.a * uColorTint.a;

    FragColor = vec4(colorFinal, alphaFinal);
}