#version 430
uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec4 vNormal;
in vec2 texcoord;


out vec2 v_texcoord;

/* Send a vec to the fragment shader */
out vec4 verts;
out vec3 normal;
out vec3 pos;

uniform float time;
void main()
{
    /* Store position */
    vec4 pos = normalize (position) ;
    //normal = normalize(vNormal);

    v_texcoord = texcoord;

    /* Output the new position */
    gl_Position = modelViewProjectionMatrix * pos;

    /* Send some values to the fragment shader */
    verts = pos;

}