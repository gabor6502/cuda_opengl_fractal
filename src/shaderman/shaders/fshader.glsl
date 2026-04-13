#version 400 core

out vec4 FragColour;

void main()
{
	FragColour = vec4(gl_FragCoord.xyz/800, 1.0);
}