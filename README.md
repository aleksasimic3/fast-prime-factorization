# fast-prime-factorization
Fast prime factorization implemented in C++

The algorithm:  
  -Trial division with generated prime numbers up to cube root of n  
  -If n==1 then we have found the prime factorization of n  
  -If remaining n>1:  
    -Check if n is prime using the Miller Rabin primality test  
    -If n is prime we have found the prime factorization of n  
    -If n is composite then it must have exactly two prime factors  
    -We can find them using the Pollard Rho algorithm
