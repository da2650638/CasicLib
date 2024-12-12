#include "CasicMatrixTransform.h"

#include <algorithm>

namespace Casic
{
namespace Math
{
	CASICLIB_API Matrix4 Ortho(float left, float right, float bottom, float top, float near, float far)
	{
		Matrix4 mat;
		float rl = right - left;
		float tb = top - bottom;
		float fn = far - near;
		mat.Data.m0 = 2.0f / rl;
		mat.Data.m5 = 2.0f / tb;
		mat.Data.m10 = -2.0f / fn;
		mat.Data.m12 = -(right + left) / rl;
		mat.Data.m13 = -(top + bottom) / tb;
		mat.Data.m14 = -(far + near) / fn;
		mat.Data.m15 = 1.0f;
		return mat;
	}

	Matrix4 Perspective(float left, float right, float bottom, float top, float near, float far)
	{
		float rl = right - left;
		float tb = top - bottom;
		float fn = far - near;

		Matrix4 result;
		result.Data.m0 = 2.0f * near / rl;
		result.Data.m5 = 2.0f * near / tb;
		result.Data.m8 = (left + right) / rl;
		result.Data.m9 = (top + bottom) / tb;
		result.Data.m10 = -(near + far) / fn;
		result.Data.m11 = -1.0f;
		result.Data.m14 = -2.0f * near * far / fn;

		return result;
	}

	Matrix4 Perspective(float fovy, float aspect, float near, float far)
	{
		float rad = degreesToRadians(fovy);
		float halfRad = rad / 2.0f;
		float top = std::tanf(halfRad);
		float width = top * aspect;
		Matrix4 result;
		// NOTE: 这里既然要使用1.0作为近平面距离，那你还传near有个jb用？
		near = 1.0f;
		result.Data.m0 = near / width;
		result.Data.m5 = near / top;
		result.Data.m10 = -(near + far) / (far - near);
		result.Data.m11 = -1.0f;
		result.Data.m14 = -2.0f * far * near / (far - near);
		return result;
	}

	CASICLIB_API Matrix4 LookAt(Vector3 eye, Vector3 target, Vector3 up)
	{
		// Calculate the orthonormal basis vectors for the camera coordinate system
		Vector3 v = Normalize(eye - target);    // z-axis (camera back direction)
		Vector3 r = Normalize(Cross(up, v));   // x-axis (camera right direction)
		Vector3 u = Cross(v, r);               // y-axis (camera up direction)

		Matrix4 mat;
		mat.Data.m0 = r.x;
		mat.Data.m1 = u.x;
		mat.Data.m2 = v.x;
		mat.Data.m3 = 0.0f;
		mat.Data.m4 = r.y;
		mat.Data.m5 = u.y;
		mat.Data.m6 = v.y;
		mat.Data.m7 = 0.0f;
		mat.Data.m8 = r.z;
		mat.Data.m9 = u.z;
		mat.Data.m10 = v.z;
		mat.Data.m11 = 0.0f;
		mat.Data.m12 = -Dot(eye, r);
		mat.Data.m13 = -Dot(eye, u);
		mat.Data.m14 = -Dot(eye, v);
		mat.Data.m15 = 1.0f;

		return mat;
	}

	Matrix4 Translate(Matrix4 mat, Vector3 vec)
	{
		// TODO: 矩阵顺序可能有问题，目前是mat * matTranslate(代表平移矩阵）
		Matrix4 result(mat);
		result.Data.m12 = vec.x * mat.Data.m0 + vec.y * mat.Data.m4 + vec.z * mat.Data.m8 + mat.Data.m12;
		result.Data.m13 = vec.x * mat.Data.m1 + vec.y * mat.Data.m5 + vec.z * mat.Data.m9 + mat.Data.m13;
		result.Data.m14 = vec.x * mat.Data.m2 + vec.y * mat.Data.m6 + vec.z * mat.Data.m10 + mat.Data.m14;
		result.Data.m15 = vec.x * mat.Data.m3 + vec.y * mat.Data.m7 + vec.z * mat.Data.m11 + mat.Data.m15;

		return result;
	}

