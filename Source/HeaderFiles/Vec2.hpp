#ifndef PACMAN_HEADERFILES_VEC2_HPP_
#define PACMAN_HEADERFILES_VEC2_HPP_

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <cmath>

template <class T> class Vec2 {
public:
	T x, y;

	Vec2() : x(0), y(0){}
	Vec2(T x, T y) : x(x), y(y){}
	Vec2(const Vec2& v) : x(v.x), y(v.y){}

	Vec2& operator=(const Vec2& v){
		x = v.x;
		y = v.y;
		return *this;
	}

	Vec2 operator+(const Vec2& v) const{
		return Vec2(x + v.x, y + v.y);
	}
	Vec2 operator-(const Vec2& v) const{
		return Vec2(x - v.x, y - v.y);
	}
	Vec2 operator*(const Vec2& v) const{
		return Vec2(x * v.x, y * v.y);
	}
	Vec2 operator/(const Vec2& v) const {
		return Vec2(x / v.x, y / v.y);
	}

	Vec2& operator+=(const Vec2& v){
		x += v.x;
		y += v.y;
		return *this;
	}
	Vec2& operator-=(const Vec2& v){
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vec2& operator*=(const float v){
		x = x * v,
		y = y * v;
		return *this;
	}

	Vec2 operator+(const T& s) const{
		return Vec2(x + s, y + s);
	}
	Vec2 operator-(const T& s) const{
		return Vec2(x - s, y - s);
	}
	Vec2 operator*(const T& s) const{
		return Vec2(x * s, y * s);
	}
	Vec2 operator/(const T& s)  const{
		return Vec2(x / s, y / s);
	}

	bool operator==(const Vec2& v) const{
		return ( (x == v.x)&&(y == v.y) );
	}

	void set(T x, T y){
		this->x = x;
		this->y = y;
	}

	void rotate(double deg){
		double theta = deg / 180.0 * M_PI;
		double c = cos(theta);
		double s = sin(theta);
		double tx = x * c - y * s;
		double ty = x * s + y * c;
		x = tx;
		y = ty;
	}

	Vec2& normalize(){
		if (length() == 0) return *this;
		*this *= (1.0 / length());
		return *this;
	}

	float dist(Vec2 v) const{
		Vec2 d(v.x - x, v.y - y);
		return d.length();
	}
	float length() const{
		return std::sqrt(x * x + y * y);
	}
	void truncate(double length) {
		double angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}

	Vec2 ortho() const{
		return Vec2(y, -x);
	}

	static float dot(Vec2 v1, Vec2 v2){
		return v1.x * v2.x + v1.y * v2.y;
	}
	static float cross(Vec2 v1, Vec2 v2){
		return (v1.x * v2.y) - (v1.y * v2.x);
	}

	const float cross(Vec2 v2) const{
		return (x * v2.y) - (y * v2.x);
	}

	const float dot(Vec2 v2) const{
		return dot(*this, v2);
	}

	const Vec2 perpCCW() const{
		return Vec2(-y, x);
	}

	const Vec2 perpCW() const{
		return Vec2(y, -x);
	}

};

typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;

template <class T> const T min2(const T val1, const T val2){
	return val1 < val2 ? val1 : val2;
}

template <class T> const T max2(const T val1, const T val2){
	return val1 > val2 ? val1 : val2;
}

template <class T> float sign(const T val) {
	return val > 0 ? 1 : val < 0 ? -1 : 0;
}

template <class T> const T clamp(const T x, const T min, const T max){
	if (x < min)
		return min;
	else if (x > max)
		return max;
	return x;
}

#endif