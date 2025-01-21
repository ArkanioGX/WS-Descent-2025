#pragma once
#include "Vector3.h"
#include <glm/gtc/quaternion.hpp>
class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion()
	{
		*this = Quaternion::identity;
	}

	// This directly sets the quaternion components --
	// don't use for axis/angle
	explicit Quaternion(float inX, float inY, float inZ, float inW);

	Quaternion(const glm::quat&);
	operator glm::quat() const { return glm::quat(w,x,y,z); }


	// Construct the quaternion from an axis and angle
	// It is assumed that axis is already normalized,
	// and the angle is in radians
	explicit Quaternion(const Vector3& axis, float angle);

	void set(float inX, float inY, float inZ, float inW);
	void conjugate();
	void normalize();

	float lengthSq() const
	{
		return (x * x + y * y + z * z + w * w);
	}

	float length() const
	{
		return Maths::sqrt(lengthSq());
	}

	// Normalize the provided quaternion
	static Quaternion normalize(const Quaternion& q)
	{
		Quaternion retVal = q;
		retVal.normalize();
		return retVal;
	}

	// Linear interpolation
	static Quaternion lerp(const Quaternion& a, const Quaternion& b, float f)
	{
		Quaternion retVal;
		retVal.x = Maths::lerp(a.x, b.x, f);
		retVal.y = Maths::lerp(a.y, b.y, f);
		retVal.z = Maths::lerp(a.z, b.z, f);
		retVal.w = Maths::lerp(a.w, b.w, f);
		retVal.normalize();
		return retVal;
	}

	static float dot(const Quaternion& a, const Quaternion& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	// Spherical Linear Interpolation
	static Quaternion slerp(const Quaternion& a, const Quaternion& b, float f)
	{
		float rawCosm = Quaternion::dot(a, b);

		float cosom = -rawCosm;
		if (rawCosm >= 0.0f)
		{
			cosom = rawCosm;
		}

		float scale0, scale1;

		if (cosom < 0.9999f)
		{
			const float omega = Maths::acos(cosom);
			const float invSin = 1.f / Maths::sin(omega);
			scale0 = Maths::sin((1.f - f) * omega) * invSin;
			scale1 = Maths::sin(f * omega) * invSin;
		}
		else
		{
			// Use linear interpolation if the quaternions
			// are collinear
			scale0 = 1.0f - f;
			scale1 = f;
		}

		if (rawCosm < 0.0f)
		{
			scale1 = -scale1;
		}

		Quaternion retVal;
		retVal.x = scale0 * a.x + scale1 * b.x;
		retVal.y = scale0 * a.y + scale1 * b.y;
		retVal.z = scale0 * a.z + scale1 * b.z;
		retVal.w = scale0 * a.w + scale1 * b.w;
		retVal.normalize();
		return retVal;
	}

	// Concatenate
	// Rotate by q FOLLOWED BY p
	static Quaternion concatenate(const Quaternion& q, const Quaternion& p)
	{
		Quaternion retVal;

		// Vector component is:
		// ps * qv + qs * pv + pv x qv
		Vector3 qv(q.x, q.y, q.z);
		Vector3 pv(p.x, p.y, p.z);
		Vector3 newVec = p.w * qv + q.w * pv + Vector3::cross(pv, qv);
		retVal.x = newVec.x;
		retVal.y = newVec.y;
		retVal.z = newVec.z;

		// Scalar component is:
		// ps * qs - pv . qv
		retVal.w = p.w * q.w - Vector3::dot(pv, qv);

		return retVal;
	}

	static Quaternion FromEuler(Vector3 euler) {
		return FromEuler(euler.x, euler.y, euler.z);
	}

	static Vector3 ToEulerAngles(Quaternion q) {
		Vector3 angles;

		// roll (x-axis rotation)
		double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
		double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
		angles.x = std::atan2(sinr_cosp, cosr_cosp);

		// pitch (y-axis rotation)
		double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
		double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
		angles.y = 2 * std::atan2(sinp, cosp) - glm::pi<double>() / 2;

		// yaw (z-axis rotation)
		double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
		double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
		angles.z = std::atan2(siny_cosp, cosy_cosp);

		return angles;
	}

	static Quaternion FromEuler(double roll, double pitch, double yaw) // roll (x), pitch (y), yaw (z), angles are in radians
	{
		// Abbreviations for the various angular functions

		double cr = cos(roll * 0.5);
		double sr = sin(roll * 0.5);
		double cp = cos(pitch * 0.5);
		double sp = sin(pitch * 0.5);
		double cy = cos(yaw * 0.5);
		double sy = sin(yaw * 0.5);

		Quaternion q;
		q.w = cr * cp * cy + sr * sp * sy;
		q.x = sr * cp * cy - cr * sp * sy;
		q.y = cr * sp * cy + sr * cp * sy;
		q.z = cr * cp * sy - sr * sp * cy;

		return q;
	}

	static const Quaternion identity;
};

