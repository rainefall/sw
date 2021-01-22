#pragma once
#ifndef MATH_H
#define MATH_H

#include <OGRE/OgreVector.h>
#include <cmath>

namespace SouthwestEngine {
	class Math {
	private:
		Math();
	public:
		static double Lerp(double v0, double v1, double t);
		static double Cubic(double v[4], double t);
		static float Distance(const Ogre::Vector3& p_from, const Ogre::Vector3& p_to);
		static double MoveToward(double p_from, double p_to, double p_delta);
		static float MoveToward(float p_from, float p_to, float p_delta);
		static Ogre::Vector3 MoveToward(const Ogre::Vector3& p_from, const Ogre::Vector3& p_to, const float p_delta);
		static Ogre::Vector3 Abs(const Ogre::Vector3& vec3);
	};

	constexpr float CMP_EPSILON{ 0.00001f };
}

#endif