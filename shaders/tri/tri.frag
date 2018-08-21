#version 330 core
out vec4 fragColor;
in vec3 vCol;
in vec2 vTex;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float blendVal;

void main()
{
	fragColor = mix(texture(texture1, vTex), texture(texture2, vTex), blendVal);
}
