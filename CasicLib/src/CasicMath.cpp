#include "CasicMath.h"
#include <numbers>

namespace Casic
{
namespace Math
{
	bool Equals(float f1, float f2, float epsilon)
	{
		return std::fabs(f1 - f2) < epsilon;
	}

	float degreesToRadians(float degree)
	{
#ifdef CASIC_USE_STDNUMBERS
		return std::numbers::pi_v<float> / 180.f * degree;
#else
		return static_cast<float>(CASIC_PI) / 180.f * degree;
#endif
	}

	CASICLIB_API float radiansToDegrees(float radians)
	{
#ifdef CASIC_USE_STDNUMBERS
		return radians * (180.f / std::numbers::pi_v<float>);
#else
		return radians * (180.f / static_cast<float>(CASIC_PI));
#endif
	}

	Vector3::Vector3(const Vector4& other)
		: x(other.x), y(other.y), z(other.z)
	{
	}
	Vector3& Vector3::RotateAroundXAxis(float angle)
	{
		float alpha = degreesToRadians(angle);
		float sinAlpha = std::sin(alpha);
		float cosAlpha = std::cos(alpha);
		float newY = cosAlpha * y - sinAlpha * z;
		float newZ = sinAlpha * y + cosAlpha * z;
		y = newY;
		z = newZ;
		return *this;
	}

	Vector3& Vector3::RotateAroundYAxis(float angle)
	{
		float alpha = degreesToRadians(angle);
		float sinAlpha = std::sin(alpha);
		float cosAlpha = std::cos(alpha);
		float newX = cosAlpha * x + sinAlpha * z;
		float newZ = -sinAlpha * x + cosAlpha * z;
		x = newX;
		z = newZ;
		return *this;
	}

	Vector3& Vector3::RotateAroundZAxis(float angle)
	{
		float alpha = degreesToRadians(angle);
		float sinAlpha = std::sin(alpha);
		float cosAlpha = std::cos(alpha);
		float newX = cosAlpha * x - sinAlpha * y;
		float newY = sinAlpha * x + cosAlpha * y;
		x = newX;
		y = newY;
		return *this;
	}

	Vector3& Vector3::RotateAroundAxis(float angle, Vector3 axis)
	{
		// NOTE：推导过程见https://songho.ca/opengl/gl_rotate.html
		Vector3 p = *this;
		Vector3 r = axis.Normalize();
		Vector3 pOnr = Dot(p, r) * r;
		Vector3 rCrossp = Cross(r, p);
		float alpha = degreesToRadians(angle);	//旋转角度
		float sinAlpha = std::sin(alpha), cosAlpha = std::cos(alpha);
		*this = (1.0f - cosAlpha) * pOnr + cosAlpha * p + sinAlpha * rCrossp;
		return *this;
	}
}
}