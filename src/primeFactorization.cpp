#include "primeFactorization.h"

//helper funcitons
namespace {
unsigned __int128 __powmod(unsigned __int128 x, unsigned __int128 p, uint64_t n) {
	
	unsigned __int128 res = 1;

	//exponentiation by squaring
	while(p) {
		if((p & 1) == 1) res = (x * res) % n;

		p >>= 1;
		x = (x * x) % n;
	}

	return res;
}

unsigned __int128 __g(unsigned __int128 x, unsigned __int128 c, uint64_t n) {
	return (x*x + c) % n;
}
}

std::map<uint64_t, unsigned> primes::factor(uint64_t n) {

	if(n == 0) return std::map<uint64_t, unsigned>{{0, 1}}; //this is not formaly correct, every non zero number divides 0 perfectly
	if(n == 1) return std::map<uint64_t, unsigned>{{1, 1}};

	std::map<uint64_t, unsigned> factors;

	uint64_t upperBound = std::cbrt(n) + 1;
	bool* primes = generatePrimes(upperBound);

	for(uint64_t i = 2; i <= upperBound && i <= n; i++) {
		if(primes[i] == true) {
			while(n % i == 0) {
				factors[i]++;
				n /= i;
			}
		}
	}

	if(n > 1) {
		if(isPrime(n)) {
			factors[n]++;
		}
		else {
			std::pair<uint64_t, uint64_t> remainingFactors = divisors(n); //replace with findDivisor(n)
			factors[remainingFactors.first]++;
			factors[remainingFactors.second]++;
		}
	}

	std::free(primes);
	return factors;
}

bool* primes::generatePrimes(uint64_t n) {

	bool* primes = (bool*)std::malloc((n+1) * sizeof(bool));
	if(primes == NULL) return NULL;
	std::memset(primes, true, (n+1) * sizeof(bool));

	for(uint64_t i = 2; i*i <= n; i++) {
		if(primes[i] == true) {
			for(uint64_t j = i*i; j <= n; j += i) {
				primes[j] = false;
			}
		}
	}

	return primes;
}

bool primes::isPrime(uint64_t n, uint64_t* possibleDivisor) {
	
	const std::vector<unsigned> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}; //no pseudo primes for these bases for n<2^64

	if(n <= 1) return false;
	for(auto prime : bases) {
		if(n == prime) return true;
		if(n % prime == 0) {
			if(possibleDivisor != nullptr) *possibleDivisor = prime;
			return false;
		}
	}

	//n - 1 = s^2 * d
	uint64_t s = 0;
	uint64_t d = n - 1;
	while(d % 2 == 0) {
		s++;
		d /= 2;
	}

	uint64_t x, y;
	for(auto a : bases) {
		x = __powmod(a, d, n);

		for(uint64_t i = 0; i < s; i++) {
			y = __powmod(x, 2, n);
			if(y == 1 && x != 1 && x != n-1) return false; //divisor found
			x = y;
		}

		if(y != 1) return false;
	}

	return true;
}

std::pair<uint64_t, uint64_t> primes::divisors(uint64_t n) {

	if(n % 2 == 0) return std::pair<uint64_t, uint64_t>(2, n/2); 
	
	uint64_t x = 2;
	uint64_t y = x;
	uint64_t d = 1;
	uint64_t c = 1;

	while(d == 1) {
		x = __g(x, c, n);
		y = __g(__g(y, c, n), c, n);
		d = std::gcd((x>y)?x-y:y-x, n);

		if(d == n) {
			x = 2;
			y = x;
			d = 1;
			c++;
		}
	}

	return std::pair<uint64_t, uint64_t>(d, n/d);
}