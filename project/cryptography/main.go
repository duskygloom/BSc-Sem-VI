package main

import (
	"cryptography/modulus"
	"fmt"
)

func main() {
	p, q := 54709, 61991
	key := 65537
	M := 123456789

	fmt.Println("Fast exponentiation:", modulus.FastExponentiation(M, key, p*q))

	fmt.Println("Fast exponentiation with prime factors:", modulus.FastPrimeFactorExponentiation(M, key, p, q))

	/* What I can do is... To use smaller but more prime numbers! But does it even matter?
	if the prime numbers themselves are small, it does not matter how big the product it,
	it will not take long to factorize it. :< */
}
