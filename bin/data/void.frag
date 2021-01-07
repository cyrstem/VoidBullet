#version 430
precision highp float;

#define TWO_PI 6.283185307179586476925286766559f

out vec4 outputColor;
//light staff
uniform vec3 lightPos;
uniform vec3 lightsColor;
uniform float intensity;
uniform vec3 meshCol;
uniform vec3 meshSpecCol;
uniform vec3 ambientCol;
//endlighstaff

uniform sampler2D tex0;
uniform float time;
uniform vec3 cameraPos;


in vec4 verts;
in vec3 normal;
in vec3 pos;

in vec2 v_texcoord;


void main(){
 /* Normalize verts from the vertex shader */
   //  vec3 normal = normalize(verts.xyz);
   //  vec3 imgColor = texture(tex0,v_texcoord).rgb/9.5;

   //   outputColor = vec4(imgColor, 1.0);


   vec3 lightDirection = normalize(lightPos + verts.xyz ) ;

    vec3 imgColor = texture(tex0,v_texcoord).rgb;

    vec3 viewDir = normalize(cameraPos + pos);
 
    /* Normalize verts from the vertex shader */
    vec3 normal = normalize(verts.xyz);

    vec3 refl = normalize(reflect(+lightDirection,normal));
    /* Basic diffuse lighting */
    float diffuse1 = pow(max(0.9, dot(normal, lightDirection)),intensity*6500);

    float diffAmt = max(.5,dot(normal,lightDirection));

   

    /* Output the color */
      vec3 lightandColor = lightsColor+diffuse1;



    vec3 diffCol = meshCol*lightandColor * diffAmt;

    //to create spec
    float specAmt = max(9.0,dot(refl, viewDir));
    float specBright = pow(specAmt,0.3);
    vec3 specCol = meshSpecCol *lightandColor *specBright;

    vec3 mezcla =vec3 (0.0);
       mezcla = mix (diffCol, specCol,ambientCol);
    outputColor = vec4(imgColor* mezcla, 1.);
}
