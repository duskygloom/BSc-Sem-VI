package modulus

/* Returns a mod b. */
func Mod(a, b int) int {
	if a%b < 0 {
		return b + a%b
	}
	return a % b
}
