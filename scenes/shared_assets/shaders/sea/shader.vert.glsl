#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 texture_uv;

out struct fragment_data
{
    vec4 position;
    vec4 normal;
    vec4 color;
    vec2 texture_uv;
} fragment;


// model transformation
uniform float time = 1.0;					     // user defined time


// view transform
uniform mat4 view;
// perspective matrix
uniform mat4 perspective;



void main()
{
    vec4 position_transformed = position;
    float abs = (position_transformed[0] + position_transformed[1])/80 + 0.5;
    position_transformed[2] = 0.2f*cos(3.1415926 * (16*abs+time/2.0f)) + position_transformed[2];

    fragment.position = position_transformed;
    fragment.normal = vec4(0.2*3.1415926*sin(3.1415926 * (16*abs+time/2.0f)), 0.2f*3.1415926*sin(3.1415926 * (16*abs+time/2.0f)), 2.0, 1.0)/3 + normal;
    //fragment.color = vec4(0.0, 0.5, 0.7,0.8f + 0.1f*cos(3.1415926 * (16*abs+time/2.0f)));
    fragment.color = color;
    fragment.texture_uv = texture_uv;


    gl_Position = perspective * view * position_transformed;
}
