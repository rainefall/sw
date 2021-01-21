#pragma once
#ifndef MATH_H
#define MATH_H

namespace SouthwestEngine {
	class Math {
	private:
		Math();
	public:
		static double Lerp(double v0, double v1, double t);
		static double Cubic(double v[4], double t);
		static double MoveToward(double p_from, double p_to, double p_delta);
		static float MoveToward(float p_from, float p_to, float p_delta);
		// TODO - Add Ogre::Vector3 overloads
	};
}

#endif