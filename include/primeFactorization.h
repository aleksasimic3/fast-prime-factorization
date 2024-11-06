#ifndef _PRIME_FACTORIZATION_H_
#define _PRIME_FACTORIZATION_H_

#include <cstdint>
#include <map>
#include <utility>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <numeric>

#include <iostream>


namespace primes {

//finds the prime factorization of n
//returns a map in the form map[factor][exponent]
std::map<uint64_t, unsigned> factor(uint64_t n);

//generate prime umbers up to n using the sieve of erathostenes
bool* generatePrimes(uint64_t n);

//check if number is prime using the miller rabin primality test
//add optional divisor
bool isPrime(uint64_t n, uint64_t* possibleDivisor=nullptr);

//returns a pair of two divisors of n using the pollard's rho algorithm
std::pair<uint64_t, uint64_t> divisors(uint64_t n);
//uint64_t findDivisor(uint64_t n); //returns non trivial divisor of n, expects n to be composite, also add skipPrimeCheck flag

}

#endif
