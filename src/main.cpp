#include <map>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <chrono>

#include "primeFactorization.h"

using primes::factor;

int main(int argc, char* argv[]) {

	auto startTime = std::chrono::high_resolution_clock::now();

	uint64_t n;
	std::map<uint64_t, unsigned> factors;

	int i = 1;
	do {
		n = argc > 1 ? std::strtoull(argv[i], nullptr, 10) : ULLONG_MAX;

		factors = factor(n);

		std::cout << '\n' << n << " : ";
			for(auto p : factors) {
			std::cout << p.first;
			if(p.second > 1) std::cout << '^' << p.second;
			std::cout << ' ';
		}

		factors.clear();
		i++;
	} while(i < argc);

	auto endTime = std::chrono::high_resolution_clock::now();
	auto timeElapsed = endTime - startTime;
	std::cout << "\n\nCalculated in: " << (timeElapsed / std::chrono::milliseconds(1)) << "ms\n";

	return 0;
}