
uniform sampler2D uTexCoord0;
varying vec2 oUv;
void main()
{
   gl_FragColor = texture(uTexCoord0, oUv);
}