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
	return {X.m_vec[0] + Y.m_vec[0], X.m_vec[1] + Y.m_vec[1], X.m_vec[2] + Y.m_vec[2], X.m_vec[3] + Y.m_vec[3]};
}

std::ostream& operator<<(std::ostream& os, const vec4& vec) {
	return os << "(" << vec.m_vec[0] << " ; " << vec.m_vec[1] << " ; " << vec.m_vec[2] << " ; " << vec.m_vec[3] << ")";
}
