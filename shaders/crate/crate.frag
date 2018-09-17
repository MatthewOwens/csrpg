#version 330 core
out vec4 fragColor;
in vec2 vTex;

uniform sampler2D texture0;

void main()
{
	fragColor = texture(texture0, vTex);
}
