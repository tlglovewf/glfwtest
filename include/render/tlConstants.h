#ifndef _TL_CONSTANT_H_
#define _TL_CONSTANT_H_


/*  uniform variable */
#define UNIFORM_MVP      "uMvp"
#define UNIFORM_MODMTX   "uModelMatrix"
#define UNIFORM_VIEWMTX  "uViewMatrix"
#define UNIFORM_PRJMTX   "uProjMatrix"

#define UNIFORM_FADE     "uFade"
#define UNIFORM_STRENGTH "uStrength"        //衰减强度
#define UNIFORM_SPSTRGTH "uSpStrength"      //镜面光照强度

#define UNIFORM_AMBCLR   "ambientcolor"     //环境光照
#define UNIFORM_LIGHTCLR "lightcolor"       
#define UNIFORM_LIGHTPOS "lightpos"
#define UNIFORM_LIGHTDIR "lightdir"

#define ATTR_VERTEX      "aVtx"
#define ATTR_COLOR       "aClr"
#define ATTR_NORMAL      "aNor"

#define ATTR_TEXTURE0    "aUv0"
#define ATTR_TEXTURE1    "aUv1"
#define ATTR_TEXTURE2    "aUv2"

#endif