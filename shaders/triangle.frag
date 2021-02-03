varying vec3 color;
uniform float fade;
void main()
{
   gl_FragColor = vec4(color * fade, 0.0);
}