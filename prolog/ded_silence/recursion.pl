factorial(0, 1) :- !.
factorial(N, F) :- P is N-1, factorial(P, Q), F is N*Q.

gcd(A, B, R) :- 

