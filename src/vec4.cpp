#include "vec4.hpp"

#include <cstdio>
#include <cstdint>

vec4::vec4(void) : m_vec{0.0, 0.0, 0.0, 0.0} {}


vec4::vec4(const double vec[4]) : m_vec{vec[0], vec[1], vec[2], vec[3]} {}


vec4::vec4(const double x, const double y, const double z, const double t) : m_vec{x, y, z, t} {}

double const& vec4::operator[](unsigned int i) const {
	return m_vec[i];
}

/**
 * Addition of two vectors
 * 
 * No use of specific assembly code, let the compiler compile
 */
vec4 operator+(const vec4& X, const vec4& Y) {
	return { X.m_vec[0] + Y.m_vec[0], X.m_vec[1] + Y.m_vec[1], X.m_vec[2] + Y.m_vec[2], X.m_vec[3] + Y.m_vec[3] };
}

vec4 operator-(const vec4& X, const vec4& Y) {
	return { X.m_vec[0] - Y.m_vec[0], X.m_vec[1] - Y.m_vec[1], X.m_vec[2] - Y.m_vec[2], X.m_vec[3] - Y.m_vec[3] };
}

vec4 operator*(const double lambda, const vec4& X) {
	return { lambda*X.m_vec[0], lambda*X.m_vec[1], lambda*X.m_vec[2], lambda*X.m_vec[3] };
}

vec4 operator*(const vec4& X, const double lambda) {
	return { lambda*X.m_vec[0], lambda*X.m_vec[1], lambda*X.m_vec[2], lambda*X.m_vec[3] };
}

vec4 operator/(const vec4& X, const double lambda) {
	return { X.m_vec[0]/lambda, X.m_vec[1]/lambda, X.m_vec[2]/lambda, X.m_vec[3]/lambda };
}

double scalar(const vec4& X, const vec4& Y) {
	return X.m_vec[0]*Y.m_vec[0] + X.m_vec[1]*Y.m_vec[1] + X.m_vec[2]*Y.m_vec[2] + X.m_vec[3]*Y.m_vec[3];
}

vec4 hadamard(const vec4& X, const vec4& Y) {
	return { X.m_vec[0]*Y.m_vec[0], X.m_vec[1]*Y.m_vec[1], X.m_vec[2]*Y.m_vec[2], X.m_vec[3]*Y.m_vec[3] };
}

/*double norm1(const vec4& X) {
	
}

double norm2(const vec4& X) {
	
}

double norminf(const vec4& X) {
	
}

double normp(const vec4& X, const double p) {
	
}*/

std::ostream& operator<<(std::ostream& os, const vec4& vec) {
	return os << "(" << vec.m_vec[0] << " ; " << vec.m_vec[1] << " ; " << vec.m_vec[2] << " ; " << vec.m_vec[3] << ")";
}
