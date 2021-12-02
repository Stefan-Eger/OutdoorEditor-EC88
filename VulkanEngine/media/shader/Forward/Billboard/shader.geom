#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_GOOGLE_include_directive : enable

#include "../common_defines.glsl"


//points, lines, triangles,
layout(points) in;

layout(set = 0, binding = 0) uniform cameraUBO_t {
    cameraData_t data;
} cameraUBO;

layout(set = 3, binding = 0) uniform objectUBO_t {
    objectData_t data;
} objectUBO;


//points, line_strips, triangle_strip
layout(triangle_strip , max_vertices = 4 ) out;
layout(location = 0) out vec2 fragTexCoord;

//Maybe constants later
float size = 1.0f;

void main() {
/*
	//Testing pipeline
	for(int i=0; i<3; i++){
		gl_Position =  gl_in[i].gl_Position;
		gl_Position.x =  gl_Position.x - 1.5;
		gl_Position =  gl_Position;
		EmitVertex();
	}
	EndPrimitive();
*/
	
	vec4 pos = gl_in[0].gl_Position;
	gl_Position = (pos + vec4(-size, -size, 0.0f, 0.0f ));
	fragTexCoord = vec2( 0.0, 0.0 );
	EmitVertex();

	gl_Position = (pos + vec4(-size, size, 0.0f, 0.0f ));
	fragTexCoord = vec2( 0.0, 1.0 );
	EmitVertex();
	
	gl_Position = (pos + vec4(size, -size, 0.0f, 0.0f ));
	fragTexCoord = vec2( 1.0, 0.0 );
	EmitVertex();

	gl_Position = (pos + vec4(size, size, 0.0f, 0.0f ));
	fragTexCoord = vec2( 1.0, 1.0 );
	EmitVertex();
	
	EndPrimitive();
	
}