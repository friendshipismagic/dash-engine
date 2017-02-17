/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#version 130

in  vec3 in_Position;
in  vec3 in_Normals;

out vec3 ex_Position;
out vec3 ex_Normals;

void main(void)
{
	ex_Position   = in_Position;
	ex_Normals    = in_Normals;

	gl_Position   = vec4(in_Position/5, 1.0f);
}
