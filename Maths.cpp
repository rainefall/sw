#include "Maths.h"

using namespace SouthwestEngine;

double Math::Lerp(double v0, double v1, double t) {
	return (1.0f - t) * v0 + t * v1; // there might be a better version of this(?)
}

double Math::Cubic(double v[4], double t) {
	return v[1] + 0.5 * t * (v[2] - v[0] + t * (2.0 * v[0] - 5.0 * v[1] + 4.0 * v[2] - v[3] + t * (3.0 * (v[1] - v[2]) + v[3] - v[0])));
}