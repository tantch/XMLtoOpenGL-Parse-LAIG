uniform sampler2D baseTexture;

varying vec4 coords;


const float sh = 0.6;
void main(){

gl_FragColor = texture2D(baseTexture, gl_TexCoord[0].st)+ (coords.y)*(sh,sh,sh,1.0);

}