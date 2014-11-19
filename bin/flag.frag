uniform sampler2D baseTexture;

varying vec4 coords;

const float shaderColor = 1.2;

void main(){

gl_FragColor = texture2D(baseTexture, gl_TexCoord[0].st)+ coords.y*(shaderColor,shaderColor,shaderColor,1.0);

}