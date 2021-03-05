uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjMatrix;
attribute vec3 aVtx;
attribute vec3 aClr;
varying vec3 color;
void main()
{
   vec4 ofrag = uProjMatrix * uViewMatrix * uModelMatrix * vec4(aVtx,1.0);
   float value = ofrag.z / ofrag.w;
   color = vec3(value);
   gl_Position = ofrag;
}