uniform vec4 ambientcolor;
uniform vec4 lightcolor;
varying vec3 color;
varying vec3 nor;
void main()
{
   gl_FragColor = vec4(color * ambientcolor.rgb, 1.0);
}