#include <iostream>

#include "vec4.hpp"



int main(int, char**) {
	vec4 v1 = {1, 2, 3, 4};
	vec4 v2 = {8, 9, 10, 11};
	double lambda = 2.7;
	
	std::cout << "v1 = " << v1 << std::endl;
	std::cout << "v2 = " << v2 << std::endl;
	std::cout << "lambda = " << lambda << std::endl;
	std::cout << std::endl;
	std::cout << "v1 + v2 = " << v1 + v2 << std::endl;
	std::cout << "v2 - v1 = " << v2 - v1 << std::endl;
	std::cout << "lambda*v1 = " << lambda*v1 << std::endl;
	std::cout << "v2*lambda = " << v2*lambda << std::endl;
	std::cout << "v1/lambda = " << v1/lambda << std::endl;
	std::cout << std::endl;
	std::cout << "<v1 | v2> = " << scalar(v1, v2) << std::endl;
	std::cout << "v1 · v2 = " << dot(v1, v2) << std::endl;
	std::cout << "v1 ⊙ v2 = " << hadamard(v1, v2) << std::endl;
	std::cout << "v1 ○ v2 = " << schur(v1, v2) << std::endl;
	
	
	return 0;
}