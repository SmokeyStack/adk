#pragma once

namespace adk {
	class Vector3 {
	public:
		Vector3() : x(0), y(0), z(0) {}
		Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
		~Vector3() {}
		double GetX() const { return x; }
		double GetY() const { return y; }
		double GetZ() const { return z; }
		std::tuple<double, double, double> Get() const { return { x, y, z }; }
	private:
		double x;
		double y;
		double z;
	};
} // namespace adk