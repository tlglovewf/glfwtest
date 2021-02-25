uniform vec4 ambientcolor;
uniform vec4 lightcolor;
uniform vec3 lightpos;

varying vec3 fragpos;
varying vec3 color;
varying vec3 nor;

void main()
{
   vec3 norm = normalize(nor);
   vec3 lightdir = normalize(lightpos - fragpos);
   float diff = max(dot(norm,lightdir), 0.0);
   vec3 diffuse = lightcolor * diff;

   gl_FragColor = vec4(color * (ambientcolor.rgb + diffuse), 1.0);
}