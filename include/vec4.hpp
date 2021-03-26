#ifndef __VEC4_HPP__
#define __VEC4_HPP__


#include <iostream>


class vec4 {
	private:
		double m_vec[4];

	public:
		vec4(void);
		vec4(const double vec[4]);
		vec4(const double x, const double y, const double z, const double t);

		friend vec4 add_com(const vec4& X, const vec4& Y);
		friend vec4 add_ser(const vec4& X, const vec4& Y);
		friend vec4 add_sse(const vec4& X, const vec4& Y);
		friend vec4 add_avx(const vec4& X, const vec4& Y);
		
		friend vec4 operator+(const vec4& X, const vec4& Y);

		friend std::ostream& operator<<(std::ostream& os, const vec4& vec);
};




#endif//__vec4_HPP__
