uniform mat4 uMvp;
attribute vec3 aVtx;
attribute vec3 aClr;
attribute vec3 aNor;
varying vec3 color;
varying vec3 nor;
void main()
{
   gl_Position = uMvp * vec4(aVtx,1.0);
   color = aClr ;
   nor = aNor;
}