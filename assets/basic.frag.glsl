#version 330
 
in vec3 FragPos;  
in vec3 Color;
in vec3 Normal;
in vec2 TexCoord;
  
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;

out vec4 FragColor; 

// layout (binding=0) // from 4.20
uniform sampler2D tex;
 
void main() {
  // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);

    // Blinn-Phong
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 16.0);
    // Phong
    // vec3 reflectDir = reflect(-lightDir, norm);  
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 specular = specularStrength * spec * lightColor;  
    
    vec3 objectColor = mix(texture(tex, TexCoord), vec4(Color, 1.0), 0.5).xyz;
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);

  // FragColor = mix(texture(tex, TexCoord), vec4(Color, 1.0), 0.5);
}
