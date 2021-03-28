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





struct Modes {
	bool operation = false;
	bool compiler = true;
	bool fpu = false;
	bool serial = true;
	bool sse = true;
	bool avx = true;
};

struct Functions {
	bool function = true;
	bool preproc = true;
	bool asmcode = false;
	bool wrapper = false;
};

struct Operations {
	bool vec4add = false;
};




int arguments(int argc, char** argv, Modes& modes, Functions& functions, Operations& operations, unsigned long long int* N);
void evaluate_vec4_add(Modes& modes, Functions& functions, vec4 v1, vec4 v2, unsigned long long int N);
void display_evaluation(unsigned long long int N, double elapsedTime);




int main(int argc, char** argv) {
	unsigned long long int N = 0; //1000000000
	vec4 v1(1.1, 2.1, 3.1, 4.1);
	vec4 v2(3.7, 6.5, 4.8, 9.3);
	Modes modes;
	Functions functions;
	Operations operations;
	
	{
		int status = arguments(argc, argv, modes, functions, operations, &N);
		
		if (status == -1) {
			return -1;
		} else if (status == 1) {
			return 0;
		}
	}

	
	if (operations.vec4add) {
		evaluate_vec4_add(modes, functions, v1, v2, N);
	}
	
	return 0;
}




int arguments(int argc, char** argv, Modes& modes, Functions& functions, Operations& operations, unsigned long long int* N) {
	if (argc > 1) {
		std::stringstream ss;
		std::string arg;
		bool error = false;
		
		for (int i = 1 ; i < argc ; i++) {
			ss.clear();
			ss.str(argv[i]);
			arg = ss.str();
			
			if (arg == "--help" || arg == "-h") {
				std::cout << "Usage : " << argv[0] << " [options]" << "\n";
				std::cout << "Options :" << "\n";
				std::cout << "  -h, --help                      Print help message" << "\n";
				std::cout << "  -f, --function FUNCTION         Specify kind of functions to evaluate, use with 'list' to list all available functions" << "\n";
				std::cout << "  -m, --mode MODE                 Specify type of implementation to evaluate, use with 'list' to list all available modes" << "\n";
				std::cout << "  -n, -N                          Number of iteration in the evaluation loop" << "\n";
				std::cout << "  -o, --operation OPERATION       Specify operations to evaluate, use with 'list' to list all available operations" << "\n";
				std::cout << "  -v1, -v2 VECTOR                 Specify components of vector v1 or v2" << "\n";                       
				
				return 1;
			} else if (arg == "-n" || arg == "-N") {
				if (++i < argc) {
					ss.clear();
					ss.str(argv[i]);
					ss >> (*N);
					
					if (ss.fail()) {
						error = true;
						
						std::cerr << "Error : \"" << argv[i] << "\" is not a valid number" << std::endl;
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
						if (mode == "list") {
							std::cout << "Available modes : all, operation [op], compiler [comp], fpu, serial, sse, avx" << std::endl;
							
							return 1;
						} else if (mode == "operation" || mode == "op") {
							modes.operation = true;
						} else if (mode == "compiler" || mode == "comp") {
							modes.compiler = true;
						} else if (mode == "fpu") {
							modes.fpu = true;
						} else if (mode == "serial") {
							modes.serial = true;
						} else if (mode == "sse") {
							modes.sse = true;
						} else if (mode == "avx") {
							modes.avx = true;
						} else if (mode == "all") {
							modes.operation = true;
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
					
					std::cerr << "Error : mode is not specified" << "\""  << std::endl;
				}
			} else if (arg == "--function" || arg == "-f") {
				if (++i < argc) {
					ss.clear();
					ss.str(argv[i]);
					std::string function = ss.str();
					std::replace(function.begin(), function.end(), ',', ' ');
					ss.clear();
					ss.str(function);
					
					functions.function = false;
					functions.preproc = false;
					functions.asmcode = false;
					functions.wrapper = false;
					
					while (ss >> function) {
						if (function == "list") {
							std::cout << "Available functions : all, function [func], preprocessor [pp], asm, wrapper" << std::endl;
							
							return 1;
						} else if (function == "function" || function == "func") {
							functions.function = true;
						} else if (function == "preprocessor" || function == "pp") {
							functions.preproc = true;
						} else if (function == "asm") {
							functions.asmcode = true;
						} else if (function == "wrapper") {
							functions.wrapper = true;
						} else if (function == "all") {
							functions.function = true;
							functions.preproc = true;
							functions.asmcode = true;
							functions.wrapper = true;
						} else {
							error = true;
							std::cerr << "Unknown function \"" << function << "\"" << std::endl;
						}
					}
					
				} else {
					error = true;
					
					std::cerr << "Error : function is not specified" << std::endl;
				}
			} else if (arg == "--operation" || arg == "-o") {
				if (++i < argc) {
					ss.clear();
					ss.str(argv[i]);
					std::string operation = ss.str();
					std::replace(operation.begin(), operation.end(), ',', ' ');
					ss.clear();
					ss.str(operation);
					
					operations.vec4add = false;
					
					while (ss >> operation) {
						if (operation == "list") {
							std::cout << "Available operations : all, vec4add" << std::endl;
							
							return 1;
						} else if (operation == "vec4add") {
							operations.vec4add = true;
						} else if (operation == "all") {
							operations.vec4add = true;
						} else {
							error = true;
							std::cerr << "Unknown operation \"" << operation << "\"" << std::endl;
						}
					}
					
				} else {
					error = true;
					
					std::cerr << "Error : operation is not specified" << std::endl;
				}
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
	
	return 0;
}


void evaluate_vec4_add(Modes& modes, Functions& functions, vec4 v1, vec4 v2, unsigned long long int N) {
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	double elapsed;
	vec4 v __attribute__((unused));
	
	
	std::cout << "===== Evaluating vec4 addition =====" << std::endl;
	std::cout << "       v1 = " << v1 << "\n";
	std::cout << "       v2 = " << v2 << "\n";
	std::cout << "  v1 + v2 = " << v1 + v2 << "\n";
	std::cout << std::endl;
	
	if (modes.operation) {
		std::cout << "Operation version" << "\n";
		std::cout << "  v1 + v2 = " << v1 + v2 << std::endl;
		
		if (N > 0) {
			begin = std::chrono::steady_clock::now();
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				v = v1 + v2;
			}
			end = std::chrono::steady_clock::now();
			
			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;
			display_evaluation(N, elapsed);
			std::cout << std::endl;
		}
	}
	
	if (modes.compiler) {
		std::cout << "Compiler version" << "\n";
		std::cout << "  v1 + v2 = " << add_compiler(v1, v2) << std::endl;
		
		if (N > 0) {
			begin = std::chrono::steady_clock::now();
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				v = add_compiler(v1, v2);
			}
			end = std::chrono::steady_clock::now();
			
			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;
			display_evaluation(N, elapsed);
			std::cout << std::endl;
		}
	}
	
	if (modes.fpu && functions.preproc) {
		std::cout << "FPU (preprocessor implementation)" << "\n";
		add_vec4_fpu_pp(v1, v2, v);
		std::cout << "  v1 + v2 = " << v << std::endl;
		
		if (N > 0) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				add_vec4_fpu_pp(v1, v2, v);
			}
			end = std::chrono::steady_clock::now();
			
			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;
			display_evaluation(N, elapsed);
			std::cout << std::endl;
		}
	}
	
	/*************
	 * SERIAL
	 *************/
	if (modes.serial && functions.function) {
		std::cout << "Serial (function implementation)" << "\n";
		std::cout << "  v1 + v2 = " << add_serial(v1, v2) << std::endl;
		
		if (N > 0) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				v = add_serial(v1, v2);
			}
			end = std::chrono::steady_clock::now();
			
			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;
			display_evaluation(N, elapsed);
			std::cout << std::endl;
		}
	}
	
	if (modes.serial && functions.preproc) {
		std::cout << "Serial (preprocessor implementation)" << "\n";
		add_vec4_serial_pp(v1, v2, v);
		std::cout << "  v1 + v2 = " << v << std::endl;
		
		if (N > 0) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				add_vec4_serial_pp(v1, v2, v);
			}
			end = std::chrono::steady_clock::now();
			
			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;
			display_evaluation(N, elapsed);
			std::cout << std::endl;
		}
	}
	
	if (modes.serial && functions.asmcode) {
		std::cout << "Serial (assembly implementation)" << "\n";
		add_vec4_serial_asm(&v1, &v2, &v);
		std::cout << "  v1 + v2 = " << v << std::endl;
		
		if (N > 0) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				add_vec4_serial_asm(&v1, &v2, &v);
			}
			end = std::chrono::steady_clock::now();
			
			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;
			display_evaluation(N, elapsed);
			std::cout << std::endl;
		}
	}
	
	if (modes.serial && functions.wrapper) {
		std::cout << "Serial (wrapped implementation)" << "\n";
		std::cout << "  v1 + v2 = " << add_vec4_serial_asm_wrapper(v1, v2) << std::endl;
		
		if (N > 0) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				v = add_vec4_serial_asm_wrapper(v1, v2);
			}
			end = std::chrono::steady_clock::now();
			
			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;
			display_evaluation(N, elapsed);
			std::cout << std::endl;
		}
	}
	
	
	/*************
	 * SSE
	 *************/
	if (modes.sse && functions.function) {
		std::cout << "SSE (function implementation)" << "\n";
		std::cout << "  v1 + v2 = " << add_sse(v1, v2) << std::endl;
		
		if (N > 0) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				v = add_sse(v1, v2);
			}
			end = std::chrono::steady_clock::now();
			
			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;
			display_evaluation(N, elapsed);
			std::cout << std::endl;
		}
	}
	
	if (modes.sse && functions.preproc) {
		std::cout << "SSE (preprocessor implementation)" << "\n";
		add_vec4_sse_pp(v1, v2, v);
		std::cout << "  v1 + v2 = " << v << std::endl;
		
		if (N > 0) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				add_vec4_sse_pp(v1, v2, v);
			}
			end = std::chrono::steady_clock::now();
			
			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;
			display_evaluation(N, elapsed);
			std::cout << std::endl;
		}
	}
	
	if (modes.sse && functions.asmcode) {
		std::cout << "SSE (assembly implementation)" << "\n";
		add_vec4_sse_asm(&v1, &v2, &v);
		std::cout << "  v1 + v2 = " << v << std::endl;
		
		if (N > 0) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				add_vec4_sse_asm(&v1, &v2, &v);
			}
			end = std::chrono::steady_clock::now();
			
			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;
			display_evaluation(N, elapsed);
			std::cout << std::endl;
		}
	}
	
	if (modes.sse && functions.wrapper) {
		std::cout << "SSE (wrapped implementation)" << "\n";
		std::cout << "  v1 + v2 = " << add_vec4_sse_asm_wrapper(v1, v2) << std::endl;
		
		if (N > 0) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				v = add_vec4_sse_asm_wrapper(v1, v2);
			}
			end = std::chrono::steady_clock::now();
			
			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;
			display_evaluation(N, elapsed);
			std::cout << std::endl;
		}
	}
	
	/*************
	 * AVX
	 *************/
	if (modes.avx && functions.function) {
		std::cout << "AVX (function implementation)" << "\n";
		std::cout << "  v1 + v2 = " << add_avx(v1, v2) << std::endl;
		
		if (N > 0) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				v = add_avx(v1, v2);
			}
			end = std::chrono::steady_clock::now();
			
			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;
			display_evaluation(N, elapsed);
			std::cout << std::endl;
		}
	}
	
	if (modes.avx && functions.preproc) {
		std::cout << "AVX (preprocessor implementation)" << "\n";
		add_vec4_avx_pp(v1, v2, v);
		std::cout << "  v1 + v2 = " << v << std::endl;
		
		if (N > 0) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				add_vec4_avx_pp(v1, v2, v);
			}
			end = std::chrono::steady_clock::now();
			
			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;
			display_evaluation(N, elapsed);
			std::cout << std::endl;
		}
	}
	
	if (modes.avx && functions.asmcode) {
		std::cout << "AVX (assembly implementation)" << "\n";
		add_vec4_avx_asm(&v1, &v2, &v);
		std::cout << "  v1 + v2 = " << v << std::endl;
		
		if (N > 0) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				add_vec4_avx_asm(&v1, &v2, &v);
			}
			end = std::chrono::steady_clock::now();
			
			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;
			display_evaluation(N, elapsed);
			std::cout << std::endl;
		}
	}
	
	if (modes.avx && functions.wrapper) {
		std::cout << "AVX (wrapped implementation)" << "\n";
		std::cout << "  v1 + v2 = " << add_vec4_avx_asm_wrapper(v1, v2) << std::endl;
		
		if (N > 0) {
			begin = std::chrono::steady_clock::now();
			
			for (unsigned long long int i = 0 ; i < N ; i++) {
				__asm__ __volatile__("");
				v = add_vec4_avx_asm_wrapper(v1, v2);
			}
			end = std::chrono::steady_clock::now();
			
			elapsed = ((double) std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()) / 1000.0;
			display_evaluation(N, elapsed);
			std::cout << std::endl;
		}
	}
}


void display_evaluation(unsigned long long int N, double elapsedTime) {
	std::cout << "    " << N << " operations done in " << elapsedTime << " s" << "\n";
	std::cout << "    " << (N/elapsedTime)/1000000 << " million operations per second" << "\n";
	std::cout << "    Mean operation time : " << (elapsedTime/N)*1000000000 << " ns" << std::endl;
}
