uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjMatrix;
attribute vec3 aVtx;

void main()
{
   gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * vec4(aVtx,1.0);
}