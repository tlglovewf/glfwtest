uniform mat4 uMvp;
attribute vec3 aVtx;

void main()
{
   gl_Position = uMvp * vec4(aVtx,1.0);
}