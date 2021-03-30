#ifndef __VEC4_HPP__
#define __VEC4_HPP__

#define dot(X, Y) scalar(X, Y)
#define schur(X, Y) hadamard(X, Y)


#include <iostream>


class vec4 {
	private:
		double m_vec[4];

	public:
		vec4(void);
		vec4(const double vec[4]);
		vec4(const double x, const double y, const double z, const double t);
		
		double const& operator[](unsigned int i) const;
		
		friend vec4 operator+(const vec4& X, const vec4& Y);
		friend vec4 operator-(const vec4& X, const vec4& Y);
		friend vec4 operator*(const double lambda, const vec4& X);
		friend vec4 operator*(const vec4& X, const double lambda);
		friend vec4 operator/(const vec4& X, const double lambda);
		friend double scalar(const vec4& X, const vec4& Y);
		friend vec4 hadamard(const vec4& X, const vec4& Y);
		friend double norm1(const vec4& X);
		friend double norm2(const vec4& X);
		friend double norminf(const vec4& X);
		friend double normp(const vec4& X, const double p);

		friend std::ostream& operator<<(std::ostream& os, const vec4& vec);
};


#endif//__vec4_HPP__
