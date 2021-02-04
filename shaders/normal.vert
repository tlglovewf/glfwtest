uniform mat4 uMvp;
attribute vec3 aVtx;
attribute vec3 aClr;
varying vec3 color;
void main()
{
   gl_Position = uMvp * vec4(aVtx,1.0);
   color = aClr;
}