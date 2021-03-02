
uniform mat4 uMvp;
attribute vec3 aVtx;
attribute vec2 aUv0;

varying vec2 oUv;
void main()
{
   gl_Position = uMvp * vec4(aVtx,1.0);
   oUv = aUv0;
}