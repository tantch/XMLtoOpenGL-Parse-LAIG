uniform float time;
uniform float angle;
uniform float wind;
varying vec4 coords;

const float PI = 3.14159265358979;

void main() {
vec4 newCoord = vec4(gl_Vertex.x, gl_Vertex.y + (sin(angle + gl_Vertex.x*PI*(0.4*wind) + time*(0.001*wind) )*0.2*wind), gl_Vertex.z, 1.0);
gl_Position = gl_ModelViewProjectionMatrix * newCoord;
gl_TexCoord[0] = gl_MultiTexCoord0;

coords = newCoord;
}