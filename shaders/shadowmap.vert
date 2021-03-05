//平行光
uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjMatrix;
uniform mat4 uLightSpaceMatrix;
uniform vec3 lightdir;

attribute vec3 aVtx;
attribute vec3 aClr;
attribute vec3 aNor;

varying vec3 fragpos;
varying vec3 color;
varying vec3 nor;
varying vec3 vlightdir;
varying vec4 fraglightpos; //顶点在光源坐标系下坐标

void main()
{
   mat4 vmMtx = uViewMatrix * uModelMatrix;
   vec4 wdpos = vmMtx * vec4(aVtx, 1.0);
   
   fragpos = wdpos;
   color = aClr ;
   //法线变换到世界坐标系中,并消除缩放给法线带来的影响
   //nor = mat3(transpose(inverse(vmMtx))) * aNor;
   //小技巧 改变相乘顺序 即 x 转置  等价上方
   nor = aNor * mat3(inverse(vmMtx));
   vlightdir = mat3(uViewMatrix) * lightdir;
   gl_Position = uProjMatrix  *  wdpos;
   fraglightpos = uLightSpaceMatrix * uModelMatrix * vec4(aVtx,1.0);
}