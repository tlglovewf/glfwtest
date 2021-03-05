uniform vec4 ambientcolor;
uniform vec4 lightcolor;
uniform float uStrength;
uniform float uSpStrength;
uniform sampler2D uTexCoord0;

varying vec3 fragpos;
varying vec3 color;
varying vec3 nor;
varying vec3 vlightdir;
varying vec4 fraglightpos; //顶点在光源坐标系下坐标

//阴影计算
float ShadowCalculation(vec4 lfragpos)
{
    // 透视剔除
    vec3 projCoords = lfragpos.xyz / lfragpos.w;
    //-> [0, 1]
    projCoords = projCoords * 0.5 + 0.5;

    //从深度图中获取最近点深度(即在光源视角物体的深度值)
    float closetDepth = texture(uTexCoord0, projCoords.xy).r;
    // 获取当前片元在光源视角下深度
    float currentDepth = projCoords.z;

    //由于分辨率的影响,会导致多个点寻址同一个点(阴影失真) 加偏移消除影响
    float bias = 0.005;
    float shadow = currentDepth - bias > closetDepth ? 1.0 : 0.0;

    return shadow;
}

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

   float shadow = ShadowCalculation(fraglightpos);

   //根据phone算法  根据物体颜色 计算最终光照颜色值
   gl_FragColor = vec4(color * (ambientcolor.rgb + (1.0 - shadow) * (diffuse + specular)), 1.0);
}