uniform vec4 ambientcolor;
uniform vec4 lightcolor;
uniform float uStrength;
uniform float uSpStrength;

varying vec3 fragpos;
varying vec3 color;
varying vec3 nor;
varying vec3 vlightdir;

void main()
{
   vec3 norm = normalize(nor);
   //计算视线方向
   vec3 viewdir  = normalize(vec3(0.0) - fragpos);
   //reflect计算反射方向  @1要求方向指向光源, 所以要取反 @2法线向量
   vec3 reflectdir = reflect(-vlightdir, norm);
   //计算镜面分量, 32 为镜面指数 2的倍数次幂  数值越大反光强度越大 光点效果越明显
   float spec = 0.0;
   
   float diff = max(dot(norm,vlightdir), 0.0);
   if( diff != 0.0)
   {
      spec = pow(max(dot(viewdir, reflectdir), 0.0), 16);
   }
   //根据镜面强度 光照颜色 计算镜面颜色值
   vec3 specular = uSpStrength * spec * lightcolor;
   vec3 diffuse = lightcolor * diff;
   //根据phone算法  根据物体颜色 计算最终光照颜色值
   gl_FragColor = vec4(color * (ambientcolor.rgb + diffuse + specular), 1.0);
}