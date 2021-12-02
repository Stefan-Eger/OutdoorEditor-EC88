#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_GOOGLE_include_directive : enable

#include "../common_defines.glsl"

#define RESOURCEARRAYLENGTH 16

layout(set = 0, binding = 0) uniform cameraUBO_t {
    cameraData_t data;
} cameraUBO;

layout(set = 1, binding = 0) uniform lightUBO_t {
    lightData_t data;
} lightUBO;

layout(set = 2, binding = 0) uniform sampler2D shadowMap[NUM_SHADOW_CASCADE];

layout(set = 3, binding = 0) uniform objectUBO_t {
    objectData_t data;
} objectUBO;

layout(set = 4, binding = 0) uniform sampler2D texSamplerArray[RESOURCEARRAYLENGTH];



layout(location = 0) in vec2 fragTexCoord;
layout(location = 0) out vec4 outColor;


void main() {
	//parameters
    vec4 texParam   = objectUBO.data.param;
    vec2 texCoord   = (fragTexCoord + texParam.zw)*texParam.xy;
    ivec4 iparam    = objectUBO.data.iparam;
    uint resIdx     = iparam.x % RESOURCEARRAYLENGTH;

    //colors
    vec4 result = texture( texSamplerArray[resIdx], texCoord ).rgba;
	
	if(result.a < 0.1)
        discard;
		
    outColor = vec4(result.r, result.g, result.b, result.a );
}








