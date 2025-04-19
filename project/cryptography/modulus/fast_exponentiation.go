package modulus

/* Computes a^b mod n. */
func FastExponentiation(a, b, n int) int {
	result := 1
	p := a

	for b != 0 {
		if b%2 == 1 {
			result = (result * p) % n
		}
		p = (p * p) % n
		b /= 2
	}

	return Mod(result, n)
}

/* Computes a^b mod p*q. */
func FastPrimeFactorExponentiation(a, b, p, q int) int {
	vp := FastExponentiation(a, b%(p-1), p)
	vq := FastExponentiation(a, b%(q-1), q)

	xp := q * ModularInverse(q, p)
	xq := p * ModularInverse(p, q)

	return (vp*xp + vq*xq) % (p * q)
}
