#version 330 core
in vec4 gl_FragCoord;
 
out vec4 frag_color;
 
#define MAX_ITERATIONS 500

uniform float center_x;
uniform float center_y;
uniform float zoom;
 
int get_iterations()
{
    float real = ((gl_FragCoord.x / 720.0f - 0.5f) * zoom + center_x) * 4.0f;
    float imag = ((gl_FragCoord.y / 720.0f - 0.5f) * zoom + center_y) * 4.0f;
 
    int iterations = 0;
    float const_real = real;
    float const_imag = imag;
 
    while (iterations < MAX_ITERATIONS)
    {
        float tmp_real = real;
        real = (real * real - imag * imag) + const_real;
        imag = (2.0 * tmp_real * imag) + const_imag;
         
        float dist = real * real + imag * imag;
         
        if (dist > 4.0)
        break;
 
        ++iterations;
    }
    return iterations;
}

vec4 return_color()
{
    int iter = get_iterations();
    if (iter == MAX_ITERATIONS)
    {
        gl_FragDepth = 0.0f;
        return vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
 
    float iterations = float(iter) / MAX_ITERATIONS;    
    return vec4(0.0f, iterations, 0.0f, 1.0f);
}
 
void main()
{
    frag_color = return_color();
}