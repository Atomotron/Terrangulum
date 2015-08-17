#version 410 core
in vec3 f_normal;
in vec3 f_color;


out vec4 color;


void main()
{   
    color.rgb = f_color + f_color*clamp(dot(vec3(0,1,1),normalize(f_normal)),0,1);
    color.a = 1.0;
}