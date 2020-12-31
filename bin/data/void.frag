#version 430
precision highp float;

#define TWO_PI 6.283185307179586476925286766559f

out vec4 outputColor;

uniform sampler2D tex0;
uniform float time;


in vec4 verts;
in vec3 normal;
in vec3 pos;

in vec2 v_texcoord;


void main(){
 /* Normalize verts from the vertex shader */
    vec3 normal = normalize(verts.xyz);
    vec3 imgColor = texture(tex0,v_texcoord).rgb /3.5;

     outputColor = vec4(imgColor, 1.0);
}
