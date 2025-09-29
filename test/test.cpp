#include <iostream>
#include <random>
#include <chrono>
#include <climits>
#include <cmath>

#include "primeFactorization.h"

bool randomUint64Test(unsigned testSize = 10, bool loggingEnabled = true);

int main() {

	//factor() tests
	std::cout << "factor():\n";
	if(!randomUint64Test(1000, false)) {
		std::cout << "FAIL!\n";
		return -1;
	}
	//add deterministic test for edge cases

	//isPrime() tests
	//...todo...

	//findDivisor() tests
	//...todo...

	return 0;
}

bool randomUint64Test(unsigned testSize, bool loggingEnabled) {

	std::cout << "Testing the factorization of " << testSize << " random numbers in the range [2^32, 2^64): ";
	if(loggingEnabled) std::cout << '\n'; //here just for formatting purposes

	const uint64_t POW_2_32 = 4294967296;
	std::random_device randomDevice;
	std::mt19937_64 mersenneTwister(randomDevice());
	std::uniform_int_distribution<uint64_t> uniformDistribution(POW_2_32, ULLONG_MAX);
 
 	unsigned totalTimeTaken = 0;
 	unsigned maxTimeTaken = 0;
 	unsigned minTimeTaken = -1; //:)
	for(unsigned i = 0; i < testSize; i++) {

		uint64_t n = uniformDistribution(mersenneTwister);

		auto startTime = std::chrono::high_resolution_clock::now();

		std::map<uint64_t, unsigned> divisors = primes::factor(n);

		auto endTime = std::chrono::high_resolution_clock::now();
		auto timeElapsed = (endTime - startTime) / std::chrono::milliseconds(1);
		totalTimeTaken += timeElapsed;
		if(timeElapsed > maxTimeTaken) maxTimeTaken = timeElapsed;
		if(timeElapsed < minTimeTaken) minTimeTaken = timeElapsed;

		uint64_t res = 1;
		for(auto divisor : divisors) {
			if(!primes::isPrime(divisor.first)) { //isPrime() requires stricter testing
				std::cout << "ERROR!\n\tDivisor " << divisor.first << " for number " << n << " is not prime!\n";
				return false;
			}
			res *= std::powl(divisor.first, divisor.second);
		}
		if(res != n) {
			std::cout << "ERROR!\n\tCalculated result for " << n << " does not match. " << res << " != " << n << '\n';
			return false;
		}

		if(loggingEnabled) {
			std::cout << '\t' << n << " : ";
			for(auto divisor : divisors) {
				if(divisor.second > 1) std::cout << divisor.first << "^" << divisor.second << ' ';
				else std::cout << divisor.first << ' ';
			}
			std::cout << "(Calculated in " << timeElapsed << "ms)\n";			
		}
	}

	//if logging enabled print more detailed statistics about min, max and average
	//...todo...

	//passed
	std::cout << "OK\n";
	std::cout << "\tTotal calculation time: " << totalTimeTaken << "ms\n";
	std::cout << "\tAverage time per number: " << totalTimeTaken/testSize << "ms (min: " << minTimeTaken << "ms, max: " << maxTimeTaken << "ms)\n";

	return true;
}