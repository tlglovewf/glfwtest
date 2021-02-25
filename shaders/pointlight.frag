uniform vec4 ambientcolor;
uniform vec4 lightcolor;

varying vec3 fragpos;
varying vec3 color;
varying vec3 nor;
varying vec3 vlightpos;

void main()
{
   vec3 norm = normalize(nor);
   vec3 lightdir = normalize(vlightpos - fragpos);
   float diff = max(dot(norm,lightdir), 0.0);
   vec3 diffuse = lightcolor * diff;

   gl_FragColor = vec4(color * (ambientcolor.rgb + diffuse), 1.0);
}