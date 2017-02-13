#pragma once

#include "flops.h"
#include "vec2.h"


namespace base
{
	union vec3
	{
		float v[3];
		struct { vec2 xy; };
		struct { float x, y, z; };

		float &operator[](size_t idx) { return v[idx]; }
		float operator[](size_t idx) const { return v[idx]; }

		vec3 &operator+=(const vec3 &o) { return *this = vec3{ x + o.x, y + o.y, z + o.z }; }

		vec3 &operator-=(const vec3 &o) { return *this = vec3{ x - o.x, y - o.y, z - o.z }; }
		vec3 &operator*=(const float s) { return *this = vec3{ x * s, y * s, z * s }; }
		vec3 &operator/=(const float s) { return *this = vec3{ x / s, y / s, z / s }; }

		vec3 operator-()			const { return vec3{ -x,-y,-z }; }

		float magnitude()			const { return sqrt(x*x + y*y + z*z); }
		vec3 normal()			    const { auto m = magnitude();  return{ x / m, y / m, z / m }; }


		vec3() : x(0), y(0), z(0) {}
		vec3(float a) :x(a), y(a), z(a) {}
		vec3(float a, float b) :x(a), y(b), z(0) {}
		vec3(float a[]) :x(a[0]), y(a[1]), z(a[2]) {}
		vec3(float a, float b, float c) : x(a), y(b), z(c) {}
		vec3(const vec2 &a, float c = 0) : x(a.x), y(a.y), z(c) {}



		static vec3 left() { return vec3{ -1, 0, 0 }; }
		static vec3 up() { return vec3{ 0, 1, 0 }; }
		static vec3 right() { return vec3{ 1, 0, 0 }; }
		static vec3 down() { return vec3{ 0,-1, 0 }; }
		static vec3 forward() { return vec3{ 0, 0, 1 }; }
		static vec3 backward() { return vec3{ 0, 0,-1 }; }
	};



	inline vec3 operator+(vec3 a, const vec3 &o) { return a += o; }
	inline vec3 operator-(vec3 a, const vec3 &o) { return a -= o; }
	inline vec3 operator*(vec3 a, float s) { return a *= s; }
	inline vec3 operator/(vec3 a, float s) { return a /= s; }

	inline vec3 operator*(float s, vec3 a) { return a *= s; }


	inline float dot(const vec3 &a, const vec3 &b) { return a.x*b.x + a.y*b.y + a.z*b.z; }



	inline float dist(const vec3 &a, const vec3 &b) { return (a - b).magnitude(); }

	inline vec3 project(const vec3 &a, const vec3 &b) { auto d = b.normal(); return d * dot(a, d); }
	inline vec3 reflect(const vec3 &a, const vec3 &b) { 2 * project(a, b) - a; }

	inline vec3 min(const vec3 &a, const vec3 &b) { return vec3{ min(a.xy, b.xy), flops::min(a.z,b.z) }; }
	inline vec3 max(const vec3 &a, const vec3 &b) { return vec3{ max(a.xy, b.xy), flops::max(a.z,b.z) }; }
	inline vec3 clamp(const vec3 &v, const vec3& n, const vec3 &x) { return min(x, max(v, n)); }

	inline vec3 snap(const vec3 &v, const vec3& n, const vec3 &x) { return vec3{ snap(v.xy, n.xy, x.xy), flops::snap(v.z,n.z,x.z) }; }
	inline vec3 lerp(const vec3 &s, const vec3 &e, float t) { return vec3{ lerp(s.xy,e.xy,t), flops::lerp(s.y,e.y,t) }; }

	inline bool operator==(const vec3 &a, const vec3 &b) { return a.xy == b.xy && flops::fequals(a.z, b.z); }
	inline bool operator!=(const vec3 &a, const vec3 &b) { return !(a == b); }

	inline vec3 cross(const vec3 &a, const vec3 &b) { return vec3{ a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x }; }
}