#version 460 core 
            
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;
uniform mat4 u_MVP;
            
void main()
{
    gl_Position = u_MVP * position;
    v_texCoord = texCoord;
};