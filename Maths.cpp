#include "Maths.h"

using namespace SouthwestEngine;

double Math::Lerp(double v0, double v1, double t) {
	return (1.0f - t) * v0 + t * v1; // there might be a better version of this(?)
}

double Math::Cubic(double v[4], double t) {
	return v[1] + 0.5 * t * (v[2] - v[0] + t * (2.0 * v[0] - 5.0 * v[1] + 4.0 * v[2] - v[3] + t * (3.0 * (v[1] - v[2]) + v[3] - v[0])));
}

float Math::Distance(const Ogre::Vector3& p_from, const Ogre::Vector3& p_to)
{
	return (p_to - p_from).length();
}

double Math::MoveToward(double p_from, double p_to, double p_delta) {
	return std::abs(p_to - p_from) <= p_delta ? p_to : p_from + (p_to - p_from) * p_delta;
}

float Math::MoveToward(float p_from, float p_to, float p_delta) {
	return std::abs(p_to - p_from) <= p_delta ? p_to : p_from + (p_to - p_from) * p_delta;
}

Ogre::Vector3 Math::MoveToward(const Ogre::Vector3& p_from, const Ogre::Vector3& p_to, const float p_delta) {
	Ogre::Vector3 distance = p_to - p_from;
	float length = distance.length();
	return length <= p_delta || length < CMP_EPSILON ? p_to : p_from + distance / length * p_delta;
}

Ogre::Vector3 Math::Abs(const Ogre::Vector3& vec3)
{
	return Ogre::Vector3(std::abs(vec3.x), std::abs(vec3.y), std::abs(vec3.z));
}