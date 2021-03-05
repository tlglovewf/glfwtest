
uniform sampler2D uTexCoord0;
varying vec2 oUv;

float near_plane = 1.0;
float far_plane = 7.0;
// required when using a perspective projection matrix
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));	
}

void main()
{
   float depth = texture(uTexCoord0, oUv).r;
   gl_FragColor = vec4(vec3(depth), 1.0);
}