package modulus

/*
Returns a, b and gcd(a, b) such that
ax + by = gcd(a, b).
*/
func ExtendedEuclidean(x, y int) (int, int, int) {
	x1, x2 := 1, 0
	y1, y2 := 0, 1

	for y != 0 {
		q := x / y
		x1, x2 = x2, x1-q*x2
		y1, y2 = y2, y1-q*y2
		x, y = y, x%y
	}

	return x1, y1, x
}

/* Returns 1/p mod n. */
func ModularInverse(p, n int) int {
	a, _, _ := ExtendedEuclidean(p, n)
	return Mod(a, n)
}
