uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjMatrix;
attribute vec3 aVtx;
attribute vec3 aClr;
attribute vec3 aNor;

varying vec3 fragpos;
varying vec3 color;
varying vec3 nor;

void main()
{
   mat4 vmMtx = uModelMatrix;
   vec4 wdpos = vmMtx * vec4(aVtx, 1.0);
   
   fragpos = wdpos;
   color = aClr ;
   //法线变换到世界坐标系中,并消除缩放给法线带来的影响
   //nor = mat3(transpose(inverse(vmMtx))) * aNor;
   //小技巧 改变相乘顺序 即 x 转置  等价上方
   nor = aNor * mat3(inverse(vmMtx));

   gl_Position = uProjMatrix * uViewMatrix *  wdpos;
}