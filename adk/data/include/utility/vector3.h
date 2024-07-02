#pragma once

#include <tuple>

namespace adk {
	class Vector3 {
	public:
		Vector3() : x_(0), y_(0), z_(0) {}
		Vector3(double x, double y, double z) : x_(x), y_(y), z_(z) {}
		~Vector3() {}
		double GetX() const { return x_; }
		double GetY() const { return y_; }
		double GetZ() const { return z_; }
		std::tuple<double, double, double> Get() const { return { x_, y_, z_ }; }
		bool operator==(const Vector3& other) const { return x_ == other.x_ && y_ == other.y_ && z_ == other.z_; }
		bool operator!=(const Vector3& other) const { return !(*this == other); }
	private:
		double x_;
		double y_;
		double z_;
	};
} // namespace adk