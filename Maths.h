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
	};
}

#endif