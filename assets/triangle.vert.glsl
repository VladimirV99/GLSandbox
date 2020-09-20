#version 330
layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec3 aColor;

out vec3 Color;
 
void main() 
{ 
   gl_Position = vec4(aPosition, 1.0);
   Color = aColor;
}