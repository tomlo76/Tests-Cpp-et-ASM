/**
 * Programme de test de quelques implémentations en assembleur d'opérations vectorielles.
 */

#include <algorithm>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>

#include "vec4.hpp"


#include "vec4_operations.hpp"
#include "vec4_operations.hxx"
#include "vec4_operations_asm.hpp"
#include "vec4_operations_asm_wrapper.hpp"




void display_evaluation(std::string title, unsigned long long int N, double elapsedTime);


struct Modes {
	bool compiler = true;
	bool serial = true;
	bool sse = true;
	bool avx = true;
};


int main(int argc, char** argv) {
	unsigned long long int N = 0; //1000000000
	vec4 v1(1.1, 2.1, 3.1, 4.1);
	vec4 v2(3.7, 6.5, 4.8, 9.3);
	Modes modes;
	
	if (argc > 1) {
		std::stringstream ss;
		std::string arg;
		bool error = false;
		
		for (int i = 1 ; i < argc ; i++) {
			ss.clear();
			ss.str(argv[i]);
			arg = ss.str();
			
			if (arg == "-n" || arg == "-N") {
				if (++i < argc) {
					ss.clear();
					ss.str(argv[i]);
					ss >> N;
					
					if (ss.fail()) {
						error = true;
						
						std::cerr << "\"" << argv[i] << "\" is not a valid number" << std::endl;
					}
				} else {
					error = true;
					
					std::cerr << "Error : number of operations is not specified" << std::endl;
				}
			} else if (arg == "--mode" || arg == "-m") {
				if (++i < argc) {
					ss.clear();
					ss.str(argv[i]);
					std::string mode = ss.str();
					std::replace(mode.begin(), mode.end(), ',', ' ');
					ss.clear();
					ss.str(mode);
					
					modes.compiler = false;
					modes.serial = false;
					modes.sse = false;
					modes.avx = false;
					
					while (ss >> mode) {
						if (mode == "compiler" || mode == "comp") {
							modes.compiler = true;
						} else if (mode == "serial") {
							modes.serial = true;
						} else if (mode == "sse") {
							modes.sse = true;
						} else if (mode == "avx") {
							modes.avx = true;
						} else if (mode == "all") {
							modes.compiler = true;
							modes.serial = true;
							modes.sse = true;
							modes.avx = true;
						} else {
							error = true;
							std::cerr << "Unknown mode \"" << mode << std::endl;
						}
					}
					
				} else {
					error = true;
					
					std::cerr << "Error : mode is not specified" << std::endl;
				}
			} else if (arg == "--operation" || arg == "-o") {
			} else if (arg == "-v1" || arg == "--v1") {
			} else if (arg == "-v2" || arg == "--v2") {
			} else {
				error = true;
				
				std::cerr << "Error : parameter \"" << arg << "\" is not valid" << std::endl;
			}
		}
		
		if (error) {
			return -1;
		}
	}


	std::cout << "===== Operation check =====" << std::endl;
	
	std::cout << " - Addition\n";
	std::cout << "        v1 = " << v1 << "\n";
	std::cout << "        v2 = " << v2 << std::endl;
	if (modes.compiler) {
		std::cout << "  Compiler version\n";
		std::cout << "   v1 + v2 = " << v1 + v2 << std::endl;
	}
	if (modes.serial) {
		std::cout << "  Serial version\n";
		std::cout << "   v1 + v2 = " << add_serial(v1, v2) << std::endl;
	}
	if (modes.sse) {
		std::cout << "  SSE version\n";
		std::cout << "   v1 + v2 = " << add_sse(v1, v2) << std::endl;
	}
	if (modes.avx) {
		std::cout << "  AVX version\n";
		std::cout << "   v1 + v2 = " << add_avx(v1, v2) << std::endl;
	}

	
	
	
	
	if (N != 0) {
		std::cout << std::endl;
		std::cout << "===== Efficiency check =====" << std::endl;
		
		std::chrono::steady_clock::time_point begin;
		std::chrono::steady_clock::time_point end;
		double elapsed;
		vec4 v __attribute__((unused));
		
		
		if (modes.compiler) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				v = add_compiler(v1, v2);
			}

			end = std::chrono::steady_clock::now();

			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;

			display_evaluation("  Compiler version", N, elapsed);
		}
		if (modes.serial) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				v = add_serial(v1, v2);
				// add_vec4_serial_asm(&v1, &v2, &v);
			}

			end = std::chrono::steady_clock::now();

			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;

			display_evaluation("  Serial version", N, elapsed);
		}
		if (modes.sse) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				v = add_sse(v1, v2);
				// add_vec4_sse_asm(&v1, &v2, &v);
			}

			end = std::chrono::steady_clock::now();

			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;

			display_evaluation("  SSE version", N, elapsed);
		}
		if (modes.avx) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N/4 ; i++) {
				__asm__ __volatile__("");
				v = add_avx(v1, v2);
				// add_vec4_avx_asm(&v1, &v2, &v);
				/*vec4* Z_ptr = &v;
				asm volatile (
					"vmovupd (%[X]), %%ymm1;\n\t"
					"vaddpd (%[Y]), %%ymm1, %%ymm0;\n\t"
					"vmovupd %%ymm0, (%[Z]);\n\t"
					: [Z] "+r" (Z_ptr)
					: [X] "r" (&v1), [Y] "r" (&v2)
					: "ymm0", "ymm1"
				);*/
			}

			end = std::chrono::steady_clock::now();

			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;

			display_evaluation("  AVX version", N, elapsed);
		}
		
		
	}

	return 0;
}





void display_evaluation(std::string title, unsigned long long int N, double elapsedTime) {
	std::cout << title << "\n";
	std::cout << "    " << N << " operations done in " << elapsedTime << " s" << "\n";
	std::cout << "    " << (N/elapsedTime)/1000000 << " million operations per second" << "\n";
	std::cout << "    Mean operation time : " << (elapsedTime/N)*1000000000 << " ns" << std::endl;
}
