#version 410 core

layout(location=0) in vec3 position_modelspace;
layout(location=1) in vec3 vert_color;
layout(location=2) in vec3 normal_modelspace;

uniform mat4 MVP;

out vec3 f_normal;
out vec3 f_color;

void main()
{
    gl_Position = MVP * vec4(position_modelspace, 1);	
    f_normal = normal_modelspace; //rotation of the model via M-matrix will not change its lighting - that's OK for our purposes here.
	f_color = vert_color;
}