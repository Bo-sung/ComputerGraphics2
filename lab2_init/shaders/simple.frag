#version 450

in vec3 fcolor;

out vec4 fragColor; // 픽셀의 색상을 의미. 왜 vec4? .R,G,B,A
void main()
{
	fragColor = vec4(fcolor,1.0);
}