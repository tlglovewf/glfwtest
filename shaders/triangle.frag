varying vec3 color;
uniform float uFade;
void main()
{
   gl_FragColor = vec4(color, uFade);
}