	Matrix4 Translate(Vector3 vec)
	{
		Matrix4 result = Matrix4::Identity();
		result.Data.m12 = vec.x;
		result.Data.m13 = vec.y;
		result.Data.m14 = vec.z;

		return result;
	}

	Matrix4 Scale(Matrix4 mat, Vector3 scale)
	{
		// TODO: 矩阵顺序可能有问题，目前是mat * matScale(代表缩放矩阵）
		Matrix4 result(mat);
		
		mat.Data.m0 *= scale.x;
		mat.Data.m1 *= scale.x;
		mat.Data.m2 *= scale.x;
		mat.Data.m3 *= scale.x;

		mat.Data.m4 *= scale.y;
		mat.Data.m5 *= scale.y;
		mat.Data.m6 *= scale.y;
		mat.Data.m7 *= scale.y;

		mat.Data.m8 *= scale.z;
		mat.Data.m9 *= scale.z;
		mat.Data.m10 *= scale.z;
		mat.Data.m11 *= scale.z;

		return result;
	}

	CASICLIB_API Matrix4 Scale(Vector3 scale)
	{
		Matrix4 result = Matrix4::Identity();
		result.Data.m0 = scale.x;
		result.Data.m5 = scale.y;
		result.Data.m10 = scale.z;

		return result;
	}

	Matrix4 Rotate(Matrix4 mat, float angle, Vector3 axis)
	{
		// TODO: 矩阵顺序可能有问题，目前是mat * matRotate(代表旋转）
		Vector3 r = Normalize(axis);
		float rad = degreesToRadians(angle);
		float c = std::cos(rad);
		float s = std::sin(rad);

		Matrix4 rotate;
		rotate.Data.m0 = (1 - c) * r.x * r.x + c;
		rotate.Data.m1 = s * r.z + (1 - c) * r.x * r.y;
		rotate.Data.m2 = -s * r.y + (1 - c) * r.x * r.z;
		rotate.Data.m3 = 0.0f;
		rotate.Data.m4 = -s * r.z + (1 - c) * r.x * r.y;
		rotate.Data.m5 = (1 - c) * r.y * r.y + c;
		rotate.Data.m6 = s * r.x + (1 - c) * r.y * r.z;
		rotate.Data.m7 = 0.0f;
		rotate.Data.m8 = s * r.y + (1 - c) * r.x * r.z;
		rotate.Data.m9 = -s * r.x + (1 - c) * r.y * r.z;
		rotate.Data.m10 = (1 - c) * r.z * r.z + c;
		rotate.Data.m11 = 0.0f;
		rotate.Data.m12 = 0.0f;
		rotate.Data.m13 = 0.0f;
		rotate.Data.m14 = 0.0f;
		rotate.Data.m15 = 1.0f;

		return mat * rotate;
	}

	Matrix4 Rotate(float angle, Vector3 axis)
	{
		Vector3 r = Normalize(axis);
		float rad = degreesToRadians(angle);
		float c = std::cos(rad);
		float s = std::sin(rad);

		Matrix4 result;
		result.Data.m0 = (1-c) * r.x * r.x + c;
		result.Data.m1 = s * r.z + (1-c)* r.x * r.y;
		result.Data.m2 = -s * r.y + (1-c)* r.x * r.z;
		result.Data.m3 = 0.0f;
		result.Data.m4 = -s * r.z + (1-c) * r.x * r.y;
		result.Data.m5 = (1-c)* r.y * r.y + c;
		result.Data.m6 = s * r.x + (1-c) * r.y * r.z;
		result.Data.m7 = 0.0f;
		result.Data.m8 = s * r.y + (1-c) * r.x * r.z;
		result.Data.m9 = -s * r.x + (1-c) * r.y * r.z;
		result.Data.m10 = (1-c) * r.z * r.z + c;
		result.Data.m11 = 0.0f;
		result.Data.m12 = 0.0f;
		result.Data.m13 = 0.0f;
		result.Data.m14 = 0.0f;
		result.Data.m15 = 1.0f;

		return result;
	}
}
}