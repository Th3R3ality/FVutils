#pragma once


// https://github.com/Marcelektro/MCP-919/blob/main/src/minecraft/net/minecraft/util/Matrix4f.java
// For readability & maybe security purposes.

struct matrix
{
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;
};