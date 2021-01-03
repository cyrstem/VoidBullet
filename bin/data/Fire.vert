
#version 330

uniform mat4 modelViewProjectionMatrix;
in vec4 pos;
out vec4 verts;
in vec4 Color;



uniform float pointSize;

void main()
{
   
gl_Position = modelViewProjectionMatrix *pos;

}

