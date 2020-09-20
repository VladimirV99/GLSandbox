#version 330
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Color;
out vec3 Normal;
out vec2 TexCoord;
 
void main() 
{ 
   FragPos = vec3(model * vec4(aPosition, 1.0));
   Normal = mat3(transpose(inverse(model))) * aNormal;
   Color = aColor;
   TexCoord = aTexCoord;
   gl_Position = projection * view * model * vec4(aPosition, 1.0);
}