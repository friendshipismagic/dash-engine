/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#version 130
#extension GL_ARB_uniform_buffer_object : require

#define MAX_NUM_LIGHTS 8

precision highp float; // needed only for version 1.30

struct dash_LightSourcesParameters {
	vec4 ambient; // Acli
	vec4 diffuse; // Dcli
	vec4 specular; // Scli
	vec4 position; // Ppli
	vec3 spotDirection; // Sdli
	float spotExponent; // Srli
	float spotCutoff; // Crli, range: [0.0,90.0], 180.0
	float spotCosCutoff; // cos(Crli), range: [1.0,0.0] -1.0
	float constantAttenuation; // K0
	float linearAttenuation; // K1
	float quadraticAttenuation;// K2
	int enabled;
	float padding_NOUSE[2]; // See above for more details
};

layout (std140) uniform dash_LightSources {
	dash_LightSourcesParameters[MAX_NUM_LIGHTS] lights;
};

in vec3 ex_Position;
in vec3 ex_Normals;

out vec4 out_Color;

void main(void)
{
	out_Color = lights[1].specular;
}
